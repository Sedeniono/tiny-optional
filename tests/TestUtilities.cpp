#include "TestUtilities.h"

#include <array>
#include <cstdio>
#include <exception>
#include <fstream>
#include <stdexcept>
#include <utility>

#ifdef TINY_OPTIONAL_WINDOWS_BUILD
  #include <Windows.h>
#endif

#if defined(TINY_OPTIONAL_x64) || defined(TINY_OPTIONAL_x86)
  #ifdef TINY_OPTIONAL_MSVC_BUILD
    #include <intrin.h>
  #elif defined(TINY_OPTIONAL_CLANG_BUILD) || defined(TINY_OPTIONAL_GCC_BUILD)
    #include <cpuid.h>
  #else
    #error Unsupported compiler for cpuid
  #endif
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

  if (!bSuccess) {
    throw std::runtime_error("CreateProcess failed with error code " + std::to_string(::GetLastError()));
  }

  threadScope.Close();
  writeHandleScope.Close();


  //-----------------------------
  // Read stdout and stdderr until the process terminates.
  std::string receivedOutput;

  {
    static constexpr DWORD BUFFER_SIZE = 1024;
    CHAR chBuf[BUFFER_SIZE] = {0};

    while (true) {
      DWORD dwRead = 0;
      BOOL const bReadSuccess = ReadFile(hReadFromChild, chBuf, BUFFER_SIZE, &dwRead, NULL);
      if (!bReadSuccess || dwRead == 0) {
        break;
      }

      receivedOutput += std::string(chBuf, dwRead);
    }
  }

  //-----------------------------
  // Check exit code of the process.

  DWORD exitCode = static_cast<DWORD>(-1);
  if (!GetExitCodeProcess(piProcInfo.hProcess, &exitCode)) {
    throw std::runtime_error("GetExitCodeProcess failed with error code " + std::to_string(::GetLastError()));
  }
  if (exitCode == STILL_ACTIVE) {
    throw std::runtime_error("Process did not exit yet although it should have.");
  }
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
  char buffer[BUFFER_SIZE] = {0};
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
    // Try several times to remove the directory. It often happens that files that were opened by now exited processes
    // are still locked for a short amount of time.
    std::error_code ec;
    size_t attempt = 0;
    do {
      if (attempt > 0) {
        Sleep(1000);
      }
      ec = {};
      std::filesystem::remove_all(tempDir, ec);
      ++attempt;
    }
    while (ec && attempt < 60);

    if (ec) {
      // Stop the tests. Note that we cannot throw an exception from within a destructor.
      std::cerr << "Error: Failed to remove temporary directory '" << tempDir << "' after several attempts."
                << std::endl;
      std::terminate();
    }
  }
}


#endif


//======================================================================================
// cpuid stuff
//======================================================================================

#if defined(TINY_OPTIONAL_x64) || defined(TINY_OPTIONAL_x86)

// Calls cpuid, returning eax, ebx, ecx and edx in that order.
static std::array<std::uint32_t, 4> cpuid(std::uint32_t function_id, std::uint32_t subfunction_id = 0)
{
  std::array<std::uint32_t, 4> regs{};

  #if defined(TINY_OPTIONAL_MSVC_BUILD)
  __cpuidex(reinterpret_cast<int *>(regs.data()), function_id, subfunction_id);
  #elif defined(TINY_OPTIONAL_CLANG_BUILD) || defined(TINY_OPTIONAL_GCC_BUILD)
  __cpuid_count(function_id, subfunction_id, regs[0], regs[1], regs[2], regs[3]);
  #else
    #error Unsupported compiler
  #endif

  return regs;
}


// Returns the number of bits the CPU uses for virtual addresses.
// Returns 48 on most current CPUs.
// Based on https://stackoverflow.com/a/64519023/3740047
static std::uint32_t GetVirtualAddressBits()
{
  std::uint32_t virtualAddressSize;

  auto const extInfo = cpuid(0x80000000U);
  if (extInfo[0] < 0x80000008U) {
    virtualAddressSize = 32;
  }
  else {
    auto const memInfo = cpuid(0x80000008U);
    virtualAddressSize = (memInfo[0] >> 8) & 0xFF;
  }

  return virtualAddressSize;
}


bool IsAddressNonCanonical(std::uint64_t addr)
{
  // See SentinelForExploitingUnusedBits for more information.

  // Returns 48 on most CPUs.
  std::uint64_t const virtualAddressBits = GetVirtualAddressBits();

  // If the CPU uses 48 bits, this is 0x0000'7fff'ffff'ffff.
  std::uint64_t const maxCanonicalLow = (1ULL << (virtualAddressBits - 1)) - 1;
  // If the CPU uses 48 bits, this is 0xffff'8000'0000'0000.
  std::uint64_t const minCanonicalHigh = ~maxCanonicalLow;

  return maxCanonicalLow < addr && addr < minCanonicalHigh;
}

#endif
