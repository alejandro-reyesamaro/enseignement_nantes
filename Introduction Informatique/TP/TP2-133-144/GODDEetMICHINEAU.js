// pong

function draw(c) {
  Initialiser();
  X = 10;
  Y = 0;
  Lrectan = 700;
  Hrectan = 600;
  var PosrectY; 
  Rectangle(X,Y,Lrectan,Hrectan,'red');
  CerclePlein(posx,posy,10,'black');
  PosrectY = Math.min(mouseY, 500);
  RectanglePlein(700,PosrectY,5,100,'blue');
  posx = posx + dirx;
  posy = posy + diry;
 
  if (posx >= 700 && posy >= PosrectY){
   dirx = -dirx; 
  }
  if (posy >=600)
    diry = -diry;
  if( posx <= 10)
    dirx = -dirx;
  if( posy <= 0)
    diry = -diry;
}

function Keypressed(c) {
  noLoop();
}

var posx,poxy;
posx=100;
posy=100;
dirx=2;
diry=2;
Loop(-1);