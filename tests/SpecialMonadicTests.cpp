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
