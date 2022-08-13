# Usage:
# 1) Create a new directory in the "buildtimes" folder
# 2) Open a Visual Studio x64 developer command line prompt in that new folder
# 3) Run powershell.exe
# 4) Execute ..\run_all.ps1
#
# Assumes that WSL is installed, and in there clang, gcc and gnuplot.

echo "Creating cpp code files"
python ..\create_code.py

echo "Compiling on windows"
..\compile_msvc.ps1

echo "Compiling on linux"
wsl ../compile_linux.sh

echo "Merging results"
python ..\merge_results.py

echo "Plotting results"
wsl gnuplot "../plot.plt"
