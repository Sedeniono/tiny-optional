PWD = $(shell pwd)
CXX_CLANG ?= clang++
CXX_GCC ?= g++

BIN_DIR = ../bin
EXE_NAME = TinyOptionalTests
#SANITIZE_FLAGS = -fsanitize=undefined -fsanitize=address -fsanitize-address-use-after-scope
SANITIZE_FLAGS =
WARNING_FLAGS = -Wall -Wextra -pedantic -Wconversion -Werror
TINY_OPTIONAL_INCLUDE_DIR_CMD = $(PWD)/../include
TINY_OPTIONAL_INCLUDE_DIR_IN_EXE = $(TINY_OPTIONAL_INCLUDE_DIR_CMD)

# The github workflow for gcc on windows sets the IS_MSYS variable. In msys, we need to convert the include path 
# that we build above (which is unix style) to windows style for use in our C++ program. See https://www.msys2.org/docs/filesystem-paths/
ifdef IS_MSYS
TINY_OPTIONAL_INCLUDE_DIR_IN_EXE = $(shell cygpath -m $(TINY_OPTIONAL_INCLUDE_DIR_CMD))
endif


CPP_FILES = ComparisonTests.cpp CompilationBase.cpp CompilationErrorTests.cpp ConstructionTests.cpp ExerciseOptionalAIP.cpp ExerciseOptionalEmptyViaType.cpp ExerciseOptionalInplace.cpp ExerciseOptionalWithCustomFlagManipulator.cpp ExerciseStdOptional.cpp ExerciseTinyOptionalPayload1.cpp ExerciseTinyOptionalPayload2.cpp GccLikeCompilation.cpp IntermediateTests.cpp MsvcCompilation.cpp NatvisTests.cpp SpecialMonadicTests.cpp Tests.cpp TestUtilities.cpp


CXX_AND_RUN_COMMAND = \
	$(eval OUT_DIR = $(BIN_DIR)/$@) \
	mkdir -p $(OUT_DIR) \
	&&   $(CXX) -o $(OUT_DIR)/$(EXE_NAME) -I"$(TINY_OPTIONAL_INCLUDE_DIR_CMD)" $(ADDITIONAL_FLAGS) $(WARNING_FLAGS) $(SANITIZE_FLAGS) -pthread -DTINY_OPTIONAL_TESTS_COMPILER_EXECUTABLE='"$(CXX)"' -DTINY_OPTIONAL_TESTS_HEADER_INCLUDE_DIR='"$(TINY_OPTIONAL_INCLUDE_DIR_IN_EXE)"' -DTINY_OPTIONAL_TESTS_COMPILATION_FLAGS='"$(ADDITIONAL_FLAGS) $(WARNING_FLAGS)"' $(CPP_FILES) \
	&&   $(OUT_DIR)/$(EXE_NAME)


#---------------------------------------------------------------------
# clang
#---------------------------------------------------------------------

clang_tidy: $(CPP_FILES)
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++20 -stdlib=libc++ -O3)
	clang-tidy $(CPP_FILES) -checks=clang-analyzer-* -- -I"$(TINY_OPTIONAL_INCLUDE_DIR_CMD)" $(ADDITIONAL_FLAGS) $(WARNING_FLAGS) $(SANITIZE_FLAGS) -pthread -DTINY_OPTIONAL_TESTS_COMPILER_EXECUTABLE='"$(CXX)"' -DTINY_OPTIONAL_TESTS_HEADER_INCLUDE_DIR='"$(TINY_OPTIONAL_INCLUDE_DIR_IN_EXE)"' -DTINY_OPTIONAL_TESTS_COMPILATION_FLAGS='"$(ADDITIONAL_FLAGS) $(WARNING_FLAGS)"'
	

clang_x64_cpp17_libcpp_debug: $(CPP_FILES)
	$(eval CXX = $(CXX_CLANG))
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++17 -stdlib=libc++)
	$(CXX_AND_RUN_COMMAND)

clang_x64_cpp17_libcpp_release: $(CPP_FILES)
	$(eval CXX = $(CXX_CLANG))
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++17 -O3 -DNDEBUG -stdlib=libc++)
	$(CXX_AND_RUN_COMMAND)

clang_x64_cpp20_libcpp_debug: $(CPP_FILES)
	$(eval CXX = $(CXX_CLANG))
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++20 -stdlib=libc++)
	$(CXX_AND_RUN_COMMAND)

