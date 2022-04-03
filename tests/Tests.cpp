#include "TestCompilationBase.h"
#include "TestTypes.h"
#include "TestUtilities.h"

#ifdef TINY_OPTIONAL_MSVC_BUILD
  // Disable "unreachable code" because it is triggered by exception tests.
  #pragma warning(disable : 4702)
#endif

#include "tiny/optional.h"

#include <cstdlib>
#include <future>
#include <iostream>
#include <optional>
#include <unordered_set>
#include <utility>
#include <vector>

//====================================================================================
//====================================================================================

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

//====================================================================================
//====================================================================================

void test_NanExploit()
{
  using namespace tiny::impl;

  {
    float testValue;
    std::memcpy(&testValue, &EmptyValueExploitingUnusedBits<float>::value, sizeof(float));
    ASSERT_TRUE(std::isnan(testValue));

    constexpr float sNaN = std::numeric_limits<float>::signaling_NaN();
    ASSERT_TRUE(std::memcmp(&EmptyValueExploitingUnusedBits<float>::value, &sNaN, sizeof(float)) != 0);
    constexpr float qNaN = std::numeric_limits<float>::quiet_NaN();
    ASSERT_TRUE(std::memcmp(&EmptyValueExploitingUnusedBits<float>::value, &qNaN, sizeof(float)) != 0);
  }
  {
    double testValue;
    std::memcpy(&testValue, &EmptyValueExploitingUnusedBits<double>::value, sizeof(double));
    ASSERT_TRUE(std::isnan(testValue));

    constexpr double sNaN = std::numeric_limits<double>::signaling_NaN();
    ASSERT_TRUE(std::memcmp(&EmptyValueExploitingUnusedBits<double>::value, &sNaN, sizeof(double)) != 0);
    constexpr double qNaN = std::numeric_limits<double>::quiet_NaN();
    ASSERT_TRUE(std::memcmp(&EmptyValueExploitingUnusedBits<double>::value, &qNaN, sizeof(double)) != 0);
  }
}


//====================================================================================
//====================================================================================

void test_SelectDecomposition()
{
  using namespace tiny;
  using namespace tiny::impl;

  // clang-format off
  static_assert(NoArgsAndBehavesAsStdOptional == SelectDecomposition<int, tiny::UseDefaultType, UseDefaultValue>::test);
  static_assert(NoArgsAndBehavesAsStdOptional == SelectDecomposition<TestClass, tiny::UseDefaultType, UseDefaultValue>::test);
  static_assert(NoArgsButExploitUnusedBits == SelectDecomposition<double, tiny::UseDefaultType, UseDefaultValue>::test);
  static_assert(EmptyValueSpecifiedForInplaceSwallowing == SelectDecomposition<int, std::integral_constant<int, 42>, UseDefaultValue>::test);
  static_assert(EmptyValueSpecifiedForInplaceSwallowingForTypeWithUnusedBits == SelectDecomposition<double, TestDoubleValue, UseDefaultValue>::test);
  static_assert(MemPtrSpecifiedToVariableWithUnusedBits == SelectDecomposition<TestClassForInplace, tiny::UseDefaultType, &TestClassForInplace::someValue2>::test);
  static_assert(EmptyValueAndMemPtrSpecifiedForInplaceSwallowingForTypeWithUnusedBits == SelectDecomposition<TestClassForInplace, TestDoubleValue, &TestClassForInplace::someValue2>::test);
  static_assert(EmptyValueAndMemPtrSpecifiedForInplaceSwallowing == SelectDecomposition<TestClassForInplace, std::integral_constant<int, 42>, &TestClassForInplace::someValue1>::test);
  
  // Should not compile:
  //static_assert(3 == SelectDecomposition<TestClass, std::integral_constant<int, 42>, UseDefaultValue>::test);
  //std::cout << "F = " << SelectDecomposition<TestClassForInplace, tiny::UseDefaultType, &TestClassForInplace::someValue1>::test << std::endl; // someValue1 is int, no default value possible
  //std::cout << "G = " << SelectDecomposition<TestClass, tiny::UseDefaultType, &TestClassForInplace::someValue2>::test << std::endl; // Mismatching type and memptr
  //std::cout << "H = " << SelectDecomposition<TestClass, std::integral_constant<int, 42>, &TestClassForInplace::someValue1>::test << std::endl; // Mismatching type and memptr

  // clang-format on
}


//====================================================================================
//====================================================================================

enum InPlaceExpectation
{
  EXPECT_INPLACE,
  EXPECT_SEPARATE
};


// validValueToAssign1 and validValueToAssign2 should be two different test values, i.e. values
// that the tests can assign to the optional to test various things.
#define EXERCISE_OPTIONAL(o, inPlaceExpectation, validValueToAssign1, validValueToAssign2)                             \
  ExerciseOptional<decltype(o), inPlaceExpectation>(                                                                   \
      #o,                                                                                                              \
      #validValueToAssign1,                                                                                            \
      #validValueToAssign2,                                                                                            \
      "",                                                                                                              \
      validValueToAssign1,                                                                                             \
      validValueToAssign2)

#define EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS(o, inPlaceExpectation, validValueToAssign1, validValueToAssign2, ...)  \
  ExerciseOptional<decltype(o), inPlaceExpectation>(                                                                   \
      #o,                                                                                                              \
      #validValueToAssign1,                                                                                            \
      #validValueToAssign2,                                                                                            \
      #__VA_ARGS__,                                                                                                    \
      validValueToAssign1,                                                                                             \
      validValueToAssign2,                                                                                             \
      __VA_ARGS__)


template <
    class Optional,
    InPlaceExpectation inPlaceExpectation,
    class TestValue1T,
    class TestValue2T,
    class... ConstructorArgsT>
