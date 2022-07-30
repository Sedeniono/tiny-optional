#include "ExerciseStdOptional.h"

#include "Exercises.h"
#include "TestTypes.h"
#include "tiny/optional.h"

#include <unordered_set>

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

  EXERCISE_OPTIONAL((std::optional<double volatile>{}), EXPECT_SEPARATE, 43.0, 44.0);
  static_assert(std::is_same_v<std::optional<double volatile>::value_type, double volatile>);
}
