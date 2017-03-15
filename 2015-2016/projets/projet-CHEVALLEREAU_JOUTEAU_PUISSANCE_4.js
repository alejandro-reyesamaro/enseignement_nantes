// PROGRAMME PUISSANCE 4
// VARIABLES
var tours = 0; // (ENTIER) cette variable compte le nombre de tours total (jetons posés) et permet d'afficher un message en cas de fin de la partie sans gagnant
var k; // (entier) la variable qui prendra le code ascii de la touche sur laquelle on appuie dans la fonction keypressed.
var x = 0; // (entiers) x et y serviront pour des boucles pour.
var y = 0;
var j = 0; // (entier) cette variable stockera le nombre de cases identiques sur une ligne dans la vérification de la victoire.
var colonne = 8; // (entier) la colonne que l'on choisit (horizontal).
var vr = Tableau(7); // (tableau d'entier une dimension) ce tableau dit le nombre de jetons dans une colonne de rang [colonne].
var end = false; // booléen de victoire.
var tour = 0; // entier déterminant quel tour c'est (rouge/ jaune).
var couleur = Tableau(13, 13); // tableau de 13*13 entiers (deux dimensions) déterminant la couleur de chaque case (entiers).
// ce tableau possède des cases en trop pour faire une "bordure" permettant de vérifier les cases sans chercher une case qui n'existe pas.
// DEBUT
setCanvasFont('Comic', '20pt', 'bold'); // cela fixe la police d'écriture (pour le texte en haut a gauche disant qui joue)
alert("Le joueur rouge commence. Les colonnes sont numérotées de 1 à 7. Utilisez le pavé numérique pour sélectionner une colonne et alignez 4 pions avant votre adversaire!"); // MESSAGE DE DÉBUT
for (y = 0; y <= 12; y = y + 1) { // affichage des ronds vides .
  for (x = 0; x <= 12; x = x + 1) { // double 'pour' pour faire un tableau.
    couleur[x][y] = 0; // les cases prennent la valeur 0 correspondant a une case vide.
  }
}
InitialiserTableau(vr, 0); // toutes les colonnes sont vides.
for (i = 0; i < 1500; i = i + 1) { // création d'une image de fond (colonne par colonne)
  Ligne(i, 0, i, 3000, rgb(255, (3 * i * 255 / 4500) + 20, 0));
}
ShadowOn(); // effet visuel pour le rectangle bleu (plateau de jeu)
RectanglePlein(250, 20, 825, 695, rgb(50, 50, 200)); // création du rectangle bleu.
ShadowOff();
Texte(300, 40, "joueur rouge", 'black'); // affichage de quel joueur joue
for (y = 75; y <= 638; y = y + 112) { // affichage des ronds vides .
  for (x = 75; x <= 750; x = x + 112) { // double 'pour' pour faire un tableau.
    CerclePlein(x + 250, y + 20, 75, rgb(255, 255, 255)); // création des "trous" pour les jetons
  }
}

function draw() { // la fonction qui dessine les ronds de couleur .
  if (vr[colonne] < 6) { //si il reste de la place.
    if (tour == 0) { // joueur 1.
      CerclePlein(325 + (colonne * 112), 655 - (vr[colonne] * 112), 75, 'red'); // on fait apparaitre un jeton de la couleur rouge.
      couleur[vr[colonne] + 3][colonne + 3] = 1; // le jeton posé est de la couleur rouge
    } else { //joueur 2.
      CerclePlein(325 + (colonne * 112), 655 - (vr[colonne] * 112), 75, 'yellow'); // on fait apparaitre un jeton de la couleur jaune.
      couleur[vr[colonne] + 3][colonne + 3] = 2; // le jeton posé est de couleur jaune.
    }
    vr[colonne] = vr[colonne] + 1; // il y a un jeton de plus dans la colonne sélectionnée.
    tour = -tour; // on passe au 
    tour = tour + 1; //tour suivant.
    tours = tours + 1; // nombre de jetons total (pour le message d'égalité)
  }
}


function Keypressed(k) { // la fonction qui prend les input.
  if (end == false) {
    RectanglePlein(300, 20, 500, 35, rgb(50, 50, 200)); // un petit rectangle bleu pour "effacer" le texte
    if (tour == 1) {
      Texte(300, 40, "joueur rouge", 'black'); // affichage de qui joue
    } else {
      Texte(300, 40, "joueur jaune", 'black');
    }

    if (k > 96 && k < 104) { // code ascii de la touche appuyée , si elle correspond aux touches de 1 à 7
      colonne = k - 97; // passage du code ascii au chiffre lui-même
      draw();
      verification();
    }
  }
}

function verification() { // chaque double boucle pour sert a vérifier dans une des 4 directions toutes les possibilités d'alignement, et met fin à la partie si un des joueurs gagne.
  if (tours > 41) { // si la partie est terminée en égalité (sans gagnant)
    alert("partie terminée!");
  }
  for (y = 0; y <= 3; y = y + 1) {
    for (x = 1; x <= 3; x = x + 1) {
      if (couleur[vr[colonne] + 2][colonne + 3 - y] == couleur[vr[colonne] + 2][colonne + 3 + x - y]) {
        j = j + 1;
      }
      if (j > 2 && end != true) {
        if (tour == 1) alert('Le joueur rouge a gagné!');
        else alert('Le joueur jaune a gagné!');
        end = true;
      }
    }
    j = 0;
  }
  for (y = 0; y <= 3; y = y + 1) {
    for (x = 1; x <= 3; x = x + 1) {
      if (couleur[vr[colonne] + 2 - y][colonne + 3] == couleur[vr[colonne] + 2 + x - y][colonne + 3]) {
        j = j + 1;
      }
      if (j > 2 && end != true) {
        if (tour == 1) alert('Le joueur rouge a gagné!');
        else alert('Le joueur jaune a gagné!');
        end = true;
      }
    }
    j = 0;
  }
  for (y = 0; y <= 3; y = y + 1) {
    for (x = 1; x <= 3; x = x + 1) {
      if (couleur[vr[colonne] + 2 - y][colonne + 3 - y] == couleur[vr[colonne] + 2 + x - y][colonne + 3 + x - y]) {
        j = j + 1;
      }
      if (j > 2 && end != true) {
        if (tour == 1) alert('Le joueur rouge a gagné!');
        else alert('Le joueur jaune a gagné!');
        end = true;
      }
    }
    j = 0;
  }
  for (y = 0; y <= 3; y = y + 1) {
    for (x = 1; x <= 3; x = x + 1) {
      if (couleur[vr[colonne] + 2 + y][colonne + 3 - y] == couleur[vr[colonne] + 2 - x + y][colonne + 3 + x - y]) {
        j = j + 1;
      }
      if (j > 2 && end != true) {
        if (tour == 1) alert('Le joueur rouge a gagné!');
        else alert('Le joueur jaune a gagné!');
        end = true;
      }
    }
    j = 0;
  }
}
// FIN