void ExerciseOptional(
    std::string const optionalStr,
    std::string const validValueToAssign1Str,
    std::string const validValueToAssign2Str,
    std::string const constructorArgsStr,
    TestValue1T const validValueToAssign1,
    TestValue2T const validValueToAssign2,
    ConstructorArgsT const... constructorArgs)
{
  if constexpr (inPlaceExpectation == EXPECT_INPLACE) {
    static_assert(
        sizeof(Optional) == sizeof(typename Optional::value_type),
        "Test failure: Expected the tiny::optional to be tiny, i.e. to not require additional memory.");
  }
  else {
    static_assert(
        sizeof(Optional) == sizeof(std::optional<typename Optional::value_type>),
        "Test failure: Expected the tiny::optional to be the same size as std::optional.");
  }

  static_assert(noexcept(Optional{}.reset()));
  static_assert(noexcept(Optional{}.has_value()));

  std::cout << "\tExercising " << optionalStr << " with validValueToAssign1='" << validValueToAssign1Str
            << ", validValueToAssign2='" << validValueToAssign2Str << "' and constructorArgs = '" << constructorArgsStr
            << "'" << std::endl;

// clang-format off
  #define TEST_PARAMS \
      [[maybe_unused]] TestValue1T validValueToAssign1, \
      [[maybe_unused]] TestValue2T validValueToAssign2, \
      [[maybe_unused]] ConstructorArgsT const... constructorArgs
  // clang-format on

  // Note: Deliberately not using std::function because it is VERY expensive when compiling with clang.
  // Compare https://stackoverflow.com/q/52499122
  // Similarly, using raw-array and char*.

  // clang-format off
  std::pair<char const *, void(*)(TestValue1T, TestValue2T, ConstructorArgsT...)> const tests[] = {
    {"Constructor_Default", [] (TEST_PARAMS) {
      static_assert(noexcept(Optional{}));
      Optional o;
      ASSERT_FALSE(o.has_value());
    }}
    ,
    {"Constructor_Nullopt", [] (TEST_PARAMS) {
      static_assert(noexcept(Optional{std::nullopt}));
      Optional o{std::nullopt};
      ASSERT_FALSE(o.has_value());
    }}
    ,
    {"Constructor_CopyOfEmpty", [] (TEST_PARAMS) {
      Optional o;
      Optional copy{o};
      ASSERT_FALSE(copy.has_value());
    }}
    ,
    {"Constructor_CopyOfNonEmpty", [] (TEST_PARAMS) {
      Optional o;
      o = validValueToAssign1;
      Optional copy(o);
      ASSERT_TRUE(o.has_value());
      ASSERT_TRUE(copy.has_value());
      ASSERT_TRUE(AreEqual(o.value(), validValueToAssign1));
      ASSERT_TRUE(AreEqual(copy.value(), validValueToAssign1));
    }}
    ,
    {"Constructor_MoveOfEmpty", [] (TEST_PARAMS) {
      Optional o;
      Optional moveTarget(std::move(o));
      ASSERT_FALSE(moveTarget.has_value());
      ASSERT_FALSE(o.has_value());
    }}
    ,
    {"Constructor_MoveOfNonEmpty", [] (TEST_PARAMS) {
      Optional o(validValueToAssign1);
      Optional moveTarget(std::move(o));
      ASSERT_TRUE(o.has_value()); // Original optional must still have a value according to the standard...
      ASSERT_TRUE(EmptyOrNoContainer(o.value())); // ... but the value itself is empty.
      ASSERT_TRUE(moveTarget.has_value());
      ASSERT_TRUE(AreEqual(moveTarget.value(), validValueToAssign1));
    }}
    ,
    {"Constructor_inplace", [] (TEST_PARAMS) {
      Optional o(std::in_place, constructorArgs...);
      ASSERT_TRUE(o.has_value());
      typename Optional::value_type manuallyConstructed{constructorArgs...};
      ASSERT_TRUE(AreEqual(o.value(), manuallyConstructed));

      // Check that the inplace constructors do not participate in overload resolution if the payload cannot be 
      // constructed. None of the payloads we use as test can be constructed with the local enum type Dummy.
      enum class Dummy{};
      static_assert(!std::is_constructible_v<Optional, std::in_place_t, ConstructorArgsT..., Dummy>);
    }}
    ,
    {"Constructor_fromValueViaParentheses", [] (TEST_PARAMS) {
      Optional o(validValueToAssign1);
      ASSERT_TRUE(o.has_value());
      ASSERT_TRUE(AreEqual(o.value(), validValueToAssign1));
    }}
    ,
    {"Constructor_fromValueViaBraces", [] (TEST_PARAMS) {
      Optional o{validValueToAssign1};
      ASSERT_TRUE(o.has_value());
      ASSERT_TRUE(AreEqual(o.value(), validValueToAssign1));
    }}
    ,
    {"Constructor_moveFromValue", [] (TEST_PARAMS) {
      auto moveFrom = validValueToAssign1;
      Optional o(std::move(moveFrom));
      ASSERT_TRUE(o.has_value());
      ASSERT_TRUE(AreEqual(o.value(), validValueToAssign1));
      ASSERT_TRUE(EmptyOrNoContainer(moveFrom)); // If moveFrom is a container, it should now be empty due to the move
    }}
    ,
    {"Assignment_nulloptToEmpty", [] (TEST_PARAMS) {
      Optional o;
      ASSERT_FALSE(o.has_value());
      Optional & returned = (o = std::nullopt);
      ASSERT_FALSE(o.has_value());
      ASSERT_TRUE(&o == &returned);
    }}
    ,
    {"Assignment_nulloptToNonEmpty", [] (TEST_PARAMS) {
      Optional o(validValueToAssign1);
      ASSERT_TRUE(o.has_value());
      Optional & returned = (o = std::nullopt);
      ASSERT_FALSE(o.has_value());
      ASSERT_TRUE(&o == &returned);
    }}
    ,
    {"Assignment_bracesToNonEmpty", [] (TEST_PARAMS) {
      Optional o(validValueToAssign1);
      ASSERT_TRUE(o.has_value());
      Optional & returned = (o = {});
      ASSERT_FALSE(o.has_value());
      ASSERT_TRUE(&o == &returned);
    }}
    ,
    {"Assignment_EmptyToEmpty", [] (TEST_PARAMS) {
      Optional o1;
      ASSERT_FALSE(o1.has_value());
      Optional o2;
      Optional & returned = (o2 = o1);
      ASSERT_FALSE(o2.has_value());
      ASSERT_TRUE(&o2 == &returned);
    }}
    ,
    {"Assignment_EmptyToNonEmpty", [] (TEST_PARAMS) {
      Optional o(validValueToAssign1);
      ASSERT_TRUE(o.has_value());
      Optional empty;
      Optional & returned = (o = empty);
      ASSERT_FALSE(o.has_value());
      ASSERT_TRUE(&o == &returned);
    }}
    ,
    {"Assignment_NonEmptyToNonEmpty", [] (TEST_PARAMS) {
      Optional o1(validValueToAssign1);
      ASSERT_TRUE(o1.has_value());
      Optional o2(validValueToAssign2);
      ASSERT_TRUE(o2.has_value());

      Optional & returned = (o2 = o1);
      ASSERT_TRUE(o2.has_value());
      ASSERT_TRUE(AreEqual(o2.value(), validValueToAssign1));
      ASSERT_TRUE(AreEqual(o2.value(), o1.value()));
      ASSERT_TRUE(&o2 == &returned);
    }}
    ,
    {"Assignment_NonEmptyToEmpty", [] (TEST_PARAMS) {
      Optional o1(validValueToAssign1);
      ASSERT_TRUE(o1.has_value());
      Optional o2;
      ASSERT_FALSE(o2.has_value());

      Optional & returned = (o2 = o1);
      ASSERT_TRUE(o2.has_value());
      ASSERT_TRUE(AreEqual(o2.value(), validValueToAssign1));
      ASSERT_TRUE(AreEqual(o2.value(), o1.value()));
      ASSERT_TRUE(&o2 == &returned);
    }}
    ,
    {"Assignment_MoveOfEmptyToEmpty", [] (TEST_PARAMS) {
      Optional o;
      Optional moveTarget;
      Optional & returned = (moveTarget = std::move(o));
      ASSERT_FALSE(o.has_value());
      ASSERT_FALSE(moveTarget.has_value());
      ASSERT_TRUE(&moveTarget == &returned);
    }}
    ,
    {"Assignment_MoveOfNonEmptyToEmpty", [] (TEST_PARAMS) {
      Optional o(validValueToAssign1);
      Optional moveTarget;
      Optional & returned = (moveTarget = std::move(o));
      ASSERT_TRUE(o.has_value()); // Original optional must still have a value according to the standard...
      ASSERT_TRUE(EmptyOrNoContainer(o.value())); // ... but the value itself is empty.
      ASSERT_TRUE(moveTarget.has_value());
      ASSERT_TRUE(AreEqual(moveTarget.value(), validValueToAssign1));
      ASSERT_TRUE(&moveTarget == &returned);
    }}
    ,
    {"Assignment_MoveOfNonEmptyToNonEmpty", [] (TEST_PARAMS) {
      Optional o(validValueToAssign1);
      Optional moveTarget(validValueToAssign2);
      Optional & returned = (moveTarget = std::move(o));
      ASSERT_TRUE(o.has_value()); // Original optional must still have a value according to the standard...
      ASSERT_TRUE(EmptyOrNoContainer(o.value())); // ... but the value itself is empty.
      ASSERT_TRUE(moveTarget.has_value());
      ASSERT_TRUE(AreEqual(moveTarget.value(), validValueToAssign1));
      ASSERT_TRUE(&moveTarget == &returned);
    }}
    ,
    {"Assignment_MoveOfEmptyToNonEmpty", [] (TEST_PARAMS) {
      Optional empty;
      Optional moveTarget(validValueToAssign1);
      ASSERT_TRUE(moveTarget.has_value());
      Optional & returned = (moveTarget = std::move(empty));
      ASSERT_FALSE(empty.has_value());
      ASSERT_FALSE(moveTarget.has_value());
      ASSERT_TRUE(&moveTarget == &returned);
    }}
    ,
    {"Assignment_PayloadToEmpty", [] (TEST_PARAMS) {
      Optional o;
      Optional & returned = (o = validValueToAssign1);
      ASSERT_TRUE(o.has_value());
      ASSERT_TRUE(AreEqual(o.value(), validValueToAssign1));
      ASSERT_TRUE(&o == &returned);
    }}
    ,
    {"Assignment_PayloadToNonEmpty", [] (TEST_PARAMS) {
      Optional o(validValueToAssign1);
      Optional & returned = (o = validValueToAssign2);
      ASSERT_TRUE(o.has_value());
      ASSERT_TRUE(AreEqual(o.value(), validValueToAssign2));
      ASSERT_TRUE(&o == &returned);
    }}
    ,
    {"Assignment_MovePayloadToEmpty", [] (TEST_PARAMS) {
      auto moveFrom = validValueToAssign1;
      Optional o;
      Optional & returned = (o = std::move(moveFrom));
      ASSERT_TRUE(o.has_value());
      ASSERT_TRUE(AreEqual(o.value(), validValueToAssign1));
      ASSERT_TRUE(EmptyOrNoContainer(moveFrom)); // If moveFrom is a container, it should now be empty due to the move
      ASSERT_TRUE(&o == &returned);
    }}
    ,
    {"Emplace_ToEmpty", [] (TEST_PARAMS) {
      Optional o;
      auto & added = o.emplace(constructorArgs...);
      ASSERT_TRUE(o.has_value());
      ASSERT_TRUE(AreEqual(o.value(), added));
      typename Optional::value_type manuallyConstructed{constructorArgs...};
      ASSERT_TRUE(AreEqual(o.value(), manuallyConstructed));
    }}
    ,
    {"Emplace_ToNonEmpty", [] (TEST_PARAMS) {
      Optional o;
      o = validValueToAssign1;
      auto & added = o.emplace(constructorArgs...);
      ASSERT_TRUE(o.has_value());
      ASSERT_TRUE(AreEqual(o.value(), added));
      typename Optional::value_type manuallyConstructed{constructorArgs...};
      ASSERT_TRUE(AreEqual(o.value(), manuallyConstructed));
    }}
    ,
    {"ResetOfEmpty", [] (TEST_PARAMS) {
      Optional o;
      o.reset();
      ASSERT_FALSE(o.has_value());
      o.reset();
      ASSERT_FALSE(o.has_value());
    }}
    ,
    {"ResetOfNonEmpty", [] (TEST_PARAMS) {
      Optional o;
      o = validValueToAssign1;
      ASSERT_TRUE(o.has_value());
      o.reset();
      ASSERT_FALSE(o.has_value());
    }}
    ,
    {"OperatorBool", [] (TEST_PARAMS) {
      Optional o;
      static_assert(noexcept(static_cast<bool>(o)));
      ASSERT_FALSE(o.has_value());
      ASSERT_FALSE(o);
      o = validValueToAssign1;
      ASSERT_TRUE(o.has_value());
      ASSERT_TRUE(o);
    }}
    ,
    {"pointerOperator", [] (TEST_PARAMS) {
      {
        Optional nonConstOpt{validValueToAssign1};
        //static_assert(noexcept(nonConstOpt.operator->())); // libc++ and MSVC are noexcept(false)?
        typename Optional::value_type * ptr = nonConstOpt.operator->();
        ASSERT_TRUE(AreEqual(*ptr, validValueToAssign1));
        ASSERT_TRUE(AreEqual(ptr, &nonConstOpt.value()));
      }
      {
        Optional const constOpt{validValueToAssign1};
        //static_assert(noexcept(constOpt.operator->())); // libc++ and MSVC are noexcept(false)?
        typename Optional::value_type const * ptr = constOpt.operator->();
        ASSERT_TRUE(AreEqual(*ptr, validValueToAssign1));
        ASSERT_TRUE(AreEqual(ptr, &constOpt.value()));
      }
    }}
    ,
    {"dereferenceForNonEmpty", [] (TEST_PARAMS) {
      {
        Optional optional_lvalue{validValueToAssign1};
        typename Optional::value_type & lvalue = *optional_lvalue;
        ASSERT_TRUE(AreEqual(lvalue, validValueToAssign1));
      }
      {
        Optional const optional_const_lvalue{validValueToAssign1};
        typename Optional::value_type const & const_lvalue = *optional_const_lvalue;
        ASSERT_TRUE(AreEqual(const_lvalue, validValueToAssign1));
      }
      {
        auto const check_rvalue = [&validValueToAssign1](typename Optional::value_type && v) {
          auto movedTo = std::move(v);
          ASSERT_TRUE(AreEqual(movedTo, validValueToAssign1));
          ASSERT_TRUE(EmptyOrNoContainer(v));
        };
        Optional optional_rvalue{validValueToAssign1};
        check_rvalue(std::move(*optional_rvalue));
        ASSERT_TRUE(optional_rvalue.has_value());
        ASSERT_TRUE(EmptyOrNoContainer(optional_rvalue.value()));
      }
      {
        auto const check_const_rvalue = [&validValueToAssign1](typename Optional::value_type const && v) {
          ASSERT_TRUE(AreEqual(v, validValueToAssign1));
        };
        Optional const optional_const_rvalue{validValueToAssign1};
        check_const_rvalue(*static_cast<Optional const &&>(optional_const_rvalue));
      }
    }}
    ,
    {"valueForNonEmpty", [] (TEST_PARAMS) {
      {
        Optional optional_lvalue{validValueToAssign1};
        static_assert(!noexcept(optional_lvalue.value()));
        typename Optional::value_type & lvalue = optional_lvalue.value();
        ASSERT_TRUE(AreEqual(lvalue, validValueToAssign1));
      }
      {
        Optional const optional_const_lvalue{validValueToAssign1};
        static_assert(!noexcept(optional_const_lvalue.value()));
        typename Optional::value_type const & const_lvalue = optional_const_lvalue.value();
        ASSERT_TRUE(AreEqual(const_lvalue, validValueToAssign1));
      }
      {
        auto const check_rvalue = [&validValueToAssign1](typename Optional::value_type && v) {
          auto movedTo = std::move(v);
          ASSERT_TRUE(AreEqual(movedTo, validValueToAssign1));
          ASSERT_TRUE(EmptyOrNoContainer(v));
        };
        Optional optional_rvalue{validValueToAssign1};
        static_assert(!noexcept(std::move(optional_rvalue).value()));
        check_rvalue(std::move(optional_rvalue).value());
        ASSERT_TRUE(optional_rvalue.has_value());
        ASSERT_TRUE(EmptyOrNoContainer(optional_rvalue.value()));
      }
      {
        auto const check_const_rvalue = [&validValueToAssign1](typename Optional::value_type const && v) {
          ASSERT_TRUE(AreEqual(v, validValueToAssign1));
        };
        Optional const optional_const_rvalue{validValueToAssign1};
        static_assert(!noexcept(static_cast<Optional const &&>(optional_const_rvalue).value()));
        check_const_rvalue(static_cast<Optional const &&>(optional_const_rvalue).value());
      }
    }}
    ,
    {"valueForEmpty", [] (TEST_PARAMS) {
      Optional empty;
      EXPECT_EXCEPTION([[maybe_unused]] auto const & v = empty.value(), std::bad_optional_access);

      Optional const empty_const_lvalue;
      EXPECT_EXCEPTION([[maybe_unused]] auto const & v = empty_const_lvalue.value(), std::bad_optional_access);

      EXPECT_EXCEPTION([[maybe_unused]] auto const v = Optional{}.value(), std::bad_optional_access);

      EXPECT_EXCEPTION([[maybe_unused]] auto const v = static_cast<Optional const &&>(empty).value(), 
                       std::bad_optional_access);
    }}
    ,
    {"value_or_ForNonEmpty", [] (TEST_PARAMS) {
      {
        Optional const o{validValueToAssign1};
        ASSERT_TRUE(AreEqual(o.value_or(validValueToAssign2), validValueToAssign1));
      }
      {
        Optional moveFrom{validValueToAssign1};
        auto movedValue = std::move(moveFrom).value_or(validValueToAssign2);
        ASSERT_TRUE(AreEqual(movedValue, validValueToAssign1));
        ASSERT_TRUE(EmptyOrNoContainer(moveFrom.value()));
      }
    }}
    ,
    {"value_or_ForEmpty", [] (TEST_PARAMS) {
      {
        Optional const o;
        ASSERT_TRUE(AreEqual(o.value_or(validValueToAssign1), validValueToAssign1));
        ASSERT_FALSE(o.has_value());
      }
      {
        auto inputValue = validValueToAssign1;
        Optional moveFrom;
        auto movedValue = std::move(moveFrom).value_or(std::move(inputValue));
        ASSERT_TRUE(AreEqual(movedValue, validValueToAssign1));
        ASSERT_FALSE(moveFrom.has_value());
        ASSERT_TRUE(EmptyOrNoContainer(inputValue));
      }
    }}
    ,
    {"swapOfEmptyAndEmpty", [] (TEST_PARAMS) {
      using std::swap;
      Optional empty1;
      Optional empty2;
      swap(empty1, empty2);
      ASSERT_FALSE(empty1.has_value());
      ASSERT_FALSE(empty2.has_value());
    }}
    ,
    {"swapOfNonEmptyAndNonEmpty", [] (TEST_PARAMS) {
      using std::swap;
      Optional o1{validValueToAssign1};
      Optional o2{validValueToAssign2};
      swap(o1, o2);
      ASSERT_TRUE(AreEqual(o1.value(), validValueToAssign2));
      ASSERT_TRUE(AreEqual(o2.value(), validValueToAssign1));
    }}
    ,
    {"swapOfEmptyAndNonEmpty", [] (TEST_PARAMS) {
      using std::swap;
      Optional o1;
      Optional o2{validValueToAssign2};
      swap(o1, o2);
      ASSERT_TRUE(AreEqual(o1.value(), validValueToAssign2));
      ASSERT_FALSE(o2.has_value());
    }}
    ,
    {"swapOfNonEmptyAndEmpty", [] (TEST_PARAMS) {
      using std::swap;
      Optional o1{validValueToAssign1};
      Optional o2;
      swap(o1, o2);
      ASSERT_FALSE(o1.has_value());
      ASSERT_TRUE(AreEqual(o2.value(), validValueToAssign1));
    }}
  };
  // clang-format on

  for (size_t testIdx = 0; testIdx < std::extent_v<decltype(tests)>; ++testIdx) {
    auto const [testName, testFunc] = tests[testIdx];
    std::cout << "\t\t" << testName << "\t";
    testFunc(validValueToAssign1, validValueToAssign2, constructorArgs...);
    std::cout << "PASS" << std::endl;
  }
}


