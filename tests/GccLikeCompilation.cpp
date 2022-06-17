#include "GccLikeCompilation.h"

#include "TestUtilities.h"

#include <iostream>

GccLikeCompilationChecks::GccLikeCompilationChecks(
    std::filesystem::path const & executable,
    std::filesystem::path const & tinyOptionalIncludeDir,
    std::string const & compilationFlags)
  : mExecutable(executable)
  , mTinyOptionalIncludeDir(weakly_canonical(tinyOptionalIncludeDir))
  , mCompilationFlags(compilationFlags)
{
  mExecutable.make_preferred();
}


void GccLikeCompilationChecks::PrintInputOptions(std::ostream & out) const
{
  out << "\t==> Compiler: " << mExecutable << std::endl;
  out << "\t==> TinyOptional include directory: " << mTinyOptionalIncludeDir << std::endl;
  out << "\t==> Flags: " << mCompilationFlags << std::endl;
}


auto GccLikeCompilationChecks::PerformCompilation(std::string const & code) const -> ExecutionResult
{
#ifdef TINY_OPTIONAL_WINDOWS_BUILD
  // Piping strings with new lines and containing quotation marks into clang on Windows is cumbersome.
  // So instead just use a temporary file. Especially since we have the required mechanism anyway for the 
  // MSVC version.
  WindowsTemporaryCodeFileScope tempCodeFileScope(code);

  // Output to NUL corresponds kind-of to /dev/null on linux. It prevents the creation of a file.
  std::string command = mExecutable.string() + " " + mCompilationFlags + " -I\"" + mTinyOptionalIncludeDir.string()
                        + "\" -c -x c++ -o NUL \"" + tempCodeFileScope.GetFullFilename().string() + "\"";
#else
  std::string command = "printf \"%s\" '" + code + "' | " + mExecutable.string() + " " + mCompilationFlags + " -I\""
                        + mTinyOptionalIncludeDir.string() + "\" -c -x c++ -o /dev/null -";
#endif

  return ExecuteProgramSync(command);
}
