#pragma once

#include "TestUtilities.h"

#include <iostream>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>


#if defined(TINY_OPTIONAL_GCC_BUILD) && defined(TINY_OPTIONAL_WINDOWS_BUILD)
  // mingw gcc 12.1 prints this warning for the swap test with TestClassForInplace.
  // It is a false positive.
  #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif


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
