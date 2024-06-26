#include "CompilationErrorTests.h"

#include "CompilationBase.h"
#include "TestUtilities.h"
#include "tiny/optional.h"

#include <future>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>


void test_ExpressionsThatShouldNotCompile()
{
  // clang-format off
  std::vector<std::pair<std::string /*toCompile*/, std::string /*expectedErrorRegex*/>> const checks = {

    {/*code*/ "tiny::optional<unsigned, -1> o;",
     /*expected regex*/ "The specified compile-time constant for the empty value is outside of the range supported"}
    
    ,

#ifndef TINY_OPTIONAL_USE_SEPARATE_BOOL_INSTEAD_OF_MEMBER
    {/*code*/ "struct TestClassForInplace { int someValue1 = -1; };\n"
              "tiny::optional<TestClassForInplace, &TestClassForInplace::someValue1> o;",
     /*expected regex*/ "The type of the member variable given by the member-pointer cannot be used as flag if you do not specify a custom SentinelValue"}
    ,
#endif

    {/*code*/ "struct TestClassForInplace { double someValue1 = 0.0; };\n"
              "struct TestClass{};\n"
              "tiny::optional_sentinel_via_type<TestClass, tiny::UseDefaultType, &TestClassForInplace::someValue1> o;",
     /*expected regex*/ "The flag given by the member-pointer is not a member of the payload type"}
    
    ,

    {/*code*/ "struct TestClassForInplace { int someValue1 = -1; };\n"
              "struct TestClass{};\n"
              "tiny::optional_sentinel_via_type<TestClass, std::integral_constant<int, 42>, &TestClassForInplace::someValue1> o;",
     /*expected regex*/ "The flag given by the member-pointer is not a member of the payload type"}
    
    ,

    {/*code*/ "tiny::optional<bool, (char)73> o;",
     /*expected regex*/ "is a bool, but not both. If one is a bool, both should be a bool"}
    
    ,

    {/*code*/ "enum UnscopedEnum{val};\n"
              "tiny::optional<UnscopedEnum, 4> o;",
     // Note: Compiler-dependent error message. First option for MSVC, second for clang, third for gcc.
     /*expected regex*/ "(return.*cannot.*convert)|(cannot.*return.*UnscopedEnum)|(invalid.*conversion.*UnscopedEnum)"}
    
    ,

    // The following check roughly tests that the copy constructor of the optional is not available if the payload
    // does not have one.
    {/*code*/ R"(
        struct WithoutCopy
        {
          WithoutCopy() = default;
          WithoutCopy(WithoutCopy const &) = delete;
          WithoutCopy(WithoutCopy &&) = default;
        };
        tiny::optional<WithoutCopy> orig;
        [[maybe_unused]] tiny::optional<WithoutCopy> copyTarget(orig);
     )",
     /*expected regex*/ "delete"}
    
    ,

    // Should not compile because the std::in_place constructor is explicit.
    {/*code*/ "struct TestClass{ TestClass(int v1, int v2){} };\n"
              "tiny::optional<TestClass> o = {std::in_place, 42, 43};",
     // First regex is for MSVC and clang, second for gcc.
     /*expected regex*/ "(explicit)|(could not convert)"}
    
    ,

    // Since the payload is not implicitly constructible from int, copy-initialization should not be possible.
    {/*code*/ R"(
        struct ExplicitConversion { 
          explicit ExplicitConversion(int v) : value(v) { }
          int value;
        };
        tiny::optional<ExplicitConversion> o = 42;
     )",
     // First for MSVC, second for clang, fourth for gcc.
     /*expected regex*/ "(cannot.*convert)|(no.*viable.*conversion)|(error.*conversion.*from)"}
    
    ,

    // Since the payload is not implicitly constructible from int, copy-list-initialization should not be possible.
    {/*code*/ R"(
        struct ExplicitConversion { 
          explicit ExplicitConversion(int v) : value(v) { }
          int value;
        };
        tiny::optional<ExplicitConversion> o = {42};
     )",
     // First for MSVC, second for clang, third for gcc < 13, fourth for gcc >= 13.
     /*expected regex*/ "(copy-list-initialization.*cannot.*use.*an.*explicit.*constructor)|(constructor.*is.*explicit.*in.*copy-initialization)|(error.*could.*not.*convert)|(error.*would.*use.*explicit.*constructor)"}
    
    ,

    {/*code*/ R"(
        struct ExplicitConversion { 
          explicit ExplicitConversion(int v) : value(v) { }
          int value;
        };
        tiny::optional<ExplicitConversion> o;
        o = 42;
     )",
     // First for MSVC, second for clang, third for gcc.
     /*expected regex*/ "(no.*operator.*found)|(no.*viable.*overloaded)|(no.*match.*for.*operator)"}

    ,

    // Neither references nor raw arrays are allowed by the C++ standard.
    {/*code*/ "tiny::optional<int &> o;",
     /*expected regex*/ "The payload type must meet the C\\+\\+ requirement 'Destructible'"}
    ,
    {/*code*/ "tiny::optional<int []> o;",
     /*expected regex*/ "The payload type must meet the C\\+\\+ requirement 'Destructible'"}

    ,

    // Monadic operations
    {/*code*/ R"(
        tiny::optional<int> o = 42;
        o.and_then([](int) { return 43; });
     )",
     /*expected regex*/ "The standard requires 'f' to return an optional"}
    ,
    {/*code*/ R"(
        tiny::optional<int> o = 42;
        o.transform([](int) { return std::nullopt; });
     )",
     /*expected regex*/ "The standard requires 'f' to not return a std::nullopt_t"}