//====================================================================================
//====================================================================================


void test_TinyOptional_EmptyValueViaType()
{
  EXERCISE_OPTIONAL((tiny::optional_empty_via_type<bool, tiny::UseDefaultType>{}), EXPECT_INPLACE, false, true);
  EXERCISE_OPTIONAL((tiny::optional_empty_via_type<bool, tiny::UseDefaultType>{}), EXPECT_INPLACE, true, false);

  EXERCISE_OPTIONAL((tiny::optional_empty_via_type<double, tiny::UseDefaultType>{}), EXPECT_INPLACE, 43.0, 44.0);
  EXERCISE_OPTIONAL((tiny::optional_empty_via_type<float, tiny::UseDefaultType>{}), EXPECT_INPLACE, 43.0f, 44.0f);

  EXERCISE_OPTIONAL((tiny::optional_empty_via_type<int, tiny::UseDefaultType>{}), EXPECT_SEPARATE, 43, 44);
  EXERCISE_OPTIONAL((tiny::optional_empty_via_type<int, std::integral_constant<int, 42>>{}), EXPECT_INPLACE, 43, 44);

  EXERCISE_OPTIONAL(
      (tiny::optional_empty_via_type<
          TestClassForInplace,
          std::integral_constant<int, 42>,
          &TestClassForInplace::someValue1>{}),
      EXPECT_INPLACE,
      TestClassForInplace{},
      TestClassForInplace(43, 44.0, 45, nullptr));

  EXERCISE_OPTIONAL(
      (tiny::optional_empty_via_type<TestClass, tiny::UseDefaultType>{}),
      EXPECT_SEPARATE,
      TestClass(true, 4.0),
      TestClass(true, 5.0));

  EXERCISE_OPTIONAL((tiny::optional_empty_via_type<double, TestDoubleValue>{}), EXPECT_INPLACE, 43.0, 44.0);

  EXERCISE_OPTIONAL(
      (tiny::optional_empty_via_type<TestClassForInplace, TestDoubleValue, &TestClassForInplace::someValue2>{}),
      EXPECT_INPLACE,
      TestClassForInplace{},
      TestClassForInplace(43, 44.0, 45, nullptr));

  {
    // Test for the std::hash specialization
    static_assert(!IsDisabledHash<tiny::optional_empty_via_type<double, TestDoubleValue>>);
    std::unordered_set<tiny::optional_empty_via_type<double, TestDoubleValue>> const set = {43.0, std::nullopt, 44.0};
    ASSERT_TRUE(set.count(43.0) > 0);
    ASSERT_TRUE(set.count(std::nullopt) > 0);
    ASSERT_TRUE(set.count(44.0) > 0);
  }
  {
    // We did not specialize std::hash for TestClassWithInitializerList, so neither should tiny optional.
    static_assert(IsDisabledHash<TestClassWithInitializerList>);
    static_assert(IsDisabledHash<tiny::optional_empty_via_type<TestClassWithInitializerList, tiny::UseDefaultType>>);
  }
}


