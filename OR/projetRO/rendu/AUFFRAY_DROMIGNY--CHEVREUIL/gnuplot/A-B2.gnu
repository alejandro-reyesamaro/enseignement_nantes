set title "Vitesse d'execution de TSP2 en fonction du nombre de lieux (instance A-B)"
set xlabel "Nombre de lieux"
set ylabel "Temps d'execution (en seconde)"
set xrange [10:50]
set yrange [-150:5000]

plot "A-B.dat" using 1:3 title "instance A" with linespoints
replot "A-B.dat" using 1:7 title "instance B" with linespoints

