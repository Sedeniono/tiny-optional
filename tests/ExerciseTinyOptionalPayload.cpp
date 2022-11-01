#include "ExerciseTinyOptionalPayload.h"

#include "Exercises.h"
#include "TestTypes.h"
#include "TestUtilities.h"
#include "tiny/optional.h"

#include <unordered_set>

#ifdef TINY_OPTIONAL_WINDOWS_BUILD
  #include <Windows.h>
#endif


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


void test_TinyOptionalPayload_IsEmptyFlagInMember()
{
  // Exploiting a member to place the IsEmpty flag

  EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS(
      (tiny::optional<TestClassForInplace, &TestClassForInplace::someValue1, 42>{}),
      EXPECT_INPLACE,
      TestClassForInplace{},
      TestClassForInplace(43, 44.0, 45, nullptr),
      2,
      5.0,
      43u,
      nullptr);

  EXERCISE_OPTIONAL(
      (tiny::optional<TestClassForInplace, &TestClassForInplace::someValue2>{}),
      EXPECT_INPLACE,
      TestClassForInplace{},
      TestClassForInplace(43, 44.0, 45, nullptr));

  EXERCISE_OPTIONAL(
      (tiny::optional<TestClassForInplace, &TestClassForInplace::someValue4>{}),
      EXPECT_INPLACE,
      TestClassForInplace{},
      TestClassForInplace(43, 44.0, 45, nullptr));
}


void test_TinyOptionalPayload_Pointers()
{
  {
    TestClass c1, c2;
    EXERCISE_OPTIONAL((tiny::optional<TestClass *>{}), EXPECT_INPLACE, &c1, &c2);
    EXERCISE_OPTIONAL((tiny::optional<TestClass *>{}), EXPECT_INPLACE, nullptr, &c1);
    EXERCISE_OPTIONAL((tiny::optional{&c1}), EXPECT_INPLACE, &c1, &c2); // Uses deduction guide
  }

  {
    TestClass c1, c2;
    EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS((tiny::optional<TestClass *, nullptr>{}), EXPECT_INPLACE, &c1, &c2, &c1);
    // The following should trigger the assert that reset() should be used instead.
    // ExerciseOptional<TestClass*>(o, nullptr);
  }

  {
    int i = 0;
    int j = 42;
    EXERCISE_OPTIONAL((tiny::optional<void *>{}), EXPECT_INPLACE, static_cast<void *>(&i), &j);
    EXERCISE_OPTIONAL((tiny::optional<void *>{}), EXPECT_INPLACE, nullptr, static_cast<void *>(&i));
  }

  // Function pointers
  {
    EXERCISE_OPTIONAL((tiny::optional<TestFuncPtr>{}), EXPECT_INPLACE, &TestFunc1, &TestFunc2);
    EXERCISE_OPTIONAL((tiny::optional<TestFuncPtr>{}), EXPECT_INPLACE, nullptr, &TestFunc2);
  }
}


