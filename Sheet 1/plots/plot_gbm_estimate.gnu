#!/usr/bin/gnuplot

set term pdf
set size 1,1
set xlabel 'Time'
set ylabel 'Value'
set title 'Plot of a GBM'
set output 'gbm_estimate.pdf'
plot "../Task\ 11/gbm_estimate.txt" using 1:2 w lp ps 0.25 t 'GBM'
