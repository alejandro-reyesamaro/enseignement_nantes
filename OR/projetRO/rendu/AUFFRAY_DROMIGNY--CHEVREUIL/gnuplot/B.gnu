set title "Vitesse d'execution du TSP en fonction du nombre de lieux (instances B)"
set xlabel "Nombre de lieux"
set ylabel "Temps d'execution (en seconde)"
set xrange [10:50]
set yrange [-500:15000]

plot "B.dat" using 1:2 title "TSP1" with linespoints
replot "B.dat" using 1:3 title "TSP2" with linespoints
replot "B.dat" using 1:4 title "TSP3" with linespoints

