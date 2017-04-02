set title "Vitesse d'execution de la fonction regroupe en fonction du nombre de lieux (instance A-B)"
set xlabel "Nombre de lieux"
set ylabel "Temps d'execution (en seconde)"
set xrange [10:50]
set yrange [-2:100]

plot "regroupe.dat" using 1:2 title "instance A" with linespoints
replot "regroupe.dat" using 1:3 title "instance B" with linespoints


