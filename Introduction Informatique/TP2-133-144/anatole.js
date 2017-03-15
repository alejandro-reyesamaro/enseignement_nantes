//Anatole TOUVRON et Paul LEBER
// Algo pong
  function draw(c) {
  Initialiser();
  Rectangle(0,0,505,305,'black');
  CerclePlein(posx,posy,10,'green');
  RectanglePlein(500,mouseY,5,100,'red');
  posx = posx + depx;
  posy = posy + depy;
  if(posx<0 || posx>495){
    depx=-depx;
  } 
  if(posy<0 || posy>300){
    depy=-depy;
  } 
  }

function Keypressed(c) {
  noLoop();
}
var posx,poxy,depx,depy;
depx=3;
depy=3;
posx=100;
posy=100;
Loop(-1);
