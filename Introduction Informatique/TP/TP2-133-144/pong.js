//Richet Axel E161888Q
//Bouré Valentin E162068L


//Algorithme pong

function draw(c) {
  Initialiser();
  RectanglePlein(400,100,750,500,'black'); //création du plateau
  RectanglePlein(450,mouseY,5,100,'white'); //création de la raquette
  CerclePlein(posx,posy,10,'white'); //création de la balle
  posx = posx + depx; 
  posy = posy + depy;
  
  if (posx>1150) {depx=-depx;}//rebond plateau
  if (posy<100 || posy>600) {depy=-depy;} //rebond plateau
  if (posx > 450 && posx < 455 && posy > mouseY && posy < mouseY + 100) {depx = -depx;}//rebond raquette
  if (posx<=400) {Texte(775,350,'GAME OVER','green');}//fin de la partie 

  if (mouseY <= 100) {mouseY=100;}//borne raquette
  if (mouseY >= 500) {mouseY=500;}//borne raquette

}

//Variables
var posx,poxy;
posx=1150; //position balle au debut
posy=100; //position balle au debut
depx=1;
depy=1;
Loop(-1);
