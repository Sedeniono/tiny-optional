PWD = $(shell pwd)
CXX_CLANG ?= clang++
CXX_GCC ?= g++

BIN_DIR = ../bin
EXE_NAME = TinyOptionalTests
#SANITIZE_FLAGS = -fsanitize=undefined -fsanitize=address -fsanitize-address-use-after-scope
SANITIZE_FLAGS =
WARNING_FLAGS = -Wall -Wextra -pedantic -Wconversion -Werror
TINY_OPTIONAL_INCLUDE_DIR = $(PWD)/../include

CPP_FILES = ComparisonTests.cpp CompilationBase.cpp CompilationErrorTests.cpp ConstructionTests.cpp ExerciseOptionalEmptyViaType.cpp ExerciseOptionalInplace.cpp ExerciseStdOptional.cpp ExerciseTinyOptionalPayload1.cpp ExerciseTinyOptionalPayload2.cpp GccLikeCompilation.cpp IntermediateTests.cpp MsvcCompilation.cpp SpecialMonadicTests.cpp Tests.cpp TestUtilities.cpp


CXX_AND_RUN_COMMAND = \
	$(eval OUT_DIR = $(BIN_DIR)/$@) \
	mkdir -p $(OUT_DIR) \
	&&   $(CXX) -o $(OUT_DIR)/$(EXE_NAME) -I"$(TINY_OPTIONAL_INCLUDE_DIR)" $(ADDITIONAL_FLAGS) $(WARNING_FLAGS) $(SANITIZE_FLAGS) -pthread -DTINY_OPTIONAL_TESTS_COMPILER_EXECUTABLE='"$(CXX)"' -DTINY_OPTIONAL_TESTS_HEADER_INCLUDE_DIR='"$(TINY_OPTIONAL_INCLUDE_DIR)"' -DTINY_OPTIONAL_TESTS_COMPILATION_FLAGS='"$(ADDITIONAL_FLAGS) $(WARNING_FLAGS)"' $(CPP_FILES) \
	&&   $(OUT_DIR)/$(EXE_NAME)


#---------------------------------------------------------------------
# clang
#---------------------------------------------------------------------

	
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


#---------------------------------------------------------------------
# generic version, used by the github actions
# Expects that CXX and ADDITIONAL_FLAGS are set from the environment.
#---------------------------------------------------------------------

generic: $(CPP_FILES)
	$(CXX_AND_RUN_COMMAND)

