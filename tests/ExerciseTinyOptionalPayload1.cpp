#include "ExerciseTinyOptionalPayload.h"

#include "Exercises.h"
#include "TestTypes.h"
#include "TestUtilities.h"
#include "tiny/optional.h"


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



