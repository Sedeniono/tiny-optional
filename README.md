# tiny::optional  <!-- omit in toc -->

![tests of gcc on linux](https://github.com/Sedeniono/tiny-optional/actions/workflows/test_gcc_linux.yml/badge.svg)
![tests of clang on linux](https://github.com/Sedeniono/tiny-optional/actions/workflows/test_clang_linux.yml/badge.svg)
![tests of msvc on windows](https://github.com/Sedeniono/tiny-optional/actions/workflows/test_msvc_win.yml/badge.svg)
![tests of clang on windows](https://github.com/Sedeniono/tiny-optional/actions/workflows/test_clang_win.yml/badge.svg)
![tests of gcc on windows](https://github.com/Sedeniono/tiny-optional/actions/workflows/test_gcc_win.yml/badge.svg)
![tests of clang on macOS](https://github.com/Sedeniono/tiny-optional/actions/workflows/test_clang_mac.yml/badge.svg)


- [Introduction](#introduction)
- [Motivation](#motivation)
- [Requirements](#requirements)
- [Limitations](#limitations)
- [Usage](#usage)
  - [Installation](#installation)
  - [Using `tiny::optional` as `std::optional` replacement](#using-tinyoptional-as-stdoptional-replacement)
  - [Using a sentinel value](#using-a-sentinel-value)
  - [Storing the empty state in a member variable](#storing-the-empty-state-in-a-member-variable)
  - [The full signature of `tiny::optional`](#the-full-signature-of-tinyoptional)
  - [Non-member definitions](#non-member-definitions)
  - [Specifying a sentinel value via a type](#specifying-a-sentinel-value-via-a-type)
  - [An optional type with automatic sentinels for integers and guarantee of in-place](#an-optional-type-with-automatic-sentinels-for-integers-and-guarantee-of-in-place)
  - [Using custom emptiness logic](#using-custom-emptiness-logic)
- [Performance results](#performance-results)
  - [Runtime](#runtime)
  - [Build time](#build-time)
- [How it works](#how-it-works)
- [Related work](#related-work)


# Introduction
The goal of this library is to provide the functionality of [`std::optional`](https://en.cppreference.com/w/cpp/utility/optional) while not wasting any memory unnecessarily for 
* types with unused bits in practice (`double`, `float`, `bool`, raw pointers), or 
* where a specific programmer-defined sentinel value should be used (e.g., an optional of `int` where the value `0` should indicate "no value").

**Warning:** This library exploits undefined/platform specific behavior on x86/x64 architectures. See below for more details.

For a quick start, see the following example, also available [live on godbolt](https://godbolt.org/z/83xo9hdxT):
```C++
//--------- Automatic exploitation of unused bit patterns ---------
// Assume you have the following optional variable:
std::optional<double> stdOptional;

// The size of it is 16 bytes due to padding; 7 bytes are wasted:
static_assert(sizeof(stdOptional) == 16);

// Replacing std::optional with tiny::optional does not waste space:
tiny::optional<double> tinyOptional;
static_assert(sizeof(tinyOptional) == 8);

// This works automatically for bool, float, double and raw pointers.


//--------- Usage of sentinel values ---------
// But what about other types, such as integers? If you know that not the 
// whole value range is used, you can instruct the library to exploit this.
// For example, assume you have an optional index into e.g. some array:
std::optional<int> stdIndex;
// which has a size of 8 bytes due to padding:
static_assert(sizeof(stdIndex) == 8);

// Assume you know that negative values can never occur. Then you can instruct
// the library to use e.g. -1 as "sentinel" and save half the memory:
tiny::optional<int, -1> tinyIndex;
static_assert(sizeof(tinyIndex) == 4);
// This is more expressive and safe than using a raw variable with a comment:
int poorMansTinyIndex = -1; // -1 value indicates emptiness

// Of course, attempting to store the value -1 in tinyIndex is an error
// and actually triggers an assertion (if not compiled with NDEBUG):
//    tinyIndex = -1; // Uncomment to trigger assert

// Note that without such a user supplied sentinel value, the optional is 
// not "tiny", because in principle the whole value range could be used:
static_assert(sizeof(tiny::optional<int>) == sizeof(std::optional<int>));

// You can also instruct the library to use a member variable of the
// contained type to store the information about the empty state. See below.
```


# Motivation
## Use case 1  <!-- omit in toc -->
`std::optional` always uses a separate `bool` member to store the information if a value is set or not. A `bool` always has a size of at least 1 byte, and often implies several padding bytes afterwards. For example, a `double` has a size of 8 bytes. A `std::optional<double>` typically has a size of 16 bytes because the compiler inserts 7 padding bytes after the internal `bool`. But for several types this is unnecessary, just wastes memory and is less cache-friendly. In the case of IEEE-754 floating point values, a wide range of bit patterns indicate quiet or signaling NaNs, but typically only one specific bit pattern for each is used in practice. This library exploits these unused bit patterns to store the information if a value is set or not in-place within the type itself. For example, we have `sizeof(tiny::optional<double>) == sizeof(double)`.

The results below show that in memory bound applications this can result in a significant performance improvement.
This optimization is similar to what Rust is doing for [booleans](https://stackoverflow.com/a/73181003/3740047) and [references](https://stackoverflow.com/a/16515488/3740047).

## Use case 2  <!-- omit in toc -->
Moreover, sometimes one wants to use special "sentinel" or "flag" values to indicate that a certain variable does not contain any information. Think about a raw integer `int index` that stores an index into some array and where the special value `-1` should indicate that the index does not refer to anything. Looking at such a variable, it is not immediately clear that it can have such a special "empty" state. This makes code harder to understand and might introduce subtle bugs. 

The present library can be used to provide more semantics: `tiny::optional<int, -1>` immediately tells the reader that the variable might be empty, and that the "sentinel" `-1` must not be within the set of valid values. At the same time, it does not waste additional memory (i.e. `sizeof(tiny::optional<int, -1>) == sizeof(int)`), in contrast to `std::optional<int>`.


# Requirements
The library currently supports x64 and x86 architectures on Windows, Linux and Mac. It is tested on MSVC, clang and gcc (see the github actions). Besides the C++ standard library, there are no external dependencies.

The library requires at least C++17. The monadic operations `and_then()` and `transform()` are always defined (although the C++ standard introduced them starting only with C++23). When C++20 is enabled, the three-way comparison operator `operator<=>()` and the monadic operation `or_else()` are additionally implemented.


# Limitations
This library exploits **platform specific behavior** (i.e. undefined behavior). So if your own code also uses platform specific tricks, you might want to check that they are not incompatible. Compare the section below where the tricks employed by this library are explained.

Currently, the following components of the interface of `std::optional` are not yet supported:
* No converting constructors and assignment operators implemented. The major issue here is to decide what to do with conversions such as `tiny::optional<int, -1>` to `tiny::optional<unsigned, 42>`: What if the source contains a `42`? Should an exception be thrown? Should this be asserted in debug? Should this specific conversion be forbidden?
* Constructors and destructors are not trivial, even if the payload type `T` would allow it.
* Methods and types are not `constexpr`. This will probably not be possible in C++17 because some of the tricks rely on `std::memcpy`, which is not `constexpr`. `std::bit_cast` might help here for C++20. Since the whole purpose of the library is to safe memory during runtime, a viable workaround is to simply use `std::optional` in `consteval` contexts.

Moreover, the monadic operation `transform()` always returns a `tiny::optional<T>`, i.e. specification of a sentinel or some other optional as return type (`tiny::optional_sentinel_via_type` etc.) is not possible. As a workaround, you can use `and_then()`.


# Usage

## Installation
This is a header-only library. Just copy the folder from the include directory containing the single header to your project. Include it via `#include <tiny/optional>`.

The library uses the standard [`assert()` macro](https://en.cppreference.com/w/cpp/error/assert) in a few places, which can be disabled as usual by defining `NDEBUG`.


## Using `tiny::optional` as `std::optional` replacement
Instead of writing `std::optional<T>`, use `tiny::optional<T>` in your code.
If `T` is a `float`, `double`, `bool` or a pointer (in the sense of `std::is_pointer`), the optional will not require additional space. E.g.: `sizeof(tiny::optional<double>) == sizeof(double)`.
Note: The type `long double` requires additional space at the moment, simply because the differing characteristics on the various supported platforms are not yet implemented.

For other types (where the automatic "tiny" state is not possible), the size of `tiny::optional` is equal to that of `std::optional`. E.g. `sizeof(tiny::optional<int>) == sizeof(std::optional<int>)`, or `sizeof(tiny::optional<SomeStruct>) == sizeof(std::optional<SomeStruct>)`. 

Besides this, all standard operations such as assignment of `std::nullopt` are supported (with the exceptions listed above).

## Using a sentinel value
`tiny::optional` has a second optional template parameter: `tiny::optional<T, sentinel>`. 
`sentinel` is not a type but rather a non-type template parameter.
Setting this `sentinel` value instructs the library to assume that the value `sentinel` cannot occur as a valid value of `T` and thus allows the library to use it to indicate the empty state. As a result: `sizeof(tiny::optional<T, sentinel>) == sizeof(T)`.

The `sentinel` should be of type `T`. Any value is possible that is supported by the compiler as a non-type template parameter. That means integers, and since C++20 also floating point types and literal class types (i.e. POD like types) that are equipped with an `operator==`.

Examples: `tiny::optional<unsigned int, MAX_UINT>` and `tiny::optional<int, -1>`.

Note: Attempting to store the sentinel value in the optional is illegal. If `NDEBUG` is **not** defined, an appropriate `assert()` gets triggered. For example, if you define `tiny::optional<int, -1> o;`, setting `o = -1;` is not allowed.


## Storing the empty state in a member variable
Imagine you have a simple POD-like data structure such as
```C++
struct Data
{
    int var1;
    double var2;
    MoreData * var3;
    // More stuff...
}; 
```
and you need an optional variable of `Data`. Writing `tiny::optional<Data>` works but the optional requires an additional internal `bool`, so the size of `tiny::optional<Data>` will be the same as `std::optional<Data>`. 
This is unnecessary since some members of `Data` have unused bit patterns, namely `var2` and `var3`.
The library allows to exploit this by specifying an accessible member where the emptiness flag can be stored by writing `tiny::optional<Data, &Data::var2>`. The resulting optional has the same size as `Data`. Using `tiny::optional<Data, &Data::var3>` works as well here. In fact, all the types mentioned above where the library stores the empty flag in-place can be specified.

Additionally, there is the option to use a sentinel value for the empty state and instruct the library to store it in one of the members. The sentinel value is specified as the third template parameter. For example, if you know that `Data::var1` can never be negative, you can instruct the library to use the value `-1` as sentinel: `tiny::optional<Data, &Data::var1, -1>`. Again the resulting `tiny::optional` will not require additional memory compared to a plain `Data`.


## The full signature of `tiny::optional`
Given the explanations above, the full signature of `tiny::optional` is:
```C++
namespace tiny {
    template <
        class PayloadType, 
        auto sentinelOrMemPtr = UseDefaultValue, 
        auto irrelevantOrSentinel = UseDefaultValue>
    class optional;
}
```
The first template parameter specifies the type that should get stored in the optional.
The second and third parameters are optional.
If the second parameter is **not** a member pointer, the value is used as sentinel for the empty state.
If the second parameter is a member pointer, it has to point to a member of `PayloadType` in which case the emptiness flag is stored in that member. Only in this case the third parameter may be optionally specified to indicate a sentinel value to store in that member.


## Non-member definitions
The template function `tiny::make_optional()` can be used to create a `tiny::optional`. [Contrary to `std::make_optional()`](https://en.cppreference.com/w/cpp/utility/optional/make_optional), it can accept two additional optional template parameters corresponding to `sentinelOrMemPtr` and `irrelevantOrSentinel` explained above.
Examples:
```C++
tiny::make_optional(42.0); // Constructs tiny::optional<double>(42.0)
tiny::make_optional<unsigned int, 0>(42u); // Constructs tiny::optional<unsigned int, 0>(42)

struct Foo{
    int v1;
    double v2;
    Foo(int v1, double v2);
};
tiny::make_optional<Foo>(2, 3.0); // tiny::optional<Foo>(2, 3.0), has size of std::optional
tiny::make_optional<Foo, &Foo::v1, -1>(2, 3.0); // tiny::optional<Foo, &Foo::v1, -1>(2, 3.0)
```

All the comparison operators `operator==`, `operator<=`, etc. are provided, [similar to the ones for `std::optional`](https://en.cppreference.com/w/cpp/utility/optional/operator_cmp). However, the C++20 spaceship operator `operator<=>` is not yet implemented.

Additionally, `std::hash` is specialized ([similar to `std::optional`](https://en.cppreference.com/w/cpp/utility/optional/hash)) for the optional types defined by this library.

An appropriate deduction guide is also defined, allowing to write e.g. `tiny::optional{42}` to construct a `tiny::optional<int>{42}`. Note that this does not allow to specify a sentinel.


## Specifying a sentinel value via a type
`tiny::optional` accepts as second or third template parameter a value, i.e. they are non-type template parameters. 
Especially in C++17, this can be restricting since e.g. floating point values cannot be used in templates.
But they can be static member constants.
To this end, the library provides an additional type 
```C++
namespace tiny {
    template <
        class PayloadType, 
        class SentinelValue, 
        auto memPtr = UseDefaultValue>
    class optional_sentinel_via_type;
}
```
where the sentinel value is expected to be given by `SentinelValue::value`.
Note that this second template parameter is not optional. If you do not need a sentinel, just use `tiny::optional<PayloadType>`.
The third parameter is optional and can be a member pointer to instruct the library to store the sentinel value in that member, similar to `tiny::optional`. I.e. the `SentinelValue::value` gets stored in `memPtr`.
Contrary to `tiny::optional`, it has to be the third and not the second parameter.
This is for technical reasons (you cannot mix type and non-type template parameters, and having an optional parameter second and a mandatory third parameter makes no sense).


## An optional type with automatic sentinels for integers and guarantee of in-place
The type `tiny::optional_aip` ("aip" for "always in-place") is similar to `tiny::optional` but with automatic "swallowing" of a value for integers to provide a sentinel, and a compilation error if no sentinel is automatically found. Hence, its size is always the same as the size of the payload.

Its deceleration is basically `tiny::optional_aip<PayloadType, SentinelValue = ...>`. If you omit the `SentinelValue`, then:
* If the `PayloadType` has unused bits, those get exploited. So for example `tiny::optional_aip<double>` behaves the same as `tiny::optional<double>`.
* If the `PayloadType` is an **unsigned integer**, the **maximal** integer value is used as sentinel. For example, `tiny::optional_aip<unsigned>` will use `UINT_MAX` as sentinel. This also means that it is no longer legal to attempt and store the value `UINT_MAX` in that optional!
* Similar, if the `PayloadType` is a **signed integer**, the **minimum** integer value is used as sentinel. E.g. `tiny::optional_aip<int>` uses `INT_MIN`.
* Note that for characters (`char`, `signed char` and `unsigned char`) and enumerations no automatic sentinel is provided.

In all other cases, you have to specify a sentinel yourself, e.g. `tiny::optional_aip<char, 'a'>`. If you do not, then a compilation error occurs. Hence, `tiny::optional_aip` is guaranteed to have the same size as the payload.

Such a type was suggested in [this issue](https://github.com/Sedeniono/tiny-optional/issues/1).


## Using custom emptiness logic

The whole point of the library is to create optional types that do not require more space than the payload.
This relies on using values from the value range of the payload type that are actually unused.
If the built-in logic (for integral types and members) is insufficient, you can use
```C++
namespace tiny {
    template <class PayloadType, class EmptinessManipulator>
    class optional_inplace;
}
```
As before, `PayloadType` is the type to store in the optional.
`EmptinessManipulator` must be a type providing the following members:
```C++
template <class PayloadType>
struct EmptinessManipulator
{
    static bool IsEmpty(PayloadType const & payload) noexcept
    {
        // Needs to return true if the optional should be considered empty.
        // I.e. if the given "payload" state indicates emptiness.
        // It can be called after InitializeIsEmptyFlag() or PrepareIsEmptyFlagForPayload().
    }

    static void InitializeIsEmptyFlag(PayloadType & uninitializedPayloadMemory) noexcept
    {
        // uninitializedPayloadMemory is a reference to an **uninitialized** payload (i.e. 
        // the constructor of PayloadType has not been called, but the memory has been
        // already allocated).
        // This function is called when the optional is constructed in an empty state or
        // once it should become empty. The function must initialize the memory such that 
        // the optional is considered empty, i.e. IsEmpty(uninitializedPayloadMemory) must
        // return true afterwards.
    }

    static void PrepareIsEmptyFlagForPayload(PayloadType & emptyPayload) noexcept
    {
        // This function is called just before a (non-empty) value is stored in the
        // optional. The given "emptyPayload" is currently indicating the empty state,
        // i.e. IsEmpty(emptyPayload) returns true.
        // The function must deconstruct the sentinel value in "emptyPayload" which was 
        // previously constructed by InitializeIsEmptyFlag(). After this function returns,
        // the library constructs the payload. After that, IsEmpty() must return false.
        // Note: The memory pointed to by "emptyPayload" must not be freed. It is handled
        // by the library.
    }
};
```
The functions must be `noexcept`. This is necessary to satisfy the same exception guarantees as `std::optional` and also because otherwise the optional could be left in a weird in-between state if they could throw exceptions.

Example: Assume you have an iterator class that knows if the iterator is still valid:
```C++
class Iterator
{
public:
    Iterator() noexcept
        : mIsValid(false), mIndex(0)
    { }

    Iterator(std::size_t index) noexcept
        : mIsValid(true), mIndex(index) 
    { }

    bool IsValid() const noexcept {
        return mIsValid;
    }

    // More members, e.g. operator++().

private:
    bool mIsValid;
    std::size_t mIndex;
    // Maybe more members that 
};
```
Now, assume you have some function that must return either a valid iterator or none at all.
You could define that an invalid iterator indicates "no iterator", but this might not be obvious to readers.
You could also return a `std::optional<Iterator>` or `tiny::optional<Iterator>` and guarantee that the iterator is always valid if the optional is not empty. But this will waste some space.
In principle, you would like to write `tiny::optional<Iterator, &Iterator::mIsValid, false>` (which would cause the library to store the emptiness by means of a `mIsValid=false` value).
But the members are private, so this does not work.
Instead you can use `tiny::optional_inplace<Iterator, EmptinessManipulator>` with a custom manipulator definition:
```C++
struct EmptinessManipulator
{
    static bool IsEmpty(Iterator const & iter) noexcept
    {
        return !iter.IsValid();
    }

    static void InitializeIsEmptyFlag(Iterator & uninitializedIteratorMemory) noexcept
    {
        // Placement new because memory is already allocated.
        // Default constructor of Iterator will set mIsValid=false.
        ::new (&uninitializedIteratorMemory) Iterator();
    }

    static void PrepareIsEmptyFlagForPayload(Iterator & emptyIterator) noexcept
    {
        // Deconstruct the iterator constructed in InitializeIsEmptyFlag().
        // The memory itself will be handled by the library.
        // After this function returns, the library will construct the new valid iterator.
        // That the new iterator will always have IsValid()==true was one of the basic
        // assumptions in this example.
        emptyIterator.~Iterator();
    }
};
```
Usage example:
```C++
int main()
{
    tiny::optional_inplace<Iterator, EmptinessManipulator> o;
    static_assert(sizeof(o) == sizeof(Iterator));
    assert(o.empty());
    
    // Construct some valid iterator and store it.
    Iterator iter{5};
    o = iter;

    // Note: Attempting to store an invalid iterator is illegal and causes a debug assert:
    //o = Iterator{};
}
```


# Performance results

## Runtime
First note that one goal of the library has no runtime performance impact: Namely it provides a more semantically expressive way to have variables where a special value indicates the empty state, i.e. instead of
```C++
int oneBasedIndex; // 0 means "does not reference anything"
```
one can write 
```C++
tiny::optional<int, 0> oneBasedIndex;
```

The second goal of the library is get rid of the additional `bool` required to store the empty state where possible. This reduces the size and thus should improve runtime performance in applications where memory bandwidth is the limiting factor.
But as always, you have to profile it in your specific application if `tiny::optional` results in a performance improvement.
As a somewhat contrived example that highlights a rather extreme case, consider the type
```C++
struct WeirdVector
{
    tiny::optional<double> x, y, z;
    tiny::optional<double> length2;
};
```
which has a size of 32 bytes. Using `std::optional<double>` instead, it is twice as large, i.e. has a size of 64 bytes.
The following piece of test code is rather memory bound:
```C++
template <class T>
constexpr T Sqr(T v) { return v*v; }

double PerformTest(std::vector<WeirdVector> & values) 
{
    for (WeirdVector & vec : values) {
        if (vec.x || vec.y || vec.z) {
            vec.length2.emplace(Sqr(vec.x.value_or(0)) + Sqr(vec.y.value_or(0)) + Sqr(vec.z.value_or(0)));
        }
    }

    double totalLength = 0;
    for (WeirdVector & vec : values) {
        totalLength += vec.length2.value_or(0);
    }
    return totalLength;
}
```
Running this code with `tiny::optional` and with `std::optional` on an Intel Core i7-4770K results in the following:
![Performance results](performance/results_relative.png)
clang 13 and gcc 11 were compiled with `-O3 -DNDEBUG -mavx` on WSL, MSVC 19.29 used `/O2 /arch:AVX /GS- /sdl-`.
The vertical axis shows the ratio of the execution time for `std::optional` divided by the execution time of the version with `tiny::optional`. 
A value of 1 thus means that they are equally fast, a value >1 means that `tiny::optional` is faster. The horizontal axis depicts the number of values in the input container `values`.
The three vertical lines show when the values using `tiny::optional` completely fill the L1 (64kiB per core), L2 (256kiB per core) and L3 cache (8.0MiB) of the Intel i7-4770K.

If the data of both the std and the tiny version fit completely into the L1 cache, there is not much performance difference. That `tiny::optional` is slightly faster for MSVC is apparently because MSVC is [better at optimizing `tiny::optional` than `std::optional`](https://stackoverflow.com/q/72755405/3740047).
Once the the std data no longer fits in the L1 cache, the tiny case is always faster compared to the std case by roughly a factor of 1.5x. The std case needs to load more data from the slower caches.
The peak improvement is reached once most of the tiny data still fits into the L3 cache but the std data does not (meaning that a significant part of the std data needs to be retrieved from RAM), in which case the tiny version is up to roughly 3x faster.
Once most of the data in both cases no longer fit, the improvement converges to a factor of roughly 2x.
The reason is that most data needs to be streamed from the RAM and the amount of data in the tiny case is half of that of the std case.


## Build time
To benchmark the time it takes to compile code using `tiny::optional` rather than `std::optional`, the following bit of generated C++ code is used:
```C++
struct S0
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o; // or std::optional
};

int main()
{
    S0 s0;
    s0.test();
}
```
However, not only a single class `S0` but additional ones `S1`, `S2`, etc. get generated and used to achieve meaningful build times.
The same code but with `tiny::optional` replaced with `std::optional` is also measured.
The ratio of the times (build time of `tiny::optional` divided by the build time of `std::optional`) is shown in the following figure:
![Build times](buildtimes//unique_types/result.png)
clang 13 and gcc 11 are used on WSL, and `cl.exe` means MSVC 19.29.
clang without the `-stdlib=libc++` flag uses gcc's stdlibc++.

Obviously, `tiny::optional` takes roughly ~1.5x-2x longer to compile than `std::optional`.
The more generic interface of `tiny::optional` requires additional template meta-programming, which apparently takes its toll.
But note that this is a rather extreme example since here the optional dominates the build time completely.
In larger real world projects (where build times actually matter) one would expect that the overwhelming majority of all variables are not optionals, meaning that the usage of `tiny::optional` should not have a noticeable impact.
Indeed, replacing all occurrences of `std::optional` in a commercial application with several million lines of code did not result in a measurable slowdown of the build.


# How it works

The library exploits **platform specific behavior** (that is not guaranteed by the C++ standard) to construct optionals that have the same size as the payload. Specifically:

* Booleans: A `bool` has a size of at least 1 byte (so that addresses to it can be formed). But only 1 bit is necessary to store the information if the value is `true` or `false`. The remaining 7 or more bits are unused. More precisely, the numerical value of `true` is `1` and for `false` it is `0` on the supported platforms. Any other numerical value results in undefined behavior. `tiny::optional<bool>` will store the numerical value `0xfe` in the `bool` to indicate an empty state.

* Floating point types (`float` and `double`): There are two types of "not a numbers" (NaNs) defined by the IEEE754 standard: Quiet and signaling NaNs. However, there is a wide range of bit patterns that represent a quite or a signaling NaN. For example, for `float` **any** bit pattern in `[0x7f800001, 0x7fbfffff]` and `[0xff800001, 0xffbfffff]` represents a signaling NaN, and **any** bit pattern in `[0x7fc00000, 0x7fffffff]` and `[0xffc00000, 0xffffffff]` represents a quiet NaN. However, on the supported platforms only one specific quiet NaN and one specific signaling NaN bit pattern is used by the supported compilers and standard libraries (e.g. for linux clang x64: `0x7fc00000` for quiet and `0x7fa00000` for signaling NaNs). 
Also see e.g. the paper ["Floating point exception tracking and NAN propagation" by Agner Fog](https://www.agner.org/optimize/nan_propagation.pdf). This holds of course only as long as a program does not do any tricks by itself. This library exploits this assumption and uses the quiet NaN `0x7fedcba9` as sentinel value for `float` and `0x7ff8fedcba987654` for `double`.
Note: `long double` is not (yet) supported and a `tiny::optional<long double>` instead uses a separate `bool`.

* Pointers: For pointers the library uses the sentinel values `0xffff'ffff - 8` (32 bit) and `0xffff'8000'0000'0000 - 1` (64 bit) to indicate an empty state. In short, these values avoid [pseudo-handles on Windows](https://devblogs.microsoft.com/oldnewthing/20210105-00/?p=104667), and for 64 bit lies in the gap of [non-canonical addresses](https://read.seas.harvard.edu/cs161/2018/doc/memory-layout/). See the explanation in the source code at `SentinelForExploitingUnusedBits<T*>` for more details. Thanks to the reddit users "compiling" and "ra-zor" for [pointing this out](https://www.reddit.com/r/cpp/comments/ybc4lf/comment/itjvkmc/?utm_source=share&utm_medium=web2x&context=3).\
Note 1: Only pointers in the sense of `std::is_pointer` are supported that way; member or member function pointers require an additional `bool` since they are not "ordinary" pointers).\
Note 2: Having a `tiny::optional<T*>` is probably not that often useful. But if you have a POD like type with a pointer in it as member, you can instruct `tiny::optional` to use that member as storage for the sentinel value (see above) and save the memory of the additional `bool`. To this end, the library implements the trick for pointers.



Additional ideas (not yet implemented!):

* Polymorphic types (`std::is_polymorphic`) have a vtable pointer at the beginning. As for ordinary pointers, it could be set to `0xffffffffffffffff`. This would allow to store **any** polymorphic type within the optional without requiring additional space. But having optionals of polymorphic types is probably rare. Also need to research how the layout is in case of multiple inheritance.
* Padding bytes in types could be exploited to store the emptiness. The closest in the standard we have is probably `std::has_unique_object_representations`. If this is `true`, there are either floating point types or padding bytes involved. But this type trait only works with trivially copyable types. But maybe one could use `boost::pfr` to get a `std::tuple` of the members, and by subtracting the addresses and comparing this difference with the actual size of the types one could identify the padding.
* For POD-like types, `boost::pfr` could be used to get a `std::tuple` to the members. Then, at compile time, we could iterate over the members and check for any type with unused bit patterns. This would make the explicit specification of a member pointer by the user unnecessary. However, it would introduce a dependency on `boost`.
* References: Similar to pointers. But references in optionals are currently forbidden by the C++ standard.
* Enums: If there were a way to automatically get the min. or max. value in an enumeration, we could find an unused value as sentinel automatically.
* Nested `tiny::optional<tiny::optional<T>>` could be optimized. But something like this is probably rare?
* Strings: Idea from [reddit](https://www.reddit.com/r/cpp/comments/ybc4lf/comment/itftn0y/?utm_source=share&utm_medium=web2x&context=3): Use `"\0\0"` for std strings, or maybe better `"\0\r\a..."`. The size of the sentinel string should not be larger than the internal storage used for the short string optimization (SSO).


# Related work
The [discussion on reddit](https://www.reddit.com/r/cpp/comments/ybc4lf/tinyoptional_a_c_optional_that_does_not_waste/?utm_source=share&utm_medium=web2x&context=3) has shown that some other libraries with similar intent exist:
* [`compact_optional`](https://github.com/akrzemi1/compact_optional) and his successors [`markable`](https://github.com/akrzemi1/markable). A major difference to `tiny::optional` is that `tiny::optional` attempts to be a drop-in replacement for `std::optional` while providing automatic optimization for floats etc. The sentinel functionality is opt-in (by specifying a second template argument). On the other hand, `markable` is not designed to be a direct replacement of `std::optional`. To get an optional of some generic type (where an additional internal boolean must be used to represent the empty state), `markable` needs to be told about this (so in a sense, it is opt-out): `markable<mark_optional<boost::optional<int>>>`. On the other hand, `tiny::optional<int>` does this automatically.
* The [talk by Arthur O'Dwyer “The Best Type Traits that C++ Doesn't Have”](https://youtu.be/MWBfmmg8-Yo) from C++Now 2018 ([github repository](https://github.com/Quuxplusone/from-scratch)) introduces `tombstone_traits`, which exposes unused bit patterns. It is exploited by his [own implementation of optional](https://github.com/Quuxplusone/from-scratch/tree/master/include/scratch/bits/optional).
* [LibCat](https://github.com/Cons-Cat/libCat/blob/main/src/libraries/optional/cat/optional): A C++20 library that includes a similar optional where you can specify a lambda as non-type template parameter that handles the sentinel. It seems to be conceptionally similar to `tiny::optional_inplace` described above.
* [foonathan/tiny](https://github.com/foonathan/tiny): Seems to be abandoned and to not implement a fully fledged `std::optional` replacement.


Also, Rust's `Option` implements some magic for [references](https://stackoverflow.com/q/16504643/3740047) and [bools](https://stackoverflow.com/q/73180983/3740047).
