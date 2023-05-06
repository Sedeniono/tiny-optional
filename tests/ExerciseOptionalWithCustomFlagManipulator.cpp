#include "ExerciseOptionalWithCustomFlagManipulator.h"

#include "Exercises.h"
#include "TestUtilities.h"
#include "tiny/optional.h"

#include <memory>
#include <string>


namespace
{
//====================================================================
// Example class in a namespace: Test::Class1
//====================================================================

namespace Test
{
  struct Class1
  {
    std::string someString;
    int someInt = 42;
    double someDouble = 42.2;

    Class1()
      : someString("someString")
    {
    }

    explicit Class1(std::string const & s)
      : someString(s)
    {
    }

    friend bool operator==(Class1 const & lhs, Class1 const & rhs)
    {
      return lhs.someString == rhs.someString && lhs.someInt == rhs.someInt && lhs.someDouble == rhs.someDouble;
    }
  };
} // namespace Test

inline const std::string CLASS1_SENTINEL = "SENTINEL";
} // namespace


template <>
struct tiny::optional_flag_manipulator<Test::Class1>
{
  static bool IsEmpty(Test::Class1 const & payload) noexcept
  {
    return payload.someString == CLASS1_SENTINEL;
  }

  static void InitializeIsEmptyFlag(Test::Class1 & uninitializedPayloadMemory) noexcept
  {
    ::new (&uninitializedPayloadMemory) Test::Class1(CLASS1_SENTINEL);
  }

  static void PrepareIsEmptyFlagForPayload(Test::Class1 & emptyPayload) noexcept
  {
    emptyPayload.~Class1();
  }
};


//====================================================================
// Example class: Class2 (contains Class1)
//====================================================================

namespace
{
struct Class2
{
  int member1 = 999;
  Test::Class1 member2;

  Class2() = default;

  Class2(int i, std::string const & s)
    : member1(i)
    , member2(s)
  {
  }

  friend bool operator==(Class2 const & lhs, Class2 const & rhs)
  {
    return lhs.member1 == rhs.member1 && lhs.member2 == rhs.member2;
  }
};
} // namespace


//====================================================================
// Example class: OuterClass::NestedClass
// Especially note: GetTinyOptionalInplaceFlagManipulator() is defined as friend.
//====================================================================

namespace
{
struct OuterClass
{
  struct NestedClass
  {
    bool isEmpty = false;

    friend bool operator==(NestedClass const & lhs, NestedClass const & rhs)
    {
      return lhs.isEmpty == rhs.isEmpty;
    }
  };

  NestedClass nestedClass;

  friend bool operator==(OuterClass const & lhs, OuterClass const & rhs)
  {
    return lhs.nestedClass == rhs.nestedClass;
  }
};
} // namespace


template <>
struct tiny::optional_flag_manipulator<OuterClass::NestedClass>
{
  static bool IsEmpty(OuterClass::NestedClass const & payload) noexcept
  {
    return payload.isEmpty;
  }

  static void InitializeIsEmptyFlag(OuterClass::NestedClass & uninitializedPayloadMemory) noexcept
  {
    ::new (&uninitializedPayloadMemory) OuterClass::NestedClass();
    uninitializedPayloadMemory.isEmpty = true;
  }

  static void PrepareIsEmptyFlagForPayload(OuterClass::NestedClass & emptyPayload) noexcept
  {
    emptyPayload.~NestedClass();
  }
};


//====================================================================
// Example class: OutermostClass
//====================================================================

namespace
{
struct OutermostClass
{
  std::shared_ptr<std::string> someString;
  OuterClass outerClass;

  explicit OutermostClass(std::string const & s)
    : someString(std::make_shared<std::string>(s))
  {
  }

  friend bool operator==(OutermostClass const & lhs, OutermostClass const & rhs)
  {
    if (lhs.outerClass == rhs.outerClass) {
      if (lhs.someString == nullptr && rhs.someString == nullptr) {
        return true;
      }
      else if (lhs.someString != nullptr && rhs.someString != nullptr) {
        return *lhs.someString == *rhs.someString;
      }
    }

    return false;
  }
};
} // namespace


// Exploiting undefined behavior: In the empty state of the optional, we do not construct a full instance of
// OutermostClass. Instead, we only change the 'payload.outerClass.nestedClass.isEmpty'
template <>
struct tiny::optional_flag_manipulator<OutermostClass>
{
  static bool IsEmpty(OutermostClass const & payload) noexcept
  {
    return payload.outerClass.nestedClass.isEmpty;
  }

  static void InitializeIsEmptyFlag(OutermostClass & uninitializedPayloadMemory) noexcept
  {
    ::new (&uninitializedPayloadMemory.outerClass.nestedClass.isEmpty) bool(true);
  }

  static void PrepareIsEmptyFlagForPayload(OutermostClass & /*emptyPayload*/) noexcept { }
};


//====================================================================
// Example enums
//====================================================================