void test_TinyOptionalPayload_StdTypes()
{
  // Tests of various std types

  {
    std::vector<int> testValue1{1, 2, 3, 4};
    std::vector<int> testValue2{5, 6, 7};
    EXERCISE_OPTIONAL((tiny::optional<std::vector<int>>{}), EXPECT_SEPARATE, testValue1, testValue2);
    EXERCISE_OPTIONAL((tiny::optional{testValue1}), EXPECT_SEPARATE, testValue1, testValue2);
  }

  {
    TestClass c1, c2;
    EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS(
        (tiny::optional<std::reference_wrapper<TestClass>>{}),
        EXPECT_SEPARATE,
        std::ref(c1),
        std::ref(c2),
        std::ref(c1));
    EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS(
        (tiny::optional<std::reference_wrapper<TestClass const>>{}),
        EXPECT_SEPARATE,
        std::cref(c1),
        std::cref(c2),
        std::cref(c1));
  }

  // Test for the std::hash specialization
  {
    static_assert(!IsDisabledHash<tiny::optional<double>>);
    std::unordered_set<tiny::optional<double>> const set = {42.0, std::nullopt, 43.0};
    ASSERT_TRUE(set.count(42.0) > 0);
    ASSERT_TRUE(set.count(std::nullopt) > 0);
    ASSERT_TRUE(set.count(43.0) > 0);
  }
  {
    static_assert(!IsDisabledHash<tiny::optional<int, 0>>);
    std::unordered_set<tiny::optional<int, 0>> const set = {42, std::nullopt};
    ASSERT_TRUE(set.count(42) > 0);
    ASSERT_TRUE(set.count(std::nullopt) > 0);
  }
  {
    static_assert(!IsDisabledHash<tiny::optional<TestClassForInplace, &TestClassForInplace::someValue1, 42>>);
    std::unordered_set<tiny::optional<TestClassForInplace, &TestClassForInplace::someValue1, 42>> const set
        = {TestClassForInplace(43, 44.0, 45, nullptr), std::nullopt};
    ASSERT_TRUE(set.count(TestClassForInplace(43, 44.0, 45, nullptr)) > 0);
    ASSERT_TRUE(set.count(std::nullopt) > 0);
  }
  {
    // We did not specialize std::hash for TestClassWithInitializerList, so neither should tiny optional.
    static_assert(IsDisabledHash<TestClassWithInitializerList>);
    static_assert(IsDisabledHash<tiny::optional<TestClassWithInitializerList>>);
  }
}


void test_TinyOptionalPayload_NestedOptionals()
{
  // Tests of nested optionals. These basically check that the various constructors are not ambiguous.
  {
    tiny::optional<double> tiny1{43.0};
    tiny::optional<double> tiny2{44.0};
    tiny::optional<double> tinyEmpty;
    EXERCISE_OPTIONAL((tiny::optional<tiny::optional<double>>{}), EXPECT_SEPARATE, tiny1, tiny2);
    EXERCISE_OPTIONAL((tiny::optional<tiny::optional<double>>{}), EXPECT_SEPARATE, tinyEmpty, tiny2);

    EXERCISE_OPTIONAL((std::optional<tiny::optional<double>>{}), EXPECT_SEPARATE, tiny1, tiny2);
    EXERCISE_OPTIONAL((std::optional<tiny::optional<double>>{}), EXPECT_SEPARATE, tinyEmpty, tiny2);

    std::optional<double> std1{43.0};
    std::optional<double> std2{44.0};
    std::optional<double> stdEmpty;
    EXERCISE_OPTIONAL((tiny::optional<std::optional<double>>{}), EXPECT_SEPARATE, std1, std2);
    EXERCISE_OPTIONAL((tiny::optional<std::optional<double>>{}), EXPECT_SEPARATE, stdEmpty, std2);
  }
}


void test_TinyOptionalPayload_ConstAndVolatile()
{
  // Tests of const and volatile
  EXERCISE_OPTIONAL((tiny::optional<double const>{}), EXPECT_INPLACE, 43.0, 44.0);
  static_assert(std::is_same_v<tiny::optional<double const>::value_type, double const>);
  EXERCISE_OPTIONAL((tiny::optional<double volatile>{}), EXPECT_INPLACE, 43.0, 44.0);
  static_assert(std::is_same_v<tiny::optional<double volatile>::value_type, double volatile>);
  EXERCISE_OPTIONAL((tiny::optional<double const volatile>{}), EXPECT_INPLACE, 43.0, 44.0);
  static_assert(std::is_same_v<tiny::optional<double const volatile>::value_type, double const volatile>);

  EXERCISE_OPTIONAL((tiny::optional<int const, 42>{}), EXPECT_INPLACE, 43, 44);
  static_assert(std::is_same_v<tiny::optional<int const>::value_type, int const>);
  EXERCISE_OPTIONAL((tiny::optional<int volatile, 42>{}), EXPECT_INPLACE, 43, 44);
  static_assert(std::is_same_v<tiny::optional<int volatile>::value_type, int volatile>);
  EXERCISE_OPTIONAL((tiny::optional<int const volatile, 42>{}), EXPECT_INPLACE, 43, 44);
  static_assert(std::is_same_v<tiny::optional<int const volatile>::value_type, int const volatile>);

  EXERCISE_OPTIONAL((tiny::optional<int const>{}), EXPECT_SEPARATE, 43, 44);
  static_assert(std::is_same_v<tiny::optional<int const>::value_type, int const>);
  EXERCISE_OPTIONAL((tiny::optional<int volatile>{}), EXPECT_SEPARATE, 43, 44);
  static_assert(std::is_same_v<tiny::optional<int volatile>::value_type, int volatile>);
  EXERCISE_OPTIONAL((tiny::optional<int const volatile>{}), EXPECT_SEPARATE, 43, 44);
  static_assert(std::is_same_v<tiny::optional<int const volatile>::value_type, int const volatile>);
}