void test_TinyOptional()
{
  EXERCISE_OPTIONAL((tiny::optional<bool>{}), EXPECT_INPLACE, false, true);
  EXERCISE_OPTIONAL((tiny::optional<bool>{}), EXPECT_INPLACE, true, false);
  EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS((tiny::optional<bool, true>{}), EXPECT_INPLACE, false, false, false);
  EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS((tiny::optional<bool, false>{}), EXPECT_INPLACE, true, true, true);
  EXERCISE_OPTIONAL((tiny::optional{false}), EXPECT_INPLACE, false, true); // Uses deduction guide

  EXERCISE_OPTIONAL((tiny::optional<int>{}), EXPECT_SEPARATE, 42, 43);
  EXERCISE_OPTIONAL((tiny::optional{100}), EXPECT_SEPARATE, 42, 43); // Uses deduction guide

  EXERCISE_OPTIONAL((tiny::optional<double>{}), EXPECT_INPLACE, 43.0, 44.0);
  EXERCISE_OPTIONAL((tiny::optional<double>{}), EXPECT_INPLACE, std::numeric_limits<double>::quiet_NaN(), 44.0);
  EXERCISE_OPTIONAL((tiny::optional<double>{}), EXPECT_INPLACE, std::numeric_limits<double>::signaling_NaN(), 44.0);
  EXERCISE_OPTIONAL((tiny::optional{100.0}), EXPECT_INPLACE, 43.0, 44.0); // Uses deduction guide

  EXERCISE_OPTIONAL((tiny::optional<float>{}), EXPECT_INPLACE, 43.0f, 44.0f);
  EXERCISE_OPTIONAL((tiny::optional<float>{}), EXPECT_INPLACE, std::numeric_limits<float>::quiet_NaN(), 44.0f);
  EXERCISE_OPTIONAL((tiny::optional<float>{}), EXPECT_INPLACE, std::numeric_limits<float>::signaling_NaN(), 44.0f);
  EXERCISE_OPTIONAL((tiny::optional{100.0f}), EXPECT_INPLACE, 43.0f, 44.0f); // Uses deduction guide
  
  EXERCISE_OPTIONAL((tiny::optional<long double>{}), EXPECT_SEPARATE, 43.0L, 44.0L);

  EXERCISE_OPTIONAL((tiny::optional<int, 42>{}), EXPECT_INPLACE, 43, 44);
  EXERCISE_OPTIONAL((tiny::optional<unsigned, std::numeric_limits<unsigned>::max()>{}), EXPECT_INPLACE, 43u, 44u);

  EXERCISE_OPTIONAL((tiny::optional<char, std::numeric_limits<char>::max()>{}), EXPECT_INPLACE, (char)43, (char)44);
  EXERCISE_OPTIONAL((tiny::optional<char, 'z'>{}), EXPECT_INPLACE, 'a', 'b');
  EXERCISE_OPTIONAL((tiny::optional{'c'}), EXPECT_SEPARATE, 'a', 'b'); // Uses deduction guide

  EXERCISE_OPTIONAL((tiny::optional<std::byte, std::byte{255}>{}), EXPECT_INPLACE, std::byte{42}, std::byte{43});

  EXERCISE_OPTIONAL((tiny::optional<ScopedEnum, ScopedEnum::vend>{}), EXPECT_INPLACE, ScopedEnum::v2, ScopedEnum::v1);
  EXERCISE_OPTIONAL((tiny::optional<UnscopedEnum, UE_end>{}), EXPECT_INPLACE, UE_v2, UE_v1);

  EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS(
      (tiny::optional<TestClassForInplace, &TestClassForInplace::someValue1, 42>{}),
      EXPECT_INPLACE,
      TestClassForInplace{},
      TestClassForInplace(43, 44.0, 45, nullptr),
      2,
      5.0,
      43u,
      nullptr);
  EXERCISE_OPTIONAL(
      (tiny::optional<TestClassForInplace, &TestClassForInplace::someValue2>{}),
      EXPECT_INPLACE,
      TestClassForInplace{},
      TestClassForInplace(43, 44.0, 45, nullptr));

  // We befriended the present function
  EXERCISE_OPTIONAL(
      (tiny::optional<TestClassPrivate, &TestClassPrivate::someValue>{}),
      EXPECT_INPLACE,
      TestClassPrivate{42.0},
      TestClassPrivate{43.0});

  EXERCISE_OPTIONAL((tiny::optional<TestClass>{}), EXPECT_SEPARATE, TestClass(true, 4.0), TestClass(true, 5.0));
  // Uses deduction guide
  EXERCISE_OPTIONAL((tiny::optional{TestClass{}}), EXPECT_SEPARATE, TestClass(true, 4.0), TestClass(true, 5.0));

  {
    TestClass c1, c2;
    EXERCISE_OPTIONAL((tiny::optional<TestClass *>{}), EXPECT_INPLACE, &c1, &c2);
    EXERCISE_OPTIONAL((tiny::optional<TestClass *>{}), EXPECT_INPLACE, nullptr, &c1);
    EXERCISE_OPTIONAL((tiny::optional{&c1}), EXPECT_INPLACE, &c1, &c2); // Uses deduction guide
  }
  {
    TestClass c1, c2;
    EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS((tiny::optional<TestClass *, nullptr>{}), EXPECT_INPLACE, &c1, &c2, &c1);
    // The following should trigger the assert that reset() should be used instead.
    // ExerciseOptional<TestClass*>(o, nullptr);
  }
  {
    TestClass c1, c2;
    EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS(
        (tiny::optional<std::reference_wrapper<TestClass>>{}),
        EXPECT_SEPARATE,
        std::ref(c1),
        std::ref(c2),
        std::ref(c1));
    EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS(
        (tiny::optional<std::reference_wrapper<TestClass const>>{}),
        EXPECT_SEPARATE,
        std::cref(c1),
        std::cref(c2),
        std::cref(c1));
  }
  {
    EXERCISE_OPTIONAL((tiny::optional<TestFuncPtr>{}), EXPECT_INPLACE, &TestFunc1, &TestFunc2);
    EXERCISE_OPTIONAL((tiny::optional<TestFuncPtr>{}), EXPECT_INPLACE, nullptr, &TestFunc2);
  }

  EXERCISE_OPTIONAL(
      (tiny::optional<TestClassForInplace, &TestClassForInplace::someValue4>{}),
      EXPECT_INPLACE,
      TestClassForInplace{},
      TestClassForInplace(43, 44.0, 45, nullptr));

  // Just to have some class with noexcept(false) stuff.
  EXERCISE_OPTIONAL(
      (tiny::optional<TestClassWithExcept>{}),
      EXPECT_SEPARATE,
      TestClassWithExcept{42},
      TestClassWithExcept{43});

  // Targets functions of tiny::optional that work with std::initializer_list.
  {
    std::initializer_list<int> const initList = {3, 4, 5};
    EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS(
        (tiny::optional<TestClassWithInitializerList>{}),
        EXPECT_SEPARATE,
        TestClassWithInitializerList({1}),
        TestClassWithInitializerList({2}),
        initList);
    EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS(
        (tiny::optional<TestClassWithInitializerList>{}),
        EXPECT_SEPARATE,
        TestClassWithInitializerList({1}),
        TestClassWithInitializerList({2}),
        initList,
        ScopedEnum::v2);
  }

  {
    std::vector<int> testValue1{1, 2, 3, 4};
    std::vector<int> testValue2{5, 6, 7};
    EXERCISE_OPTIONAL((tiny::optional<std::vector<int>>{}), EXPECT_SEPARATE, testValue1, testValue2);
    EXERCISE_OPTIONAL((tiny::optional{testValue1}), EXPECT_SEPARATE, testValue1, testValue2);
  }

  {
    // Tests that target cases where the deduction guide of std::optional would come into play.
    // https://en.cppreference.com/w/cpp/utility/optional/deduction_guides
    int arr1[2] = {1, 2};
    int arr2[2] = {3, 4};
    static_assert(std::is_same_v<decltype(tiny::optional{arr1})::value_type, int *>);
    EXERCISE_OPTIONAL((tiny::optional{arr1}), EXPECT_INPLACE, arr1, arr2);

    struct NonCopyable
    {
      NonCopyable() = default;
      NonCopyable(NonCopyable const &) = delete;
      NonCopyable(NonCopyable &&) = default;
    };
    static_assert(std::is_same_v<decltype(tiny::optional{NonCopyable{}})::value_type, NonCopyable>);
  }

  // Test for the std::hash specialization
  {
    static_assert(!IsDisabledHash<tiny::optional<double>>);
    std::unordered_set<tiny::optional<double>> const set = {42.0, std::nullopt, 43.0};
    ASSERT_TRUE(set.count(42.0) > 0);
    ASSERT_TRUE(set.count(std::nullopt) > 0);
    ASSERT_TRUE(set.count(43.0) > 0);
  }
  {
    static_assert(!IsDisabledHash<tiny::optional<int, 0>>);
    std::unordered_set<tiny::optional<int, 0>> const set = {42, std::nullopt};
    ASSERT_TRUE(set.count(42) > 0);
    ASSERT_TRUE(set.count(std::nullopt) > 0);
  }
  {
    static_assert(!IsDisabledHash<tiny::optional<TestClassForInplace, &TestClassForInplace::someValue1, 42>>);
    std::unordered_set<tiny::optional<TestClassForInplace, &TestClassForInplace::someValue1, 42>> const set
        = {TestClassForInplace(43, 44.0, 45, nullptr), std::nullopt};
    ASSERT_TRUE(set.count(TestClassForInplace(43, 44.0, 45, nullptr)) > 0);
    ASSERT_TRUE(set.count(std::nullopt) > 0);
  }
  {
    // We did not specialize std::hash for TestClassWithInitializerList, so neither should tiny optional.
    static_assert(IsDisabledHash<TestClassWithInitializerList>);
    static_assert(IsDisabledHash<tiny::optional<TestClassWithInitializerList>>);
  }
}

