#pragma once

#include <cassert>
#include <cmath>
#include <filesystem>
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <type_traits>
#include <vector>


//=================================================================
// Detection macros
//=================================================================

#if defined(_WIN64) || defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__) || defined(__CYGWIN__)
  #define TINY_OPTIONAL_WINDOWS_BUILD
#endif

#if defined(__clang__)
  #define TINY_OPTIONAL_CLANG_BUILD
#elif defined(__GNUC__) || defined(__GNUG__)
  #define TINY_OPTIONAL_GCC_BUILD
#elif defined(_MSC_VER)
  #define TINY_OPTIONAL_MSVC_BUILD
#else
  #error Unknown compiler
#endif

// https://stackoverflow.com/a/66249936
#if defined(__x86_64__) || defined(_M_X64) || defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
  #define TINY_OPTIONAL_X86_OR_X64
#endif


// <=C++20: The libstdc++ in version 11 contains a bug that prevents e.g. std::optional<const volatile int>
// See https://github.com/gcc-mirror/gcc/commit/fc6f1128ae603164aea6303ce2b3ed0b57e6a378
//
// >= C++23: The "voidify" and thus the support for volatile and const payloads got removed from the standard.
// See LWG 3870 (https://www.open-std.org/jtc1/sc22/wg21/docs/lwg-defects.html#3870).
// gcc's stdlibc++ in version >=15 also removed it for any C++ version before C++23.
// Corresponding gcc commit: https://github.com/gcc-mirror/gcc/commit/2eaae1bd69302efe6d73d8d63739b081299f8641
#if (!defined(_GLIBCXX_RELEASE) || (_GLIBCXX_RELEASE != 11 && _GLIBCXX_RELEASE < 15)) && !defined(TINY_OPTIONAL_CPP23)
  #define TINY_OPTIONAL_ENABLE_CONST_VOLATILE_TEST
#endif


//=================================================================
// Test assertions
//=================================================================

#ifdef TINY_OPTIONAL_MSVC_BUILD
  #define TINY_OPTIONAL_CURRENT_FUNC __FUNCSIG__
#else
  #define TINY_OPTIONAL_CURRENT_FUNC __PRETTY_FUNCTION__
#endif

#define ASSERT_BOOL_IMPL(x, exprStr, expected, actual)                                                                 \
  do {                                                                                                                 \
    if ((x)) {                                                                                                         \
      std::cerr << "\tExpression '" << exprStr << "' expected to be " << expected << ", but it is " << actual          \
                << ".\n\t\tIn line " << __LINE__ << ", function " << TINY_OPTIONAL_CURRENT_FUNC << ", file '"          \
                << __FILE__ << "'\n";                                                                                  \
      assert(!(x));                                                                                                    \
      exit(42);                                                                                                        \
    }                                                                                                                  \
  }                                                                                                                    \
  while (false)

#define ASSERT_FALSE(x) ASSERT_BOOL_IMPL(x, #x, "false", "true")
#define ASSERT_TRUE(x) ASSERT_BOOL_IMPL(!(x), #x, "true", "false")

#define FAIL()                                                                                                         \
  do {                                                                                                                 \
    std::cerr << "\tFAIL() in line " << __LINE__ << ", function " << TINY_OPTIONAL_CURRENT_FUNC << ", file '"          \
              << __FILE__ << "'\n";                                                                                    \
    assert(false);                                                                                                     \
    exit(42);                                                                                                          \
  }                                                                                                                    \
  while (false)


#define EXPECT_EXCEPTION(expression, expectedException)                                                                \
  do {                                                                                                                 \
    try {                                                                                                              \
      expression;                                                                                                      \
      /* We should not execute this FAIL() because an exception should be thrown.*/                                    \
      std::cerr << "\tExpected that expression '" << #expression << "' throws, but it did not." << std::endl;          \
      FAIL();                                                                                                          \
    }                                                                                                                  \
    catch (expectedException const &) {                                                                                \
    }                                                                                                                  \
    catch (std::exception const & ex) {                                                                                \
      std::cerr << "\tUnexpected exception of type '" << typeid(ex).name() << "' caught. Message: " << ex.what()       \
                << std::endl;                                                                                          \
      FAIL();                                                                                                          \
    }                                                                                                                  \
    catch (...) {                                                                                                      \
      std::cerr << "\tUnexpected unknown exception caught." << std::endl;                                              \
      FAIL();                                                                                                          \
    }                                                                                                                  \
  }                                                                                                                    \
  while (false)


