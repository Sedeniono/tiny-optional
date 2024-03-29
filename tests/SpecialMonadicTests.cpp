#include "SpecialMonadicTests.h"

#include "TestUtilities.h"
#include "tiny/optional.h"

#include <vector>


void test_SpecialTestsFor_and_then()
{
  // Check that modification of the payload works from within the function called by and_then.
  {
    tiny::optional<std::vector<int>> o{{40}};
    ASSERT_TRUE(o.value().size() == 1);

    o.and_then([](auto & vec) {
      vec.push_back(42);
      return tiny::optional<int>{};
    });
    ASSERT_TRUE(o.value().size() == 2);
    ASSERT_TRUE(o->at(1) == 42);
  }

  // Check that moving out the payload works from within the function called by and_then.
  {
    tiny::optional<std::vector<int>> o{{40}};
    ASSERT_TRUE(o.value().size() == 1);

    std::vector<int> movedTo;
    std::move(o).and_then([&](auto && vec) {
      movedTo = std::move(vec);
      return tiny::optional<int>{};
    });
    ASSERT_TRUE(o.value().empty());
    ASSERT_TRUE(movedTo.at(0) == 40);
  }
}


void test_SpecialTestsFor_transform()
{
  // Check that modification of the payload works from within the function called by transform.
  {
    tiny::optional<std::vector<int>> o{{40}};
    ASSERT_TRUE(o.value().size() == 1);

    o.transform([](auto & vec) {
      vec.push_back(42);
      return 1;
    });
    ASSERT_TRUE(o.value().size() == 2);
    ASSERT_TRUE(o->at(1) == 42);
  }

  // Check that moving out the payload works from within the function called by transform.
  {
    tiny::optional<std::vector<int>> o{{40}};
    ASSERT_TRUE(o.value().size() == 1);

    std::vector<int> movedTo;
    std::move(o).transform([&](auto && vec) {
      movedTo = std::move(vec);
      return 1;
    });
    ASSERT_TRUE(o.value().empty());
    ASSERT_TRUE(movedTo.at(0) == 40);
  }

  // transform() is supposed to work even if the type returned by the called function is neither copyable nor moveable.
  // This is the stuff with DirectInitializationFromFunctionTag in the implementation. Check that this is true.
  {
    struct NonCopyableAndNonMovable
    {
      int value;

      explicit NonCopyableAndNonMovable(int value)
        : value(value)
      {
      }

      NonCopyableAndNonMovable(NonCopyableAndNonMovable const &) = delete;
      NonCopyableAndNonMovable(NonCopyableAndNonMovable &&) = delete;
    };

    tiny::optional<int> original = 42;
    tiny::optional<NonCopyableAndNonMovable> transformed
        = original.transform([](int v) { return NonCopyableAndNonMovable{v}; });
    ASSERT_TRUE(transformed.value().value == 42);
  }
}


void test_SpecialTestsFor_or_else()
{
#ifdef TINY_OPTIONAL_ENABLE_ORELSE
  // Check that or_else moves out the payload when called on a rvalue.
  {
    tiny::optional<std::vector<int>> origOpt{{40}};
    ASSERT_TRUE(origOpt.value().size() == 1);

    tiny::optional<std::vector<int>> newOpt = std::move(origOpt).or_else([]() -> decltype(origOpt) { FAIL(); });
    ASSERT_TRUE(newOpt.value().size() == 1);
    ASSERT_TRUE(newOpt->at(0) == 40);

    // Core check: The original optional should contain an empty vector because it was moved out.
    ASSERT_TRUE(origOpt.has_value()); // NOLINT(clang-analyzer-cplusplus.Move)
    ASSERT_TRUE(origOpt->empty());
  }
  // Similar test, but with a move-only type.
  {
    tiny::optional<std::unique_ptr<int>> origOpt{std::make_unique<int>(42)};
    ASSERT_TRUE(origOpt.value() != nullptr);

    tiny::optional<std::unique_ptr<int>> newOpt = std::move(origOpt).or_else([]() -> decltype(origOpt) { FAIL(); });
    ASSERT_TRUE(newOpt.value() != nullptr);
    ASSERT_TRUE(*newOpt.value() == 42);

    // Core check: The original optional should contain an pointer because it was moved out.
    ASSERT_TRUE(origOpt.has_value());
    ASSERT_TRUE(origOpt.value() == nullptr);
  }
#endif
}
