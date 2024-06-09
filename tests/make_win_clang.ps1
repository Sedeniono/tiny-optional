# Helper script to run the clang windows build locally.

$CXX = "clang++"
$ADDITIONAL_FLAGS = "-m64", "-std=c++20"
$OUT_DIR_NAME = "win_clang_x64_cpp20_debug"

$script = $PSScriptRoot + "\make_win_gcclike.ps1"
& $script
