clang: main.cpp
	clang++ -Wall -Wextra -pedantic -std=c++17 -O3 -DNDEBUG -mavx -I../include -o clangPerf $?
	./clangPerf

gcc: main.cpp
	g++ -Wall -Wextra -pedantic -std=c++17 -O3 -DNDEBUG -mavx -I../include -o gccPerf $?
	./gccPerf
