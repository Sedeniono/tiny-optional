#include "ExerciseTinyOptionalPayload.h"
#include "Exercises.h"
#include "TestTypes.h"
#include "TestUtilities.h"
#include "tiny/optional.h"

#include <unordered_set>


void test_TinyOptionalPayload_IsEmptyFlagInMember()
{
  // Exploiting a member to place the IsEmpty flag

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

  EXERCISE_OPTIONAL(
      (tiny::optional<TestClassForInplace, &TestClassForInplace::someValue4>{}),
      EXPECT_INPLACE,
      TestClassForInplace{},
      TestClassForInplace(43, 44.0, 45, nullptr));
}

void test_TinyOptionalPayload_Pointers()
{
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
    int i = 0;
    int j = 42;
    EXERCISE_OPTIONAL((tiny::optional<void *>{}), EXPECT_INPLACE, static_cast<void *>(&i), &j);
    EXERCISE_OPTIONAL((tiny::optional<void *>{}), EXPECT_INPLACE, nullptr, static_cast<void *>(&i));
  }

  // Function pointers
  {
    EXERCISE_OPTIONAL((tiny::optional<TestFuncPtr>{}), EXPECT_INPLACE, &TestFunc1, &TestFunc2);
    EXERCISE_OPTIONAL((tiny::optional<TestFuncPtr>{}), EXPECT_INPLACE, nullptr, &TestFunc2);
  }
}

void test_TinyOptionalPayload_StdTypes()
{
  // Tests of various std types

  {
    std::vector<int> testValue1{1, 2, 3, 4};
    std::vector<int> testValue2{5, 6, 7};
    EXERCISE_OPTIONAL((tiny::optional<std::vector<int>>{}), EXPECT_SEPARATE, testValue1, testValue2);
    EXERCISE_OPTIONAL((tiny::optional{testValue1}), EXPECT_SEPARATE, testValue1, testValue2);
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
