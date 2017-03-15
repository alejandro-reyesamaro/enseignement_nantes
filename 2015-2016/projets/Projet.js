//Placet Florian et Kayiranga Manzi
function Cadran() {
  //La fonction ne prends aucun parametre et dessine le cadran
  //Variables
  var i; //Entier
  //Debut
  //Cercle exterieur
  for (i = 0; i <= 25; i = i + 1) {
    if (i < 5) {
      Cercle(200, 200, 200 + i, 'black');
    } else {
      if (i > 20) {
        Cercle(200, 200, 200 + i, 'black');
      } else {
        Cercle(200, 200, 200 + i, 'goldenrod');
      }
    }
  }
  //Graduations
  Deplacer(200, 200);
  for (i = 0; i <= 59; i = i + 1) {
    Droite(6);
    Avancer(100);
    Deplacer(200, 200);
  }
  CerclePlein(200, 200, 185, 'white');
  for (i = 0; i <= 11; i = i + 1) {
    Droite(30);
    Avancer(100);
    Deplacer(200, 200);
  }
  Deplacer(1000, 1000);
  CerclePlein(200, 200, 175, 'white');

  //Texte
  Texte(195, 99, '12', 'Black');
  Texte(303, 200, '3', 'black');
  Texte(195, 310, '6', 'black');
  Texte(91, 200, '9', 'black');

  //Affichage Analogique
  RectanglePlein(395, 395, 160, 30, 'Goldenrod');
  RectanglePlein(400, 400, 150, 20, 'Black');
  //Fin
}

function Aiguille(longueur /* Entier */ , couleur /*Chaine de caractere*/ , n /*Entier*/ ) {
  //Cette fonction cree les aiguilles minutes et secondes.
  //Debut
  Deplacer(200, 200);
  Droite(6 * n);
  Couleur(couleur);
  Avancer(longueur);
  Gauche(6 * n);
  //Fin
}

function AiguilleHeure(longueur /* Entier */ , couleur /*Chaine de caract??re*/ , h /*Entier*/ , m /*Entier*/ ) {
  //Cette fonction cree l'aiguille des heures.
  //Debut
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
  //Debut
  CerclePlein(200, 200, 176, 'white');
  Aiguille((175 / 2), 'Navy', s); //Aiguille Secondes
  Aiguille((175 / 2) - 5, 'Red', m); //Aiguille Minutes
  AiguilleHeure(175 / 4, 'Black', h, m); //Aiguille Heures
  Deplacer(2000, 2000);
  //Fin
}

function Calendrier(aujourdhui) {
  //Variables
  var jour, mois; //Entier
  var x, date, y, year; //Chaine de Caracteres
  //Debut
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
              x = "SAMEDI";
            } else {
              x = "DIMANCHE";
            }
          }
        }
      }
    }
  }

  //afficher le numero du jour
  date = aujourdhui.getDate();

  //2-affichage du mois
  mois = aujourdhui.getMonth();
  if (mois == '0') {
    y = "Janvier";
  } else {
    if (mois == '1') {
      y = "Fevrier";
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
                        y = "Decembre";
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
  //3-affichage de l'annee//
  year = aujourdhui.getFullYear();
  Texte(410, 100, x + ' ' + enChaine(date) + ' ' + y + ' ' + enChaine(year), 'black');
}

function Time() {
  //Cette fonction reinitialise les aiguilles et l'afichage analogique a chaque seconde
  //Variables
  var aujourdhui; //Chaine de Caractere
  var heure; //Entier
  var minutes; //Entier
  var secondes; //Entier
  //Debut
  setTimeout("Time();", 1000); //Fonction qui actualise le tout
  aujourdhui = new Date();
  heure = aujourdhui.getHours();
  minutes = aujourdhui.getMinutes();
  secondes = aujourdhui.getSeconds();
  AfficheHeure(heure, minutes, secondes); //Dessine les aiguilles
  RectanglePlein(400, 400, 150, 20, 'Black'); //Efface l'horloge analogique precedente
  if (heure < 10) {
    heure = '0' + enChaine(heure);
  }
  if (minutes < 10) {
    minutes = '0' + enChaine(minutes);
  }
  if (secondes < 10) {
    secondes = '0' + enChaine(secondes);
  }
  Texte(410, 415, enChaine(heure) + ':' + enChaine(minutes) + ':' +enChaine(secondes), 'white'); //Horloge analogique
  if(heure=='00') {
    RectanglePlein(410,80,150,20,'white');
  Calendrier(new Date());
  }
  //Fin
}
//Algorithme
//Debut
Cadran();
Calendrier(new Date());
Time();
//Fin
