#include "MsvcCompilation.h"

#include "TestUtilities.h"

#ifdef TINY_OPTIONAL_WINDOWS_BUILD
  #include <Windows.h>
  #include <filesystem>
  #include <iostream>
  #include <regex>
  #include <sstream>
#endif


#ifdef TINY_OPTIONAL_WINDOWS_BUILD

static std::filesystem::path GetVcvarsBatFilePath(std::filesystem::path fullCompilerPath)
{
  // Example:
  // fullCompilerPath: C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.44.35207/bin/Hostx64/x64/cl.exe
  // -> vcvars: C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat

  fullCompilerPath = canonical(fullCompilerPath);

  std::string const arch = fullCompilerPath.parent_path().filename().string();
  std::string vcvarsFilename;
  if (arch == "x86") {
    vcvarsFilename = "vcvars32.bat";
  }
  else if (arch == "x64") {
    vcvarsFilename = "vcvars64.bat";
  }
  else {
    throw std::runtime_error("Unknown architecture: " + arch);
  }

  std::filesystem::path vcInstallDir = fullCompilerPath;
  while (!vcInstallDir.empty() && vcInstallDir.filename() != "VC") {
    vcInstallDir = vcInstallDir.parent_path();
  }
  if (vcInstallDir.empty()) {
    throw std::runtime_error("Failed to find the VC directory in the path: " + fullCompilerPath.string());
  }
  std::filesystem::path const fullVcvarsPath = vcInstallDir / "Auxiliary" / "Build" / vcvarsFilename;
  return canonical(fullVcvarsPath);
}


MsvcCompilationChecks::MsvcCompilationChecks(
    std::filesystem::path const & fullCompilerPath,
    std::filesystem::path const & tinyOptionalIncludeDir,
    std::string const & compilationFlags)
  : mVcvarsBatFile(GetVcvarsBatFilePath(fullCompilerPath))
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
        + "&& cd /D \"" + tempDirectory.string() + "\" "
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
