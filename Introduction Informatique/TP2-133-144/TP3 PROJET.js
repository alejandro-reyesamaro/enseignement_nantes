DUMAST ANTHONY 133A
DORE THOMAS    133B


//ALGORITHME PROJET
//Jeux de Pong a un joueur
//variables posx, posy, x, y : entiers

//FONCTIONS
function draw(){
  Initialiser();
  RectanglePlein(0,0,810,740,'black');
  CerclePlein(posx,posy,20,'white');
  RectanglePlein(790,mouseY-50,10,100,'white');
  
  posx = posx + x;
  posy = posy + y;

  if(posx<10){
    x=-x;
  }
  if(posy<10 || posy>730){
    y=-y;
  }

   
  if(posx==780 && posy>mouseY-50 && posy<mouseY+50){
    x = -x;
  }
}
function Keypressed(c){
  noLoop();
}

//DEBUT
var posx, posy, x, y;
posx = 400;
posy = 10;
x = 1;
y = 1;
Loop(-1);
//FIN