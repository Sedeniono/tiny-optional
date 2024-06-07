#include "ExerciseOptionalAIP.h"

#include "Exercises.h"
#include "TestTypes.h"
#include "tiny/optional.h"

void test_OptionalAIP()
{
  //----------------------
  // Tests with automatic selection of the sentinel

#ifndef TINY_OPTIONAL_USE_SEPARATE_BOOL_INSTEAD_OF_UNUSED_BITS
  EXERCISE_OPTIONAL((tiny::optional_aip<double>{}), EXPECT_INPLACE, 43.0, 44.0);
#endif

  EXERCISE_OPTIONAL((tiny::optional_aip<short>{}), EXPECT_INPLACE, static_cast<short>(-10), static_cast<short>(42));
  EXERCISE_OPTIONAL(
      (tiny::optional_aip<unsigned short>{}),
      EXPECT_INPLACE,
      static_cast<unsigned short>(10),
      static_cast<unsigned short>(42));

  EXERCISE_OPTIONAL((tiny::optional_aip<int>{}), EXPECT_INPLACE, -10, 42);
  EXERCISE_OPTIONAL((tiny::optional_aip<unsigned int>{}), EXPECT_INPLACE, 10u, 42u);

  EXERCISE_OPTIONAL((tiny::optional_aip<long>{}), EXPECT_INPLACE, -10l, 42l);
  EXERCISE_OPTIONAL((tiny::optional_aip<unsigned long>{}), EXPECT_INPLACE, 10ul, 42ul);

  EXERCISE_OPTIONAL((tiny::optional_aip<long long>{}), EXPECT_INPLACE, -10ll, 42ll);
  EXERCISE_OPTIONAL((tiny::optional_aip<unsigned long long>{}), EXPECT_INPLACE, 10ull, 42ull);

#ifndef TINY_OPTIONAL_USE_SEPARATE_BOOL_INSTEAD_OF_UNUSED_BITS
  TestClass c1, c2;
  EXERCISE_OPTIONAL((tiny::optional_aip<TestClass *>{}), EXPECT_INPLACE, &c1, &c2);
#endif

  //----------------------
  // Tests with manual specification of sentinel

  EXERCISE_OPTIONAL((tiny::optional_aip<int, -1>{}), EXPECT_INPLACE, INT_MIN, INT_MAX);

  EXERCISE_OPTIONAL((tiny::optional_aip<char, 'a'>{}), EXPECT_INPLACE, 'b', 'c');
  EXERCISE_OPTIONAL(
      (tiny::optional_aip<ScopedEnum, ScopedEnum::vend>{}),
      EXPECT_INPLACE,
      ScopedEnum::v2,
      ScopedEnum::v1);
}
