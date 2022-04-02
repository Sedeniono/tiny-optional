#include "TestMsvcCompilation.h"

#include "TestUtilities.h"

#ifdef TINY_OPTIONAL_WINDOWS_BUILD
  #include <Windows.h>
  #include <filesystem>
  #include <regex>
  #include <sstream>
  #include <iostream>
#endif


#ifdef TINY_OPTIONAL_WINDOWS_BUILD
MsvcCompilationChecks::MsvcCompilationChecks(
    std::filesystem::path const & vcvarsBatFile,
    std::filesystem::path const & tinyOptionalIncludeDir,
    std::string const & compilationFlags)
  : mVcvarsBatFile(vcvarsBatFile)
  , mTinyOptionalIncludeDir(weakly_canonical(tinyOptionalIncludeDir))
  , mCompilationFlags(compilationFlags)
{
  mVcvarsBatFile.make_preferred();
}


void MsvcCompilationChecks::PrintInputOptions(std::ostream & out) const
{
  out << "\t==> vcvars: " << mVcvarsBatFile << std::endl;
  out << "\t==> TinyOptional include directory: " << mTinyOptionalIncludeDir << std::endl;
  out << "\t==> Flags: " << mCompilationFlags << std::endl;
}


auto MsvcCompilationChecks::PerformCompilation(std::string const & code) const -> ExecutionResult
{
  // cl.exe cannot read from stdin, so we need to put the code into a temporary file.
  WindowsTemporaryCodeFileScope tempFileScope(code);
  auto const tempCodeFilename = tempFileScope.GetFilename();
  auto const tempDirectory = tempFileScope.GetDirectory();

  // clang-format off
  // 
  // We run cmd.exe because we need to setup an environment via the vcvars*.bat file. Running cl.exe directly will not work since it
  // will fail to find even the STL headers.
  std::string batchCmd = 
    // /S/C are the options to cmd.exe. Everything afterwards is surrounded by "".
    "cmd.exe /S/C " 
    // Surround everything after the /C with quotes.
    "\""
        // First command: Execute the batch that imports all the necessary environment variables required by cl.exe to actually work.
          "\"" + mVcvarsBatFile.string() + "\"" + " "
        // Second command: Change working directory to where the temporary file is located.
        + "&& cd \"" + tempDirectory.string() + "\" "
        // Third command: Compile. 
        // /c causes the link step to be skipped.
        + "&& cl.exe "
            + mCompilationFlags
            + " /c "
            + "/I\"" + mTinyOptionalIncludeDir.string() + "\" "
            + "\"" + tempCodeFilename.string() + "\""
    // Closing quotation mark for /C of cmd.exe.
    + "\""
  ;
  // clang-format on

  return ExecuteProgramSync(batchCmd);
}


#endif
