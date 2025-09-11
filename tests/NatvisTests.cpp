#include "NatvisTests.h"

#include "TestTypes.h"
#include "tiny/optional.h"

#include <memory>
#include <optional>


namespace
{
struct ClassWithCustomManip
{
  std::string someString = "someString";
  int someInt = 42;

  // Because we use a dereference trick in the Natvis file, added to check that an
  // operator* does not confuse Natvis.
  int const & operator*() const
  {
    return someInt;
  }
};

inline std::string const CLASS_SENTINEL = "SENTINEL";
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
enum class TestEnum : unsigned long long
{
  VALUE1,
  VALUE2,
  INVALID = 0xffff800000000000ull - 1
};
} // namespace


template <>
struct tiny::optional_flag_manipulator<TestEnum> : tiny::sentinel_flag_manipulator<TestEnum, TestEnum::INVALID>
{
};


namespace
{
struct AdditionalInplaceTestClass
{
  TestEnum someEnum = TestEnum::VALUE1;
  void (*someFuncPtr)() = nullptr;
};


void someFunc() { }

struct ClassWithFunc
{
  void memberFunc() { }
};
} // namespace


// We cannot really run automated tests for Visual Studio natvis files. The code here serves as convenient
// place to stop the Visual Studio debugger and step through the lines, manually observing the displayed
// values to check that natvis works.
void test_Natvis()
{
  //-------------- Supported by natvis --------------

  // Not in-place (i.e. not compressed)
  {
    [[maybe_unused]] tiny::optional<unsigned> empty;
    [[maybe_unused]] tiny::optional<unsigned> nonEmpty = 42u;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    [[maybe_unused]] tiny::optional<TestClassForInplace> empty;
    [[maybe_unused]] tiny::optional<TestClassForInplace> nonEmpty = TestClassForInplace{};
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    typedef void (ClassWithFunc::*MemFuncType)();
    [[maybe_unused]] tiny::optional<MemFuncType> empty;
    [[maybe_unused]] tiny::optional<MemFuncType> nonEmpty = &ClassWithFunc::memberFunc;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    [[maybe_unused]] tiny::optional<std::shared_ptr<unsigned>> empty;
    [[maybe_unused]] tiny::optional<std::shared_ptr<unsigned>> nonEmpty = nullptr;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    [[maybe_unused]] tiny::optional<std::shared_ptr<unsigned>> empty;
    [[maybe_unused]] tiny::optional<std::shared_ptr<unsigned>> nonEmpty = std::make_shared<unsigned>(42u);
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }

  // Special built-in sentinels.
  {
    [[maybe_unused]] tiny::optional<bool> empty;
    [[maybe_unused]] tiny::optional<bool> nonEmpty = true;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    [[maybe_unused]] tiny::optional<double> empty;
    [[maybe_unused]] tiny::optional<double> nonEmpty = 42.0;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    [[maybe_unused]] tiny::optional<float> empty;
    [[maybe_unused]] tiny::optional<float> nonEmpty = 42.0f;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    [[maybe_unused]] tiny::optional<TestClass *> empty;
    [[maybe_unused]] tiny::optional<TestClass *> nonEmpty = nullptr;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    TestClass c;
    [[maybe_unused]] tiny::optional<TestClass *> empty;
    [[maybe_unused]] tiny::optional<TestClass *> nonEmpty = &c;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    [[maybe_unused]] tiny::optional<void (*)()> empty;
    [[maybe_unused]] tiny::optional<void (*)()> nonEmpty = &someFunc;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }

  // In-place in member variable, built-in sentinels
  {
    [[maybe_unused]] tiny::optional<TestClassForInplace, &TestClassForInplace::someBool> empty;
    [[maybe_unused]] tiny::optional<TestClassForInplace, &TestClassForInplace::someBool> nonEmpty
        = TestClassForInplace{};
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    [[maybe_unused]] tiny::optional<TestClassForInplace, &TestClassForInplace::someDouble> empty;
    [[maybe_unused]] tiny::optional<TestClassForInplace, &TestClassForInplace::someDouble> nonEmpty
        = TestClassForInplace{};
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    [[maybe_unused]] tiny::optional<TestClassForInplace, &TestClassForInplace::someFloat> empty;
    [[maybe_unused]] tiny::optional<TestClassForInplace, &TestClassForInplace::someFloat> nonEmpty
        = TestClassForInplace{};
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    [[maybe_unused]] tiny::optional<TestClassForInplace, &TestClassForInplace::somePtr> empty;
    [[maybe_unused]] tiny::optional<TestClassForInplace, &TestClassForInplace::somePtr> nonEmpty
        = TestClassForInplace{};
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    [[maybe_unused]] tiny::optional<AdditionalInplaceTestClass, &AdditionalInplaceTestClass::someFuncPtr> empty;
    [[maybe_unused]] tiny::optional<AdditionalInplaceTestClass, &AdditionalInplaceTestClass::someFuncPtr> nonEmpty
        = AdditionalInplaceTestClass{};
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }

  // In-place with custom sentinel
  {
    [[maybe_unused]] tiny::optional<unsigned, 999> empty;
    [[maybe_unused]] tiny::optional<unsigned, 999> nonEmpty = 42u;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }

  // In-place in member variable, custom sentinel
  {
    [[maybe_unused]] tiny::optional<TestClassForInplace, &TestClassForInplace::someUnsigned, 42> empty;
    [[maybe_unused]] tiny::optional<TestClassForInplace, &TestClassForInplace::someUnsigned, 42> nonEmpty
        = TestClassForInplace{};
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }

  // optional_sentinel_via_type
  {
    [[maybe_unused]] tiny::optional_sentinel_via_type<unsigned, std::integral_constant<unsigned, 999>> empty;
    [[maybe_unused]] tiny::optional_sentinel_via_type<unsigned, std::integral_constant<unsigned, 999>> nonEmpty = 42u;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }

  // optional_aip
  {
    [[maybe_unused]] tiny::optional_aip<unsigned> empty;
    [[maybe_unused]] tiny::optional_aip<unsigned> nonEmpty = 42u;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }


  //-------------- Not supported by our generic natvis file --------------

  // These have specializations of tiny::optional_flag_manipulator.
  // Because Natvis does not allow to call functions, we cannot support them with a generic Natvis.
  {
    [[maybe_unused]] tiny::optional<ClassWithCustomManip> empty;
    [[maybe_unused]] tiny::optional<ClassWithCustomManip> nonEmpty = ClassWithCustomManip{};
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    [[maybe_unused]] tiny::optional<TestEnum> empty;
    [[maybe_unused]] tiny::optional<TestEnum> nonEmpty = TestEnum::VALUE2;
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
  {
    [[maybe_unused]] tiny::optional<AdditionalInplaceTestClass, &AdditionalInplaceTestClass::someEnum> empty;
    [[maybe_unused]] tiny::optional<AdditionalInplaceTestClass, &AdditionalInplaceTestClass::someEnum> nonEmpty
        = AdditionalInplaceTestClass{};
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }

  // optional_inplace: Always uses a custom FlagManipulator, so also no chance to write a
  // generic Natvis visualizer.
  {
    [[maybe_unused]] tiny::optional_inplace<ClassWithCustomManip, tiny::optional_flag_manipulator<ClassWithCustomManip>>
        empty;
    [[maybe_unused]] tiny::optional_inplace<ClassWithCustomManip, tiny::optional_flag_manipulator<ClassWithCustomManip>>
        nonEmpty
        = ClassWithCustomManip{};
    [[maybe_unused]] int dummyToPlaceBreakpoint = 0;
  }
}
