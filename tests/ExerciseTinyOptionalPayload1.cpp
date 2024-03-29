#include "ExerciseTinyOptionalPayload.h"
#include "Exercises.h"
#include "TestTypes.h"
#include "TestUtilities.h"
#include "tiny/optional.h"

#include <cmath>
#include <limits>
#include <unordered_set>


void test_TinyOptionalPayload_Bool()
{
  EXERCISE_OPTIONAL((tiny::optional<bool>{}), EXPECT_INPLACE, false, true);
  EXERCISE_OPTIONAL((tiny::optional<bool>{}), EXPECT_INPLACE, true, false);
  EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS((tiny::optional<bool, true>{}), EXPECT_INPLACE, false, false, false);
  EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS((tiny::optional<bool, false>{}), EXPECT_INPLACE, true, true, true);
  EXERCISE_OPTIONAL((tiny::optional{false}), EXPECT_INPLACE, false, true); // Uses deduction guide
}


void test_TinyOptionalPayload_FloatingPoint()
{
  EXERCISE_OPTIONAL((tiny::optional<double>{}), EXPECT_INPLACE, 43.0, 44.0);
  EXERCISE_OPTIONAL((tiny::optional<double>{}), EXPECT_INPLACE, std::numeric_limits<double>::quiet_NaN(), 44.0);
  EXERCISE_OPTIONAL((tiny::optional<double>{}), EXPECT_INPLACE, std::numeric_limits<double>::signaling_NaN(), 44.0);
  EXERCISE_OPTIONAL((tiny::optional{100.0}), EXPECT_INPLACE, 43.0, 44.0); // Uses deduction guide

  EXERCISE_OPTIONAL((tiny::optional<float>{}), EXPECT_INPLACE, 43.0f, 44.0f);
  EXERCISE_OPTIONAL((tiny::optional<float>{}), EXPECT_INPLACE, std::numeric_limits<float>::quiet_NaN(), 44.0f);
  EXERCISE_OPTIONAL((tiny::optional<float>{}), EXPECT_INPLACE, NAN, 44.0f);
  EXERCISE_OPTIONAL((tiny::optional<float>{}), EXPECT_INPLACE, std::numeric_limits<float>::signaling_NaN(), 44.0f);
  EXERCISE_OPTIONAL((tiny::optional{100.0f}), EXPECT_INPLACE, 43.0f, 44.0f); // Uses deduction guide

  EXERCISE_OPTIONAL((tiny::optional<long double>{}), EXPECT_SEPARATE, 43.0L, 44.0L);
}


void test_TinyOptionalPayload_IntegersAndEnums()
{
  EXERCISE_OPTIONAL((tiny::optional<int>{}), EXPECT_SEPARATE, 42, 43);
  EXERCISE_OPTIONAL((tiny::optional{100}), EXPECT_SEPARATE, 42, 43); // Uses deduction guide

  EXERCISE_OPTIONAL((tiny::optional<int, 42>{}), EXPECT_INPLACE, 43, 44);
  EXERCISE_OPTIONAL((tiny::optional<unsigned, (std::numeric_limits<unsigned>::max)()>{}), EXPECT_INPLACE, 43u, 44u);

  EXERCISE_OPTIONAL((tiny::optional<char, (std::numeric_limits<char>::max)()>{}), EXPECT_INPLACE, (char)43, (char)44);
  EXERCISE_OPTIONAL((tiny::optional<char, 'z'>{}), EXPECT_INPLACE, 'a', 'b');
  EXERCISE_OPTIONAL((tiny::optional{'c'}), EXPECT_SEPARATE, 'a', 'b'); // Uses deduction guide

  EXERCISE_OPTIONAL((tiny::optional<std::byte, std::byte{255}>{}), EXPECT_INPLACE, std::byte{42}, std::byte{43});

  EXERCISE_OPTIONAL((tiny::optional<ScopedEnum, ScopedEnum::vend>{}), EXPECT_INPLACE, ScopedEnum::v2, ScopedEnum::v1);
  EXERCISE_OPTIONAL((tiny::optional<UnscopedEnum, UE_end>{}), EXPECT_INPLACE, UE_v2, UE_v1);
}


