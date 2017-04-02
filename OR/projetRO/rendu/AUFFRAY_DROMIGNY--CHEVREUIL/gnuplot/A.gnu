set title "Vitesse d'execution du TSP en fonction du nombre de lieux (instances A)"
set xlabel "Nombre de lieux"
set ylabel "Temps d'execution (en seconde)"
set xrange [10:50]
set yrange [-2:30]

plot "A.dat" using 1:2 title "TSP1" with linespoints
replot "A.dat" using 1:3 title "TSP2" with linespoints
replot "A.dat" using 1:4 title "TSP3" with linespoints

