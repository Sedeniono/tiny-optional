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

  {
    {
      struct UniqueObjectRepr
      {
        int i1 = 0;
        int i2 = 0;

        bool operator==(UniqueObjectRepr const & rhs) const
        {
          return i1 == rhs.i1 && i2 == rhs.i2;
        }
      };

      struct UniqueObjectReprFlagManipulator
      {
        static bool is_empty(UniqueObjectRepr const & flag) noexcept
        {
          return flag.i1 == -1;
        }

        static void init_empty_flag(UniqueObjectRepr & uninitializedFlagMemory) noexcept
        {
          ::new (&uninitializedFlagMemory) UniqueObjectRepr{-1, 0};
        }

        static void invalidate_empty_flag(UniqueObjectRepr & emptyFlag) noexcept
        {
          emptyFlag.~UniqueObjectRepr();
        }
      };

      static_assert(std::has_unique_object_representations_v<UniqueObjectRepr>);
      EXERCISE_OPTIONAL(
          (tiny::optional_inplace<UniqueObjectRepr, UniqueObjectReprFlagManipulator>{}),
          EXPECT_INPLACE,
          UniqueObjectRepr{1},
          UniqueObjectRepr{2});
#ifdef TINY_OPTIONAL_TRIVIAL_SPECIAL_MEMBER_FUNCTIONS
      static_assert(std::is_trivially_copy_constructible_v<tiny::optional<UniqueObjectRepr>>);
      static_assert(std::is_trivially_move_constructible_v<tiny::optional<UniqueObjectRepr>>);
      static_assert(std::is_trivially_move_assignable_v<tiny::optional<UniqueObjectRepr>>);
      static_assert(std::is_trivially_move_assignable_v<tiny::optional<UniqueObjectRepr>>);
#endif
    }
  }
}
