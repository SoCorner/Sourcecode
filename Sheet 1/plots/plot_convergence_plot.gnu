#!/usr/bin/gnuplot

set term pdf
set size 1,1
set title 'Estimation errors for mean = 1.5'
set grid xtics ytics
set xlabel 'N'
set ylabel 'estimation error'
set logscale xy
set output 'convergence_plot_sigma_estimation.pdf'
l(x) = x**(-0.6) 
plot "../Task\ 9/estimate_sigma_convergence_plot_sigma_1.txt" using 1:2 w lp t 'sigma = 0.1', "../Task\ 9/estimate_sigma_convergence_plot_sigma_2.txt" using 1:2 w lp t 'sigma = 1.0', "../Task\ 9/estimate_sigma_convergence_plot_sigma_3.txt" using 1:2 w lp t 'sigma = 10.0', l(x) title 'l(N) = N^{-0.6}'