void test_TinyOptional_CustomInplace()
{
  EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS(
      (tiny::optional_inplace<TestClass, FlagManipulatorForTestClass>{}),
      EXPECT_INPLACE,
      TestClass(true, 4.0),
      TestClass(true, 6.0),
      true,
      5.0);

  {
    // Test for the std::hash specialization
    static_assert(!IsDisabledHash<tiny::optional_inplace<TestClass, FlagManipulatorForTestClass>>);
    std::unordered_set<tiny::optional_inplace<TestClass, FlagManipulatorForTestClass>> const set
        = {TestClass(true, 42.0), std::nullopt, TestClass(true, 43.0)};
    ASSERT_TRUE(set.count(TestClass(true, 42.0)) > 0);
    ASSERT_TRUE(set.count(std::nullopt) > 0);
    ASSERT_TRUE(set.count(TestClass(true, 43.0)) > 0);
  }
}


void test_CrosscheckStdOptional()
{
  // We also run our generic tests with std::optional to cross-check that the tests themselves
  // do not test non-standard behavior.

  {
    std::vector<int> testValue1{1, 2, 3, 4};
    std::vector<int> testValue2{5, 6, 7};
    EXERCISE_OPTIONAL((std::optional<std::vector<int>>{}), EXPECT_SEPARATE, testValue1, testValue2);
  }

  {
    std::initializer_list<int> const initList = {3, 4, 5};
    EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS(
        (std::optional<TestClassWithInitializerList>{}),
        EXPECT_SEPARATE,
        TestClassWithInitializerList({1}),
        TestClassWithInitializerList({2}),
        initList,
        ScopedEnum::v2);
  }
}


namespace
{
struct Probe
{
  Probe() noexcept
  {
    created = true;
  }

  Probe(Probe const &) noexcept
  {
    created = true;
  }

  Probe(Probe &&) noexcept
  {
    created = true;
  }

  Probe & operator=(Probe const &) = default;
  Probe & operator=(Probe &&) = default;

  ~Probe()
  {
    destroyed = true;
  }

  inline static bool created = false;
  inline static bool destroyed = false;

  static void Reset()
  {
    created = false;
    destroyed = false;
  }
};
} // namespace


// Checks that the optional is properly calling the constructor and destructor.
void test_TinyOptionalMemoryManagement()
{
  Probe::Reset();
  Probe p;
  Probe::Reset();

  // reset() should destroy probe.
  {
    tiny::optional<Probe> o;
    ASSERT_FALSE(Probe::created);
    ASSERT_FALSE(Probe::destroyed);
    ASSERT_FALSE(o.has_value());

    o = p;
    ASSERT_TRUE(Probe::created);
    ASSERT_FALSE(Probe::destroyed);
    ASSERT_TRUE(o.has_value());

    o.reset();
    ASSERT_TRUE(Probe::destroyed);
    ASSERT_FALSE(o.has_value());
  }

  Probe::Reset();

  // Destructor of optional should destroy probe.
  {
    {
      tiny::optional<Probe> o;
      o = p;
      ASSERT_TRUE(Probe::created);
      ASSERT_FALSE(Probe::destroyed);
      ASSERT_TRUE(o.has_value());
    }
    ASSERT_TRUE(Probe::destroyed);
  }

  Probe::Reset();

  // Empty optional should not create nor destroy the probe.
  {
    {
      [[maybe_unused]] tiny::optional<Probe> o;
    }
    ASSERT_FALSE(Probe::created);
    ASSERT_FALSE(Probe::destroyed);
  }

  Probe::Reset();

  // Assigning an empty optional should destroy the probe.
  {
    tiny::optional<Probe> o;
    o = p;
    ASSERT_TRUE(Probe::created);
    ASSERT_FALSE(Probe::destroyed);
    ASSERT_TRUE(o.has_value());

    Probe::Reset();
    tiny::optional<Probe> empty;
    o = empty;
    ASSERT_TRUE(Probe::destroyed);
    ASSERT_FALSE(o.has_value());
  }

  Probe::Reset();

  // emplace() should destroy probe.
  {
    tiny::optional<Probe> o;
    o = p;
    ASSERT_TRUE(Probe::created);
    ASSERT_FALSE(Probe::destroyed);
    ASSERT_TRUE(o.has_value());

    Probe::Reset();

    o.emplace();
    ASSERT_TRUE(Probe::destroyed);
    ASSERT_TRUE(o.has_value());
  }

  Probe::Reset();
}


void test_Exceptions()
{
  struct ConstructorException : std::exception
  {
  };
  struct CopyException : std::exception
  {
  };
  struct AssignmentException : std::exception
  {
  };

  struct Throwing
  {
    explicit Throwing(int value, bool doThrow = true)
      : value(value)
    {
      if (doThrow) {
        throw ConstructorException();
      }
    }

    Throwing(Throwing const &)
    {
      throw CopyException();
    }

    Throwing operator=(Throwing const &)
    {
      throw AssignmentException();
    }

    int value;
  };

  {
    tiny::optional<Throwing> o;
    tiny::optional<Throwing> nonEmpty{std::in_place, 42, false};
    EXPECT_EXCEPTION(o = nonEmpty, CopyException);
    ASSERT_FALSE(o.has_value());

    EXPECT_EXCEPTION(o.emplace(43), ConstructorException);
    ASSERT_FALSE(o.has_value());
  }
  {
    tiny::optional<Throwing> o1{std::in_place, 42, false};
    tiny::optional<Throwing> o2{std::in_place, 43, false};

    EXPECT_EXCEPTION(o2 = o1, AssignmentException);
    ASSERT_TRUE(o2.has_value());
    ASSERT_TRUE(o2.value().value == 43); // o2 should still contain the old value.
  }
  {
    using std::swap;

    tiny::optional<Throwing> o;
    tiny::optional<Throwing> nonEmpty{std::in_place, 42, false};

    static_assert(!noexcept(o.swap(nonEmpty)));
    static_assert(!noexcept(swap(o, nonEmpty)));

    EXPECT_EXCEPTION(o.swap(nonEmpty), CopyException);
    ASSERT_FALSE(o.has_value());
    ASSERT_TRUE(nonEmpty.has_value());

    EXPECT_EXCEPTION(swap(nonEmpty, o), CopyException);
    ASSERT_FALSE(o.has_value());
    ASSERT_TRUE(nonEmpty.has_value());
  }
}


