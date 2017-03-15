// Tristan GEMIN
//Léana JUGE

function draw(c) {
  Initialiser();
 RectanglePlein(10,50,1100,600,'blue');
  CerclePlein(posx,posy,10,'orange');
  RectanglePlein(1100,mouseY,5,100,'red');
  if (posx <= 1110 && posx >= 10) {
  posx = posx + 1;
     } else {
       posx = posx - 1;}
  if (posy <= 650 && posy >= 50) {
  posy = posy + 1;
        } else {posy = posy - 1;
     }
}
  if (posx == mouseX && mouseY>=posy && posy>=mouseY-100) {
    posx = posx - 1;
}

function Keypressed(c) {
  noLoop();
}


var posx,posy;

posx=100;
posy=100;
Loop(-1);

