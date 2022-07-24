set terminal pngcairo size 1024,500

set key top left

set output "results_relative.png"
set logscale x
set xlabel "Number of values"
set yrange [0:]
set ylabel "Ratio of execution time: std/tiny\n(>1 means tiny is faster)"

set arrow from 1024, graph 0 to 1024, graph 1 nohead
set label "L1 " at 1024, graph 0.95 right

set arrow from 4096, graph 0 to 4096, graph 1 nohead
set label "L2 " at 4096, graph 0.95 right

set arrow from 131072, graph 0 to 131072, graph 1 nohead
set label "L3 " at 131072, graph 0.95 right

plot \
    "results_msvc.dat"  u 2:6 w lp lw 3 lt 7 lc "red"   title "MSVC", \
    "results_clang.dat" u 2:6 w lp lw 3 lt 7 lc "black" title "clang", \
    "results_gcc.dat"   u 2:6 w lp lw 3 lt 7 lc "blue"  title "gcc", \
    1 lw 1 lc "black" notitle
set output



set output "results_absolute.png"
set logscale x
set xlabel "numVals"
set yrange [*:]
set ylabel "Duration [s]"

plot \
    "results_msvc.dat"  u 2:4 w lp lw 3 lt 7 lc "red"              title "msvc std", \
    "results_msvc.dat"  u 2:5 w lp lw 3 lt 7 lc "orange"    dt "-" title "msvc tiny", \
    "results_clang.dat" u 2:4 w lp lw 3 lt 7 lc "black"            title "clang std", \
    "results_clang.dat" u 2:5 w lp lw 3 lt 7 lc "gray30"    dt "-" title "clang tiny", \
    "results_gcc.dat"   u 2:4 w lp lw 3 lt 7 lc "blue"             title "gcc std", \
    "results_gcc.dat"   u 2:5 w lp lw 3 lt 7 lc "royalblue" dt "-" title "gcc tiny"
set output
