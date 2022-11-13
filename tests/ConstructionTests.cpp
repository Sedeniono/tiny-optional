#include "ConstructionTests.h"

#include "TestTypes.h"

#ifdef TINY_OPTIONAL_MSVC_BUILD
  // Disable "unreachable code" because it is triggered by exception tests. Because, due to the exceptions, certain code
  // is simply unreachable within the tiny optional.
  #pragma warning(disable : 4702)
#endif

#include "tiny/optional.h"

namespace
{
struct Probe
{
  Probe() noexcept
  {
    created = true;
  }

  Probe(Probe const &) noexcept
  {
    created = true;
  }

  Probe(Probe &&) noexcept
  {
    created = true;
  }

  Probe & operator=(Probe const &) = default;
  Probe & operator=(Probe &&) = default;

  ~Probe()
  {
    destroyed = true;
  }

  inline static bool created = false;
  inline static bool destroyed = false;

  static void Reset()
  {
    created = false;
    destroyed = false;
  }
};
} // namespace


// Checks that the optional is properly calling the constructor and destructor.
void test_TinyOptionalMemoryManagement()
{
  Probe::Reset();
  Probe p;
  Probe::Reset();

  // reset() should destroy probe.
  {
    tiny::optional<Probe> o;
    ASSERT_FALSE(Probe::created);
    ASSERT_FALSE(Probe::destroyed);
    ASSERT_FALSE(o.has_value());

    o = p;
    ASSERT_TRUE(Probe::created);
    ASSERT_FALSE(Probe::destroyed);
    ASSERT_TRUE(o.has_value());

    o.reset();
    ASSERT_TRUE(Probe::destroyed);
    ASSERT_FALSE(o.has_value());
  }

  Probe::Reset();

  // Destructor of optional should destroy probe.
  {
    {
      tiny::optional<Probe> o;
      o = p;
      ASSERT_TRUE(Probe::created);
      ASSERT_FALSE(Probe::destroyed);
      ASSERT_TRUE(o.has_value());
    }
    ASSERT_TRUE(Probe::destroyed);
  }

  Probe::Reset();

  // Empty optional should not create nor destroy the probe.
  {
    {
      [[maybe_unused]] tiny::optional<Probe> o;
    }
    ASSERT_FALSE(Probe::created);
    ASSERT_FALSE(Probe::destroyed);
  }

  Probe::Reset();

  // Assigning an empty optional should destroy the probe.
  {
    tiny::optional<Probe> o;
    o = p;
    ASSERT_TRUE(Probe::created);
    ASSERT_FALSE(Probe::destroyed);
    ASSERT_TRUE(o.has_value());

    Probe::Reset();
    tiny::optional<Probe> empty;
    o = empty;
    ASSERT_TRUE(Probe::destroyed);
    ASSERT_FALSE(o.has_value());
  }

  Probe::Reset();

  // emplace() should destroy probe.
  {
    tiny::optional<Probe> o;
    o = p;
    ASSERT_TRUE(Probe::created);
    ASSERT_FALSE(Probe::destroyed);
    ASSERT_TRUE(o.has_value());

    Probe::Reset();

    o.emplace();
    ASSERT_TRUE(Probe::destroyed);
    ASSERT_TRUE(o.has_value());
  }

  Probe::Reset();
}