void test_TinyOptionalCopyConstruction()
{
  // Check that the copy constructor actually does copy the data (and does not move it).
  {
    tiny::optional<std::vector<int>> orig;
    orig.emplace({1, 2, 3, 4});
    ASSERT_TRUE(orig.has_value());
    ASSERT_FALSE(orig.value().empty());

    tiny::optional<std::vector<int>> copyTarget(orig);
    ASSERT_TRUE(copyTarget.has_value());
    ASSERT_FALSE(copyTarget.value().empty());
    ASSERT_TRUE((copyTarget.value() == std::vector<int>{1, 2, 3, 4}));

    ASSERT_TRUE(orig.has_value());
    ASSERT_TRUE((orig.value() == std::vector<int>{1, 2, 3, 4}));
  }

  // Check that tiny::optional is not copy constructible if the copy constructor is deleted.
  {
    struct DeletedCopy
    {
      DeletedCopy() = default;
      DeletedCopy(DeletedCopy const &) = delete;
      DeletedCopy(DeletedCopy &&) = default;
      DeletedCopy & operator=(DeletedCopy const &) = default;
      DeletedCopy & operator=(DeletedCopy &&) = default;
    };

    static_assert(!std::is_copy_constructible_v<tiny::optional<DeletedCopy>>);
    static_assert(std::is_swappable_v<tiny::optional<DeletedCopy>>);
  }
}


void test_TinyOptionalMoveConstruction()
{
  // Check that the move constructor really moves the data.
  {
    tiny::optional<std::vector<int>> orig;
    orig.emplace({1, 2, 3, 4});
    ASSERT_TRUE(orig.has_value());
    ASSERT_FALSE(orig.value().empty());

    tiny::optional<std::vector<int>> moveTarget(std::move(orig));
    ASSERT_TRUE(moveTarget.has_value());
    ASSERT_FALSE(moveTarget.value().empty());
    ASSERT_TRUE((moveTarget.value() == std::vector<int>{1, 2, 3, 4}));

    // According to the standard, the original should still have a value.
    // But it was moved from, so the vector should be empty.
    ASSERT_TRUE(orig.has_value());
    ASSERT_TRUE(orig.value().empty());
  }

  // Check that the noexcept specification of the move constructor is taken from the payload.
  {
    struct NothrowMove
    {
      NothrowMove(NothrowMove &&) noexcept(true) { }
    };
    static_assert(noexcept(tiny::optional<NothrowMove>(std::declval<tiny::optional<NothrowMove> &&>())));
  }
  {
    struct ThrowMove
    {
      ThrowMove(ThrowMove &&) noexcept(false) { }
    };
    static_assert(!noexcept(tiny::optional<ThrowMove>(std::declval<tiny::optional<ThrowMove> &&>())));
  }

  // Check that constructing the optional with another rvalue optional compiles even if the payload
  // has a deleted move constructor. I.e. it should call the copy constructor instead.
  {
    struct DeletedMove
    {
      DeletedMove() = default;
      DeletedMove(DeletedMove const &) = default;
      DeletedMove(DeletedMove &&) = delete;
      DeletedMove & operator=(DeletedMove const &) = delete;
      DeletedMove & operator=(DeletedMove &&) = delete;
    };

    static_assert(std::is_copy_constructible_v<tiny::optional<DeletedMove>>);
    static_assert(std::is_move_constructible_v<tiny::optional<DeletedMove>>);
    static_assert(!std::is_swappable_v<tiny::optional<DeletedMove>>);

    tiny::optional<DeletedMove> orig;
    [[maybe_unused]] tiny::optional<DeletedMove> moveTarget(std::move(orig));
  }

  // Check that move construction compiles if the copy constructor is deleted.
  {
    struct DeletedCopy
    {
      DeletedCopy() = default;
      DeletedCopy(DeletedCopy const &) = delete;
      DeletedCopy(DeletedCopy &&) = default;
      DeletedCopy & operator=(DeletedCopy const &) = delete;
      DeletedCopy & operator=(DeletedCopy &&) = delete;
    };

    static_assert(!std::is_copy_constructible_v<tiny::optional<DeletedCopy>>);
    static_assert(std::is_move_constructible_v<tiny::optional<DeletedCopy>>);
    static_assert(!std::is_swappable_v<tiny::optional<DeletedCopy>>);

    tiny::optional<DeletedCopy> orig;
    [[maybe_unused]] tiny::optional<DeletedCopy> moveTarget(std::move(orig));
  }
}


void test_TinyOptionalCopyAssignment()
{
  // Check that the copy assignment operator really copies the data (and does not move it).
  {
    tiny::optional<std::vector<int>> orig;
    orig.emplace({1, 2, 3, 4});
    ASSERT_TRUE(orig.has_value());
    ASSERT_FALSE(orig.value().empty());

    tiny::optional<std::vector<int>> copyTarget;
    copyTarget = orig;
    ASSERT_TRUE(copyTarget.has_value());
    ASSERT_FALSE(copyTarget.value().empty());
    ASSERT_TRUE((copyTarget.value() == std::vector<int>{1, 2, 3, 4}));

    ASSERT_TRUE(orig.has_value());
    ASSERT_TRUE((orig.value() == std::vector<int>{1, 2, 3, 4}));
  }

  // If the payload does have a copy assignment operator but is not copy constructible, the copy assignment operator of
  // tiny::optional should still be deleted. Reason: The copy assignment of tiny::optional might need to
  // construct a new payload object, if the optional was empty before. Similar for the assignment of a payload.
  {
    struct NotCopyConstructible
    {
      NotCopyConstructible(NotCopyConstructible const &) = delete;
      NotCopyConstructible(NotCopyConstructible &&) = delete;
      NotCopyConstructible & operator=(NotCopyConstructible &&) = default;
      NotCopyConstructible & operator=(NotCopyConstructible const &) = default;
    };
    // Cross-check properties of the test object.
    static_assert(!std::is_copy_constructible_v<NotCopyConstructible>);
    static_assert(std::is_copy_assignable_v<NotCopyConstructible>);

    // Actual check: Copy assignment
    static_assert(!std::is_copy_assignable_v<tiny::optional<NotCopyConstructible>>);

    // Actual check: Assignment of payload
    static_assert(!std::is_assignable_v<tiny::optional<NotCopyConstructible>, NotCopyConstructible>);
    static_assert(!std::is_assignable_v<tiny::optional<NotCopyConstructible>, NotCopyConstructible &>);
    static_assert(!std::is_assignable_v<tiny::optional<NotCopyConstructible>, NotCopyConstructible &&>);

    // Actual check: swappable
    static_assert(!std::is_swappable_v<tiny::optional<NotCopyConstructible>>);
  }

  // If the payload is copy constructible but not copy assignable, then the optional should not be copy assignable.
  {
    struct NotCopyAssignable
    {
      NotCopyAssignable(NotCopyAssignable const &) = default;
      NotCopyAssignable(NotCopyAssignable &&) = default;
      NotCopyAssignable & operator=(NotCopyAssignable &&) = default;
      NotCopyAssignable & operator=(NotCopyAssignable const &) = delete;
    };
    // Cross-check properties of the test object.
    static_assert(std::is_copy_constructible_v<NotCopyAssignable>);
    static_assert(!std::is_copy_assignable_v<NotCopyAssignable>);

    // Actual check
    static_assert(!std::is_copy_assignable_v<tiny::optional<NotCopyAssignable>>);

    // Actual check: swappable
    static_assert(std::is_swappable_v<tiny::optional<NotCopyAssignable>>);
  }
}


