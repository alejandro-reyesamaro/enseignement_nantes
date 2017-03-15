function draw(c) {
  Initialiser();
  RectanglePlein(0, 0, 900, 700, 'black');
  CerclePlein(posx, posy, 10, 'red');
  RectanglePlein(850,mouseY, 5, 100, 'blue');
  posx = posx + dep_x;
  posy = posy + dep_y;

  if (posy > 700 || posy < 0) {
    dep_y = dep_y * -1;
  }

  if (posx > 900 || posx < 0) {
    dep_x = dep_x  * -1 ;
  }
}

if(posy<= mouseY+100 && posy>=mouseY && posx<=850)
   {dep_x=dep_x*-1;
   dep_y=dep_y*-1;
   }
   
   
function Keypressed(c) {
  noLoop();
}
var posx, posy, dep_x, dep_y;
posx = 100;
posy = 100;
dep_x = 3;
dep_y = 3;
Loop(-1);

//LEDUC Mathieu / THUILIER Elea
