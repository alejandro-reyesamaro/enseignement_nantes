//Algorithme TP 3

function draw(c) {
  Initialiser();
  RectanglePlein(100,99,750,500,'blue');
  CerclePlein(posx,posy,10,'black');
  RectanglePlein(700,mouseY,5,100,'red');
  if(mouseY<=99)
    mouseY=99-1;
  if(mouseY>=500)
    mouseY=500-1;

  if(posy==599)
    posy=posy-depy;

  if(posy==99)
    posy=posy+depy;


}
function Keypressed(c) {
  noLoop();
}
var posx,poxy,depx,depy;
posx=100;
posy=100;
Loop(-1);
depx=1;
depy=1;
