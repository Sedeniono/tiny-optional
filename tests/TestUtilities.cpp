#include "TestUtilities.h"

#include <fstream>
#include <stdexcept>
#include <utility>
#include <cstdio>

#ifdef TINY_OPTIONAL_WINDOWS_BUILD
  #include <Windows.h>
#endif


#ifdef TINY_OPTIONAL_WINDOWS_BUILD

namespace
{
class CloseHandleScope
{
public:
  explicit CloseHandleScope(HANDLE & handle)
    : mHandle(handle)
  {
  }

  ~CloseHandleScope()
  {
    Close();
  }

  void Close()
  {
    if (mHandle != NULL) {
      CloseHandle(mHandle);
      mHandle = NULL;
    }
  }

private:
  HANDLE & mHandle;
};
} // namespace


ExecutionResult ExecuteProgramSync(std::string const & commandline)
{
  // Based on:
  // https://docs.microsoft.com/en-us/windows/win32/procthread/creating-a-child-process-with-redirected-input-and-output
  // https://gitlab.com/eidheim/tiny-process-library/-/blob/master/process_win.cpp

  //-----------------------------
  // Run the program.

  std::cerr << "MSVC: ExecuteProgramSync 1" << std::endl;

  SECURITY_ATTRIBUTES saAttr;
  saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
  saAttr.bInheritHandle = TRUE;
  saAttr.lpSecurityDescriptor = NULL;

  HANDLE hReadFromChild = NULL;
  HANDLE hWriteToChild = NULL;
  CloseHandleScope readHandleScope(hReadFromChild);
  CloseHandleScope writeHandleScope(hWriteToChild);

  if (!CreatePipe(&hReadFromChild, &hWriteToChild, &saAttr, 0)) {
    throw std::runtime_error(
        "Failed to open pipe to communicate with child process. Last error code: " + std::to_string(::GetLastError()));
  }
  if (!SetHandleInformation(hReadFromChild, HANDLE_FLAG_INHERIT, 0)) {
    throw std::runtime_error("Failed to set HANDLE_FLAG_INHERIT. Last error code: " + std::to_string(::GetLastError()));
  }

  PROCESS_INFORMATION piProcInfo;
  STARTUPINFOA siStartInfo;
  ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
  ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));

  CloseHandleScope threadScope(piProcInfo.hThread);
  CloseHandleScope processScope(piProcInfo.hProcess);

  siStartInfo.cb = sizeof(STARTUPINFO);
  siStartInfo.hStdError = hWriteToChild;
  siStartInfo.hStdOutput = hWriteToChild;
  siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

  std::cerr << "MSVC: ExecuteProgramSync 2" << std::endl;

  std::string commandlineCopy = commandline;
  BOOL const bSuccess = CreateProcessA(
      NULL,
      commandlineCopy.data(), // command line
      NULL, // process security attributes
      NULL, // primary thread security attributes
      TRUE, // handles are inherited
      0, // creation flags
      NULL, // use parent's environment
      NULL, // use parent's current directory
      &siStartInfo, // STARTUPINFO pointer
      &piProcInfo); // receives PROCESS_INFORMATION

  std::cerr << "MSVC: ExecuteProgramSync 3" << std::endl;

  if (!bSuccess) {
    throw std::runtime_error("CreateProcess failed with error code " + std::to_string(::GetLastError()));
  }

  threadScope.Close();
  writeHandleScope.Close();


  //-----------------------------
  // Read stdout and stdderr until the process terminates.
  std::cerr << "MSVC: ExecuteProgramSync 4" << std::endl;
  std::string receivedOutput;

  {
    static constexpr DWORD BUFFER_SIZE = 1024;
    CHAR chBuf[BUFFER_SIZE] = { 0 };

    while (true) {
      DWORD dwRead = 0;
      BOOL const bReadSuccess = ReadFile(hReadFromChild, chBuf, BUFFER_SIZE, &dwRead, NULL);
      if (!bReadSuccess || dwRead == 0) {
        break;
      }

      receivedOutput += std::string(chBuf, dwRead);
    }
  }
  std::cerr << "MSVC: ExecuteProgramSync 5" << std::endl;
  //-----------------------------
  // Check exit code of the process.

  DWORD exitCode = static_cast<DWORD>(-1);
  if (!GetExitCodeProcess(piProcInfo.hProcess, &exitCode)) {
    throw std::runtime_error("GetExitCodeProcess failed with error code " + std::to_string(::GetLastError()));
  }
  if (exitCode == STILL_ACTIVE) {
    throw std::runtime_error("Process did not exit yet although it should have.");
  }
  std::cerr << "MSVC: ExecuteProgramSync 6" << std::endl;
  return ExecutionResult{commandline, static_cast<int>(exitCode), std::move(receivedOutput)};
}

#else // Not Windows, assume that popen() does what we want.

ExecutionResult ExecuteProgramSync(std::string const & commandline)
{
  // Redirect stderr, too.
  std::string const fullCmd = commandline + " 2>&1";
  FILE * file = popen(fullCmd.c_str(), "r");
  if (file == nullptr) {
    throw std::runtime_error("popen failed for command: " + fullCmd);
  }

  std::string receivedOutput;

  static constexpr size_t BUFFER_SIZE = 1024;
  char buffer[BUFFER_SIZE] = { 0 };
  while (fgets(buffer, BUFFER_SIZE, file) != nullptr) {
    receivedOutput += buffer;
  }

  int const exitCode = pclose(file);
  if (exitCode == -1) {
    throw std::runtime_error("pclose failed");
  }

  return ExecutionResult{fullCmd, WEXITSTATUS(exitCode), std::move(receivedOutput)};
}

#endif


//======================================================================================
// WindowsTemporaryCodeFileScope
//======================================================================================

#ifdef TINY_OPTIONAL_WINDOWS_BUILD

namespace
{
std::filesystem::path CreateTemporaryCodeFile(std::string const & code)
{
  std::string const newDirName
      = "tiny_optional_tests_" + std::to_string(GetCurrentProcessId()) + "_" + std::to_string(GetCurrentThreadId());

  auto const tempDir = std::filesystem::temp_directory_path() / newDirName;
  if (std::filesystem::is_directory(tempDir)) {
    std::filesystem::remove_all(tempDir);
  }
  std::filesystem::create_directory(tempDir);

  auto const tempFile = tempDir / "temp_tiny_optional_test.cpp";

  // Overwrite a possibly existing file.
  std::ofstream out;
  out.open(tempFile);
  if (!out) {
    throw std::runtime_error("Failed to open temporary code file: " + tempFile.string());
  }

  out << code << std::endl;
  if (!out) {
    throw std::runtime_error("Failed to write to temporary code file: " + tempFile.string());
  }

  out.close();

  if (!std::filesystem::exists(tempFile)) {
    throw std::runtime_error("Written temporary file does not exist after writing: " + tempFile.string());
  }

  return std::filesystem::absolute(tempFile);
}

} // namespace

WindowsTemporaryCodeFileScope::WindowsTemporaryCodeFileScope(std::string const & code)
  : mCodeFile(CreateTemporaryCodeFile(code))
{
}


WindowsTemporaryCodeFileScope ::~WindowsTemporaryCodeFileScope()
{
  auto const tempDir = GetDirectory();
  if (std::filesystem::is_directory(tempDir)) {
    std::filesystem::remove_all(tempDir);
  }
}


#endif
