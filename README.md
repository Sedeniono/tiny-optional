# tiny::optional

The goal of this library is to provide the functionality of `std::optional` while not wasting any memory for 
* types with unused bits (`double`, `bool`, ...), or 
* where a specific programmer-defined sentinel value should be used (e.g., an optional `int` where the value `0` or `MAX_INT` should indicate "no value").


## Motivation
`std::optional` always uses a separate `bool` member to store the information if a value is set. A `bool` always has a size of at least 1 byte, and often implies several padding bytes. For example, a `double` has a size of 8 bytes. A `std::optional<double>` typically has a size of 16 bytes because the compiler inserts 7 padding bytes. But for several types, this is unnecessary. For example, a wide range of bit patterns of IEEE-754 floating point values all indicate quite or signaling NaNs, but typically only 1 bit pattern is used in practice. Another example is `bool` (size of at least 1 byte to form addresses to it), where 7 of the 8 bites are unused. This library exploits these unused bit patterns to store the information if a value is set or not in-place within the type itself. I.e., we have `sizeof(tiny::optional<double>) == sizeof(double)`.

Moreover, sometimes one wants to use special "sentinel" or "flag" values to indicate that a certain variable does not contain any information. Think about an integer that stores an index to some array, or the special value `-1` to indicate that it does not refer to anything. Often, it is not immediately clear that a variable can have such a special "empty" state, which makes code harder to understand and might introduce subtle bugs. To provide more semantics, the present library can be used: `tiny::optional<int, -1>` immediately tells the reader that the variable might be empty, and that `-1` must not be within the set of valid values, while it does not waste additional memory (i.e. `sizeof(tiny::optional<int, -1>) == sizeof(int)`).


## Requirements
The library currently supports x64 and x86 architectures on Windows and Linux. Tested on MSVC, clang and gcc. It requires at least C++17 mode. Besides the STL, no external dependencies.


## Usage
Usage: This is a header-only library. Just copy the folder from the include directory containing the single header to your project. Include it via `#include <tiny/optional>`. Instead of writing `std::optional`, use `tiny::optional`.

If you just want to exploit unused bit patterns of standard types, just use e.g. `tiny::optional<double>`, and the library takes care of the rest. I.e. `sizeof(tiny::optional<double>) == sizeof(double)`. If you want to use a special sentinel value, let's say `42` for an integer, the syntax is `tiny::optional<int, 42>`.

If the type is not a built-in type for which the "tiny" state is possible, the size is equal to that of `std::optional`. E.g. `sizeof(tiny::optional<int>) == sizeof(std::optional<int>)`, or `sizeof(tiny::optional<SomeStruct>) == sizeof(std::optional<SomeStruct>)`.

TODO: Document that you can also store the empty flag in a member of the type.


## Notes
This is a work in progress, hence there are some rough edges, but it should already work pretty well.
Currently, the following components of the interface of `std::optional` are not yet supported:
* No converting constructors and assignment operators implemented.
* Constructors and destructors are not trivial, even when they could be.
* Methods and types are not yet `constexpr`.

