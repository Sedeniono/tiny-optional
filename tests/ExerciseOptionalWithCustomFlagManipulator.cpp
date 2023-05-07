#include "ExerciseOptionalWithCustomFlagManipulator.h"

#include "Exercises.h"
#include "TestUtilities.h"
#include "tiny/optional.h"

#include <memory>
#include <string>

#if defined(__GNUG__) && !defined(__clang__)
// Disable incorrect warning for gcc.
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif


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
} // namespace


template <>
struct tiny::optional_flag_manipulator<EnumNamespace::TestUnscopedEnum>
  : tiny::sentinel_flag_manipulator<EnumNamespace::TestUnscopedEnum, EnumNamespace::INVALID>
{
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
  : tiny::sentinel_flag_manipulator<TestScopedEnum, TestScopedEnum::MAX_NUM>
{
};


//====================================================================
// Specialization via enable_if, which uses the 2nd template argument of optional_flag_manipulator.
// For this we simply use enums since they are more convenient than creating two full blown classes.
//====================================================================

namespace
{
enum class SpecialEnum1 : int
{
  VALUE1 = 0,
  VALUE2 = 1
};


enum class SpecialEnum2 : int
{
  VALUE1 = 0,
  VALUE2 = 1
};
} // namespace


template <class SpecialEnumType>
struct tiny::optional_flag_manipulator<
    SpecialEnumType,
    std::enable_if_t<std::is_same_v<SpecialEnumType, SpecialEnum1> || std::is_same_v<SpecialEnumType, SpecialEnum2>>>
{
  static bool IsEmpty(SpecialEnumType const & payload) noexcept
  {
    return static_cast<int>(payload) == -1;
  }

  static void InitializeIsEmptyFlag(SpecialEnumType & uninitializedPayloadMemory) noexcept
  {
    ::new (&uninitializedPayloadMemory) SpecialEnumType(static_cast<SpecialEnumType>(-1));
  }

  static void PrepareIsEmptyFlagForPayload(SpecialEnumType & emptyPayload) noexcept
  {
    emptyPayload.~SpecialEnumType();
  }
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
    EXERCISE_OPTIONAL(
        (tiny::optional<ClassInHeader<int>>{}),
        EXPECT_INPLACE,
        ClassInHeader<int>{},
        ClassInHeader<int>{});
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

  // Cases where the flag manipulator specialization was defined with the help of std::enable_if.
  {
    EXERCISE_OPTIONAL((tiny::optional<SpecialEnum1>{}), EXPECT_INPLACE, SpecialEnum1::VALUE1, SpecialEnum1::VALUE2);
    EXERCISE_OPTIONAL((tiny::optional<SpecialEnum2>{}), EXPECT_INPLACE, SpecialEnum2::VALUE1, SpecialEnum2::VALUE2);
  }

  // A special test for transform(): It always returns a tiny::optional. Nevertheless, it should see
  // the flag manipulator.
  {
    tiny::optional<Test::Class1> opt1 = Test::Class1{"val1"};
    auto const opt2 = opt1.transform([](Test::Class1 const & c1) { return OutermostClass{c1.someString}; });
    static_assert(sizeof(opt1) == sizeof(Test::Class1));
    static_assert(sizeof(opt2) == sizeof(OutermostClass));
    static_assert(std::is_same_v<std::remove_cv_t<decltype(opt2)>, tiny::optional<OutermostClass>>);
    ASSERT_TRUE(opt2->someString != nullptr);
    ASSERT_TRUE(opt1->someString == *opt2->someString);
  }

  // Test that tiny::optional_aip picks up the tiny::optional_flag_manipulator specialization and uses it. If it did
  // not, we would get a compilation error here.
  {
    EXERCISE_OPTIONAL((tiny::optional_aip<Test::Class1>{}), EXPECT_INPLACE, Test::Class1{"val1"}, Test::Class1{"val2"});
  }
}

#if defined(__GNUG__) && !defined(__clang__)
  #pragma GCC diagnostic pop
#endif
