#include "ExerciseTinyOptionalPayload.h"
#include "Exercises.h"
#include "TestTypes.h"
#include "TestUtilities.h"
#include "tiny/optional.h"

#ifdef TINY_OPTIONAL_WINDOWS_BUILD
  #include <Windows.h>
#endif


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
    EXERCISE_OPTIONAL(
        (tiny::optional<HANDLE>{}),
        EXPECT_INPLACE,
        ::GetCurrentThreadEffectiveToken(),
        INVALID_HANDLE_VALUE);
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
