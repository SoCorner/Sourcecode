#!/usr/bin/gnuplot

set term pdf
set size 1,1
set xlabel 'Time'
set ylabel 'Value'
set title 'Plot of GBMs'
set output 'gbm.pdf'
r(x) = 10*exp(0.1 * x)
plot "../Task\ 10/gbm_smaller_steps.txt" using 1:2 w lp ps 0.25 t 'Sample 1', "../Task\ 10/gbm_smaller_steps.txt" using 1:3 w lp ps 0.25 t 'Sample 2', "../Task\ 10/gbm_smaller_steps.txt" using 1:4 w lp ps 0.25 t 'Sample 3', "../Task\ 10/gbm_large_steps.txt" using 1:2 w lp ps 0.25 t 'Sample 1', "../Task\ 10/gbm_large_steps.txt" using 1:3 w lp ps 0.25 t 'Sample 2', "../Task\ 10/gbm_large_steps.txt" using 1:4 w lp ps 0.25 t 'Sample 3', r(x) t "mean"    