clang_x64_cpp20_libcpp_release: $(CPP_FILES)
	$(eval CXX = $(CXX_CLANG))
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++20 -O3 -DNDEBUG -stdlib=libc++)
	$(CXX_AND_RUN_COMMAND)

clang_x64_cpp23_libcpp_debug: $(CPP_FILES)
	$(eval CXX = $(CXX_CLANG))
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++2b -stdlib=libc++)
	$(CXX_AND_RUN_COMMAND)


clang_x86_cpp20_libcpp_debug: $(CPP_FILES)
	$(eval CXX = $(CXX_CLANG))
	$(eval ADDITIONAL_FLAGS = -m32 -std=c++20 -stdlib=libc++)
	$(CXX_AND_RUN_COMMAND)
	
clang_x86_cpp17_libcpp_debug: $(CPP_FILES)
	$(eval CXX = $(CXX_CLANG))
	$(eval ADDITIONAL_FLAGS = -m32 -std=c++17 -stdlib=libc++)
	$(CXX_AND_RUN_COMMAND)


clang_x64_cpp20_gcclib_debug: $(CPP_FILES)
	$(eval CXX = $(CXX_CLANG))
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++20 -stdlib=libstdc++)
	$(CXX_AND_RUN_COMMAND)
	
clang_x64_cpp17_gcclib_debug: $(CPP_FILES)
	$(eval CXX = $(CXX_CLANG))
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++17 -stdlib=libstdc++)
	$(CXX_AND_RUN_COMMAND)


clang_x64_cpp20_libcpp_debug_noUB: $(CPP_FILES)
	$(eval CXX = $(CXX_CLANG))
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++20 -stdlib=libc++ -DTINY_OPTIONAL_USE_SEPARATE_BOOL_INSTEAD_OF_UB_TRICKS)
	$(CXX_AND_RUN_COMMAND)


#---------------------------------------------------------------------
# gcc
#---------------------------------------------------------------------

gcc_x64_cpp20_debug: $(CPP_FILES)
	$(eval CXX = $(CXX_GCC))
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++20)
	$(CXX_AND_RUN_COMMAND)

gcc_x64_cpp17_debug: $(CPP_FILES)
	$(eval CXX = $(CXX_GCC))
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++17)
	$(CXX_AND_RUN_COMMAND)

gcc_x86_cpp20_debug: $(CPP_FILES)
	$(eval CXX = $(CXX_GCC))
	$(eval ADDITIONAL_FLAGS = -m32 -std=c++20)
	$(CXX_AND_RUN_COMMAND)

gcc_x86_cpp17_debug: $(CPP_FILES)
	$(eval CXX = $(CXX_GCC))
	$(eval ADDITIONAL_FLAGS = -m32 -std=c++17)
	$(CXX_AND_RUN_COMMAND)

gcc_x86_cpp17_release: $(CPP_FILES)
	$(eval CXX = $(CXX_GCC))
	$(eval ADDITIONAL_FLAGS = -m32 -std=c++17 -O3 -DNDEBUG)
	$(CXX_AND_RUN_COMMAND)

gcc_x64_cpp20_release: $(CPP_FILES)
	$(eval CXX = $(CXX_GCC))
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++20 -O3 -DNDEBUG)
	$(CXX_AND_RUN_COMMAND)
	
gcc_x64_cpp20_fastmath_release: $(CPP_FILES)
	$(eval CXX = $(CXX_GCC))
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++20 -O3 -DNDEBUG -ffast-math)
	$(CXX_AND_RUN_COMMAND)
	
gcc_x64_cpp17_release: $(CPP_FILES)
	$(eval CXX = $(CXX_GCC))
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++17 -O3 -DNDEBUG)
	$(CXX_AND_RUN_COMMAND)

gcc_x64_cpp20_release_noUB: $(CPP_FILES)
	$(eval CXX = $(CXX_GCC))
	$(eval ADDITIONAL_FLAGS = -m64 -std=c++20 -O3 -DNDEBUG -DTINY_OPTIONAL_USE_SEPARATE_BOOL_INSTEAD_OF_UB_TRICKS)
	$(CXX_AND_RUN_COMMAND)


#---------------------------------------------------------------------
# generic version, used by the github actions
# Expects that CXX and ADDITIONAL_FLAGS are set from the environment.
#---------------------------------------------------------------------

generic: $(CPP_FILES)
	$(CXX_AND_RUN_COMMAND)

