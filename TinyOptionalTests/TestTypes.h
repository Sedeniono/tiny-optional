#pragma once

#include "TestUtilities.h"

#include <initializer_list>
#include <vector>


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
  [[nodiscard]] static bool IsEmpty(TestClass const & flag) noexcept
  {
    return !flag.IsValid();
  }

  static void InitializeIsEmptyFlag(TestClass & uninitializedFlagMemory) noexcept
  {
    // Placement new because memory is already allocated.
    ::new (&uninitializedFlagMemory) TestClass();
  }

  static void PrepareIsEmptyFlagForPayload(TestClass & emptyFlag) noexcept
  {
    // Freeing memory is handled by the TinyOptional implementation.
    emptyFlag.~TestClass();
  }
};




struct TestClassForInplace
{
  int someValue1 = -1;
  double someValue2 = 1.0;
  unsigned someValue3 = 3;
  TestClassForInplace * someValue4 = nullptr;

  friend bool operator==(TestClassForInplace const & lhs, TestClassForInplace const & rhs)
  {
    return lhs.someValue1 == rhs.someValue1 && MatchingFloat(lhs.someValue2, rhs.someValue2)
           && lhs.someValue3 == rhs.someValue3 && lhs.someValue4 == rhs.someValue4;
  }

  TestClassForInplace() = default;

  TestClassForInplace(int someValue1, double someValue2, unsigned someValue3, TestClassForInplace * someValue4)
    : someValue1(someValue1)
    , someValue2(someValue2)
    , someValue3(someValue3)
    , someValue4(someValue4)
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
    hash_combine(s, v.someValue1);
    hash_combine(s, v.someValue2);
    hash_combine(s, v.someValue3);
    hash_combine(s, v.someValue4);
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

  friend void test_TinyOptional();

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
  TestClassWithExcept() noexcept(false)
  {
  }

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

