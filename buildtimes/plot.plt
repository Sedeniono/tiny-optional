set terminal pngcairo crop size 1024,720

set datafile separator ";"

ver_clang = system("cat version_clang.txt")[:-2]
ver_gcc = system("cat version_gcc.txt")[:-2]
ver_msvc = system("iconv -f UTF-16LE -t UTF-8 version_msvc.txt | tr -d '\r\n'")
set title sprintf("clang %s, gcc %s, msvc %s", ver_clang, ver_gcc, ver_msvc)

unset key
set boxwidth 0.5
set style fill solid
set xtics rotate by 40 right
set xtics noenhanced
set ytics 0.2

set yrange [0.9:2.1]
set ylabel "Ratio of compilation times: tiny/std\n(>1 means tiny is slower)"
set output "result_tiny_vs_std_cpp17.png"
plot \
    "result_tiny_vs_std_cpp17.csv" u 2:xtic(1) with boxes lc "red", \
    1 w l lc "black"
set output

set output "result_tiny_vs_std_cpp20.png"
plot \
    "result_tiny_vs_std_cpp20.csv" u 2:xtic(1) with boxes lc "red", \
    1 w l lc "black"
set output


set xtics rotate by 50 right
set yrange [0.9:1.6]
set ylabel "Ratio of compilation times of tiny: no-concept/concept\n(>1 means concepts are faster)"
set output "result_tiny_concept_vs_no_concept.png"
plot \
    "result_tiny_concept_vs_no_concept.csv" u 2:xtic(1) with boxes lc "red", \
    1 w l lc "black"
set output