namespace
{
namespace EnumNamespace
{
  enum TestUnscopedEnum
  {
    INVALID = -1,
    UNSCOPED_VALUE1,
    UNSCOPED_VALUE2
  };
}
}

template <>
struct tiny::optional_flag_manipulator<EnumNamespace::TestUnscopedEnum>
{
  static bool IsEmpty(EnumNamespace::TestUnscopedEnum const & payload) noexcept
  {
    return payload == EnumNamespace::INVALID;
  }

  static void InitializeIsEmptyFlag(EnumNamespace::TestUnscopedEnum & uninitializedPayloadMemory) noexcept
  {
    ::new (&uninitializedPayloadMemory) EnumNamespace::TestUnscopedEnum(EnumNamespace::INVALID);
  }

  static void PrepareIsEmptyFlagForPayload(EnumNamespace::TestUnscopedEnum & /*emptyPayload*/) noexcept { }
};


namespace
{
enum class TestScopedEnum
{
  VALUE1,
  VALUE2,
  MAX_NUM
};
}


template <>
struct tiny::optional_flag_manipulator<TestScopedEnum>
{
  static bool IsEmpty(TestScopedEnum const & payload) noexcept
  {
    return payload == TestScopedEnum::MAX_NUM;
  }

  static void InitializeIsEmptyFlag(TestScopedEnum & uninitializedPayloadMemory) noexcept
  {
    ::new (&uninitializedPayloadMemory) TestScopedEnum(TestScopedEnum::MAX_NUM);
  }

  static void PrepareIsEmptyFlagForPayload(TestScopedEnum & /*emptyPayload*/) noexcept { }
};


//====================================================================
// Tests of the types
//====================================================================

void test_TinyOptionalWithRegisteredCustomFlagManipulator()
{
  // Basic test: Especially EXPECT_INPLACE, since the tiny::optional should use the flag manipulator.
  {
    EXERCISE_OPTIONAL((tiny::optional<Test::Class1>{}), EXPECT_INPLACE, Test::Class1{"val1"}, Test::Class1{"val2"});
  }

  // Storing the 'IsEmpty' flag in Class2::member2, which should be possible because of the flag manipulator for the
  // type of member2, i.e. of Class1.
  {
    EXERCISE_OPTIONAL(
        (tiny::optional<Class2, &Class2::member2>{}),
        EXPECT_INPLACE,
        Class2(42, "val1"),
        Class2(43, "val2"));
  }

  // We specify some member in Class1 where the IsEmpty flag should be stored. Thus, tiny::optional should actually
  // ignore the flag manipulator and use the sentinel instead. Thus, the special "SENTINEL" string is expected to be a
  // valid value.
  {
    EXERCISE_OPTIONAL(
        (tiny::optional<Test::Class1, &Test::Class1::someDouble>{}),
        EXPECT_INPLACE,
        Test::Class1(CLASS1_SENTINEL),
        Test::Class1("val2"));

    EXERCISE_OPTIONAL(
        (tiny::optional<Test::Class1, &Test::Class1::someInt, -1>{}),
        EXPECT_INPLACE,
        Test::Class1(CLASS1_SENTINEL),
        Test::Class1("val2"));
  }

  // Test with a NestedClass.
  {
    EXERCISE_OPTIONAL(
        (tiny::optional<OuterClass::NestedClass>{}),
        EXPECT_INPLACE,
        OuterClass::NestedClass{},
        OuterClass::NestedClass{});
  }

  // Test where we exploit some undefined behavior so as not to construct the full payload while the optional is in the
  // empty state.
  {
    EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS(
        (tiny::optional<OutermostClass>{}),
        EXPECT_INPLACE,
        OutermostClass{"val1"},
        OutermostClass{"val2"},
        "val3");
  }

  // Version with a **const** payload: Since we do not provide a specialization of the flag manipulator for const
  // payloads, we expect that the library uses a separate bool to indicate the empty state.
  {
    EXERCISE_OPTIONAL(
        (tiny::optional<Test::Class1 const>{}),
        EXPECT_SEPARATE,
        Test::Class1{"val1"},
        Test::Class1{"val2"});
  }

  // Version where, at the point of definition, the "tiny/optional.h" header is not included.
  {
    EXERCISE_OPTIONAL((tiny::optional<ClassInHeader>{}), EXPECT_INPLACE, ClassInHeader{}, ClassInHeader{});
  }

  // Enums
  {
    EXERCISE_OPTIONAL(
        (tiny::optional<EnumNamespace::TestUnscopedEnum>{}),
        EXPECT_INPLACE,
        EnumNamespace::UNSCOPED_VALUE1,
        EnumNamespace::UNSCOPED_VALUE2);
    EXERCISE_OPTIONAL(
        (tiny::optional<TestScopedEnum>{}),
        EXPECT_INPLACE,
        TestScopedEnum::VALUE1,
        TestScopedEnum::VALUE2);
  }
}