void test_Exceptions()
{
  struct ConstructorException : std::exception
  {
  };
  struct CopyException : std::exception
  {
  };
  struct AssignmentException : std::exception
  {
  };

  struct Throwing
  {
    explicit Throwing(int value, bool doThrow = true)
      : value(value)
    {
      if (doThrow) {
        throw ConstructorException();
      }
    }

    Throwing(Throwing const &)
    {
      throw CopyException();
    }

    Throwing operator=(Throwing const &)
    {
      throw AssignmentException();
    }

    int value;
  };

  {
    tiny::optional<Throwing> o;
    tiny::optional<Throwing> nonEmpty{std::in_place, 42, false};
    EXPECT_EXCEPTION(o = nonEmpty, CopyException);
    ASSERT_FALSE(o.has_value());

    EXPECT_EXCEPTION(o.emplace(43), ConstructorException);
    ASSERT_FALSE(o.has_value());
  }
  {
    tiny::optional<Throwing> o1{std::in_place, 42, false};
    tiny::optional<Throwing> o2{std::in_place, 43, false};

    EXPECT_EXCEPTION(o2 = o1, AssignmentException);
    ASSERT_TRUE(o2.has_value());
    ASSERT_TRUE(o2.value().value == 43); // o2 should still contain the old value.
  }
  {
    using std::swap;

    tiny::optional<Throwing> o;
    tiny::optional<Throwing> nonEmpty{std::in_place, 42, false};

    static_assert(!noexcept(o.swap(nonEmpty)));
    static_assert(!noexcept(swap(o, nonEmpty)));

    EXPECT_EXCEPTION(o.swap(nonEmpty), CopyException);
    ASSERT_FALSE(o.has_value());
    ASSERT_TRUE(nonEmpty.has_value());

    EXPECT_EXCEPTION(swap(nonEmpty, o), CopyException);
    ASSERT_FALSE(o.has_value());
    ASSERT_TRUE(nonEmpty.has_value());
  }
}


void test_TinyOptionalCopyConstruction()
{
  // Check that the copy constructor actually does copy the data (and does not move it).
  {
    tiny::optional<std::vector<int>> orig;
    orig.emplace({1, 2, 3, 4});
    ASSERT_TRUE(orig.has_value());
    ASSERT_FALSE(orig.value().empty());

    tiny::optional<std::vector<int>> copyTarget(orig);
    ASSERT_TRUE(copyTarget.has_value());
    ASSERT_FALSE(copyTarget.value().empty());
    ASSERT_TRUE((copyTarget.value() == std::vector<int>{1, 2, 3, 4}));

    ASSERT_TRUE(orig.has_value());
    ASSERT_TRUE((orig.value() == std::vector<int>{1, 2, 3, 4}));
  }

  // Check that tiny::optional is not copy constructible if the copy constructor is deleted.
  {
    struct DeletedCopy
    {
      DeletedCopy() = default;
      DeletedCopy(DeletedCopy const &) = delete;
      DeletedCopy(DeletedCopy &&) = default;
      DeletedCopy & operator=(DeletedCopy const &) = default;
      DeletedCopy & operator=(DeletedCopy &&) = default;
    };

    static_assert(!std::is_copy_constructible_v<tiny::optional<DeletedCopy>>);
    static_assert(std::is_swappable_v<tiny::optional<DeletedCopy>>);
  }
}


void test_TinyOptionalMoveConstruction()
{
  // Check that the move constructor really moves the data.
  {
    tiny::optional<std::vector<int>> orig;
    orig.emplace({1, 2, 3, 4});
    ASSERT_TRUE(orig.has_value());
    ASSERT_FALSE(orig.value().empty());

    tiny::optional<std::vector<int>> moveTarget(std::move(orig));
    ASSERT_TRUE(moveTarget.has_value());
    ASSERT_FALSE(moveTarget.value().empty());
    ASSERT_TRUE((moveTarget.value() == std::vector<int>{1, 2, 3, 4}));

    // According to the standard, the original should still have a value.
    // But it was moved from, so the vector should be empty.
    ASSERT_TRUE(orig.has_value());
    ASSERT_TRUE(orig.value().empty());
  }

  // Check that the noexcept specification of the move constructor is taken from the payload.
  {
    struct NothrowMove
    {
      NothrowMove(NothrowMove &&) noexcept(true) { }
    };
    static_assert(noexcept(tiny::optional<NothrowMove>(std::declval<tiny::optional<NothrowMove> &&>())));
  }
  {
    struct ThrowMove
    {
      ThrowMove(ThrowMove &&) noexcept(false) { }
    };
    static_assert(!noexcept(tiny::optional<ThrowMove>(std::declval<tiny::optional<ThrowMove> &&>())));
  }

  // Check that constructing the optional with another rvalue optional compiles even if the payload
  // has a deleted move constructor. I.e. it should call the copy constructor instead.
  {
    struct DeletedMove
    {
      DeletedMove() = default;
      DeletedMove(DeletedMove const &) = default;
      DeletedMove(DeletedMove &&) = delete;
      DeletedMove & operator=(DeletedMove const &) = delete;
      DeletedMove & operator=(DeletedMove &&) = delete;
    };

    static_assert(std::is_copy_constructible_v<tiny::optional<DeletedMove>>);
    static_assert(std::is_move_constructible_v<tiny::optional<DeletedMove>>);
    static_assert(!std::is_swappable_v<tiny::optional<DeletedMove>>);

    tiny::optional<DeletedMove> orig;
    [[maybe_unused]] tiny::optional<DeletedMove> moveTarget(std::move(orig));
  }

  // Check that move construction compiles if the copy constructor is deleted.
  {
    struct DeletedCopy
    {
      DeletedCopy() = default;
      DeletedCopy(DeletedCopy const &) = delete;
      DeletedCopy(DeletedCopy &&) = default;
      DeletedCopy & operator=(DeletedCopy const &) = delete;
      DeletedCopy & operator=(DeletedCopy &&) = delete;
    };

    static_assert(!std::is_copy_constructible_v<tiny::optional<DeletedCopy>>);
    static_assert(std::is_move_constructible_v<tiny::optional<DeletedCopy>>);
    static_assert(!std::is_swappable_v<tiny::optional<DeletedCopy>>);

    tiny::optional<DeletedCopy> orig;
    [[maybe_unused]] tiny::optional<DeletedCopy> moveTarget(std::move(orig));
  }
}


