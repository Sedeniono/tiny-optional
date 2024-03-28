#include "IntermediateTests.h"

#include "TestTypes.h"
#include "TestUtilities.h"
#include "tiny/optional.h"

void test_IsIntegralInRange()
{
  using namespace tiny::impl;

  static_assert(IsIntegralInRange<int>(-1));
  static_assert(IsIntegralInRange<int>(1));

  static_assert(IsIntegralInRange<unsigned>(1));
  static_assert(!IsIntegralInRange<unsigned>(-1));

  static_assert(IsIntegralInRange<std::int8_t>(INT8_MIN));
  static_assert(IsIntegralInRange<std::int8_t>(INT8_MAX));
  static_assert(!IsIntegralInRange<std::int8_t>(UINT8_MAX));
  static_assert(IsIntegralInRange<std::int8_t>(std::intmax_t{INT8_MIN}));
  static_assert(IsIntegralInRange<std::int8_t>(std::intmax_t{INT8_MAX}));
  static_assert(!IsIntegralInRange<std::int8_t>(std::intmax_t{INT8_MIN} - 1));
  static_assert(!IsIntegralInRange<std::int8_t>(std::intmax_t{INT8_MAX} + 1));

  static_assert(IsIntegralInRange<std::uint8_t>(0));
  static_assert(IsIntegralInRange<std::uint8_t>(UINT8_MAX));
  static_assert(!IsIntegralInRange<std::uint8_t>(INT8_MIN));
  static_assert(IsIntegralInRange<std::uint8_t>(std::intmax_t{0}));
  static_assert(IsIntegralInRange<std::uint8_t>(std::intmax_t{INT8_MAX}));
  static_assert(!IsIntegralInRange<std::uint8_t>(std::intmax_t{-1}));
  static_assert(!IsIntegralInRange<std::uint8_t>(std::intmax_t{UINT8_MAX} + 1));

  static_assert(IsIntegralInRange<std::intmax_t>(INTMAX_MIN));
  static_assert(IsIntegralInRange<std::intmax_t>(INTMAX_MAX));
  static_assert(!IsIntegralInRange<std::intmax_t>(UINTMAX_MAX));

  static_assert(IsIntegralInRange<std::uintmax_t>(0));
  static_assert(IsIntegralInRange<std::uintmax_t>(UINTMAX_MAX));
  static_assert(!IsIntegralInRange<std::uintmax_t>(INTMAX_MIN));
}


void test_NanExploit()
{
  using namespace tiny::impl;

  {
#ifndef __FAST_MATH__ // std::isnan is broken with -ffast-math
    float testValue;
    std::memcpy(&testValue, &SentinelForExploitingUnusedBits<float>::value, sizeof(float));
    ASSERT_TRUE(std::isnan(testValue));
#endif

    constexpr float sNaN = std::numeric_limits<float>::signaling_NaN();
    ASSERT_TRUE(std::memcmp(&SentinelForExploitingUnusedBits<float>::value, &sNaN, sizeof(float)) != 0);
    constexpr float qNaN = std::numeric_limits<float>::quiet_NaN();
    ASSERT_TRUE(std::memcmp(&SentinelForExploitingUnusedBits<float>::value, &qNaN, sizeof(float)) != 0);
  }
  {
#ifndef __FAST_MATH__ // std::isnan is broken with -ffast-math
    double testValue;
    std::memcpy(&testValue, &SentinelForExploitingUnusedBits<double>::value, sizeof(double));
    ASSERT_TRUE(std::isnan(testValue));
#endif

    constexpr double sNaN = std::numeric_limits<double>::signaling_NaN();
    ASSERT_TRUE(std::memcmp(&SentinelForExploitingUnusedBits<double>::value, &sNaN, sizeof(double)) != 0);
    constexpr double qNaN = std::numeric_limits<double>::quiet_NaN();
    ASSERT_TRUE(std::memcmp(&SentinelForExploitingUnusedBits<double>::value, &qNaN, sizeof(double)) != 0);
  }
}


void test_SelectDecomposition()
{
  using namespace tiny;
  using namespace tiny::impl;

  // clang-format off
  static_assert(NoArgsAndBehavesAsStdOptional == SelectDecomposition<int, tiny::UseDefaultType, UseDefaultValue>::test);
  static_assert(NoArgsAndBehavesAsStdOptional == SelectDecomposition<TestClass, tiny::UseDefaultType, UseDefaultValue>::test);
  static_assert(NoArgsAndHasCustomFlagManipulator == SelectDecomposition<double, tiny::UseDefaultType, UseDefaultValue>::test);
  static_assert(SentinelValueSpecifiedForInplaceSwallowing == SelectDecomposition<int, std::integral_constant<int, 42>, UseDefaultValue>::test);
  static_assert(SentinelValueSpecifiedForInplaceSwallowingForTypeWithCustomFlagManipulator == SelectDecomposition<double, TestDoubleValue, UseDefaultValue>::test);
  static_assert(MemPtrSpecifiedToVariableWithCustomFlagManipulator == SelectDecomposition<TestClassForInplace, tiny::UseDefaultType, &TestClassForInplace::someDouble>::test);
  static_assert(SentinelValueAndMemPtrSpecifiedForInplaceSwallowingForTypeWithCustomFlagManipulator == SelectDecomposition<TestClassForInplace, TestDoubleValue, &TestClassForInplace::someDouble>::test);
  static_assert(SentinelValueAndMemPtrSpecifiedForInplaceSwallowing == SelectDecomposition<TestClassForInplace, std::integral_constant<int, 42>, &TestClassForInplace::someInt>::test);
  
  // Should not compile:
  //static_assert(3 == SelectDecomposition<TestClass, std::integral_constant<int, 42>, UseDefaultValue>::test);
  //std::cout << "F = " << SelectDecomposition<TestClassForInplace, tiny::UseDefaultType, &TestClassForInplace::someValue1>::test << std::endl; // someValue1 is int, no default value possible
  //std::cout << "G = " << SelectDecomposition<TestClass, tiny::UseDefaultType, &TestClassForInplace::someValue2>::test << std::endl; // Mismatching type and memptr
  //std::cout << "H = " << SelectDecomposition<TestClass, std::integral_constant<int, 42>, &TestClassForInplace::someValue1>::test << std::endl; // Mismatching type and memptr

  // clang-format on
}
