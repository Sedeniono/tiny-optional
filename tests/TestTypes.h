#pragma once

#include "TestUtilities.h"

#include <initializer_list>
#include <vector>

#if defined(__GNUG__) && !defined(__clang__)
// Disable incorrect warning for gcc.
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

enum class ScopedEnum
{
  v1,
  v2,
  vend
};


enum UnscopedEnum
{
  UE_v1,
  UE_v2,
  UE_end
};


struct TestClass
{
  bool IsValid() const noexcept
  {
    return isValid;
  }

  bool isValid = false;
  double someValue = 0.0;

  friend bool operator==(TestClass const & lhs, TestClass const & rhs)
  {
    return lhs.isValid == rhs.isValid && MatchingFloat(lhs.someValue, rhs.someValue);
  }

  TestClass() = default;

  TestClass(bool isValid, double someValue)
    : isValid(isValid)
    , someValue(someValue)
  {
  }
};

namespace std
{
template <>
struct hash<TestClass>
{
  size_t operator()(TestClass const & v) const
  {
    size_t s = 0;
    hash_combine(s, v.isValid);
    hash_combine(s, v.someValue);
    return s;
  }
};
} // namespace std


struct FlagManipulatorForTestClass
{
  [[nodiscard]] static bool is_empty(TestClass const & flag) noexcept
  {
    return !flag.IsValid();
  }

  static void init_empty_flag(TestClass & uninitializedFlagMemory) noexcept
  {
    // Placement new because memory is already allocated.
    ::new (&uninitializedFlagMemory) TestClass();
  }

  static void invalidate_empty_flag(TestClass & emptyFlag) noexcept
  {
    // Freeing memory is handled by the TinyOptional implementation.
    emptyFlag.~TestClass();
  }
};


struct TestClassForInplace
{
  int someInt = -1;
  unsigned someUnsigned = 3;
  double someDouble = 1.0;
  float someFloat = 2.0;
  bool someBool = false;
  TestClassForInplace * somePtr = nullptr;

  friend bool operator==(TestClassForInplace const & lhs, TestClassForInplace const & rhs)
  {
    return lhs.someInt == rhs.someInt && lhs.someUnsigned == rhs.someUnsigned
           && MatchingFloat(lhs.someDouble, rhs.someDouble) && MatchingFloat(lhs.someFloat, rhs.someFloat)
           && lhs.someBool == rhs.someBool && lhs.somePtr == rhs.somePtr;
  }

  TestClassForInplace() = default;

  TestClassForInplace(int someValue1, double someValue2, unsigned someValue3, TestClassForInplace * someValue4)
    : someInt(someValue1)
    , someUnsigned(someValue3)
    , someDouble(someValue2)
    , somePtr(someValue4)
  {
  }
};

namespace std
{
template <>
struct hash<TestClassForInplace>
{
  size_t operator()(TestClassForInplace const & v) const
  {
    size_t s = 0;
    hash_combine(s, v.someInt);
    hash_combine(s, v.someUnsigned);
    hash_combine(s, v.someDouble);
    hash_combine(s, v.someFloat);
    hash_combine(s, v.someBool);
    hash_combine(s, v.somePtr);
    return s;
  }
};
} // namespace std


struct TestClassWithInitializerList
{
  std::vector<int> values;

  TestClassWithInitializerList(std::initializer_list<int> v)
    : values(v)
  {
  }

  TestClassWithInitializerList(std::initializer_list<int> v, ScopedEnum anotherValue)
    : values(v)
  {
    values.emplace_back(static_cast<int>(anotherValue));
  }

  friend bool operator==(TestClassWithInitializerList const & lhs, TestClassWithInitializerList const & rhs)
  {
    return lhs.values == rhs.values;
  }
};


struct TestClassPrivate
{
  friend bool operator==(TestClassPrivate const & lhs, TestClassPrivate const & rhs)
  {
    return MatchingFloat(lhs.someValue, rhs.someValue);
  }

  friend void test_TinyOptionalPayload_OtherTypes();

  TestClassPrivate()
    : someValue(-1.0)
  {
  }

  explicit TestClassPrivate(double value)
    : someValue(value)
  {
  }

private:
  double someValue;
};


// Various stuff is noexcept(false)
struct TestClassWithExcept
{
  TestClassWithExcept() noexcept(false) { }

  TestClassWithExcept(int value) noexcept(false)
    : someValue(value)
  {
  }

  TestClassWithExcept(TestClassWithExcept const & rhs) noexcept(false)
    : someValue(rhs.someValue)
  {
  }

  TestClassWithExcept & operator=(TestClassWithExcept const & rhs) noexcept(false)
  {
    someValue = rhs.someValue;
    return *this;
  }

  friend bool operator==(TestClassWithExcept const & lhs, TestClassWithExcept const & rhs)
  {
    return lhs.someValue == rhs.someValue;
  }

  int someValue = 42;
};


typedef int (*TestFuncPtr)(double, TestClass &);

inline int TestFunc1(double, TestClass &)
{
  return -1;
}

inline int TestFunc2(double, TestClass &)
{
  return -1;
}


struct TestDoubleValue
{
  static constexpr double value = 42.0;
};


// Used for C++20 tests where we specify a sentinel value at compile to be an instance of this class.
struct LiteralClass
{
  constexpr LiteralClass(int v1, double v2)
    : v1(v1)
    , v2(v2)
  {
  }

  // Not default so that we have a non-trivial copy constructor.
  constexpr LiteralClass(LiteralClass const & rhs)
    : v1(rhs.v1)
    , v2(rhs.v2)
  {
  }

  // Not default so that we have a non-trivial copy assignment.
  constexpr LiteralClass & operator=(LiteralClass const & rhs) noexcept
  {
    v1 = rhs.v1;
    v2 = rhs.v2;
    return *this;
  }

  int v1;
  double v2;
};

inline constexpr bool operator==(LiteralClass const & lhs, LiteralClass const & rhs) noexcept
{
  return lhs.v1 == rhs.v1 && lhs.v2 == rhs.v2;
}


// Used for C++20 tests where we specify a sentinel value at compile to be an instance of this class, and stored in the
// member lc.
struct TestClassWithLiteralClass
{
  TestClassWithLiteralClass()
    : TestClassWithLiteralClass(1, 2.0, 3)
  {
  }

  TestClassWithLiteralClass(int v1, double v2, int v3)
    : lc(v1, v2)
    , someInt(v3)
  {
  }

  LiteralClass lc;
  int someInt;
};

inline bool operator==(TestClassWithLiteralClass const & lhs, TestClassWithLiteralClass const & rhs)
{
  return lhs.lc == rhs.lc && lhs.someInt == rhs.someInt;
}

#if defined(__GNUG__) && !defined(__clang__)
  #pragma GCC diagnostic pop
#endif
