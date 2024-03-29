#pragma once

#include "CompilationBase.h"

#include <filesystem>

// Compilers that follow gcc's syntax (gcc, clang, ...)
class GccLikeCompilationChecks final : public CompilationChecksBase
{
public:
  explicit GccLikeCompilationChecks(
      std::filesystem::path const & executable,
      std::filesystem::path const & tinyOptionalIncludeDir,
      std::string const & compilationFlags);

  virtual void PrintInputOptions(std::ostream & out) const override;

protected:
  virtual ExecutionResult PerformCompilation(std::string const & code) const override;

private:
  std::filesystem::path mExecutable;
  std::filesystem::path mTinyOptionalIncludeDir;
  std::filesystem::path mTinyOptionalIncludeDirCanon;
  std::string const mCompilationFlags;
};
