set title "Vitesse d'execution de TSP1 en fonction du nombre de lieux (instance A-B)"
set xlabel "Nombre de lieux"
set ylabel "Temps d'execution (en seconde)"
set xrange [10:50]
set yrange [-1000:15000]

plot "A-B.dat" using 1:2 title "instance A" with linespoints
replot "A-B.dat" using 1:6 title "instance B" with linespoints

