#!/usr/bin/gnuplot

set term pdf
set size 1,1
set xlabel 'Time'
set ylabel 'Value'
set title 'Plot of Wiener processes'
set output 'wiener.pdf'
plot "../Task\ 10/wiener_process_smaller_steps.txt" using 1:2 w lp ps 0.25 t 'Sample 1', "../Task\ 10/wiener_process_smaller_steps.txt" using 1:3 w lp ps 0.25 t 'Sample 2', "../Task\ 10/wiener_process_smaller_steps.txt" using 1:4 w lp ps 0.25 t 'Sample 3', "../Task\ 10/wiener_process_large_steps.txt" using 1:2 w lp ps 0.25 t 'Sample 1', "../Task\ 10/wiener_process_large_steps.txt" using 1:3 w lp ps 0.25 t 'Sample 2', "../Task\ 10/wiener_process_large_steps.txt" using 1:4 w lp ps 0.25 t 'Sample 3' 
