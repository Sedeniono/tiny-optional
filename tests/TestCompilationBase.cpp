#include "TestCompilationBase.h"

#include "TestGccLikeCompilation.h"
#include "TestMsvcCompilation.h"
#include "TestUtilities.h"

#include <regex>
#include <sstream>


std::string CompilationChecksBase::CheckDoesNotCompile(
    std::string const & codeSnippet,
    std::string const & expectedRegex) const
{
  std::string const code = CompleteCppCodeSnippet(codeSnippet);
  ExecutionResult const result = PerformCompilation(code);

  // 0 means the compilation succeeded, but we expect a failure.
  if (result.exitCode == 0) {
    return "ERROR: The compilation succeeded unexpectedly (exit code == " + std::to_string(result.exitCode)
           + "). Expected that it fails and includes the regex \"" + expectedRegex + "\" in the compiler's output.\n"
           + FormatInfo(code, result);
  }
  else {
    std::regex r(expectedRegex);
    bool const foundExpected = std::regex_search(result.output, r);
    if (!foundExpected) {
      return "ERROR: Failed to find the expected regex \"" + expectedRegex + "\" in the compiler's output.\n"
             + FormatInfo(code, result);
    }
  }

  return {};
}


namespace
{
std::string
    PrependToEveryLine(std::string const & original, std::string const & toPrepend, bool includeLineNumbers = false)
{
  std::stringstream s(original);
  std::string line;
  std::stringstream modified;
  int lineNumber = 1;
  while (std::getline(s, line)) {
    modified << toPrepend;
    if (includeLineNumbers) {
      modified << std::setw(2) << lineNumber << " ";
    }
    modified << line << "\n";
    ++lineNumber;
  }
  return modified.str();
}
} // namespace


std::string CompilationChecksBase::FormatInfo(std::string const & code, ExecutionResult const & result)
{
  std::stringstream s;

  s << "Compiled the following code:\n";
  s << PrependToEveryLine(code, "\t", true) << "\n";
  s << "using the following command:\n";
  s << PrependToEveryLine(result.command, "\t") << "\n";
  s << "It returned exit code " << result.exitCode << "\n";
  s << "and the following output:\n";
  s << PrependToEveryLine(result.output, "\t") << "\n";

  return s.str();
}


std::unique_ptr<CompilationChecksBase> CreateCompilationChecker()
{
#if defined(TINY_OPTIONAL_MSVC_BUILD)
  // E.g.: "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\"
  std::filesystem::path const vcInstallDir = TINY_OPTIONAL_TESTS_VC_INSTALL_DIR;
  // E.g.: vcvars64.bat
  std::string const vcvarsFilename = TINY_OPTIONAL_TESTS_VCVARS_NAME;
  std::filesystem::path fullVcvarsPath = vcInstallDir / "Auxiliary" / "Build" / vcvarsFilename;
  fullVcvarsPath = canonical(fullVcvarsPath);

  std::filesystem::path const tinyOptionalIncludeDir = TINY_OPTIONAL_TESTS_HEADER_INCLUDE_DIR;
  std::string const compilationFlags = TINY_OPTIONAL_TESTS_COMPILATION_FLAGS;

  return std::make_unique<MsvcCompilationChecks>(fullVcvarsPath, tinyOptionalIncludeDir, compilationFlags);

#else
  std::filesystem::path const executable = TINY_OPTIONAL_TESTS_COMPILER_EXECUTABLE;
  std::filesystem::path const tinyOptionalIncludeDir = TINY_OPTIONAL_TESTS_HEADER_INCLUDE_DIR;
  std::string const compilationFlags = TINY_OPTIONAL_TESTS_COMPILATION_FLAGS;
  return std::make_unique<GccLikeCompilationChecks>(executable, tinyOptionalIncludeDir, compilationFlags);
#endif
}