void test_TinyOptionalPayload_Cpp20NTTP()
{
  // Non type template parameters supported since C++20.
  // C++20 allows using floating point values and literal class types in templates.
  // Unfortunately, even clang 14 does yet support it.
#if defined(TINY_OPTIONAL_CPP20) && !defined(TINY_OPTIONAL_CLANG_BUILD)
  {
    // Floating point, directly in the payload
    EXERCISE_OPTIONAL((tiny::optional<float, 42.0f>{}), EXPECT_INPLACE, 43.0f, 44.0f);
    EXERCISE_OPTIONAL((tiny::optional<double, 42.0>{}), EXPECT_INPLACE, 43.0, 44.0);
    EXERCISE_OPTIONAL((tiny::optional<long double, 42.0L>{}), EXPECT_INPLACE, 43.0L, 44.0L);

    // Floating point, stored in member.
    EXERCISE_OPTIONAL(
        (tiny::optional<TestClassForInplace, &TestClassForInplace::someValue2, 42.0>{}),
        EXPECT_INPLACE,
        TestClassForInplace{},
        TestClassForInplace(43, 44.0, 45, nullptr));

    // Literal class, directly as payload.
    constexpr LiteralClass lc1(42, 43.0);
    constexpr LiteralClass lc2(44, 45.0);
    constexpr LiteralClass lc3(46, 47.0);
    EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS((tiny::optional<LiteralClass, lc1>{}), EXPECT_INPLACE, lc2, lc3, 48, 49.0);

    // Literal class, stored in member.
    EXERCISE_OPTIONAL(
        (tiny::optional<TestClassWithLiteralClass, &TestClassWithLiteralClass::lc, lc1>{}),
        EXPECT_INPLACE,
        TestClassWithLiteralClass{},
        TestClassWithLiteralClass(43, 44.0, 45));
  }
#endif
}