void test_TinyOptionalCopyAssignment()
{
  // Check that the copy assignment operator really copies the data (and does not move it).
  {
    tiny::optional<std::vector<int>> orig;
    orig.emplace({1, 2, 3, 4});
    ASSERT_TRUE(orig.has_value());
    ASSERT_FALSE(orig.value().empty());

    tiny::optional<std::vector<int>> copyTarget;
    copyTarget = orig;
    ASSERT_TRUE(copyTarget.has_value());
    ASSERT_FALSE(copyTarget.value().empty());
    ASSERT_TRUE((copyTarget.value() == std::vector<int>{1, 2, 3, 4}));

    ASSERT_TRUE(orig.has_value());
    ASSERT_TRUE((orig.value() == std::vector<int>{1, 2, 3, 4}));
  }

  // If the payload does have a copy assignment operator but is not copy constructible, the copy assignment operator of
  // tiny::optional should still be deleted. Reason: The copy assignment of tiny::optional might need to
  // construct a new payload object, if the optional was empty before. Similar for the assignment of a payload.
  {
    struct NotCopyConstructible
    {
      NotCopyConstructible(NotCopyConstructible const &) = delete;
      NotCopyConstructible(NotCopyConstructible &&) = delete;
      NotCopyConstructible & operator=(NotCopyConstructible &&) = default;
      NotCopyConstructible & operator=(NotCopyConstructible const &) = default;
    };
    // Cross-check properties of the test object.
    static_assert(!std::is_copy_constructible_v<NotCopyConstructible>);
    static_assert(std::is_copy_assignable_v<NotCopyConstructible>);

    // Actual check: Copy assignment
    static_assert(!std::is_copy_assignable_v<tiny::optional<NotCopyConstructible>>);

    // Actual check: Assignment of payload
    static_assert(!std::is_assignable_v<tiny::optional<NotCopyConstructible>, NotCopyConstructible>);
    static_assert(!std::is_assignable_v<tiny::optional<NotCopyConstructible>, NotCopyConstructible &>);
    static_assert(!std::is_assignable_v<tiny::optional<NotCopyConstructible>, NotCopyConstructible &&>);

    // Actual check: swappable
    static_assert(!std::is_swappable_v<tiny::optional<NotCopyConstructible>>);
  }

  // If the payload is copy constructible but not copy assignable, then the optional should not be copy assignable.
  {
    struct NotCopyAssignable
    {
      NotCopyAssignable(NotCopyAssignable const &) = default;
      NotCopyAssignable(NotCopyAssignable &&) = default;
      NotCopyAssignable & operator=(NotCopyAssignable &&) = default;
      NotCopyAssignable & operator=(NotCopyAssignable const &) = delete;
    };
    // Cross-check properties of the test object.
    static_assert(std::is_copy_constructible_v<NotCopyAssignable>);
    static_assert(!std::is_copy_assignable_v<NotCopyAssignable>);

    // Actual check
    static_assert(!std::is_copy_assignable_v<tiny::optional<NotCopyAssignable>>);

    // Actual check: swappable
    static_assert(std::is_swappable_v<tiny::optional<NotCopyAssignable>>);
  }
}


