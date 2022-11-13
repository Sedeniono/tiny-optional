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
