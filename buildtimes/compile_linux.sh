#!/bin/bash

RESULT_NAME="result_linux.csv"

shopt -s nullglob

cmds=("clang++ -std=c++17"   "clang++ -O3 -std=c++17"   "clang++ -std=c++17 -stdlib=libc++"   "clang++ -O3 -std=c++17 -stdlib=libc++"   "g++ -std=c++17"   "g++ -O3 -std=c++17")


printf "Testcode" > "$RESULT_NAME"
for cmd in "${cmds[@]}"; do
    printf ";$cmd" >> "$RESULT_NAME"
done
printf "\n" >> "$RESULT_NAME"

for file in *.cpp; do
    echo "============ Compiling $file ============"

    printf "$file" >> "$RESULT_NAME"
    for cmd in "${cmds[@]}"; do
        echo "Compiling with: $cmd"
        timing=$(/usr/bin/time --format "%e" $cmd -I../../include "$file" 2>&1)
        printf ";$timing" >> "$RESULT_NAME"
    done
    printf "\n" >> "$RESULT_NAME"
    echo ""
done