#ifdef TINY_OPTIONAL_ENABLE_ORELSE
    ,
    {/*code*/ R"(
        tiny::optional<int> o = 42;
        o.or_else([]() -> std::optional<int> { return std::nullopt; });
     )",
     /*expected regex*/ "The function F passed to OPT::or_else\\(F&&\\) needs to return an optional of the same type OPT"}
    ,
    {/*code*/ R"(
        tiny::optional_sentinel_via_type<int, tiny::UseDefaultType> o = 42;
        o.or_else([]() -> tiny::optional<int> { return std::nullopt; });
     )",
     /*expected regex*/ "The function F passed to OPT::or_else\\(F&&\\) needs to return an optional of the same type OPT"}
#endif

    ,

    {/*code*/ R"(
        tiny::optional_aip<char> o;
     )",
     /*expected regex*/ "optional_aip: No automatic sentinel for the PayloadType available"}
    ,
    {/*code*/ R"(
        struct Foo{};
        tiny::optional_aip<Foo> o;
     )",
     /*expected regex*/ "optional_aip: No automatic sentinel for the PayloadType available"}
  };
  // clang-format on


  std::unique_ptr<CompilationChecksBase> checker = CreateCompilationChecker();
  checker->PrintInputOptions(std::cout);

#ifdef TINY_OPTIONAL_WINDOWS_BUILD
  // Although every thread uses its own temporary files, running the checks in parallel on Windows results
  // in flaky tests that fail for all sorts of reasons (such as 'access denied' errors).
  static constexpr bool cRunSerial = true;
#else
  static constexpr bool cRunSerial = false;
#endif

  // Since the compilation of the above code snippets takes a notable time, we run them in parallel if possible.
  std::vector<std::future<std::string>> checkResults;
  for (auto check : checks) {
    auto threadFunc = [&checker, check]() -> std::string {
      auto const & [toCompile, expectedErrorRegex] = check;
      return checker->CheckDoesNotCompile(toCompile, expectedErrorRegex);
    };

    checkResults.push_back(std::async(cRunSerial ? std::launch::deferred : std::launch::async, std::move(threadFunc)));
  }
  ASSERT_TRUE(checkResults.size() == checks.size());

  bool foundFailure = false;
  for (size_t idx = 0; idx < checkResults.size(); ++idx) {
    std::cout << "\tCompilation check " << idx + 1 << "/" << checks.size() << std::endl;
    auto const result = checkResults.at(idx).get();
    if (!result.empty()) {
      if (foundFailure) {
        std::cerr << "========================================\n";
      }
      std::cerr << result;
      foundFailure = true;
      std::cerr << "========================================\n";
    }
  }

  if (foundFailure) {
    exit(43);
  }
}
