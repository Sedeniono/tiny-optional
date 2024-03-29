#pragma once

#include <iosfwd>
#include <memory>
#include <string>

struct ExecutionResult;

class CompilationChecksBase
{
public:
  virtual ~CompilationChecksBase() = default;

  // Test that the code snippet does not compile and that the error message contains the expected regex expression.
  // Returns an empty string in case this test succeeds (i.e. in case it did not compile as expected).
  // Otherwise, returns a string containing what was done (so that one can figure out why the test failed).
  std::string CheckDoesNotCompile(std::string const & codeSnippet, std::string const & expectedRegex) const;

  virtual void PrintInputOptions(std::ostream & out) const = 0;

protected:
  virtual ExecutionResult PerformCompilation(std::string const & code) const = 0;

private:
  static std::string FormatInfo(std::string const & code, ExecutionResult const & result);
};


std::unique_ptr<CompilationChecksBase> CreateCompilationChecker();
