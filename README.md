# tiny::optional

![tests of gcc on linux](https://github.com/Sedeniono/tiny-optional/actions/workflows/test_gcc_linux.yml/badge.svg)
![tests of clang on linux](https://github.com/Sedeniono/tiny-optional/actions/workflows/test_clang_linux.yml/badge.svg)
![tests of msvc on windows](https://github.com/Sedeniono/tiny-optional/actions/workflows/test_msvc_win.yml/badge.svg)
![tests of clang on windows](https://github.com/Sedeniono/tiny-optional/actions/workflows/test_clang_win.yml/badge.svg)
![tests of gcc on windows](https://github.com/Sedeniono/tiny-optional/actions/workflows/test_gcc_win.yml/badge.svg)
![tests of clang on macOS](https://github.com/Sedeniono/tiny-optional/actions/workflows/test_clang_mac.yml/badge.svg)



# Introduction
The goal of this library is to provide the functionality of `std::optional` while not unnecessarily wasting any memory for 
* types with unused bits in practice (`double`, `float`, `bool`, pointers), or 
* where a specific programmer-defined sentinel value should be used (e.g., an optional of `int` where the value `0` should indicate "no value").


# Motivation
`std::optional` always uses a separate `bool` member to store the information if a value is set or not. A `bool` always has a size of at least 1 byte, and often implies several padding bytes. For example, a `double` has a size of 8 bytes. A `std::optional<double>` typically has a size of 16 bytes because the compiler inserts 7 padding bytes. But for several types this is unnecessary, just wastes memory and is less cache-friendly. In the case of IEEE-754 floating point values, a wide range of bit patterns indicate quiet or signaling NaNs, but typically only one specific bit pattern for each is used in practice. This library exploits these unused bit patterns to store the information if a value is set or not in-place within the type itself. E.e., we have `sizeof(tiny::optional<double>) == sizeof(double)`.

Moreover, sometimes one wants to use special "sentinel" or "flag" values to indicate that a certain variable does not contain any information. Think about an integer that stores an index into some array and where the special value `-1` should indicate that the index does not refer to anything. Looking at such a variable, it is not immediately clear that it can have such a special "empty" state. This makes code harder to understand and might introduce subtle bugs. The present library can be used to provide more semantics: `tiny::optional<int, -1>` immediately tells the reader that the variable might be empty, and that `-1` must not be within the set of valid values. At the same time, it does not waste additional memory (i.e. `sizeof(tiny::optional<int, -1>) == sizeof(int)`).


# Requirements
The library currently supports x64 and x86 architectures on Windows, Linux and Mac. It is tested on MSVC, clang and gcc. It requires at least C++17. Besides the C++ standard library, there are no external dependencies.


# Usage
This is a header-only library. Just copy the folder from the include directory containing the single header to your project. Include it via `#include <tiny/optional>`.

## Using `tiny::optional` as `std::optional` replacement
Instead of writing `std::optional<T>`, use `tiny::optional<T>` in your code.
If `T` is a `float`, `double`, `bool` or a pointer (in the sense of `std::is_pointer`), the optional will not require additional space. E.g.: `sizeof(tiny::optional<double>) == sizeof(double)`.
Note: The type `long double` requires additional space at the moment, simply because the differing characteristics on the various supported platforms are not yet implemented.

For other types (where the automatic "tiny" state is not possible), the size of `tiny::optional` is equal to that of `std::optional`. E.g. `sizeof(tiny::optional<int>) == sizeof(std::optional<int>)`, or `sizeof(tiny::optional<SomeStruct>) == sizeof(std::optional<SomeStruct>)`. 


## Using sentinel values
`tiny::optional` has a second optional template parameter: `tiny::optional<T, sentinel>`. 
`sentinel` is not a type but rather a non-type template parameter.
Setting this `sentinel` value instructs the library to assume that the value `sentinel` cannot occur as a valid value of `T` and thus allows the library to use it to indicate the empty state. As a result: `sizeof(tiny::optional<T, sentinel> == sizeof(T)`.

The `sentinel` should be of type `T`. Any value is possible that is supported by the compiler as a non-type template parameter. That means integers, and since C++20 also floating point types and literal class types (i.e. POD like types) that are equipped with an `operator==`.

Examples: `tiny::optional<unsigned int, MAX_UINT>`, `tiny::optional<int, -1>`.


# Notes
This is a work in progress, hence there are some rough edges. But it should already work pretty well as indicated by the automatic tests.
Currently, the following components of the interface of `std::optional` are not yet supported:
* No converting constructors and assignment operators implemented.
* Methods and types are not yet `constexpr`.
* Constructors and destructors are not trivial, even if the value type `T` would allow it.
* C++20 monadic operations (`and_then` etc) are not yet implemented.



# TODO
TODO: Describe more precisely how it works + the member pointer stuff.
