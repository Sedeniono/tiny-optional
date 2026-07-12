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

set(TINY_OPTIONAL_ADDITIONAL_FLAGS "" CACHE STRING
    "Flags that differ between builds of the tests,and thus are set by the callers.")
separate_arguments(ADDITIONAL_FLAGS_AS_LIST NATIVE_COMMAND "${TINY_OPTIONAL_ADDITIONAL_FLAGS}")

if (MSVC)
    set(DEFAULT_FLAGS /W4 /WX /bigobj /sdl)
else()
    set(DEFAULT_FLAGS -Wall -Wextra -pedantic -Wconversion -Werror)
endif()

set(ALL_FLAGS ${DEFAULT_FLAGS} ${ADDITIONAL_FLAGS_AS_LIST})

target_compile_options(tiny_optional_tests PRIVATE ${ALL_FLAGS})

target_link_libraries(tiny_optional_tests PRIVATE tiny-optional::tiny-optional)


#---------------------------------------------------------------

set(TINY_OPTIONAL_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
list(JOIN ALL_FLAGS " " COMPILATION_FLAGS)
set(COMPILER_PATH "${CMAKE_CXX_COMPILER}")

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/TestBuildFlags.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/generated/TestBuildFlags.h"
    @ONLY)

target_include_directories(tiny_optional_tests PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/generated")


#---------------------------------------------------------------

add_test(NAME tiny_optional_tests COMMAND tiny_optional_tests)
