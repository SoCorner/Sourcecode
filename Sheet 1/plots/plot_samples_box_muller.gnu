#!/usr/bin/gnuplot

set xlabel "first component" font "Times New Roman, 12"
set ylabel "second component" font "Times New Roman, 12"
set title "Box-Muller samples"
set term pdf font "Times New Roman, 8"
set output "Box-Muller.pdf"
plot "../Task\ 6/samples_box_muller.txt" pt 1 title " "
set output
