# Generic "makefile" like powershell script to compile and run the tests
# using clang or gcc on windows.

$ErrorActionPreference = "Stop"

# Get input variables from environment if they are defined there.
if ($null -ne $env:CXX) { $CXX = $env:CXX }
if ($null -ne $env:ADDITIONAL_FLAGS) { $ADDITIONAL_FLAGS = -split $env:ADDITIONAL_FLAGS }
if ($null -ne $env:OUT_DIR_NAME) { $OUT_DIR_NAME = $env:OUT_DIR_NAME }

$PS_VERSION_MAJOR = (get-host).Version.Major
$PS_VERSION_MINOR = (get-host).Version.Minor
$PS_VERSION_COMBINED = $PS_VERSION_MAJOR * 1000 + $PS_VERSION_MINOR
echo "Powershell version: $PS_VERSION_MAJOR.$PS_VERSION_MINOR (combined: $PS_VERSION_COMBINED)"

$WARNING_FLAGS = "-Wall", "-Wextra", "-pedantic", "-Wconversion", "-Werror"
$CPP_FILES = "ComparisonTests.cpp", "CompilationBase.cpp", "CompilationErrorTests.cpp", "ConstructionTests.cpp", "ExerciseOptionalAIP.cpp", "ExerciseOptionalEmptyViaType.cpp", "ExerciseOptionalInplace.cpp", "ExerciseOptionalWithCustomFlagManipulator.cpp", "ExerciseStdOptional.cpp", "ExerciseTinyOptionalPayload1.cpp", "ExerciseTinyOptionalPayload2.cpp", "GccLikeCompilation.cpp", "IntermediateTests.cpp", "MsvcCompilation.cpp", "SpecialMonadicTests.cpp", "Tests.cpp", "TestUtilities.cpp"
$TINY_OPTIONAL_INCLUDE_DIR = "../include"
$EXE_NAME = "TinyOptionalTests.exe"

# The quotation escape rules changed in powershell 7.3 (probably: https://github.com/PowerShell/PowerShell/issues/1995)
if ($PS_VERSION_COMBINED -le 7002) {
    echo "Using old escape rules"
    $TINY_OPTIONAL_TESTS_COMPILER_EXECUTABLE = '-DTINY_OPTIONAL_TESTS_COMPILER_EXECUTABLE=' + '\"' + $CXX + '\"'
    $TINY_OPTIONAL_TESTS_HEADER_INCLUDE_DIR = '-DTINY_OPTIONAL_TESTS_HEADER_INCLUDE_DIR=' + '\"' + $TINY_OPTIONAL_INCLUDE_DIR +'\"'
    $TINY_OPTIONAL_TESTS_COMPILATION_FLAGS = '-DTINY_OPTIONAL_TESTS_COMPILATION_FLAGS=' + '""' + $WARNING_FLAGS + ' ' + $ADDITIONAL_FLAGS + '""'    
}
else {
    echo "Using new escape rules"
    $TINY_OPTIONAL_TESTS_COMPILER_EXECUTABLE = '-DTINY_OPTIONAL_TESTS_COMPILER_EXECUTABLE=' + '"' + $CXX + '"'
    $TINY_OPTIONAL_TESTS_HEADER_INCLUDE_DIR = '-DTINY_OPTIONAL_TESTS_HEADER_INCLUDE_DIR=' + '"' + $TINY_OPTIONAL_INCLUDE_DIR +'"'
    $TINY_OPTIONAL_TESTS_COMPILATION_FLAGS = '-DTINY_OPTIONAL_TESTS_COMPILATION_FLAGS=' + '"' + $WARNING_FLAGS + ' ' + $ADDITIONAL_FLAGS + '"'
}

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

echo "TINY_OPTIONAL_TESTS_COMPILER_EXECUTABLE: $TINY_OPTIONAL_TESTS_COMPILER_EXECUTABLE"
echo "TINY_OPTIONAL_TESTS_HEADER_INCLUDE_DIR: $TINY_OPTIONAL_TESTS_HEADER_INCLUDE_DIR"
echo "TINY_OPTIONAL_TESTS_COMPILATION_FLAGS: $TINY_OPTIONAL_TESTS_COMPILATION_FLAGS"

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

