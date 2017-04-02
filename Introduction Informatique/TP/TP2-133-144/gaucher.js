 // TP scéance 3 Pong
 //GAUCHER Marc E165770K
//KURTALIQI Endrit  E161106Q


  var posx,poxy;
posx=100;
posy=100;
Loop(-1);


function draw(c) {
  Initialiser();
  CerclePlein(posx,posy,10,'black');
  RectanglePlein(mouseX,mouseY,-5,-100,'blue');

  if (posx>mouseX && posx<mouseX+5 && posy<mouseY && posy<mouseY+100){
  posx=posx-75;
  posy=posy-75;
}else{
  posx = posx + 2;
  posy = posy + 2;
}


function Keypressed(c) {
  noLoop();
}
}
