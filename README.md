# tiny::optional

![tests of gcc on linux](https://github.com/Sedeniono/tiny-optional/actions/workflows/test_gcc_linux.yml/badge.svg)
![tests of clang on linux](https://github.com/Sedeniono/tiny-optional/actions/workflows/test_clang_linux.yml/badge.svg)
![tests of msvc on windows](https://github.com/Sedeniono/tiny-optional/actions/workflows/test_msvc_win.yml/badge.svg)
![tests of clang on windows](https://github.com/Sedeniono/tiny-optional/actions/workflows/test_clang_win.yml/badge.svg)
![tests of gcc on windows](https://github.com/Sedeniono/tiny-optional/actions/workflows/test_gcc_win.yml/badge.svg)
![tests of clang on macOS](https://github.com/Sedeniono/tiny-optional/actions/workflows/test_clang_mac.yml/badge.svg)



# Introduction
The goal of this library is to provide the functionality of [`std::optional`](https://en.cppreference.com/w/cpp/utility/optional) while not unnecessarily wasting any memory for 
* types with unused bits in practice (`double`, `float`, `bool`, pointers), or 
* where a specific programmer-defined sentinel value should be used (e.g., an optional of `int` where the value `0` should indicate "no value").


# Motivation
`std::optional` always uses a separate `bool` member to store the information if a value is set or not. A `bool` always has a size of at least 1 byte, and often implies several padding bytes. For example, a `double` has a size of 8 bytes. A `std::optional<double>` typically has a size of 16 bytes because the compiler inserts 7 padding bytes. But for several types this is unnecessary, just wastes memory and is less cache-friendly. In the case of IEEE-754 floating point values, a wide range of bit patterns indicate quiet or signaling NaNs, but typically only one specific bit pattern for each is used in practice. This library exploits these unused bit patterns to store the information if a value is set or not in-place within the type itself. E.g., we have `sizeof(tiny::optional<double>) == sizeof(double)`.

Moreover, sometimes one wants to use special "sentinel" or "flag" values to indicate that a certain variable does not contain any information. Think about an integer that stores an index into some array and where the special value `-1` should indicate that the index does not refer to anything. Looking at such a variable, it is not immediately clear that it can have such a special "empty" state. This makes code harder to understand and might introduce subtle bugs. The present library can be used to provide more semantics: `tiny::optional<int, -1>` immediately tells the reader that the variable might be empty, and that `-1` must not be within the set of valid values. At the same time, it does not waste additional memory (i.e. `sizeof(tiny::optional<int, -1>) == sizeof(int)`).


# Requirements
The library currently supports x64 and x86 architectures on Windows, Linux and Mac. It is tested on MSVC, clang and gcc (see the github actions). It requires at least C++17. Besides the C++ standard library, there are no external dependencies.


# Limitations
Currently, the following components of the interface of `std::optional` are not yet supported:
* No converting constructors and assignment operators implemented (e.g. `tiny::optional<unsigned>` to `tiny::optional<int>`).
* Methods and types are not `constexpr`.
* Constructors and destructors are not trivial, even if the payload type `T` would allow it.
* C++20 monadic operations (`and_then` etc.) are not yet implemented.

Moreover, this library exploits **platform specific behavior**. So if your own code also uses platform specific tricks, you might want to check that they are not incompatible. Compare the section below where the tricks employed by this library are explained.


# Usage

## Installation
This is a header-only library. Just copy the folder from the include directory containing the single header to your project. Include it via `#include <tiny/optional>`.

## Using `tiny::optional` as `std::optional` replacement
Instead of writing `std::optional<T>`, use `tiny::optional<T>` in your code.
If `T` is a `float`, `double`, `bool` or a pointer (in the sense of `std::is_pointer`), the optional will not require additional space. E.g.: `sizeof(tiny::optional<double>) == sizeof(double)`.
Note: The type `long double` requires additional space at the moment, simply because the differing characteristics on the various supported platforms are not yet implemented.

For other types (where the automatic "tiny" state is not possible), the size of `tiny::optional` is equal to that of `std::optional`. E.g. `sizeof(tiny::optional<int>) == sizeof(std::optional<int>)`, or `sizeof(tiny::optional<SomeStruct>) == sizeof(std::optional<SomeStruct>)`. 

Besides this, all standard operations such as assignment of `std::nullopt` are supported (with the exceptions listed above).

## Using a sentinel value
`tiny::optional` has a second optional template parameter: `tiny::optional<T, sentinel>`. 
`sentinel` is not a type but rather a non-type template parameter.
Setting this `sentinel` value instructs the library to assume that the value `sentinel` cannot occur as a valid value of `T` and thus allows the library to use it to indicate the empty state. As a result: `sizeof(tiny::optional<T, sentinel> == sizeof(T)`.

The `sentinel` should be of type `T`. Any value is possible that is supported by the compiler as a non-type template parameter. That means integers, and since C++20 also floating point types and literal class types (i.e. POD like types) that are equipped with an `operator==`.

Examples: `tiny::optional<unsigned int, MAX_UINT>`, `tiny::optional<int, -1>`.

Note: Attempting to store the sentinel value in the optional is illegal. If `NDEBUG` is not defined, an appropriate `assert()` gets triggered. For example, if you define `tiny::optional<int, -1> o;`, setting `o = -1;` is not allowed.


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
The library allows to exploit this by specifying a public member where the emptiness flag can be stored by writing `tiny::optional<Data, &Data::var2>`. The resulting optional has the same size as `Data`. Using `tiny::optional<Data, &Data::var3>` works as well here. In fact, all the types mentioned above where the library stores the empty flag in place can be specified.

Additionally, there is the option to use a sentinel value for the empty state and instruct the library to store it in one of the members. The sentinel value is specified as the third template parameter. For example, if you know that `Data::var1` can never be negative, you can instruct the library to use the value `-1` as sentinel: `tiny::optional<Data, &Data::var1, -1>`. Again the resulting `tiny::optional` will not require additional memory compared to a plain `Data`.


## The full signature of `tiny::optional`
Given the explanations above, the full signature of `tiny::optional` is:
```C++
namespace tiny {
    template <
        class PayloadType, 
        auto emptyValueOrMemPtr = UseDefaultValue, 
        auto irrelevantOrEmptyValue = UseDefaultValue>
    class optional;
}
```
The first template parameter specifies the type that should get stored in the optional.
The second and third parameters are optional.
If the second parameter is **not** a member pointer, the value is used as sentinel for the empty state.
If the second parameter is a member pointer, it has to point to a member of `PayloadType` in which case the emptiness flag is stored in that member. Only in this case the third parameter may be optionally specified to indicate a sentinel value to store in that member.


## Non-member definitions
The template function `tiny::make_optional()` can be used to create a `tiny::optional`. [Contrary to `std::make_optional()`](https://en.cppreference.com/w/cpp/utility/optional/make_optional), it can accept two additional optional template parameters corresponding to `emptyValueOrMemPtr` and `irrelevantOrEmptyValue` explained above.
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

An appropriate deduction guide is also defined, allowing to write e.g. `tiny::optional{42}` to construct a `tiny::optional<int>{42}`.


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
    class optional_empty_via_type;
}
```
where the sentinel value is expected to be given by `SentinelValue::value`.
Note that this second template parameter is not optional. If you do not need a sentinel, just use `tiny::optional<PayloadType>`.
The third parameter is optional and can be a member pointer to instruct the library to store the sentinel value in that member, similar to `tiny::optional`. I.e. the `SentinelValue::value` gets stored in `memPtr`.
Contrary to `tiny::optional`, it has to be the third and not the second parameter.
This is for technical reasons (you cannot mix type and non-type template parameters, and having an optional second but a mandatory third parameter makes no sense).


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


# How does it work

The library exploits **platform specific behavior** (that is not guaranteed by the C++ standard) to construct optionals that have the same size as the payload. Specifically:

* Booleans: A `bool` has a size of at least 1 byte (so that addresses to it can be formed). But only 1 bit is necessary to store the information if the value is `true` or `false`. The remaining 7 or more bits are unused. More precisely, the numerical value of `true` is `1` and for `false` it is `0` on the supported platforms. Any other numerical value results in undefined behavior. `tiny::optional<bool>` will store the numerical value `0xfe` in the `bool` to indicate an empty state.

* Floating point types (`float` and `double`): There are two types of "not a numbers" (NaNs) defined by the IEEE754 standard: Quiet and signaling NaNs. However, there is a wide range of bit patterns that represent a quite or a signaling NaN. For example, for `float` **any** bit pattern in `[0x7f800001, 0x7fbfffff]` and `[0xff800001, 0xffbfffff]` represents a signaling NaN, and **any** bit pattern in `[0x7fc00000, 0x7fffffff]` and `[0xffc00000, 0xffffffff]` represents a quiet NaN. However, on the supported platforms only one specific quiet NaN and one specific signaling NaN bit pattern is used by the supported compilers and standard libraries (e.g. for linux clang x64: `0x7fc00000` for quiet and `0x7fa00000` for signaling NaNs). This holds of course only as long as a program does not do any tricks by itself. This library exploits this assumption and uses the quiet NaN `0x7fedcba9` as sentinel value for `float` and `0x7ff8fedcba987654` for `double`.
Note: `long double` is not (yet) supported and a `tiny::optional<long double>` instead uses a separate `bool`.

* Pointers: For pointers the library uses the sentinel values `0xffffffff` (32 bit) and `0xffffffffffffffff` (64 bit) to indicate an empty state. This exploits that there is never any memory allocated at these virtual addresses on the supported platforms where a pointer could point to it.
Note 1: Only pointers in the sense of `std::is_pointer` are supported that way; member or member function pointers require an additional `bool` since they are not "ordinary" pointers).
Note 2: Having a `tiny::optional<T*>` is probably rarely useful. But if you have a POD like type with a pointer in it as member, you can instruct `tiny::optional` to use that member as storage for the sentinel value (see above) and save the memory of the additional `bool`. To this end, the library implements the trick for pointers.



Additional ideas (not yet implemented!):

* Polymorphic types (`std::is_polymorphic`) have a vtable pointer at the beginning. As for ordinary pointers, it could be set to `0xffffffffffffffff`. This would allow to store **any** polymorphic type within the optional without requiring additional space. But having optionals of polymorphic types is probably rare. Also need to research how the layout is in case of multiple inheritance.
* In theory, padding bytes in types could be exploited to store the emptiness. However, I am not aware of any easy automatic way to find these padding bytes (even with compiler specific tricks). The closest we have is probably `std::has_unique_object_representations`. If this is `true`, there are either floating point types or padding bytes involved. But this type trait only works with trivially copyable types.
* For POD-like types, `boost::pfr` could be used to get a `std::tuple` to the members. Then, at compile time, we could iterate over the members and check for any type with unused bit patterns. This would make the explicit specification of a member pointer by the user unnecessary. However, it would introduce a dependency on `boost`.
* References: Similar to pointers. But references in optionals are currently forbidden by the C++ standard.
* Enums: If there were a way to automatically get the min. or max. value in an enumeration, we could find an unused value as sentinel automatically.
* Nested `tiny::optional<tiny::optional<T>>` could be optimized. But something like this is probably rare?
