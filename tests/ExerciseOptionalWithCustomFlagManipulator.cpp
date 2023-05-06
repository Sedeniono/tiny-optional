#include "Exercises.h"
#include "TestUtilities.h"
#include "tiny/optional.h"

#include <memory>
#include <string>


namespace
{
//====================================================================
// Example class: Test::Class1
//====================================================================
namespace Test
{
  struct Class1FlagManipulator;


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


  // Key line: Allows tiny::optional to find Class1FlagManipulator.
  [[maybe_unused]] Class1FlagManipulator GetTinyOptionalInplaceFlagManipulator(Class1 const &);

  struct Class1FlagManipulator
  {
    static inline const std::string SENTINEL = "SENTINEL";

    static bool IsEmpty(Class1 const & payload) noexcept
    {
      return payload.someString == SENTINEL;
    }

    static void InitializeIsEmptyFlag(Class1 & uninitializedPayloadMemory) noexcept
    {
      ::new (&uninitializedPayloadMemory) Class1(SENTINEL);
    }

    static void PrepareIsEmptyFlagForPayload(Class1 & emptyPayload) noexcept
    {
      emptyPayload.~Class1();
    }
  };
} // namespace Test


//====================================================================
// Example class: Class2 (contains Class1)
//====================================================================

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


//====================================================================
// Example class: OuterClass::NestedClass
// Especially note: GetTinyOptionalInplaceFlagManipulator() is defined as friend.
//====================================================================

struct NestedClassFlagManipulator;

struct OuterClass
{
  struct NestedClass
  {
    bool isEmpty = false;

    // Key line: Allows tiny::optional to find NestedClassFlagManipulator.
    friend NestedClassFlagManipulator GetTinyOptionalInplaceFlagManipulator(NestedClass const &);

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


// Silence clang warning:
// function 'GetTinyOptionalInplaceFlagManipulator' is not needed and will not be emitted
// [-Wunneeded-internal-declaration]
[[maybe_unused]] NestedClassFlagManipulator GetTinyOptionalInplaceFlagManipulator(OuterClass::NestedClass const &);


struct NestedClassFlagManipulator
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


// Exploiting undefined behavior: In the empty state of the optional, we do not construct a full instance of
// OutermostClass. Instead, we only change the 'payload.outerClass.nestedClass.isEmpty'
struct OutermostFlagManipulator
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


// Key line: Allows tiny::optional to find OutermostFlagManipulator.
[[maybe_unused]] OutermostFlagManipulator GetTinyOptionalInplaceFlagManipulator(OutermostClass const &);


} // namespace


//====================================================================
// Tests of the types
//====================================================================

void test_TinyOptionalWithRegisteredCustomFlagManipulator()
{
  // Basic test: Especially EXPECT_INPLACE, since the tiny::optional should use the Class1FlagManipulator.
  {
    Test::Class1 const val1{"Value1"};
    Test::Class1 const val2{"Value2"};
    EXERCISE_OPTIONAL((tiny::optional<Test::Class1>{}), EXPECT_INPLACE, val1, val2);
    EXERCISE_OPTIONAL((tiny::optional<Test::Class1 const>{}), EXPECT_INPLACE, val1, val2);
  }

  // Storing the 'IsEmpty' flag in Class2::member2, which should be possible because of the Class1FlagManipulator.
  {
    EXERCISE_OPTIONAL(
        (tiny::optional<Class2, &Class2::member2>{}),
        EXPECT_INPLACE,
        Class2(42, "val1"),
        Class2(43, "val2"));
  }

  // We specify some member in Class1 where the IsEmpty flag should be stored. Thus, tiny::optional should actually
  // ignore Class1FlagManipulator and use the sentinel instead. Thus, the special "SENTINEL" string is expected to be a
  // valid value.
  {
    EXERCISE_OPTIONAL(
        (tiny::optional<Test::Class1, &Test::Class1::someDouble>{}),
        EXPECT_INPLACE,
        Test::Class1(Test::Class1FlagManipulator::SENTINEL),
        Test::Class1("val2"));

    EXERCISE_OPTIONAL(
        (tiny::optional<Test::Class1, &Test::Class1::someInt, -1>{}),
        EXPECT_INPLACE,
        Test::Class1(Test::Class1FlagManipulator::SENTINEL),
        Test::Class1("val2"));
  }

  // Test with a NestedClass, where the FlagManipulator is defined as friend function. Despite being a friend function,
  // ADL should find it.
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
}
