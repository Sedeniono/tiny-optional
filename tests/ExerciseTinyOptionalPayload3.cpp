#include "ExerciseTinyOptionalPayload.h"
#include "Exercises.h"
#include "TestTypes.h"
#include "TestUtilities.h"
#include "tiny/optional.h"


void test_TinyOptionalPayload_NestedOptionals()
{
  // Tests of nested optionals. These basically check that the various constructors are not ambiguous.
  {
    tiny::optional<double> tiny1{43.0};
    tiny::optional<double> tiny2{44.0};
    tiny::optional<double> tinyEmpty;
    EXERCISE_OPTIONAL((tiny::optional<tiny::optional<double>>{}), EXPECT_SEPARATE, tiny1, tiny2);
    EXERCISE_OPTIONAL((tiny::optional<tiny::optional<double>>{}), EXPECT_SEPARATE, tinyEmpty, tiny2);

    EXERCISE_OPTIONAL((std::optional<tiny::optional<double>>{}), EXPECT_SEPARATE, tiny1, tiny2);
    EXERCISE_OPTIONAL((std::optional<tiny::optional<double>>{}), EXPECT_SEPARATE, tinyEmpty, tiny2);

    std::optional<double> std1{43.0};
    std::optional<double> std2{44.0};
    std::optional<double> stdEmpty;
    EXERCISE_OPTIONAL((tiny::optional<std::optional<double>>{}), EXPECT_SEPARATE, std1, std2);
    EXERCISE_OPTIONAL((tiny::optional<std::optional<double>>{}), EXPECT_SEPARATE, stdEmpty, std2);
  }
}

void test_TinyOptionalPayload_ConstAndVolatile()
{
  // Tests of const and volatile
  EXERCISE_OPTIONAL((tiny::optional<double const>{}), EXPECT_INPLACE, 43.0, 44.0);
  static_assert(std::is_same_v<tiny::optional<double const>::value_type, double const>);
  EXERCISE_OPTIONAL((tiny::optional<double volatile>{}), EXPECT_INPLACE, 43.0, 44.0);
  static_assert(std::is_same_v<tiny::optional<double volatile>::value_type, double volatile>);
  EXERCISE_OPTIONAL((tiny::optional<double const volatile>{}), EXPECT_INPLACE, 43.0, 44.0);
  static_assert(std::is_same_v<tiny::optional<double const volatile>::value_type, double const volatile>);

  EXERCISE_OPTIONAL((tiny::optional<int const, 42>{}), EXPECT_INPLACE, 43, 44);
  static_assert(std::is_same_v<tiny::optional<int const>::value_type, int const>);
  EXERCISE_OPTIONAL((tiny::optional<int volatile, 42>{}), EXPECT_INPLACE, 43, 44);
  static_assert(std::is_same_v<tiny::optional<int volatile>::value_type, int volatile>);
  EXERCISE_OPTIONAL((tiny::optional<int const volatile, 42>{}), EXPECT_INPLACE, 43, 44);
  static_assert(std::is_same_v<tiny::optional<int const volatile>::value_type, int const volatile>);

  EXERCISE_OPTIONAL((tiny::optional<int const>{}), EXPECT_SEPARATE, 43, 44);
  static_assert(std::is_same_v<tiny::optional<int const>::value_type, int const>);
  EXERCISE_OPTIONAL((tiny::optional<int volatile>{}), EXPECT_SEPARATE, 43, 44);
  static_assert(std::is_same_v<tiny::optional<int volatile>::value_type, int volatile>);
  EXERCISE_OPTIONAL((tiny::optional<int const volatile>{}), EXPECT_SEPARATE, 43, 44);
  static_assert(std::is_same_v<tiny::optional<int const volatile>::value_type, int const volatile>);
}

void test_TinyOptionalPayload_Cpp20NTTP()
{
  // Non type template parameters supported since C++20.
  // C++20 allows using floating point values and literal class types in templates.
  // Unfortunately, even clang 14 does yet support it.
#if defined(TINY_OPTIONAL_CPP20) && !defined(TINY_OPTIONAL_CLANG_BUILD)
  {
    // Floating point, directly in the payload
    EXERCISE_OPTIONAL((tiny::optional<float, 42.0f>{}), EXPECT_INPLACE, 43.0f, 44.0f);
    EXERCISE_OPTIONAL((tiny::optional<double, 42.0>{}), EXPECT_INPLACE, 43.0, 44.0);
    EXERCISE_OPTIONAL((tiny::optional<long double, 42.0L>{}), EXPECT_INPLACE, 43.0L, 44.0L);

    // Floating point, stored in member.
    EXERCISE_OPTIONAL(
        (tiny::optional<TestClassForInplace, &TestClassForInplace::someValue2, 42.0>{}),
        EXPECT_INPLACE,
        TestClassForInplace{},
        TestClassForInplace(43, 44.0, 45, nullptr));

    // Literal class, directly as payload.
    constexpr LiteralClass lc1(42, 43.0);
    constexpr LiteralClass lc2(44, 45.0);
    constexpr LiteralClass lc3(46, 47.0);
    EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS((tiny::optional<LiteralClass, lc1>{}), EXPECT_INPLACE, lc2, lc3, 48, 49.0);

    // Literal class, stored in member.
    EXERCISE_OPTIONAL(
        (tiny::optional<TestClassWithLiteralClass, &TestClassWithLiteralClass::lc, lc1>{}),
        EXPECT_INPLACE,
        TestClassWithLiteralClass{},
        TestClassWithLiteralClass(43, 44.0, 45));
  }
#endif
}

