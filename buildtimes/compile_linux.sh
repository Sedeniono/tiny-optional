#!/bin/bash

export PATH=/opt/gcc/latest/bin:$PATH
export LD_LIBRARY_PATH=/opt/gcc/latest/lib:/opt/gcc/latest/lib64:/opt/gcc/latest/lib32:$LD_LIBRARY_PATH

export PATH=/opt/clang/latest/bin:$PATH
export LD_LIBRARY_PATH=/opt/clang/latest/lib:/opt/clang/latest/lib/x86_64-unknown-linux-gnu:$LD_LIBRARY_PATH

shopt -s nullglob

clangVersion=$(clang++ --version | head -n1 | grep -oP '(?<=version )\d+(\.\d+)+')
echo "clang version: $clangVersion"
echo "$clangVersion" > "version_clang.txt"

gccVersion=$(g++ --version | head -n1 | awk '{print $NF}')
echo "gcc version: $gccVersion"
echo "$gccVersion" > "version_gcc.txt"

cmds=("clang++ -std=c++17"                  
      "clang++ -std=c++17 -O3 -DNDEBUG"   
      "clang++ -std=c++17              -stdlib=libc++"   
      "clang++ -std=c++17 -O3 -DNDEBUG -stdlib=libc++"   
      "clang++ -std=c++20"                  
      "clang++ -std=c++20 -O3 -DNDEBUG"   
      "clang++ -std=c++20              -stdlib=libc++"   
      "clang++ -std=c++20 -O3 -DNDEBUG -stdlib=libc++"   
      "clang++ -std=c++20                              -DTINY_OPTIONAL_NO_TRIVIAL_SPECIAL_MEMBER_FUNCTIONS"                  
      "clang++ -std=c++20 -O3 -DNDEBUG                 -DTINY_OPTIONAL_NO_TRIVIAL_SPECIAL_MEMBER_FUNCTIONS"   
      "clang++ -std=c++20              -stdlib=libc++ -DTINY_OPTIONAL_NO_TRIVIAL_SPECIAL_MEMBER_FUNCTIONS"   
      "clang++ -std=c++20 -O3 -DNDEBUG -stdlib=libc++ -DTINY_OPTIONAL_NO_TRIVIAL_SPECIAL_MEMBER_FUNCTIONS"   
      "g++ -std=c++17"                      
      "g++ -std=c++17 -O3 -DNDEBUG"
      "g++ -std=c++20"                      
      "g++ -std=c++20 -O3 -DNDEBUG"
      "g++ -std=c++20              -DTINY_OPTIONAL_NO_TRIVIAL_SPECIAL_MEMBER_FUNCTIONS"  
      "g++ -std=c++20 -O3 -DNDEBUG -DTINY_OPTIONAL_NO_TRIVIAL_SPECIAL_MEMBER_FUNCTIONS")

RESULT_NAME="result_linux.csv"
printf "Testcode" > "$RESULT_NAME"
for cmd in "${cmds[@]}"; do
    printf ";$cmd" >> "$RESULT_NAME"
done
printf "\n" >> "$RESULT_NAME"

for file in *.cpp; do
    echo "============ Compiling $file ============"

    printf "$file" >> "$RESULT_NAME"
    for cmd in "${cmds[@]}"; do
        echo -n "Compiling with: $cmd"
        NUM_CALLS=5
        totalSeconds=0
        for i in $(seq 1 $NUM_CALLS); do
            timing=$(/usr/bin/time --format "%e" $cmd -I../../include "$file" 2>&1)
            totalSeconds=$(echo "scale=4; $totalSeconds + $timing" | bc)
            echo -n " - $i/$NUM_CALLS ($timing s)"
        done
        avgSeconds=$(echo "scale=4; $totalSeconds / $NUM_CALLS" | bc)
        avgSeconds=$(printf "%.4f" "$avgSeconds")
        echo " = $avgSeconds s"
        printf ";$avgSeconds" >> "$RESULT_NAME"
    done
    printf "\n" >> "$RESULT_NAME"
    echo ""
done