void test_TinyOptionalMoveAssignment()
{
  // Check that the move assignment really moves the data.
  {
    tiny::optional<std::vector<int>> orig;
    orig.emplace({1, 2, 3, 4});
    ASSERT_TRUE(orig.has_value());
    ASSERT_FALSE(orig.value().empty());

    tiny::optional<std::vector<int>> moveTarget;
    moveTarget = std::move(orig);
    ASSERT_TRUE(moveTarget.has_value());
    ASSERT_FALSE(moveTarget.value().empty());
    ASSERT_TRUE((moveTarget.value() == std::vector<int>{1, 2, 3, 4}));

    // According to the standard, the original should still have a value.
    // But it was moved from, so the vector should be empty.
    ASSERT_TRUE(orig.has_value());
    ASSERT_TRUE(orig.value().empty());
  }

  // If the payload does have an move assignment operator but is not move constructible, the move assignment operator of
  // tiny::optional should still be deleted. Reason: The move assignment of tiny::optional might need to
  // construct a new payload object, if the optional was empty before. Similar for the assignment and swap of a payload.
  {
    struct NotMoveConstructible
    {
      NotMoveConstructible(NotMoveConstructible const &) = delete;
      NotMoveConstructible(NotMoveConstructible &&) = delete;
      NotMoveConstructible & operator=(NotMoveConstructible &&) = default;
      NotMoveConstructible & operator=(NotMoveConstructible const &) = default;
    };
    // Cross-check properties of the test object.
    static_assert(!std::is_move_constructible_v<NotMoveConstructible>);
    static_assert(std::is_move_assignable_v<NotMoveConstructible>);

    // Actual check: Move assignment
    static_assert(!std::is_move_assignable_v<tiny::optional<NotMoveConstructible>>);

    // Actual check: Assignment of payload
    static_assert(!std::is_assignable_v<tiny::optional<NotMoveConstructible>, NotMoveConstructible>);
    static_assert(!std::is_assignable_v<tiny::optional<NotMoveConstructible>, NotMoveConstructible &>);
    static_assert(!std::is_assignable_v<tiny::optional<NotMoveConstructible>, NotMoveConstructible &&>);

    // Actual check: Not swappable
    static_assert(!std::is_swappable_v<tiny::optional<NotMoveConstructible>>);
  }

  // If the payload is move constructible but not move assignable, then the optional should not be move assignable.
  {
    struct NotMoveAssignable
    {
      NotMoveAssignable(NotMoveAssignable const &) = delete;
      NotMoveAssignable(NotMoveAssignable &&) = default;
      NotMoveAssignable & operator=(NotMoveAssignable &&) = delete;
      NotMoveAssignable & operator=(NotMoveAssignable const &) = default;
    };
    // Cross-check properties of the test object.
    static_assert(std::is_move_constructible_v<NotMoveAssignable>);
    static_assert(!std::is_move_assignable_v<NotMoveAssignable>);

    // Actual check
    static_assert(!std::is_move_assignable_v<tiny::optional<NotMoveAssignable>>);

    // Actual check: Not swappable
    static_assert(!std::is_swappable_v<tiny::optional<NotMoveAssignable>>);
  }

  // Check that the noexcept specification of the move assignment operator is taken from the payload.
  {
    struct NothrowMove
    {
      NothrowMove(NothrowMove &&) noexcept(true) { }
      NothrowMove & operator=(NothrowMove &&) noexcept(true)
      {
        return *this;
      }
    };
    static_assert(
        noexcept(std::declval<tiny::optional<NothrowMove> &>() = std::declval<tiny::optional<NothrowMove> &&>()));
  }
  {
    struct ThrowMove
    {
      ThrowMove(ThrowMove &&) noexcept(false) { }
      ThrowMove & operator=(ThrowMove &&) noexcept(false)
      {
        return *this;
      }
    };
    static_assert(
        !noexcept(std::declval<tiny::optional<ThrowMove> &>() = std::declval<tiny::optional<ThrowMove> &&>()));
  }
  {
    struct ThrowMoveConstructionNoThrowMoveAssignment
    {
      ThrowMoveConstructionNoThrowMoveAssignment(ThrowMoveConstructionNoThrowMoveAssignment &&) noexcept(false) { }
      ThrowMoveConstructionNoThrowMoveAssignment & operator=(ThrowMoveConstructionNoThrowMoveAssignment &&) noexcept(
          true)
      {
        return *this;
      }
    };
    static_assert(!noexcept(
        std::declval<tiny::optional<ThrowMoveConstructionNoThrowMoveAssignment> &>()
        = std::declval<tiny::optional<ThrowMoveConstructionNoThrowMoveAssignment> &&>()));
  }
  {
    struct NoThrowMoveConstructionThrowMoveAssignment
    {
      NoThrowMoveConstructionThrowMoveAssignment(NoThrowMoveConstructionThrowMoveAssignment &&) noexcept(true) { }
      NoThrowMoveConstructionThrowMoveAssignment & operator=(NoThrowMoveConstructionThrowMoveAssignment &&) noexcept(
          false)
      {
        return *this;
      }
    };
    static_assert(!noexcept(
        std::declval<tiny::optional<NoThrowMoveConstructionThrowMoveAssignment> &>()
        = std::declval<tiny::optional<NoThrowMoveConstructionThrowMoveAssignment> &&>()));
  }

  // Check that move assignment compiles if the copy assignment operator is deleted.
  {
    struct DeletedCopy
    {
      DeletedCopy() = default;
      DeletedCopy(DeletedCopy const &) = delete;
      DeletedCopy(DeletedCopy &&) = default;
      DeletedCopy & operator=(DeletedCopy const &) = delete;
      DeletedCopy & operator=(DeletedCopy &&) = default;
    };

    static_assert(!std::is_copy_constructible_v<tiny::optional<DeletedCopy>>);
    static_assert(!std::is_copy_assignable_v<tiny::optional<DeletedCopy>>);

    static_assert(std::is_move_constructible_v<tiny::optional<DeletedCopy>>);
    static_assert(std::is_move_assignable_v<tiny::optional<DeletedCopy>>);

    static_assert(std::is_swappable_v<tiny::optional<DeletedCopy>>);

    tiny::optional<DeletedCopy> orig;
    tiny::optional<DeletedCopy> moveTarget;
    moveTarget = std::move(orig);
  }
}


void test_TinyOptionalConversions()
{
  {
    struct ImplicitConversion
    {
      // Note: Not specified as 'explicit'
      ImplicitConversion(int v)
        : value(v)
      {
      }
      int value;
    };

    static_assert(std::is_constructible_v<tiny::optional<ImplicitConversion>, int>);

    // The following two constructions always compile, regardless if the constructor is explicit or not.
    tiny::optional<ImplicitConversion> o1(42);
    ASSERT_TRUE(o1.value().value == 42);
    tiny::optional<ImplicitConversion> o2{42};
    ASSERT_TRUE(o2.value().value == 42);

    // The following two constructions would not compile if the payload had an explicit constructor.
    tiny::optional<ImplicitConversion> o3 = 42;
    ASSERT_TRUE(o3.value().value == 42);
    tiny::optional<ImplicitConversion> o4 = {42};
    ASSERT_TRUE(o4.value().value == 42);

    // Assignment of payload also performs the implicit conversion. Would not compile if the payload had an explicit
    // constructor.
    tiny::optional<ImplicitConversion> o5;
    o5 = 42;
    ASSERT_TRUE(o5.value().value == 42);
  }

  {
    struct ExplicitConversion
    {
      explicit ExplicitConversion(int v)
        : value(v)
      {
      }
      int value;
    };

    static_assert(std::is_constructible_v<tiny::optional<ExplicitConversion>, int>);

    // The following two constructions always compile, regardless of the explicit
    tiny::optional<ExplicitConversion> o1(42);
    ASSERT_TRUE(o1.value().value == 42);
    tiny::optional<ExplicitConversion> o2{42};
    ASSERT_TRUE(o2.value().value == 42);

    // The following two constructions do not compile as the payload has an explicit constructor.
    // We check this in the compilation-error checks.
    // tiny::optional<ExplicitConversion> o3 = 42;
    // tiny::optional<ExplicitConversion> o4 = {42};

    // Similar, the assignment of payload does not perform the implicit conversion. The following would not compile.
    // tiny::optional<ExplicitConversion> o5;
    // o5 = 42;
    // ASSERT_TRUE(o5.value().value == 42);
  }

  {
    // Cross-check that the typetrait std::is_constructible works as expected.
    static_assert(!std::is_constructible_v<tiny::optional<TestClass>, int>);
  }
}


void test_MakeOptional()
{
  //--------- Test first version of make_optional
  {
    auto o = tiny::make_optional(42.0);
    static_assert(sizeof(o) == sizeof(double));
    static_assert(std::is_same_v<decltype(o)::value_type, double>);
    ASSERT_TRUE(o.value() == 42.0);
  }
  {
    auto o = tiny::make_optional(42);
    static_assert(sizeof(o) == sizeof(std::optional<int>));
    static_assert(std::is_same_v<decltype(o)::value_type, int>);
    ASSERT_TRUE(o.value() == 42);
  }
  {
    auto o = tiny::make_optional<unsigned int, 0>(42u);
    static_assert(sizeof(o) == sizeof(unsigned int));
    static_assert(std::is_same_v<decltype(o)::value_type, unsigned int>);
    ASSERT_TRUE(o.value() == 42u);
  }
  {
    TestClassForInplace const testValue{};
    auto o = tiny::make_optional<TestClassForInplace, &TestClassForInplace::someValue1, 42>(testValue);
    static_assert(sizeof(o) == sizeof(TestClassForInplace));
    static_assert(std::is_same_v<decltype(o)::value_type, TestClassForInplace>);
    ASSERT_TRUE(o.value() == testValue);
  }
  {
    auto ptr = std::make_unique<int>(42);
    auto o = tiny::make_optional(std::move(ptr));
    ASSERT_TRUE(*o.value() == 42u);
    ASSERT_TRUE(ptr == nullptr);
  }

  //--------- Test second version of make_optional
  {
    auto o = tiny::make_optional<TestClassForInplace>(2, 5.0, 43u, nullptr);
    static_assert(sizeof(o) == sizeof(std::optional<TestClassForInplace>));
    static_assert(std::is_same_v<decltype(o)::value_type, TestClassForInplace>);
    ASSERT_TRUE(o.value() == TestClassForInplace(2, 5.0, 43u, nullptr));
  }
  {
    auto o = tiny::make_optional<TestClassForInplace, &TestClassForInplace::someValue1, 42>(2, 5.0, 43u, nullptr);
    static_assert(sizeof(o) == sizeof(TestClassForInplace));
    static_assert(std::is_same_v<decltype(o)::value_type, TestClassForInplace>);
    ASSERT_TRUE(o.value() == TestClassForInplace(2, 5.0, 43u, nullptr));
  }

  //--------- Test third version of make_optional
  {
    std::initializer_list<int> const initList = {3, 4, 5};
    auto o = tiny::make_optional<TestClassWithInitializerList>(initList);
    static_assert(sizeof(o) == sizeof(std::optional<TestClassWithInitializerList>));
    static_assert(std::is_same_v<decltype(o)::value_type, TestClassWithInitializerList>);
    ASSERT_TRUE(o.value() == TestClassWithInitializerList{initList});
  }
  {
    std::initializer_list<int> const initList = {3, 4, 5};
    auto o = tiny::make_optional<TestClassWithInitializerList>(initList, ScopedEnum::v2);
    static_assert(sizeof(o) == sizeof(std::optional<TestClassWithInitializerList>));
    static_assert(std::is_same_v<decltype(o)::value_type, TestClassWithInitializerList>);
    ASSERT_TRUE(o.value() == TestClassWithInitializerList(initList, ScopedEnum::v2));
  }
}


