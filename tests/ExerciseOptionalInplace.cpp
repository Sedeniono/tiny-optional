#include "ExerciseOptionalInplace.h"

#include "Exercises.h"
#include "TestTypes.h"
#include "tiny/optional.h"

#include <unordered_set>

void test_OptionalInplace()
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
