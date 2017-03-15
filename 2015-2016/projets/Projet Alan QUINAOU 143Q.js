	/*Question 1*/

function EnCode(message /*cha�ne de caract�res*/ , clef /*cha�ne de caract�res*/ ) /*cha�ne de caract�res*/
{ /*Variables*/

  var res; /*caract�re*/

  /*D�but*/
  res = (Caractere_vers_Ascii(message) - 65);
  if ((res > 0) && (res < 26)) {/*La boucle "si" permet de traduire seulement les caract�res de l'alphabet*/
    res = res + (Caractere_vers_Ascii(clef) - 65);
    if (res > 25) {/*celle-ci permet de ne pas sortir de l'alphabet*/
      res = res - 27;
    }
  }
  res = (Ascii_vers_Caractere(res + 65));
  return (res);
}

/*Fin*/

/*Variables*/

var i, j, n, mod; /*entiers*/
var message, clef, messcode; /*cha�nes de caract�res*/

/*D�but*/

messcode = '';
message = Saisie('Saisissez le message � coder');
clef = Saisie('Saisissez la clef');
n = Longueur(message);
for (i = 0; i <= (Math.floor(Longueur(message) / Longueur(clef))); i = i + 1) { /*A chaque tour de la boucle, on traduit le message cod� gr�ce � la clef.*/
  for (j = 0; j < (Longueur(clef)); j = j + 1) { /*A chaque tour de la boucle, on utilise le caract�re de la clef au rang j pour traduire le message cod�.*/

    messcode = messcode + EnCode(CaractereEn(message, i * Longueur(clef) + j), CaractereEn(clef, j));

  }
}
Ecrire(messcode);

/*Fin*/

/*Question 2*/

function DeCode(messcode /*cha�ne de caract�res*/ , clef /*cha�ne de caract�res*/ ) /*cha�ne de caract�res*/
{ /*Variables*/

  var res; /*caract�re*/

  /*D�but*/
  res = (Caractere_vers_Ascii(messcode) - 65);
  if ((res > 0) && (res < 26)) {
    res = res - (Caractere_vers_Ascii(clef) - 65);
    if (res <0) {
      res = res + 27;
    }
  }
  res = (Ascii_vers_Caractere(res + 65));
  return (res);
}

/*Fin*/

/*Variables*/

var i, j, n, mod; /*entiers*/
var messcode, clef, message; /*cha�nes de caract�res*/

/*D�but*/

message = '';
messcode = Saisie('Saisissez le message cod�');
clef = Saisie('Saisissez la clef');
n = Longueur(messcode);
for (i = 0; i <= (Math.floor(Longueur(messcode) / Longueur(clef))); i = i + 1) { 
  for (j = 0; j < (Longueur(clef)); j = j + 1) {

    message = message + DeCode(CaractereEn(messcode, i * Longueur(clef) + j), CaractereEn(clef, j));

  }
}
Ecrire(message);

/*Fin*/


//Question 3
//Variables
var j, n; //j et n sont des entiers
//D�but
n = 0;
for (j = 0; j <= 25; j = j + 1) {
  n = n + 1;
}
n = Math.pow(n, 5);
Ecrire(enChaine(n));

//Le resultat est trop grand, l'utilisateur humain ne peut pas chercher le message dans une telle liste

//Fin

//Question 4

function FriedMan(messcode /*cha�ne de caract�res*/ ) { /*cha�ne de caract�res*/

  var I;/*r�el*/
  var Na, n, i, j;/*entiers*/
  Na = 0;
  I=0;
  n=Longueur(messcode);
  var Tableau = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'];
  for (i = 0; i <= 25; i = i + 1) { /*prend une lettre de l'alphabet*/
    for (j = 0; j <= Longueur(messcode)-1; j = j + 1) { /*Prend un caract�re du message � cod�*/
      if (CaractereEn(messcode, j) == Tableau[i]) { /*V�rifie si le caract�re correspond aux lettres de l'alphabet*/
        Na = Na + 1;
            Ecrire(Na);
      }
    }
    I = I+(Na * (Na - 1))/(n*(n-1)); /*formule de Friedman*/
    Na = 0;
  }
  return (I);
}

Ecrire(enChaine(FriedMan(Saisie('Saisissez le message � coder'))));