void test_TinyOptionalMoveAssignment()
{
  // Check that the move assignment really moves the data.
  {
    tiny::optional<std::vector<int>> orig;
    orig.emplace({1, 2, 3, 4});
    ASSERT_TRUE(orig.has_value());
    ASSERT_FALSE(orig.value().empty());

    tiny::optional<std::vector<int>> moveTarget;
    moveTarget = std::move(orig);
    ASSERT_TRUE(moveTarget.has_value());
    ASSERT_FALSE(moveTarget.value().empty());
    ASSERT_TRUE((moveTarget.value() == std::vector<int>{1, 2, 3, 4}));

    // According to the standard, the original should still have a value.
    // But it was moved from, so the vector should be empty.
    ASSERT_TRUE(orig.has_value());
    ASSERT_TRUE(orig.value().empty());
  }

  // If the payload does have an move assignment operator but is not move constructible, the move assignment operator of
  // tiny::optional should still be deleted. Reason: The move assignment of tiny::optional might need to
  // construct a new payload object, if the optional was empty before. Similar for the assignment and swap of a payload.
  {
    struct NotMoveConstructible
    {
      NotMoveConstructible(NotMoveConstructible const &) = delete;
      NotMoveConstructible(NotMoveConstructible &&) = delete;
      NotMoveConstructible & operator=(NotMoveConstructible &&) = default;
      NotMoveConstructible & operator=(NotMoveConstructible const &) = default;
    };
    // Cross-check properties of the test object.
    static_assert(!std::is_move_constructible_v<NotMoveConstructible>);
    static_assert(std::is_move_assignable_v<NotMoveConstructible>);

    // Actual check: Move assignment
    static_assert(!std::is_move_assignable_v<tiny::optional<NotMoveConstructible>>);

    // Actual check: Assignment of payload
    static_assert(!std::is_assignable_v<tiny::optional<NotMoveConstructible>, NotMoveConstructible>);
    static_assert(!std::is_assignable_v<tiny::optional<NotMoveConstructible>, NotMoveConstructible &>);
    static_assert(!std::is_assignable_v<tiny::optional<NotMoveConstructible>, NotMoveConstructible &&>);

    // Actual check: Not swappable
    static_assert(!std::is_swappable_v<tiny::optional<NotMoveConstructible>>);
  }

  // If the payload is move constructible but not move assignable, then the optional should not be move assignable.
  {
    struct NotMoveAssignable
    {
      NotMoveAssignable(NotMoveAssignable const &) = delete;
      NotMoveAssignable(NotMoveAssignable &&) = default;
      NotMoveAssignable & operator=(NotMoveAssignable &&) = delete;
      NotMoveAssignable & operator=(NotMoveAssignable const &) = default;
    };
    // Cross-check properties of the test object.
    static_assert(std::is_move_constructible_v<NotMoveAssignable>);
    static_assert(!std::is_move_assignable_v<NotMoveAssignable>);

    // Actual check
    static_assert(!std::is_move_assignable_v<tiny::optional<NotMoveAssignable>>);

    // Actual check: Not swappable
    static_assert(!std::is_swappable_v<tiny::optional<NotMoveAssignable>>);
  }

  // Check that the noexcept specification of the move assignment operator is taken from the payload.
  {
    struct NothrowMove
    {
      NothrowMove(NothrowMove &&) noexcept(true) { }
      NothrowMove & operator=(NothrowMove &&) noexcept(true)
      {
        return *this;
      }
    };
    static_assert(
        noexcept(std::declval<tiny::optional<NothrowMove> &>() = std::declval<tiny::optional<NothrowMove> &&>()));
  }
  {
    struct ThrowMove
    {
      ThrowMove(ThrowMove &&) noexcept(false) { }
      ThrowMove & operator=(ThrowMove &&) noexcept(false)
      {
        return *this;
      }
    };
    static_assert(
        !noexcept(std::declval<tiny::optional<ThrowMove> &>() = std::declval<tiny::optional<ThrowMove> &&>()));
  }
  {
    struct ThrowMoveConstructionNoThrowMoveAssignment
    {
      ThrowMoveConstructionNoThrowMoveAssignment(ThrowMoveConstructionNoThrowMoveAssignment &&) noexcept(false) { }
      ThrowMoveConstructionNoThrowMoveAssignment & operator=(ThrowMoveConstructionNoThrowMoveAssignment &&) noexcept(
          true)
      {
        return *this;
      }
    };
    static_assert(!noexcept(
        std::declval<tiny::optional<ThrowMoveConstructionNoThrowMoveAssignment> &>()
        = std::declval<tiny::optional<ThrowMoveConstructionNoThrowMoveAssignment> &&>()));
  }
  {
    struct NoThrowMoveConstructionThrowMoveAssignment
    {
      NoThrowMoveConstructionThrowMoveAssignment(NoThrowMoveConstructionThrowMoveAssignment &&) noexcept(true) { }
      NoThrowMoveConstructionThrowMoveAssignment & operator=(NoThrowMoveConstructionThrowMoveAssignment &&) noexcept(
          false)
      {
        return *this;
      }
    };
    static_assert(!noexcept(
        std::declval<tiny::optional<NoThrowMoveConstructionThrowMoveAssignment> &>()
        = std::declval<tiny::optional<NoThrowMoveConstructionThrowMoveAssignment> &&>()));
  }

  // Check that move assignment compiles if the copy assignment operator is deleted.
  {
    struct DeletedCopy
    {
      DeletedCopy() = default;
      DeletedCopy(DeletedCopy const &) = delete;
      DeletedCopy(DeletedCopy &&) = default;
      DeletedCopy & operator=(DeletedCopy const &) = delete;
      DeletedCopy & operator=(DeletedCopy &&) = default;
    };

    static_assert(!std::is_copy_constructible_v<tiny::optional<DeletedCopy>>);
    static_assert(!std::is_copy_assignable_v<tiny::optional<DeletedCopy>>);

    static_assert(std::is_move_constructible_v<tiny::optional<DeletedCopy>>);
    static_assert(std::is_move_assignable_v<tiny::optional<DeletedCopy>>);

    static_assert(std::is_swappable_v<tiny::optional<DeletedCopy>>);

    tiny::optional<DeletedCopy> orig;
    tiny::optional<DeletedCopy> moveTarget;
    moveTarget = std::move(orig);
  }
}


