#include "NatvisTests.h"

#include "TestTypes.h"
#include "tiny/optional.h"

#include <optional>


namespace
{
struct ClassWithCustomManip
{
  std::string someString = "someString";
  int someInt = 42;
};

inline const std::string CLASS_SENTINEL = "SENTINEL";
} // namespace


template <>
struct tiny::optional_flag_manipulator<ClassWithCustomManip>
{
  static bool is_empty(ClassWithCustomManip const & payload) noexcept
  {
    return payload.someString == CLASS_SENTINEL;
  }

  static void init_empty_flag(ClassWithCustomManip & uninitializedPayloadMemory) noexcept
  {
    ::new (&uninitializedPayloadMemory) ClassWithCustomManip{CLASS_SENTINEL};
  }

  static void invalidate_empty_flag(ClassWithCustomManip & emptyPayload) noexcept
  {
    emptyPayload.~ClassWithCustomManip();
  }
};


namespace
{
enum class TestEnum
{
  VALUE1,
  VALUE2,
  INVALID
};
} // namespace


template <>
struct tiny::optional_flag_manipulator<TestEnum> : tiny::sentinel_flag_manipulator<TestEnum, TestEnum::INVALID>
{
};


// We cannot really run automated tests for Visual Studio natvis files. The code here serves as convenient
// place to stop the Visual Studio debugger and step through the lines, manually observing the displayed
// values to check that natvis works.
void test_Natvis()
{
  // Not in-place (i.e. not compressed)
  {
    tiny::optional<unsigned> empty;
    tiny::optional<unsigned> nonEmpty = 42;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }

  // Special built-in sentinels.
  {
    tiny::optional<bool> empty;
    tiny::optional<bool> nonEmpty = true;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    tiny::optional<double> empty;
    tiny::optional<double> nonEmpty = 42.0;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    tiny::optional<float> empty;
    tiny::optional<float> nonEmpty = 42.0f;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    tiny::optional<TestClass *> empty;
    tiny::optional<TestClass *> nonEmpty = nullptr;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    TestClass c;
    tiny::optional<TestClass *> empty;
    tiny::optional<TestClass *> nonEmpty = &c;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }

  // These have specializations of tiny::optional_flag_manipulator.
  {
    tiny::optional<ClassWithCustomManip> empty;
    tiny::optional<ClassWithCustomManip> nonEmpty = ClassWithCustomManip{};
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    tiny::optional<TestEnum> empty;
    tiny::optional<TestEnum> nonEmpty = TestEnum::VALUE2;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }

  // In-place with custom sentinel
  {
    tiny::optional<unsigned, 999> empty;
    tiny::optional<unsigned> nonEmpty = 42;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }

  // In-place in member variable
  {
    tiny::optional<TestClassForInplace, &TestClassForInplace::someValue2> empty;
    tiny::optional<TestClassForInplace, &TestClassForInplace::someValue2> nonEmpty = TestClassForInplace{};
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    tiny::optional<TestClassForInplace, &TestClassForInplace::someValue3, 42> empty;
    tiny::optional<TestClassForInplace, &TestClassForInplace::someValue3, 42> nonEmpty = TestClassForInplace{};
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
}