template <class Opt1, class Opt2, class Val1, class Val2, class Comparer>
void TestCompareOptWithOpt(Val1 val1, Val2 val2, Comparer comparer)
{
  std::cout << "\tComparison '" << typeid(Comparer).name() << "':\n\t\tOpt1='" << typeid(Opt1).name() << "' and Opt2='"
            << typeid(Opt2).name() << "'\n\t\tval1='" << val1 << "' and val2='" << val2 << "'" << std::endl;

  Opt1 const tiny1{val1};
  Opt2 const tiny2{val2};
  std::optional<typename Opt1::value_type> const std1{val1};
  std::optional<typename Opt2::value_type> const std2{val2};

  ASSERT_TRUE(comparer(tiny1, tiny2) == comparer(std1, std2));
  ASSERT_TRUE(comparer(tiny2, tiny1) == comparer(std2, std1));
}


template <class Opt1, class Val1, class Val2, class Comparer>
void TestCompareOptWithValue(Val1 val1, Val2 val2, Comparer comparer)
{
  std::cout << "\tComparison '" << typeid(Comparer).name() << "':\n\t\tOpt1='" << typeid(Opt1).name() << "'\n\t\tval1='"
            << val1 << "' and val2='" << val2 << "'" << std::endl;

  Opt1 const tiny1{val1};
  std::optional<typename Opt1::value_type> const std1{val1};

  ASSERT_TRUE(comparer(tiny1, val2) == comparer(std1, val2));
  ASSERT_TRUE(comparer(val2, tiny1) == comparer(val2, std1));
}


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

    // Comparison between tiny::optional and std::optional
    (TestCompareOptWithOpt<tiny::optional<int>, std::optional<int>>(42, 42, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<int>, std::optional<int>>(42, 999, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<int, 1>, std::optional<int>>(42, 1, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<int>, std::optional<int>>(std::nullopt, std::nullopt, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<int>, std::optional<int>>(42, std::nullopt, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<int>, std::optional<int>>(std::nullopt, 42, comparer), ...);

    // Comparison between tiny::optional and tiny::optional_empty_via_type.
    // clang-format off
    (TestCompareOptWithOpt<tiny::optional<int>, tiny::optional_empty_via_type<int, std::integral_constant<int, 1>>>(42, 42, comparer), ...);
    // clang-format on

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
    static constexpr double NaN = std::numeric_limits<double>::quiet_NaN();
    (TestCompareOptWithOpt<tiny::optional<double>, tiny::optional<double>>(42, NaN, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<double>, tiny::optional<double>>(NaN, NaN, comparer), ...);
    (TestCompareOptWithOpt<tiny::optional<double>, tiny::optional<double>>(std::nullopt, NaN, comparer), ...);
    (TestCompareOptWithValue<tiny::optional<double>>(42, NaN, comparer), ...);
    (TestCompareOptWithValue<tiny::optional<double>>(NaN, NaN, comparer), ...);
    (TestCompareOptWithValue<tiny::optional<double>>(std::nullopt, NaN, comparer), ...);

    // Comparisons for optional_empty_via_type.
    using OptionalIntViaType = tiny::optional_empty_via_type<int, std::integral_constant<int, 1>>;
    (TestCompareOptWithOpt<OptionalIntViaType, OptionalIntViaType>(42, 43, comparer), ...);
    (TestCompareOptWithOpt<OptionalIntViaType, tiny::optional_empty_via_type<double, TestDoubleValue>>(
         42,
         43,
         comparer),
     ...);
    (TestCompareOptWithValue<OptionalIntViaType>(42, 999, comparer), ...);
    (TestCompareOptWithValue<OptionalIntViaType>(42, std::nullopt, comparer), ...);

    // Rough cross check that the tests also work with std::optional
    (TestCompareOptWithOpt<std::optional<int>, std::optional<int>>(42, 42, comparer), ...);
    (TestCompareOptWithOpt<std::optional<int>, std::optional<double>>(42, 999.0, comparer), ...);
    (TestCompareOptWithOpt<std::optional<int>, std::optional<double>>(42, NaN, comparer), ...);
    (TestCompareOptWithOpt<std::optional<int>, std::optional<int>>(42, std::nullopt, comparer), ...);
    (TestCompareOptWithValue<std::optional<int>>(42, 999, comparer), ...);
    (TestCompareOptWithValue<std::optional<int>>(std::nullopt, 42, comparer), ...);
    (TestCompareOptWithValue<std::optional<int>>(42, std::nullopt, comparer), ...);
  };


  runAllComparisons(
      std::equal_to<>(),
      std::not_equal_to<>(),
      std::less<>(),
      std::less_equal<>(),
      std::greater<>(),
      std::greater_equal<>());
}


void test_ExpressionsThatShouldNotCompile()
{
  // clang-format off
  std::vector<std::pair<std::string /*toCompile*/, std::string /*expectedErrorRegex*/>> const checks = {
    {/*code*/ "struct TestClass{};\n"
              "tiny::optional_empty_via_type<TestClass, TestClass> o;",
     /*expected regex*/ "The payload type does not support an inplace flag.*you specified an EmptyValue, which is inconistent and unnecessary"}
    
    ,

    {/*code*/ "tiny::optional<unsigned, -1> o;",
     /*expected regex*/ "The specified compile-time constant for the empty value is outside of the range supported"}
    
    ,

    {/*code*/ "struct TestClassForInplace { int someValue1 = -1; };\n"
              "tiny::optional<TestClassForInplace, &TestClassForInplace::someValue1> o;",
     /*expected regex*/ "The type of the member variable given by the member-pointer cannot be used as flag if you do not specify a custom EmptyValue"}
    
    ,

    {/*code*/ "struct TestClassForInplace { double someValue1 = 0.0; };\n"
              "struct TestClass{};\n"
              "tiny::optional_empty_via_type<TestClass, tiny::UseDefaultType, &TestClassForInplace::someValue1> o;",
     /*expected regex*/ "The flag given by the member-pointer is not a member of the payload type"}
    
    ,

    {/*code*/ "struct TestClassForInplace { int someValue1 = -1; };\n"
              "struct TestClass{};\n"
              "tiny::optional_empty_via_type<TestClass, std::integral_constant<int, 42>, &TestClassForInplace::someValue1> o;",
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
     // First for MSVC, second for clang, third for gcc.
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
     // First for MSVC, second for clang, third for gcc.
     /*expected regex*/ "(copy-list-initialization.*cannot.*use.*an.*explicit.*constructor)|(constructor.*is.*explicit.*in.*copy-initialization)|(error.*could.*not.*convert)"}
    
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
      std::cerr << "before CheckDoesNotCompile" << std::endl;
      auto result = checker->CheckDoesNotCompile(toCompile, expectedErrorRegex);
      std::cerr << "after CheckDoesNotCompile" << std::endl;
      return result;
    };

    checkResults.push_back(std::async(cRunSerial ? std::launch::deferred : std::launch::async, std::move(threadFunc)));
  }
  assert(checkResults.size() == checks.size());

  bool foundFailure = false;
  for (size_t idx = 0; idx < checkResults.size(); ++idx) {
    std::cout << "\tCompilation check " << idx + 1 << "/" << checks.size() << std::endl;
    std::cerr << "before checkResults.get()" << std::endl;
    auto const result = checkResults.at(idx).get();
    std::cerr << "after checkResults.get()" << std::endl;
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


void RunTests()
{
#define ADD_TEST(x) {x, #x}

  std::vector<std::pair<void (*)(), std::string>> const tests
      = {ADD_TEST(test_IsIntegralInRange),
         ADD_TEST(test_NanExploit),
         ADD_TEST(test_SelectDecomposition),
         ADD_TEST(test_NanExploit),
         ADD_TEST(test_TinyOptional),
         ADD_TEST(test_TinyOptional_EmptyValueViaType),
         ADD_TEST(test_TinyOptional_CustomInplace),
         ADD_TEST(test_CrosscheckStdOptional),
         ADD_TEST(test_TinyOptionalMemoryManagement),
         ADD_TEST(test_TinyOptionalCopyConstruction),
         ADD_TEST(test_TinyOptionalMoveConstruction),
         ADD_TEST(test_TinyOptionalCopyAssignment),
         ADD_TEST(test_TinyOptionalMoveAssignment),
         ADD_TEST(test_TinyOptionalConversions),
         ADD_TEST(test_Exceptions),
         ADD_TEST(test_MakeOptional),
         ADD_TEST(test_Comparisons),
         ADD_TEST(test_ExpressionsThatShouldNotCompile)};

  for (size_t testIdx = 0; testIdx < tests.size(); ++testIdx) {
    auto const [testFunc, testName] = tests.at(testIdx);
    std::cout << "Running: " << testName << std::endl;
    testFunc();
  }
}


int main()
{
  try {
    std::cout << "Running tests..." << std::endl;
    RunTests();
    std::cout << "All tests PASSED" << std::endl;
    return 0;
  }
  catch (std::exception const & ex) {
    std::cerr << "Caught exception: " << ex.what() << " (type: " << typeid(ex).name() << ")" << std::endl;
    assert(false);
    exit(44);
  }
  catch (...) {
    std::cerr << "Caught unknown exception." << std::endl;
    assert(false);
    exit(45);
  }
}