void test_TinyOptionalConversions()
{
  {
    struct ImplicitConversion
    {
      // Note: Not specified as 'explicit'
      ImplicitConversion(int v)
        : value(v)
      {
      }
      int value;
    };

    static_assert(std::is_constructible_v<tiny::optional<ImplicitConversion>, int>);

    // The following two constructions always compile, regardless if the constructor is explicit or not.
    tiny::optional<ImplicitConversion> o1(42);
    ASSERT_TRUE(o1.value().value == 42);
    tiny::optional<ImplicitConversion> o2{42};
    ASSERT_TRUE(o2.value().value == 42);

    // The following two constructions would not compile if the payload had an explicit constructor.
    tiny::optional<ImplicitConversion> o3 = 42;
    ASSERT_TRUE(o3.value().value == 42);
    tiny::optional<ImplicitConversion> o4 = {42};
    ASSERT_TRUE(o4.value().value == 42);

    // Assignment of payload also performs the implicit conversion. Would not compile if the payload had an explicit
    // constructor.
    tiny::optional<ImplicitConversion> o5;
    o5 = 42;
    ASSERT_TRUE(o5.value().value == 42);
  }

  {
    struct ExplicitConversion
    {
      explicit ExplicitConversion(int v)
        : value(v)
      {
      }
      int value;
    };

    static_assert(std::is_constructible_v<tiny::optional<ExplicitConversion>, int>);

    // The following two constructions always compile, regardless of the explicit
    tiny::optional<ExplicitConversion> o1(42);
    ASSERT_TRUE(o1.value().value == 42);
    tiny::optional<ExplicitConversion> o2{42};
    ASSERT_TRUE(o2.value().value == 42);

    // The following two constructions do not compile as the payload has an explicit constructor.
    // We check this in the compilation-error checks.
    // tiny::optional<ExplicitConversion> o3 = 42;
    // tiny::optional<ExplicitConversion> o4 = {42};

    // Similar, the assignment of payload does not perform the implicit conversion. The following would not compile.
    // tiny::optional<ExplicitConversion> o5;
    // o5 = 42;
    // ASSERT_TRUE(o5.value().value == 42);
  }

  {
    // Cross-check that the typetrait std::is_constructible works as expected.
    static_assert(!std::is_constructible_v<tiny::optional<TestClass>, int>);
  }
}


