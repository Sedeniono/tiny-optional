cmake_minimum_required(VERSION 3.21)

add_executable(tiny_optional_tests)

target_sources(tiny_optional_tests PRIVATE
    TestUtilities.h
    ComparisonTests.cpp
    ComparisonTests.h
    CompilationBase.cpp
    CompilationBase.h
    CompilationErrorTests.cpp
    CompilationErrorTests.h
    ConstructionTests.cpp
    ConstructionTests.h
    ExerciseOptionalAIP.cpp
    ExerciseOptionalAIP.h
    ExerciseOptionalEmptyViaType.cpp
    ExerciseOptionalEmptyViaType.h
    ExerciseOptionalInplace.cpp
    ExerciseOptionalInplace.h
    ExerciseOptionalWithCustomFlagManipulator.cpp
    ExerciseOptionalWithCustomFlagManipulator.h
    Exercises.h
    ExerciseStdOptional.cpp
    ExerciseStdOptional.h
    ExerciseTinyOptionalPayload.h
    ExerciseTinyOptionalPayload1.cpp
    ExerciseTinyOptionalPayload2.cpp
    GccLikeCompilation.cpp
    GccLikeCompilation.h
    IntermediateTests.cpp
    IntermediateTests.h
    MsvcCompilation.cpp
    MsvcCompilation.h
    NatvisTests.cpp
    NatvisTests.h
    SpecialMonadicTests.cpp
    SpecialMonadicTests.h
    Tests.cpp
    TestTypes.h
    TestUtilities.cpp
    "${PROJECT_SOURCE_DIR}/include/tiny_optional.natvis"
)

#---------------------------------------------------------------
# Compilation flags

# We need to build and run the tests for all sorts of compilers and compilation flags. We could use the
# abstraction cmake usually promotes and introduce cmake variables to control e.g. if fast-math 
# (--ffast-math for gcc/clang, /fp:fast for msvc) is enabled or not. The GitHub workflows would then set
# the variables accordingly.
# However, we also need to pass the compilation flags to the program (for the build failure tests). This
# could be done by checking the cmake variables (default ones like CMAKE_BUILD_TYPE or CMAKE_CXX_STANDARD;
# and custom ones like one for fast-math) and re-building the compilation flags, which would be quite
# error prone. Alternatively, we could parse the compile_commands.json file that cmake generates. But it
# isn't generated for all multi-configuration generators.
# The GitHub workflows are already necessarily tied to a specific compiler and OS, because they need to
# install e.g. the correct gcc version. So having the cmake abstraction doesn't really help us here. It
# just introduces unnecessary complexity.
# Basically, the difference to normal projects is that are interested in so many different combinations.
# And the compiler invocation itself is part of what is being tested.
# In the end, we let the callers of cmake specify the raw flags. They are forward to the tests via
# configure_file() below. Since this approach is fundamentally incompatible with multi-configuration
# generators, we also enforce that only a single configuration exists.
if (CMAKE_BUILD_TYPE)
    message(FATAL_ERROR
        "Do not use CMAKE_BUILD_TYPE (set to ${CMAKE_BUILD_TYPE}). "
        "See comment in the source above this message for details.")
endif()
if (NOT CMAKE_CONFIGURATION_TYPES STREQUAL "Build")
    message(FATAL_ERROR
        "Expected CMAKE_CONFIGURATION_TYPES to be 'Build'. "
        "See comment in the source above this message for details.")
endif()

set(TINY_OPTIONAL_ADDITIONAL_FLAGS "" CACHE STRING
    "Flags that differ between builds of the tests,and thus are set by the callers.")
separate_arguments(ADDITIONAL_FLAGS_AS_LIST NATIVE_COMMAND "${TINY_OPTIONAL_ADDITIONAL_FLAGS}")

if (MSVC)
    set(DEFAULT_FLAGS /W4 /WX /bigobj /sdl /MP /Zi /Zc:wchar_t /Zc:forScope /Zc:inline)
else()
    set(DEFAULT_FLAGS -Wall -Wextra -pedantic -Wconversion -Werror -g)
endif()

set(ALL_FLAGS ${DEFAULT_FLAGS} ${ADDITIONAL_FLAGS_AS_LIST})

target_compile_options(tiny_optional_tests PRIVATE ${ALL_FLAGS})

target_link_libraries(tiny_optional_tests PRIVATE tiny-optional::tiny-optional)

target_link_options(tiny_optional_tests PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/DEBUG>)

set_property(DIRECTORY "${PROJECT_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT tiny_optional_tests)

if (MSVC)
    # Enable some additional common optimizations with /O2.
    if ("/O2" IN_LIST ADDITIONAL_FLAGS_AS_LIST)
        target_link_options(tiny_optional_tests PRIVATE /OPT:REF /OPT:ICF)
    endif()
    # Link-time optimization requires corresponding linker flags.
    if ("/GL" IN_LIST ADDITIONAL_FLAGS_AS_LIST)
        target_link_options(tiny_optional_tests PRIVATE /LTCG /INCREMENTAL:NO)
    endif()
else()
    # We especially need to pass on architecture flags (-m32/-m64).
    target_link_options(tiny_optional_tests PRIVATE ${ADDITIONAL_FLAGS_AS_LIST})
endif()


#---------------------------------------------------------------
# Generate header file with the compiler path and flags.
# Used by tests that check if certain code snippets that should not compile actually fail, and fail correctly.

set(TINY_OPTIONAL_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
list(JOIN ALL_FLAGS " " COMPILATION_FLAGS)
set(COMPILER_PATH "${CMAKE_CXX_COMPILER}")

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/TestBuildFlags.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/generated/TestBuildFlags.h"
    @ONLY)

target_include_directories(tiny_optional_tests PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/generated")
target_sources(tiny_optional_tests PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/generated/TestBuildFlags.h")

#---------------------------------------------------------------

add_test(NAME tiny_optional_tests COMMAND tiny_optional_tests)