//=================================================================
// Other helpers
//=================================================================


// Returns true if lhs and rhs match, or if both are (any type of) NaN.
template <class Float1T, class Float2T>
bool MatchingFloat(Float1T lhs, Float2T rhs)
{
  static_assert(std::is_floating_point_v<Float1T>);
  static_assert(std::is_floating_point_v<Float2T>);
  if (std::isnan(lhs)) {
    return std::isnan(rhs);
  }
  else {
    return lhs == rhs;
  }
}


template <class Val1T, class Val2T>
bool AreEqual(Val1T && lhs, Val2T && rhs)
{
  if constexpr (std::is_floating_point_v<std::decay_t<Val1T>>) {
    return MatchingFloat(std::forward<Val1T>(lhs), std::forward<Val2T>(rhs));
  }
  else {
    return std::forward<Val1T>(lhs) == std::forward<Val2T>(rhs);
  }
}


// Used to check that a container where data was moved from is now empty.
// For not-supported containers, simply returns true. Especially, if T is e.g. an integer,
// there is no difference between copying the value and moving the value.
template <class T>
bool EmptyOrNoContainer(T const &)
{
  return true;
}
template <class T>
bool EmptyOrNoContainer(std::vector<T> const & c)
{
  return c.empty();
}


// Checks weather T is not hashable.
// clang-format off
template <class T>
constexpr bool IsDisabledHash 
   = !std::is_default_constructible_v<std::hash<T>>
  && !std::is_copy_constructible_v<std::hash<T>> 
  && !std::is_move_constructible_v<std::hash<T>> 
  && !std::is_copy_assignable_v<std::hash<T>> 
  && !std::is_move_assignable_v<std::hash<T>>;
// clang-format on


// From boost
template <class T>
inline void hash_combine(std::size_t & seed, T const & v)
{
  seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}


inline std::ostream & operator<<(std::ostream & out, std::nullopt_t)
{
  return out << "nullopt";
}


inline std::string CompleteCppCodeSnippet(std::string const & codeSnippet)
{
  std::string cpp = "#include \"tiny/optional.h\"\n";
  cpp += "int main() {\n";
  cpp += codeSnippet;
  cpp += "\n}\n";
  return cpp;
}


struct ExecutionResult
{
  std::string command;
  int exitCode = -1;
  std::string output;
};


// Runs the specified program and waits until it terminates.
// The returned string contains both stdout and stderr of the run program.
ExecutionResult ExecuteProgramSync(std::string const & commandline);


#ifdef TINY_OPTIONAL_WINDOWS_BUILD

// Creates a folder in the 'Temp' directory and a cpp file in it containing the given code.
// The destructor deletes everything again (folder + all the files in it).
class WindowsTemporaryCodeFileScope
{
public:
  explicit WindowsTemporaryCodeFileScope(std::string const & code);
  ~WindowsTemporaryCodeFileScope();

  // Returns the full path (absolute path including the filename).
  std::filesystem::path GetFullFilename() const
  {
    return mCodeFile;
  }

  // Returns just the filename with the extension.
  std::filesystem::path GetFilename() const
  {
    return mCodeFile.filename();
  }

  // Returns the directory that contains the file. This is a temporary directory that get removed
  // when the scope is destructed.
  std::filesystem::path GetDirectory() const
  {
    return mCodeFile.parent_path();
  }


private:
  std::filesystem::path const mCodeFile;
};
#endif


#ifdef TINY_OPTIONAL_X86_OR_X64
// Returns true if the given address is NOT a canonical address, i.e. returns true if the address can never be a valid
// address. See `SentinelForExploitingUnusedBits<T *>` for more information.
bool IsAddressNonCanonical(std::uint64_t addr);
#endif