void test_MakeOptional()
{
  //--------- Test first version of make_optional
  {
    auto o = tiny::make_optional(42.0);
    static_assert(sizeof(o) == sizeof(double));
    static_assert(std::is_same_v<decltype(o)::value_type, double>);
    ASSERT_TRUE(o.value() == 42.0);
  }
  {
    auto o = tiny::make_optional(42);
    static_assert(sizeof(o) == sizeof(std::optional<int>));
    static_assert(std::is_same_v<decltype(o)::value_type, int>);
    ASSERT_TRUE(o.value() == 42);
  }
  {
    auto o = tiny::make_optional<unsigned int, 0>(42u);
    static_assert(sizeof(o) == sizeof(unsigned int));
    static_assert(std::is_same_v<decltype(o)::value_type, unsigned int>);
    ASSERT_TRUE(o.value() == 42u);
  }
  {
    TestClassForInplace const testValue{};
    auto o = tiny::make_optional<TestClassForInplace, &TestClassForInplace::someValue1, 42>(testValue);
    static_assert(sizeof(o) == sizeof(TestClassForInplace));
    static_assert(std::is_same_v<decltype(o)::value_type, TestClassForInplace>);
    ASSERT_TRUE(o.value() == testValue);
  }
  {
    auto ptr = std::make_unique<int>(42);
    auto o = tiny::make_optional(std::move(ptr));
    ASSERT_TRUE(*o.value() == 42u);
    ASSERT_TRUE(ptr == nullptr);
  }

  //--------- Test second version of make_optional
  {
    auto o = tiny::make_optional<TestClassForInplace>(2, 5.0, 43u, nullptr);
    static_assert(sizeof(o) == sizeof(std::optional<TestClassForInplace>));
    static_assert(std::is_same_v<decltype(o)::value_type, TestClassForInplace>);
    ASSERT_TRUE(o.value() == TestClassForInplace(2, 5.0, 43u, nullptr));
  }
  {
    auto o = tiny::make_optional<TestClassForInplace, &TestClassForInplace::someValue1, 42>(2, 5.0, 43u, nullptr);
    static_assert(sizeof(o) == sizeof(TestClassForInplace));
    static_assert(std::is_same_v<decltype(o)::value_type, TestClassForInplace>);
    ASSERT_TRUE(o.value() == TestClassForInplace(2, 5.0, 43u, nullptr));
  }

  //--------- Test third version of make_optional
  {
    std::initializer_list<int> const initList = {3, 4, 5};
    auto o = tiny::make_optional<TestClassWithInitializerList>(initList);
    static_assert(sizeof(o) == sizeof(std::optional<TestClassWithInitializerList>));
    static_assert(std::is_same_v<decltype(o)::value_type, TestClassWithInitializerList>);
    ASSERT_TRUE(o.value() == TestClassWithInitializerList{initList});
  }
  {
    std::initializer_list<int> const initList = {3, 4, 5};
    auto o = tiny::make_optional<TestClassWithInitializerList>(initList, ScopedEnum::v2);
    static_assert(sizeof(o) == sizeof(std::optional<TestClassWithInitializerList>));
    static_assert(std::is_same_v<decltype(o)::value_type, TestClassWithInitializerList>);
    ASSERT_TRUE(o.value() == TestClassWithInitializerList(initList, ScopedEnum::v2));
  }
}
