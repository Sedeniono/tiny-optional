set terminal pngcairo size 1024,1400

set datafile separator ";"
set output "result.png"

unset key
set yrange [0:]
set ylabel "Ratio of compilation times: tiny/std\n(>1 means tiny is slower)"
set boxwidth 0.5
set style fill solid
set xtics rotate by 90 right
set xtics noenhanced

plot \
    "result_merged.csv" u 2:xtic(1) with boxes lc "red", \
    1 w l lc "black"
set output
