// Your code here
//VICTOR GODET et JULIEN LEPLAE-GIOVE
//Jeu de pong
//Debut
x=1;
y=1;

function draw(c) {
  Initialiser();
  Rectangle(50,50,600,350,'black');
  CerclePlein(posx,posy,10,'black');
  RectanglePlein(625,mouseY,5,50,'blue');

 if (posy==400){
    y=-y;
}
 if (posx==650){
   x=-x;
 }
 if (posy==50) {
   y=-y;
 }
 if (posx==50) {
   x=-x;
 }
  if (posx==625) {
   if (posy >= mouseY && posy <= mouseY + 50 ) {
     y=-y;
      }}

  posx = posx + x;
  posy = posy + y;

 }

function Keypressed(c) {
  noLoop();
  }

var posx,poxy,x,y;
posx=100;
posy=100;
Loop(-1);
//Fin
