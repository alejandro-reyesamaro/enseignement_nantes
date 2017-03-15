function Cadran() { 
  //cette fonction dessine un cadran vierge
  //Variables
  var i; //Entier
  //D??but
  //Cercle exterieur
  for (i = 0; i <= 25; i = i + 1) {
    if (i < 5) { //la  boucle c'est pour faire deux cercles!
      Cercle(200, 200, 200 + i, 'brown');//coordonn??es du centre et du cadran+colours
    } else {
      if (i > 20) {
        Cercle(200, 200, 200 + i, 'brown');//coordonn??es du centre et ducadran+colours
      } else {
        Cercle(200, 200, 200 + i, 'pink');//pour que ??a fasse girly
      }
    }
  }
  
  Deplacer(200, 200);//fonction tortue vilaine >.< pour faire les graduations! 
  for (i = 0; i <= 59; i = i + 1) {
    Droite(6);
    Avancer(100);
    Deplacer(200, 200);
  }
  CerclePlein(200, 200, 185, 'white');//200,200 coordonn??es du centre +185 Diam??tre
  for (i = 0; i <= 11; i = i + 1) { // ??a va de 0 ?? 11, donc de 1 ?? 12!
    Droite(30); //30=l'angle
    Avancer(100);
    Deplacer(200, 200);
  }
  Deplacer(1000, 1000);
  CerclePlein(200, 200, 175, 'white');//le cercle doit etre vierge pour pouvoir voirnos aiguilles//

  //Texte+coordonn??es sur le cercle!
  Texte(195, 99, '12', 'Black');
  Texte(303, 200, '3', 'black');
  Texte(195, 310, '6', 'black');
  Texte(91, 200, '9', 'black');

  //Affichage Analogique
  RectanglePlein(395, 395, 160, 30, 'brown');
  RectanglePlein(400, 400, 150, 20, 'Black');
  //Fin
}

function Aiguille(longueur /* Entier */ , couleur /*Chaine de caract??re*/, n
/*Entier*/ ) { 
  //Cette fonction cr????e les aiguilles minutes et secondes.
  //D??but
  Deplacer(200, 200);
  Droite(6 * n);
  Couleur(couleur);
  Avancer(longueur);
  Gauche(6 * n);
  //Fin
}

function AiguilleHeure(longueur /* Entier */ , couleur /*Chaine de caract??re*/ , h
/*Entier*/ , m /*Entier*/ ) { 
  //Cette fonction cr???? l'aiguille des heures.
  //D??but
  Deplacer(200, 200);
  if (h >= 12) {
    h = h - 12;
  }
  Droite(30 * h + m / 2);
  Couleur(couleur);
  Avancer(longueur);
  Gauche(30 * h + m / 2);
  //Fin
}

function AfficheHeure(h /*Entier*/ , m /*Entier*/ , s /*Entier*/ ) {
//Cette fonction trace les aiguilles
  //D??but
  CerclePlein(200, 200, 176, 'white');
  Aiguille((175 / 2), 'purple', s); //Aiguille Secondes
  Aiguille((175 / 2) - 5, 'Red', m); //Aiguille Minutes
  AiguilleHeure(175 / 4, 'Black', h, m); //Aiguille Heures
  Deplacer(1000, 1000);
  //Fin
}

