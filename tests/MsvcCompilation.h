#pragma once

#include "TestUtilities.h"

#ifdef TINY_OPTIONAL_WINDOWS_BUILD
  #include "CompilationBase.h"

  #include <filesystem>
#endif

// Microsoft MSVC is only available on Windows, and we need to use Windows specific functions to run it. So compile it
// only on Windows.
#ifdef TINY_OPTIONAL_WINDOWS_BUILD
class MsvcCompilationChecks final : public CompilationChecksBase
{
public:
  explicit MsvcCompilationChecks(
      std::filesystem::path const & vcvarsBatFile,
      std::filesystem::path const & tinyOptionalIncludeDir,
      std::string const & compilationFlags);

  virtual void PrintInputOptions(std::ostream & out) const override;

protected:
  virtual ExecutionResult PerformCompilation(std::string const & code) const override;

private:
  std::filesystem::path mVcvarsBatFile;
  std::filesystem::path mTinyOptionalIncludeDir;
  std::string const mCompilationFlags;
};

#endif
