#include "ComparisonTests.h"

#include "TestTypes.h"
#include "TestUtilities.h"
#include "tiny/optional.h"


namespace
{

#ifdef __cpp_lib_three_way_comparison
// Basically the same as std::compare_three_way, but without the annoying std::three_way_comparable_with constraint,
// which forbids e.g. `std::compare_three_way(std::optional<int>{}, tiny::optional<int>{})`, although the
// expression `std::optional<int>{} <=> tiny::optional<int>{}` is valid and compiles.
// See https://stackoverflow.com/a/66938093/3740047 for more details.
struct my_compare_three_way
{
  template <class T, class U>
  constexpr auto operator()(T const & lhs, U const & rhs) const
  {
    return lhs <=> rhs;
  }
};
#endif


template <class Opt1, class Opt2, class Val1, class Val2, class Comparer>
void TestCompareOptWithOpt(Val1 val1, Val2 val2, Comparer comparer)
{
  std::cout << "\tComparison '" << typeid(Comparer).name() << "':\n\t\tOpt1='" << typeid(Opt1).name() << "' and Opt2='"
            << typeid(Opt2).name() << "'\n\t\tval1='" << val1 << "' and val2='" << val2 << "'" << std::endl;

  Opt1 const opt1{val1};
  Opt2 const opt2{val2};
  std::optional<typename Opt1::value_type> const std1{val1};
  std::optional<typename Opt2::value_type> const std2{val2};

  ASSERT_TRUE(comparer(opt1, opt2) == comparer(std1, std2));
  ASSERT_TRUE(comparer(opt2, opt1) == comparer(std2, std1));
}


template <class Opt1, class Val1, class Val2, class Comparer>
void TestCompareOptWithValue(Val1 val1, Val2 val2, Comparer comparer)
{
  std::cout << "\tComparison '" << typeid(Comparer).name() << "':\n\t\tOpt1='" << typeid(Opt1).name() << "'\n\t\tval1='"
            << val1 << "' and val2='" << val2 << "'" << std::endl;

  Opt1 const opt1{val1};
  std::optional<typename Opt1::value_type> const std1{val1};

  ASSERT_TRUE(comparer(opt1, val2) == comparer(std1, val2));
  ASSERT_TRUE(comparer(val2, opt1) == comparer(val2, std1));
}
} // namespace


// Some comparison tests involving NaNs fail with -ffast-math, C++20, gcc <=10 and optimizations enabled. fast-math is
// quite problematic for reproducible results, so there does not seem to be a defect in the tiny::optional library, and
// certainly not with the sentinel used within tiny::optional. Instead, the optimizer is giving inconsistent results.
// Thus, simply disable the tests for these cases.
#if !defined(TINY_OPTIONAL_GCC_BUILD) || __GNUC__ >= 11 || (!defined(__FAST_MATH__) && !defined(TINY_OPTIONAL_CPP20))
  #define TINY_OPTIONAL_ENABLE_NAN_COMPARISON_TESTS
#endif