function Calendrier(aujourdhui) { //d??sol??e pour les boucles je me d??brouille pasbien en tableauuu//
  //Variables
  var jour, mois; //Entier
  var x, date, y, year; //Cha??ne de Caract??res
  //D??but
  //1-affichage du jour
  jour = aujourdhui.getDay();
  if (jour == '1') {
    x = "LUNDI";
  } else {
    if (jour == '2') {
      x = "MARDI";
    } else {
      if (jour == '3') {
        x = "MERCREDI";
      } else {
        if (jour == '4') {
          x = "JEUDI";
        } else {
          if (jour == '5') {
            x = "VENDREDI";
          } else {
            if (jour == '6') {
              x = "Samedi";
            } else {
              x = "Dimanche";
            }
          }
        }
      }
    }
  }
  //enfin termin?? ma vilaine boucle imbriqu??e!!!

  //afficher le num??ro du jour
  date = aujourdhui.getDate();

  //2-affichage du mois
  mois = aujourdhui.getMonth();
  if (mois == '0') {
    y = "Janvier";
  } else {
    if (mois == '1') {
      y = "F??vrier";
    } else {
      if (mois == "2") {
        y = "Mars";
      } else {
        if (mois == "3") {
          y = "Avril";
        } else {
          if (mois == "4") {
            y = "Mai";
          } else {
            if (mois == "5") {
              y = "Juin";
            } else {
              if (mois == "6") {
                y = "Juillet";
              } else {
                if (mois == "7") {
                  y = "Aout";
                } else {
                  if (mois == "8") {
                    y = "Septembre";
                  } else {
                    if (mois == "9") {
                      y = "Octobre";
                    } else {
                      if (mois == "10") {
                        y = "Novembre";
                      } else {
                        y = "D??cembre";
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  //3-affichage de l'ann??e//
  year = aujourdhui.getFullYear();
  Texte(410, 100, x +' '+ enChaine(date)+' ' + y +' '+ enChaine(year),
'black');
}

function Time() { //merci Open class Room !
  //pour actualiser l'heure et l'affichage analogique
  //Variables
  var aujourdhui; //Cha??ne de Caract??re
  var heure; //Entier
  var minutes; //Entier
  var secondes; //Entier
  //D??but
  setTimeout("Time();", 1000);
  aujourdhui = new Date();
  heure = aujourdhui.getHours();
  minutes = aujourdhui.getMinutes();
  secondes = aujourdhui.getSeconds();

  AfficheHeure(heure, minutes, secondes);
  RectanglePlein(400, 400, 150, 20, 'pink');
  if(heure<10) {
    heure='0'+enChaine(heure);
  }
    if(minutes<10) {
    minutes='0'+enChaine(minutes);
  }
    if(secondes<10) {
    secondes='0'+enChaine(secondes);
  }
  Texte(410, 415, enChaine(heure) + ':' + enChaine(minutes) + ':' +
enChaine(secondes), 'black');
  //Fin
}
//Algorithme
//D??but
Cadran();//cadran vierge
Time();
Calendrier(new Date());
//Finfunction Cadran() { 
  //cette fonction dessine un cadran vierge
  //Variables
  var i; //Entier
  //D??but
  //Cercle exterieur
  for (i = 0; i <= 25; i = i + 1) {
    if (i < 5) { //la  boucle c'est pour faire deux cercles!
      Cercle(200, 200, 200 + i, 'brown');//coordonn??es du centre et du cadran+colours
    } else {
      if (i > 20) {
        Cercle(200, 200, 200 + i, 'brown');//coordonn??es du centre et ducadran+colours
      } else {
        Cercle(200, 200, 200 + i, 'pink');//pour que ??a fasse girly
      }
    }
  }

  
  Deplacer(200, 200);//fonction tortue vilaine >.< pour faire les graduations! 
  for (i = 0; i <= 59; i = i + 1) {
    Droite(6);
    Avancer(100);
    Deplacer(200, 200);
  }
  CerclePlein(200, 200, 185, 'white');//200,200 coordonn??es du centre +185 Diam??tre
  for (i = 0; i <= 11; i = i + 1) { // ??a va de 0 ?? 11, donc de 1 ?? 12!
    Droite(30); //30=l'angle
    Avancer(100);
    Deplacer(200, 200);
  }
  Deplacer(1000, 1000);
  CerclePlein(200, 200, 175, 'white');//le cercle doit etre vierge pour pouvoir voirnos aiguilles//

  //Texte+coordonn??es sur le cercle!
  Texte(195, 99, '12', 'Black');
  Texte(303, 200, '3', 'black');
  Texte(195, 310, '6', 'black');
  Texte(91, 200, '9', 'black');

  //Affichage Analogique
  RectanglePlein(395, 395, 160, 30, 'brown');
  RectanglePlein(400, 400, 150, 20, 'Black');
  //Fin


function Aiguille(longueur /* Entier */ , couleur /*Chaine de caract??re*/, n
/*Entier*/ ) { 
  //Cette fonction cr????e les aiguilles minutes et secondes.
  //D??but
  Deplacer(200, 200);
  Droite(6 * n);
  Couleur(couleur);
  Avancer(longueur);
  Gauche(6 * n);
  //Fin
}

function AiguilleHeure(longueur /* Entier */ , couleur /*Chaine de caract??re*/ , h
/*Entier*/ , m /*Entier*/ ) { 
  //Cette fonction cr???? l'aiguille des heures.
  //D??but
  Deplacer(200, 200);
  if (h >= 12) {
    h = h - 12;
  }
  Droite(30 * h + m / 2);
  Couleur(couleur);
  Avancer(longueur);
  Gauche(30 * h + m / 2);
  //Fin
}

function AfficheHeure(h /*Entier*/ , m /*Entier*/ , s /*Entier*/ ) {
//Cette fonction trace les aiguilles
  //D??but
  CerclePlein(200, 200, 176, 'white');
  Aiguille((175 / 2), 'purple', s); //Aiguille Secondes
  Aiguille((175 / 2) - 5, 'Red', m); //Aiguille Minutes
  AiguilleHeure(175 / 4, 'Black', h, m); //Aiguille Heures
  Deplacer(1000, 1000);
  //Fin
}

function Calendrier(aujourdhui) { //d??sol??e pour les boucles je me d??brouille pasbien en tableauuu//
  //Variables
  var jour, mois; //Entier
  var x, date, y, year; //Cha??ne de Caract??res
  //D??but
  //1-affichage du jour
  jour = aujourdhui.getDay();
  if (jour == '1') {
    x = "LUNDI";
  } else {
    if (jour == '2') {
      x = "MARDI";
    } else {
      if (jour == '3') {
        x = "MERCREDI";
      } else {
        if (jour == '4') {
          x = "JEUDI";
        } else {
          if (jour == '5') {
            x = "VENDREDI";
          } else {
            if (jour == '6') {
              x = "Samedi";
            } else {
              x = "Dimanche";
            }
          }
        }
      }
    }
  }
  //enfin termin?? ma vilaine boucle imbriqu??e!!!

  //afficher le num??ro du jour
  date = aujourdhui.getDate();

  //2-affichage du mois
  mois = aujourdhui.getMonth();
  if (mois == '0') {
    y = "Janvier";
  } else {
    if (mois == '1') {
      y = "F??vrier";
    } else {
      if (mois == "2") {
        y = "Mars";
      } else {
        if (mois == "3") {
          y = "Avril";
        } else {
          if (mois == "4") {
            y = "Mai";
          } else {
            if (mois == "5") {
              y = "Juin";
            } else {
              if (mois == "6") {
                y = "Juillet";
              } else {
                if (mois == "7") {
                  y = "Aout";
                } else {
                  if (mois == "8") {
                    y = "Septembre";
                  } else {
                    if (mois == "9") {
                      y = "Octobre";
                    } else {
                      if (mois == "10") {
                        y = "Novembre";
                      } else {
                        y = "D??cembre";
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  //3-affichage de l'ann??e//
  year = aujourdhui.getFullYear();
  Texte(410, 100, x +' '+ enChaine(date)+' ' + y +' '+ enChaine(year),
'black');
}

function Time() { //merci Open class Room !
  //pour actualiser l'heure et l'affichage analogique
  //Variables
  var aujourdhui; //Cha??ne de Caract??re
  var heure; //Entier
  var minutes; //Entier
  var secondes; //Entier
  //D??but
  setTimeout("Time();", 1000);
  aujourdhui = new Date();
  heure = aujourdhui.getHours();
  minutes = aujourdhui.getMinutes();
  secondes = aujourdhui.getSeconds();

  AfficheHeure(heure, minutes, secondes);
  RectanglePlein(400, 400, 150, 20, 'pink');
  if(heure<10) {
    heure='0'+enChaine(heure);
  }
    if(minutes<10) {
    minutes='0'+enChaine(minutes);
  }
    if(secondes<10) {
    secondes='0'+enChaine(secondes);
  }
  Texte(410, 415, enChaine(heure) + ':' + enChaine(minutes) + ':' +
enChaine(secondes), 'black');
  //Fin
}
//Algorithme
//D??but
Cadran();//cadran vierge
Time();
Calendrier(new Date());
//Fin
