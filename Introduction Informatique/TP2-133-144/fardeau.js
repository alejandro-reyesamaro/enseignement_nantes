Fardeau Maxime
Gicqueau Maxime

Mouseclick → exécute l'action lorsqu'on clique gauche
MouseMove → effectue l'action lorsque l'on clique et que l’on bouge la souris 
Keypressed → effectue l'action lorsque l'on appui sur la touche demandée


//Pong
function draw(c) {
  Initialiser();
  RectanglePlein(0,0,1500,750,'red'); //aire de jeu
  CerclePlein(posx,posy,10,'black');
  RectanglePlein(900,mouseY,5,100,'blue');
  posx = posx + dirx;
  posy = posy + diry;
  
  	if (posx>900 && mouseY<posy && posy<mouseY+100){ //La balle tape exactement la barre bleue : fixe en x et mobile en y
   		dirx = -dirx;  
	}
  
  if (posx>1500 || posx<0 ){ // limite de l'aire de jeu
    dirx=-dirx;
}
  
  if (posy>750 || posy<0){
    diry=-diry;
  }
  
  if (posx>1000){
    noLoop();
  	RectanglePlein(0,0,1500,750,'black');//Le jeu est perdu : écran noir
  }
}


  
function Keypressed(c) { //arret du programme touche 'c'
  noLoop();
}


var posx,posy;
posx=100;
posy=100;
dirx = 5; //vitesse de la balle
diry = 5;
Loop(-1);
