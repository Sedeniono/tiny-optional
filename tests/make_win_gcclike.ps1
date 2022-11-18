# Generic "makefile" like powershell script to compile and run the tests
# using clang or gcc on windows.

$ErrorActionPreference = "Stop"

# Get input variables from environment if they are defined there.
if ($null -ne $env:CXX) { $CXX = $env:CXX }
if ($null -ne $env:ADDITIONAL_FLAGS) { $ADDITIONAL_FLAGS = -split $env:ADDITIONAL_FLAGS }
if ($null -ne $env:OUT_DIR_NAME) { $OUT_DIR_NAME = $env:OUT_DIR_NAME }

$WARNING_FLAGS = "-Wall", "-Wextra", "-pedantic", "-Wconversion", "-Werror"
$CPP_FILES = "ComparisonTests.cpp", "CompilationBase.cpp", "CompilationErrorTests.cpp", "ConstructionTests.cpp", "ExerciseOptionalEmptyViaType.cpp", "ExerciseOptionalInplace.cpp", "ExerciseStdOptional.cpp", "ExerciseTinyOptionalPayload1.cpp", "ExerciseTinyOptionalPayload2.cpp", "ExerciseTinyOptionalPayload3.cpp", "ExerciseTinyOptionalPayload4.cpp", "GccLikeCompilation.cpp", "IntermediateTests.cpp", "MsvcCompilation.cpp", "SpecialMonadicTests.cpp", "Tests.cpp", "TestUtilities.cpp"
$TINY_OPTIONAL_INCLUDE_DIR = "../include"
$EXE_NAME = "TinyOptionalTests.exe"

$TINY_OPTIONAL_TESTS_COMPILER_EXECUTABLE = '-DTINY_OPTIONAL_TESTS_COMPILER_EXECUTABLE=' + '\"' + $CXX + '\"'
$TINY_OPTIONAL_TESTS_HEADER_INCLUDE_DIR = '-DTINY_OPTIONAL_TESTS_HEADER_INCLUDE_DIR=' + '\"' + $TINY_OPTIONAL_INCLUDE_DIR +'\"'
$TINY_OPTIONAL_TESTS_COMPILATION_FLAGS = '-DTINY_OPTIONAL_TESTS_COMPILATION_FLAGS=' + '""' + $WARNING_FLAGS + ' ' + $ADDITIONAL_FLAGS + '""'

$OUT_DIR = "../bin/" + $OUT_DIR_NAME
$FULL_EXE_PATH = $OUT_DIR + "/" + $EXE_NAME


# Cross check input
if ([string]::IsNullOrEmpty($CXX)) {
    echo "CXX is null"
    exit 50
}
if ([string]::IsNullOrEmpty($ADDITIONAL_FLAGS)) {
    echo "ADDITIONAL_FLAGS is null"
    exit 51
}
if ([string]::IsNullOrEmpty($OUT_DIR_NAME)) {
    echo "OUT_DIR_NAME is null"
    exit 52
}



echo "Creating directory if it does not exist: $OUT_DIR"
New-Item -ItemType Directory -Force -Path "$OUT_DIR" | Out-Null

echo "Removing existing executable if it exists: $FULL_EXE_PATH"
rm "$FULL_EXE_PATH" -ErrorAction Ignore

echo "Compiling using CXX='$CXX' with ADDITIONAL_FLAGS='$ADDITIONAL_FLAGS' and OUT_DIR_NAME='$OUT_DIR_NAME'. FULL_EXE_PATH='$FULL_EXE_PATH'"
& "$CXX" -o "$FULL_EXE_PATH"  @WARNING_FLAGS  @ADDITIONAL_FLAGS  -I $TINY_OPTIONAL_INCLUDE_DIR  `
    $TINY_OPTIONAL_TESTS_COMPILER_EXECUTABLE  $TINY_OPTIONAL_TESTS_HEADER_INCLUDE_DIR  $TINY_OPTIONAL_TESTS_COMPILATION_FLAGS  `
    @CPP_FILES
$CompilationResult = $LASTEXITCODE
if ($CompilationResult -ne 0) {
    echo "Compilation failed"
    exit $CompilationResult
}

echo "Executing tests: $FULL_EXE_PATH"
& "$FULL_EXE_PATH"
exit $LASTEXITCODE

