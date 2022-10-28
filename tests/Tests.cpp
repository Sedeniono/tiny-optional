#include "ComparisonTests.h"
#include "CompilationErrorTests.h"
#include "ConstructionTests.h"
#include "ExerciseOptionalEmptyViaType.h"
#include "ExerciseOptionalInplace.h"
#include "ExerciseStdOptional.h"
#include "ExerciseTinyOptionalPayload.h"
#include "IntermediateTests.h"
#include "TestUtilities.h"
#include "tiny/optional.h"

#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

#ifdef TINY_OPTIONAL_WINDOWS_BUILD
  #include <crtdbg.h>
#endif

void RunTests()
{
#define ADD_TEST(x) {x, #x}

  std::vector<std::pair<void (*)(), std::string>> const tests
      = {ADD_TEST(test_IsIntegralInRange),
         ADD_TEST(test_NanExploit),
         ADD_TEST(test_SelectDecomposition),
         ADD_TEST(test_NanExploit),
         ADD_TEST(test_TinyOptionalPayload_Bool),
         ADD_TEST(test_TinyOptionalPayload_FloatingPoint),
         ADD_TEST(test_TinyOptionalPayload_IntegersAndEnums),
         ADD_TEST(test_TinyOptionalPayload_IsEmptyFlagInMember),
         ADD_TEST(test_TinyOptionalPayload_Pointers),
         ADD_TEST(test_TinyOptionalPayload_StdTypes),
         ADD_TEST(test_TinyOptionalPayload_NestedOptionals),
         ADD_TEST(test_TinyOptionalPayload_ConstAndVolatile),
         ADD_TEST(test_TinyOptionalPayload_Cpp20NTTP),
         ADD_TEST(test_TinyOptionalPayload_OtherTypes),
         ADD_TEST(test_TinyOptionalMemoryManagement),
         ADD_TEST(test_TinyOptionalCopyConstruction),
         ADD_TEST(test_TinyOptionalMoveConstruction),
         ADD_TEST(test_TinyOptionalCopyAssignment),
         ADD_TEST(test_TinyOptionalMoveAssignment),
         ADD_TEST(test_TinyOptionalConversions),
         ADD_TEST(test_OptionalEmptyViaType),
         ADD_TEST(test_OptionalInplace),
         ADD_TEST(test_CrosscheckStdOptional),
         ADD_TEST(test_Exceptions),
         ADD_TEST(test_MakeOptional),
         ADD_TEST(test_Comparisons),
         ADD_TEST(test_ExpressionsThatShouldNotCompile)};

  for (size_t testIdx = 0; testIdx < tests.size(); ++testIdx) {
    auto const [testFunc, testName] = tests.at(testIdx);
    std::cout << "Running: " << testName << std::endl;
    testFunc();
  }
}


int main()
{
#ifdef TINY_OPTIONAL_WINDOWS_BUILD
  // Explicitly disable the creation of windows due to assert(). I suspect this might cause problems in the github
  // action runners (a window might pop up and prevent the termination of the runners because the window waits for user
  // input which will never come).
  _set_error_mode(_OUT_TO_STDERR);
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif

  try {
    std::cout << "Running tests..." << std::endl;
    RunTests();
    std::cout << "All tests PASSED" << std::endl;
    return 0;
  }
  catch (std::exception const & ex) {
    std::cerr << "ERROR: Caught exception: " << ex.what() << " (type: " << typeid(ex).name() << ")" << std::endl;
    assert(false);
    return 44;
  }
  catch (...) {
    std::cerr << "ERROR: Caught unknown exception." << std::endl;
    assert(false);
    return 45;
  }
}
