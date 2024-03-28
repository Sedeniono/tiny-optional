#include "ExerciseOptionalEmptyViaType.h"

#include "Exercises.h"
#include "TestTypes.h"
#include "tiny/optional.h"

#include <unordered_set>

void test_OptionalEmptyViaType()
{
  EXERCISE_OPTIONAL((tiny::optional_sentinel_via_type<bool, tiny::UseDefaultType>{}), EXPECT_INPLACE, false, true);
  EXERCISE_OPTIONAL((tiny::optional_sentinel_via_type<bool, tiny::UseDefaultType>{}), EXPECT_INPLACE, true, false);

  EXERCISE_OPTIONAL((tiny::optional_sentinel_via_type<double, tiny::UseDefaultType>{}), EXPECT_INPLACE, 43.0, 44.0);
  EXERCISE_OPTIONAL((tiny::optional_sentinel_via_type<float, tiny::UseDefaultType>{}), EXPECT_INPLACE, 43.0f, 44.0f);

  EXERCISE_OPTIONAL((tiny::optional_sentinel_via_type<int, tiny::UseDefaultType>{}), EXPECT_SEPARATE, 43, 44);
  EXERCISE_OPTIONAL((tiny::optional_sentinel_via_type<int, std::integral_constant<int, 42>>{}), EXPECT_INPLACE, 43, 44);

  EXERCISE_OPTIONAL(
      (tiny::optional_sentinel_via_type<
          TestClassForInplace,
          std::integral_constant<int, 42>,
          &TestClassForInplace::someInt>{}),
      EXPECT_INPLACE,
      TestClassForInplace{},
      TestClassForInplace(43, 44.0, 45, nullptr));

  EXERCISE_OPTIONAL(
      (tiny::optional_sentinel_via_type<TestClass, tiny::UseDefaultType>{}),
      EXPECT_SEPARATE,
      TestClass(true, 4.0),
      TestClass(true, 5.0));

  EXERCISE_OPTIONAL((tiny::optional_sentinel_via_type<double, TestDoubleValue>{}), EXPECT_INPLACE, 43.0, 44.0);

  EXERCISE_OPTIONAL(
      (tiny::optional_sentinel_via_type<TestClassForInplace, TestDoubleValue, &TestClassForInplace::someDouble>{}),
      EXPECT_INPLACE,
      TestClassForInplace{},
      TestClassForInplace(43, 44.0, 45, nullptr));

  {
    // Test for the std::hash specialization
    static_assert(!IsDisabledHash<tiny::optional_sentinel_via_type<double, TestDoubleValue>>);
    std::unordered_set<tiny::optional_sentinel_via_type<double, TestDoubleValue>> const set = {43.0, std::nullopt, 44.0};
    ASSERT_TRUE(set.count(43.0) > 0);
    ASSERT_TRUE(set.count(std::nullopt) > 0);
    ASSERT_TRUE(set.count(44.0) > 0);
  }
  {
    // We did not specialize std::hash for TestClassWithInitializerList, so neither should tiny optional.
    static_assert(IsDisabledHash<TestClassWithInitializerList>);
    static_assert(IsDisabledHash<tiny::optional_sentinel_via_type<TestClassWithInitializerList, tiny::UseDefaultType>>);
  }
}
