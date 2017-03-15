	/*Question 1*/

function EnCode(message /*chaîne de caractères*/ , clef /*chaîne de caractères*/ ) /*chaîne de caractères*/
{ /*Variables*/

  var res; /*caractère*/

  /*Début*/
  res = (Caractere_vers_Ascii(message) - 65);
  if ((res > 0) && (res < 26)) {/*La boucle "si" permet de traduire seulement les caractères de l'alphabet*/
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
var message, clef, messcode; /*chaînes de caractères*/

/*Début*/

messcode = '';
message = Saisie('Saisissez le message à coder');
clef = Saisie('Saisissez la clef');
n = Longueur(message);
for (i = 0; i <= (Math.floor(Longueur(message) / Longueur(clef))); i = i + 1) { /*A chaque tour de la boucle, on traduit le message codé grâce à la clef.*/
  for (j = 0; j < (Longueur(clef)); j = j + 1) { /*A chaque tour de la boucle, on utilise le caractère de la clef au rang j pour traduire le message codé.*/

    messcode = messcode + EnCode(CaractereEn(message, i * Longueur(clef) + j), CaractereEn(clef, j));

  }
}
Ecrire(messcode);

/*Fin*/

/*Question 2*/

function DeCode(messcode /*chaîne de caractères*/ , clef /*chaîne de caractères*/ ) /*chaîne de caractères*/
{ /*Variables*/

  var res; /*caractère*/

  /*Début*/
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
var messcode, clef, message; /*chaînes de caractères*/

/*Début*/

message = '';
messcode = Saisie('Saisissez le message codé');
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
//Début
n = 0;
for (j = 0; j <= 25; j = j + 1) {
  n = n + 1;
}
n = Math.pow(n, 5);
Ecrire(enChaine(n));

//Le resultat est trop grand, l'utilisateur humain ne peut pas chercher le message dans une telle liste

//Fin

//Question 4

function FriedMan(messcode /*chaîne de caractères*/ ) { /*chaîne de caractères*/

  var I;/*réel*/
  var Na, n, i, j;/*entiers*/
  Na = 0;
  I=0;
  n=Longueur(messcode);
  var Tableau = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'];
  for (i = 0; i <= 25; i = i + 1) { /*prend une lettre de l'alphabet*/
    for (j = 0; j <= Longueur(messcode)-1; j = j + 1) { /*Prend un caractère du message à codé*/
      if (CaractereEn(messcode, j) == Tableau[i]) { /*Vérifie si le caractère correspond aux lettres de l'alphabet*/
        Na = Na + 1;
            Ecrire(Na);
      }
    }
    I = I+(Na * (Na - 1))/(n*(n-1)); /*formule de Friedman*/
    Na = 0;
  }
  return (I);
}

Ecrire(enChaine(FriedMan(Saisie('Saisissez le message à coder'))));