void test_TinyOptionalPayload_WindowsHandles() 
{
  // On Windows, there are various handle types (HANDLE, HINSTANCE, HWND, etc). They are essentially void*. The problem
  // is that there various special HANDLE values that the WinAPI can return. These tests here essentially test that we
  // do not use one of those special values as sentinel to indicate the empty state. See
  // https://stackoverflow.com/a/3905643/3740047 and https://stackoverflow.com/a/45632388/3740047.

#ifdef TINY_OPTIONAL_WINDOWS_BUILD
  {
    // Some error codes returned by common WinAPI functions.
    // https://devblogs.microsoft.com/oldnewthing/20040302-00/?p=40443
    EXERCISE_OPTIONAL((tiny::optional<HANDLE>{}), EXPECT_INPLACE, static_cast<HANDLE>(NULL), INVALID_HANDLE_VALUE);
    EXERCISE_OPTIONAL((tiny::optional<HANDLE>{}), EXPECT_INPLACE, static_cast<HANDLE>(0), INVALID_HANDLE_VALUE);
    EXERCISE_OPTIONAL((tiny::optional<HANDLE>{}), EXPECT_INPLACE, reinterpret_cast<HANDLE>(-1), INVALID_HANDLE_VALUE);
    EXERCISE_OPTIONAL((tiny::optional<HANDLE>{}), EXPECT_INPLACE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE);

    // Pseudo handles:
    // https://github.com/winsiderss/systeminformer/blob/c19d69317a8eedcce773eb7317462eac8dfebf66/phnt/include/ntpsapi.h#L1294
    // https://devblogs.microsoft.com/oldnewthing/20210105-00/?p=104667
    // Current possible values: 
    //     NtCurrentProcess() ((HANDLE)(LONG_PTR)-1)
    //     NtCurrentThread() ((HANDLE)(LONG_PTR)-2)
    //     NtCurrentSession() ((HANDLE)(LONG_PTR)-3)
    //     NtCurrentProcessToken() ((HANDLE)(LONG_PTR)-4) // NtOpenProcessToken(NtCurrentProcess())
    //     NtCurrentThreadToken() ((HANDLE)(LONG_PTR)-5) // NtOpenThreadToken(NtCurrentThread())
    //     NtCurrentThreadEffectiveToken() ((HANDLE)(LONG_PTR)-6) // NtOpenThreadToken(NtCurrentThread())
    //                                                               + NtOpenProcessToken(NtCurrentProcess())
    //     NtCurrentSilo() ((HANDLE)(LONG_PTR)-1)
    EXERCISE_OPTIONAL((tiny::optional<HANDLE>{}), EXPECT_INPLACE, ::GetCurrentProcess(), INVALID_HANDLE_VALUE);
    EXERCISE_OPTIONAL((tiny::optional<HANDLE>{}), EXPECT_INPLACE, ::GetCurrentThread(), INVALID_HANDLE_VALUE);
  #ifndef TINY_OPTIONAL_GCC_BUILD // Functions are unknown to mingw for some reason.
    EXERCISE_OPTIONAL((tiny::optional<HANDLE>{}), EXPECT_INPLACE, ::GetCurrentProcessToken(), INVALID_HANDLE_VALUE);
    EXERCISE_OPTIONAL((tiny::optional<HANDLE>{}), EXPECT_INPLACE, ::GetCurrentThreadToken(), INVALID_HANDLE_VALUE);
    EXERCISE_OPTIONAL((tiny::optional<HANDLE>{}), EXPECT_INPLACE, ::GetCurrentThreadEffectiveToken(), INVALID_HANDLE_VALUE);
 #endif
    EXERCISE_OPTIONAL((tiny::optional<HANDLE>{}), EXPECT_INPLACE, ((HANDLE)(LONG_PTR)(-1)), INVALID_HANDLE_VALUE);
    EXERCISE_OPTIONAL((tiny::optional<HANDLE>{}), EXPECT_INPLACE, ((HANDLE)(LONG_PTR)(-2)), INVALID_HANDLE_VALUE);
    EXERCISE_OPTIONAL((tiny::optional<HANDLE>{}), EXPECT_INPLACE, ((HANDLE)(LONG_PTR)(-3)), INVALID_HANDLE_VALUE);
    EXERCISE_OPTIONAL((tiny::optional<HANDLE>{}), EXPECT_INPLACE, ((HANDLE)(LONG_PTR)(-4)), INVALID_HANDLE_VALUE);
    EXERCISE_OPTIONAL((tiny::optional<HANDLE>{}), EXPECT_INPLACE, ((HANDLE)(LONG_PTR)(-5)), INVALID_HANDLE_VALUE);
    EXERCISE_OPTIONAL((tiny::optional<HANDLE>{}), EXPECT_INPLACE, ((HANDLE)(LONG_PTR)(-6)), INVALID_HANDLE_VALUE);


    // Some return values of ShellExecute().
    EXERCISE_OPTIONAL(
        (tiny::optional<HINSTANCE>{}),
        EXPECT_INPLACE,
        reinterpret_cast<HINSTANCE>(ERROR_FILE_NOT_FOUND),
        static_cast<HINSTANCE>(0));
    EXERCISE_OPTIONAL(
        (tiny::optional<HINSTANCE>{}),
        EXPECT_INPLACE,
        reinterpret_cast<HINSTANCE>(SE_ERR_SHARE),
        static_cast<HINSTANCE>(0));
  }
#endif

  // Same as above, but instead of using the Windows specific types, we directly use void*. Less direct, but that way we
  // can also run these tests on non-Windows builds, to ensure some behavior consistency between the operating systems.
  {
    EXERCISE_OPTIONAL((tiny::optional<void *>{}), EXPECT_INPLACE, static_cast<void *>(0), nullptr);

    // Pseudo handles. The -1 is additionally INVALID_HANDLE_VALUE.
    EXERCISE_OPTIONAL((tiny::optional<void *>{}), EXPECT_INPLACE, reinterpret_cast<void *>(-1), nullptr);
    EXERCISE_OPTIONAL((tiny::optional<void *>{}), EXPECT_INPLACE, reinterpret_cast<void *>(-2), nullptr);
    EXERCISE_OPTIONAL((tiny::optional<void *>{}), EXPECT_INPLACE, reinterpret_cast<void *>(-3), nullptr);
    EXERCISE_OPTIONAL((tiny::optional<void *>{}), EXPECT_INPLACE, reinterpret_cast<void *>(-4), nullptr);
    EXERCISE_OPTIONAL((tiny::optional<void *>{}), EXPECT_INPLACE, reinterpret_cast<void *>(-5), nullptr);
    EXERCISE_OPTIONAL((tiny::optional<void *>{}), EXPECT_INPLACE, reinterpret_cast<void *>(-6), nullptr);

    // As for ShellExecute() above.
    EXERCISE_OPTIONAL((tiny::optional<void *>{}), EXPECT_INPLACE, reinterpret_cast<void *>(2), nullptr);
    EXERCISE_OPTIONAL((tiny::optional<void *>{}), EXPECT_INPLACE, reinterpret_cast<void *>(26), nullptr);
  }
}