void test_Comparisons()
{
  auto const runAllComparisons = [](auto &&... comparer) {
    // Basic comparisons.
    (TestCompareOptWithOpt<tiny::optional<int>, tiny::optional<int>>(42, 42, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<int>, tiny::optional<int>>(42, 999, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<int>, tiny::optional<int>>(42, 1, comparer), ...);

    // One optional has a sentinel value.
    (TestCompareOptWithOpt<tiny::optional<int>, tiny::optional<int, 1>>(42, 42, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<int>, tiny::optional<int, 1>>(42, 999, comparer), ...);

    // The 1st contains '1' which is the sentinel of the 2nd.
    (TestCompareOptWithOpt<tiny::optional<int>, tiny::optional<int, 1>>(1, 42, comparer), ...);

    // Both optionals are empty
    (TestCompareOptWithOpt<tiny::optional<int>, tiny::optional<int>>(std::nullopt, std::nullopt, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<int>, tiny::optional<int, 1>>(std::nullopt, std::nullopt, comparer), ...);

    // One optional is empty
    (TestCompareOptWithOpt<tiny::optional<int>, tiny::optional<int>>(42, std::nullopt, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<int>, tiny::optional<int, 1>>(1, std::nullopt, comparer), ...);

    // Comparison between distinct payload types.
    (TestCompareOptWithOpt<tiny::optional<int>, tiny::optional<double>>(42, 42.0, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<int>, tiny::optional<double>>(42, 999.0, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<float>, tiny::optional<double>>(42.0f, 999.0, comparer), ...);

    // Comparison between tiny::optional and std::optional
    (TestCompareOptWithOpt<tiny::optional<int>, std::optional<int>>(42, 42, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<int>, std::optional<int>>(42, 999, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<int, 1>, std::optional<int>>(42, 1, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<int>, std::optional<int>>(std::nullopt, std::nullopt, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<int>, std::optional<int>>(42, std::nullopt, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<int>, std::optional<int>>(std::nullopt, 42, comparer), ...);

    // Comparison between tiny/std::optional and tiny::optional_sentinel_via_type.
    // clang-format off
    (TestCompareOptWithOpt<tiny::optional<int>, tiny::optional_sentinel_via_type<int, std::integral_constant<int, 1>>>(42, 43, comparer), ...);
    (TestCompareOptWithOpt<std::optional<int>, tiny::optional_sentinel_via_type<int, std::integral_constant<int, 1>>>(42, 43, comparer), ...);
    // clang-format on

    // Comparison between tiny/std::optional and tiny::optional_aip.
    (TestCompareOptWithOpt<tiny::optional<int>, tiny::optional_aip<int>>(42, 43, comparer), ...);
    (TestCompareOptWithOpt<std::optional<int>, tiny::optional_aip<int>>(42, 43, comparer), ...);

    // Comparisons with std::nullopt
    (TestCompareOptWithValue<tiny::optional<int>>(42, std::nullopt, comparer), ...);
    (TestCompareOptWithValue<tiny::optional<int>>(std::nullopt, std::nullopt, comparer), ...);

    // Comparisons with a value of the same type as the payload
    (TestCompareOptWithValue<tiny::optional<int>>(42, 42, comparer), ...);
    (TestCompareOptWithValue<tiny::optional<int>>(42, 999, comparer), ...);
    (TestCompareOptWithValue<tiny::optional<int>>(std::nullopt, 42, comparer), ...);

    // Comparisons with a value of a different type than the payload
    (TestCompareOptWithValue<tiny::optional<int>>(42, 42.0, comparer), ...);
    (TestCompareOptWithValue<tiny::optional<int>>(42, 999.0, comparer), ...);

    // Comparisons involving partially ordered values.
#ifdef TINY_OPTIONAL_ENABLE_NAN_COMPARISON_TESTS
    static constexpr double NaN = std::numeric_limits<double>::quiet_NaN();
    (TestCompareOptWithOpt<tiny::optional<double>, tiny::optional<double>>(42, NaN, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<double>, tiny::optional<double>>(NaN, NaN, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<double>, tiny::optional<double>>(std::nullopt, NaN, comparer), ...);
    (TestCompareOptWithValue<tiny::optional<double>>(42, NaN, comparer), ...);
    (TestCompareOptWithValue<tiny::optional<double>>(NaN, NaN, comparer), ...);
    (TestCompareOptWithValue<tiny::optional<double>>(std::nullopt, NaN, comparer), ...);
#endif

    // Comparisons for optional_sentinel_via_type.
    using OptionalIntViaType = tiny::optional_sentinel_via_type<int, std::integral_constant<int, 1>>;
    (TestCompareOptWithOpt<OptionalIntViaType, OptionalIntViaType>(42, 43, comparer), ...);
    (TestCompareOptWithOpt<OptionalIntViaType, tiny::optional_sentinel_via_type<double, TestDoubleValue>>(
         42,
         43,
         comparer),
     ...);
    (TestCompareOptWithValue<OptionalIntViaType>(42, 999, comparer), ...);
    (TestCompareOptWithValue<OptionalIntViaType>(42, std::nullopt, comparer), ...);

    // Rough cross check that the tests also work with std::optional
    (TestCompareOptWithOpt<std::optional<int>, std::optional<int>>(42, 42, comparer), ...);
    (TestCompareOptWithOpt<std::optional<int>, std::optional<double>>(42, 999.0, comparer), ...);
    (TestCompareOptWithOpt<std::optional<int>, std::optional<int>>(42, std::nullopt, comparer), ...);
    (TestCompareOptWithValue<std::optional<int>>(42, 999, comparer), ...);
    (TestCompareOptWithValue<std::optional<int>>(std::nullopt, 42, comparer), ...);
    (TestCompareOptWithValue<std::optional<int>>(42, std::nullopt, comparer), ...);

#ifdef TINY_OPTIONAL_ENABLE_NAN_COMPARISON_TESTS
    (TestCompareOptWithOpt<std::optional<int>, std::optional<double>>(42, NaN, comparer), ...);
#endif
  };


  // clang-format off
  runAllComparisons(
      std::equal_to<>(),
      std::not_equal_to<>(),
      std::less<>(),
      std::less_equal<>(),
      std::greater<>(),
      std::greater_equal<>()
#ifdef __cpp_lib_three_way_comparison
      , my_compare_three_way()
#endif
  );
  // clang-format on
}
