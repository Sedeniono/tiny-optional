PWD = $(shell pwd)
CXX_CLANG = clang++
CXX_GCC = g++

BIN_DIR = ../bin
EXE_NAME = TinyOptionalTests
#SANITIZE_FLAGS = -fsanitize=undefined -fsanitize=address -fsanitize-address-use-after-scope
SANITIZE_FLAGS =
WARNING_FLAGS = -Wall -Wextra -pedantic -Wconversion -Werror
TINY_OPTIONAL_INCLUDE_DIR = $(PWD)/../include

CPP_FILES = Tests.cpp TestCompilationBase.cpp TestGccLikeCompilation.cpp TestMsvcCompilation.cpp TestUtilities.cpp


CXX_AND_RUN_COMMAND = \
	$(eval OUT_DIR = $(BIN_DIR)/$@) \
	mkdir -p $(OUT_DIR) \
	&&   $(CXX) -o $(OUT_DIR)/$(EXE_NAME) -I"$(TINY_OPTIONAL_INCLUDE_DIR)" $(ADDITIONAL_FLAGS) $(WARNING_FLAGS) $(SANITIZE_FLAGS) -pthread -DTINY_OPTIONAL_TESTS_COMPILER_EXECUTABLE='"$(CXX)"' -DTINY_OPTIONAL_TESTS_HEADER_INCLUDE_DIR='"$(TINY_OPTIONAL_INCLUDE_DIR)"' -DTINY_OPTIONAL_TESTS_COMPILATION_FLAGS='"$(ADDITIONAL_FLAGS) $(WARNING_FLAGS)"' $(CPP_FILES) \
	&&   $(OUT_DIR)/$(EXE_NAME)


clang_x64_cpp20_libcpp: $(CPP_FILES)
	$(eval CXX = $(CXX_CLANG))
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++20 -stdlib=libc++)
	$(CXX_AND_RUN_COMMAND)
	
clang_x64_cpp17_libcpp: $(CPP_FILES)
	$(eval CXX = $(CXX_CLANG))
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++17 -stdlib=libc++)
	$(CXX_AND_RUN_COMMAND)


clang_x64_cpp20_gcclib: $(CPP_FILES)
	$(eval CXX = $(CXX_CLANG))
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++20 -stdlib=libstdc++)
	$(CXX_AND_RUN_COMMAND)
	
clang_x64_cpp17_gcclib: $(CPP_FILES)
	$(eval CXX = $(CXX_CLANG))
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++17 -stdlib=libstdc++)
	$(CXX_AND_RUN_COMMAND)


gcc64cpp20: $(CPP_FILES)
	$(eval CXX = $(CXX_GCC))
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++20 -Wno-deprecated-copy)
	$(CXX_AND_RUN_COMMAND)

gcc64cpp17: $(CPP_FILES)
	$(eval CXX = $(CXX_GCC))
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++17 -Wno-deprecated-copy)
	$(CXX_AND_RUN_COMMAND)