void test_TinyOptionalPayload_OtherTypes()
{
  // We befriended the present function
  EXERCISE_OPTIONAL(
      (tiny::optional<TestClassPrivate, &TestClassPrivate::someValue>{}),
      EXPECT_INPLACE,
      TestClassPrivate{42.0},
      TestClassPrivate{43.0});

  EXERCISE_OPTIONAL((tiny::optional<TestClass>{}), EXPECT_SEPARATE, TestClass(true, 4.0), TestClass(true, 5.0));
  // Uses deduction guide
  EXERCISE_OPTIONAL((tiny::optional{TestClass{}}), EXPECT_SEPARATE, TestClass(true, 4.0), TestClass(true, 5.0));

  // Just to have some class with noexcept(false) stuff.
  EXERCISE_OPTIONAL(
      (tiny::optional<TestClassWithExcept>{}),
      EXPECT_SEPARATE,
      TestClassWithExcept{42},
      TestClassWithExcept{43});

  // Targets functions of tiny::optional that work with std::initializer_list.
  {
    std::initializer_list<int> const initList = {3, 4, 5};
    EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS(
        (tiny::optional<TestClassWithInitializerList>{}),
        EXPECT_SEPARATE,
        TestClassWithInitializerList({1}),
        TestClassWithInitializerList({2}),
        initList);
    EXERCISE_OPTIONAL_WITH_CONSTRUCTOR_ARGS(
        (tiny::optional<TestClassWithInitializerList>{}),
        EXPECT_SEPARATE,
        TestClassWithInitializerList({1}),
        TestClassWithInitializerList({2}),
        initList,
        ScopedEnum::v2);
  }

  // Tests that target cases where the deduction guide of std::optional would come into play.
  // https://en.cppreference.com/w/cpp/utility/optional/deduction_guides
  {
    int arr1[2] = {1, 2};
    int arr2[2] = {3, 4};
    static_assert(std::is_same_v<decltype(tiny::optional{arr1})::value_type, int *>);
    EXERCISE_OPTIONAL((tiny::optional{arr1}), EXPECT_INPLACE, arr1, arr2);

    struct NonCopyable
    {
      NonCopyable() = default;
      NonCopyable(NonCopyable const &) = delete;
      NonCopyable(NonCopyable &&) = default;
    };
    static_assert(std::is_same_v<decltype(tiny::optional{NonCopyable{}})::value_type, NonCopyable>);
  }
}

