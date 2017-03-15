// Javascript code here

//Projet chaine de caractere 2



function trouverpos(x /*caractere*/ ) {

  //cette fonction retourne l'entier correspondant a la position de la lettre

  var alphabet/*chaine de caractere*/;

  var pos/*entier*/;

  var i/*entier*/;

  alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';

  pos = -1;

  for (i = 0; i < Longueur(alphabet); i = i + 1)

  if (CaractereEn(alphabet, i) == x) {

    pos = i;

  }

  return (pos);

}

//----------------------------------------------------



function trouverlettre(rang /*entier*/ ) { //cette fonction retourne la lettre dont la position correspond a l'entier rang

  var lettre, alphabets/*chaine de caractere*/;

  alphabets = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';

  lettre = CaractereEn(alphabets, rang);

  return (lettre);

}



//-----------------------------------------------------



function encode(messag /*message a coder*/ , cle) {



  var car_messag/*chaine de caractere*/, car_cle/*chaine de caractere*/, messag_code/*chaine de caractere*/, pos_car/*entier*/, pos_cle/*entier*/, lettre_codee/*chaine de caractere*/,
code/*entier*/, j/*entier*/;



  messag_code = '';



  while (Longueur(cle) < Longueur(messag))

  cle = cle + cle;

  for (j = 0; j < Longueur(messag); j = j + 1) {

    car_messag = CaractereEn(messag, j);//trouve la lettre au rang j

    pos_car = trouverpos(car_messag);//trouve la position correspondant a la lettre

    car_cle = CaractereEn(cle, j);//trouve la lettre au rang j

    pos_cle = trouverpos(car_cle);//trouve la position correspondant a la lettre

    if (pos_car >= 0) {

      code = pos_car + pos_cle;//position de la lettre codée
      if(code>25)
        code=code-26;//permet le retour de la valeur dans l'intervalle de 0 à 25

      lettre_codee = trouverlettre(code);

    } else lettre_codee = car_messag;

    messag_code = messag_code + lettre_codee;

  }

  return (messag_code);

}

//-------------------------------------------------------

function decode(mess_cod /*message a decoder*/ , cl) {



  var car_mess/*chaine de caractere*/, car_cl/*chaine de caractere*/, mess_decod/*chaine de caractere*/, ps_car/*entier*/, ps_cl/*entier*/, letre_decodee/*chaine de caractere*/, cde/*entier*/, k/*entier*/;



  mess_decod = '';



  while (Longueur(cl) < Longueur(mess_cod))

  cl = cl + cl;

  for (k = 0; k < Longueur(mess_cod); k = k + 1) {

    car_mess = CaractereEn(mess_cod, k);

    ps_car = trouverpos(car_mess);

    car_cl = CaractereEn(cl, k);

    ps_cl = trouverpos(car_cl);

    if (ps_car >= 0) {

      cde = ps_car - ps_cl;//position de la lettre codée
      if(cde<0)
        cde=cde+26;//permet le retour de la valeur dans l'intervalle de 0 à 25
      letre_decodee = trouverlettre(cde);

    } else letre_decodee = car_mess;

    mess_decod = mess_decod + letre_decodee;

  }

  return (mess_decod);

}

//------------------------------------------------------

//algo

var mes/*chaine de caractere*/, cler/*chaine de caractere*/, result/*chaine de caractere*/, longcl=5/*entier*/, fact1/*entier*/, fact2/*entier*/, nb/*entier*/, m/*entier*/, n/*entier*/, den/*entier*/;

//debut

Ecrire('saisir le message à coder');

mes = Saisie();

Ecrire('le message à coder est ------------- '+mes);

Ecrire('saisir la cle de codage');

cler = Saisie();

Ecrire('la cle de codage est --------------------- '+cler);

result = encode(mes, cler);

Ecrire('premiere question-------le message coder est --------------------'+result);

Ecrire('deuxieme question-------le decodage donne --------------'+decode(result,cler));


//calcul du nombre de possibilité
fact1=1;
fact2=1;
for (m=1;m<=26;m=m+1)
fact1=fact1*m;//calcul le factorielle de 26
den=26-longcl;//
for(n=1;n<=den;n=n+1)
fact2=fact2*n;//calcul le factorielle de 26-le nombre de caractere
nb=fact1/fact2;//calcul le nbre de possibilité

Ecrire('troisieme question-------le nombre de decodage possible est de------------'+nb);