void test_TinyOptionalPayload_IsEmptyFlagInMember()
{
  // Exploiting a member to place the IsEmpty flag

  EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS(
      (tiny::optional<TestClassForInplace, &TestClassForInplace::someInt, 42>{}),
      EXPECT_INPLACE,
      TestClassForInplace{},
      TestClassForInplace(43, 44.0, 45, nullptr),
      2,
      5.0,
      43u,
      nullptr);

  EXERCISE_OPTIONAL(
      (tiny::optional<TestClassForInplace, &TestClassForInplace::someDouble>{}),
      EXPECT_INPLACE,
      TestClassForInplace{},
      TestClassForInplace(43, 44.0, 45, nullptr));

  EXERCISE_OPTIONAL(
      (tiny::optional<TestClassForInplace, &TestClassForInplace::somePtr>{}),
      EXPECT_INPLACE,
      TestClassForInplace{},
      TestClassForInplace(43, 44.0, 45, nullptr));
}


void test_TinyOptionalPayload_Pointers()
{
  // Ordinary pointers
  {
    TestClass c1, c2;
    EXERCISE_OPTIONAL((tiny::optional<TestClass *>{}), EXPECT_INPLACE, &c1, &c2);
    EXERCISE_OPTIONAL((tiny::optional<TestClass *>{}), EXPECT_INPLACE, nullptr, &c1);
    EXERCISE_OPTIONAL((tiny::optional{&c1}), EXPECT_INPLACE, &c1, &c2); // Uses deduction guide
    EXERCISE_OPTIONAL((tiny::optional<TestClass const *>{}), EXPECT_INPLACE, nullptr, &c1);
    EXERCISE_OPTIONAL((tiny::optional<TestClass volatile const *>{}), EXPECT_INPLACE, nullptr, &c1);
    EXERCISE_OPTIONAL((tiny::optional<TestClass volatile *>{}), EXPECT_INPLACE, nullptr, &c1);
  }

  {
    TestClass c1, c2;
    EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS((tiny::optional<TestClass *, nullptr>{}), EXPECT_INPLACE, &c1, &c2, &c1);
    // The following should trigger the assert that reset() should be used instead.
    // ExerciseOptional<TestClass*>(o, nullptr);
  }

  // Also test void*, just for the sake of it.
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

  // Member pointers
  {
    // MSVC has a bug here: https://stackoverflow.com/q/76182002/3740047. The expression 'new MemberPointer()' (which
    // appears in the form of a placement new internally) is not zero initialized if the list of arguments to the '()'
    // is empty.
#ifndef TINY_OPTIONAL_MSVC_BUILD
    EXERCISE_OPTIONAL((tiny::optional<double TestClass::*>{}), EXPECT_SEPARATE, &TestClass::someValue, nullptr);
#endif

    // Version where we pass nullptr explicitly to the constructors instead of an empty argument list, to work around
    // the above mentioned compiler bug.
    EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS(
        (tiny::optional<double TestClass::*>{}),
        EXPECT_SEPARATE,
        &TestClass::someValue,
        nullptr,
        nullptr);
  }

  // Member function pointers
  {
    EXERCISE_OPTIONAL(
        (tiny::optional<bool (TestClass::*)() const noexcept>{}),
        EXPECT_SEPARATE,
        &TestClass::IsValid,
        nullptr);
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
    static_assert(!IsDisabledHash<tiny::optional<TestClassForInplace, &TestClassForInplace::someInt, 42>>);
    std::unordered_set<tiny::optional<TestClassForInplace, &TestClassForInplace::someInt, 42>> const set
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
