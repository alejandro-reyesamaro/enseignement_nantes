// Your code here
function MouseClick(x,y) {
	Texte(x,y,'Aie !!!','red');
}

function MouseMove(x,y) {
	CerclePlein(x,y,5,'black');
}

/*
function draw(c) {
  Initialiser();
  
  // creating a rectagle
  Rectangle(5,5,700,900,'green');
  
  CerclePlein(posx,posy,10,'black');  
  // the bar only moves along y-axis
  var barX = 700;
  if(mouseY > 5 && mouseY < 800)
	RectanglePlein(barX,mouseY,5,100,'blue');
  
  // positions are affected by the direction
  posx = posx + vitX;
  posy = posy + vitY;
  
  // directions changing at limits
  if(posx <= 5 || (posx >= 700 && mouseY <= posy && mouseY >= posy - 100))
    vitX = vitX * (-1);
  if(posy >= 900 || posy <= 5)
    vitY = vitY * (-1);
  
  if(posx > 750)
  {
    vitX = 0;
    vitY = 0;
  }
}
*/


function Keypressed(c) {
  //noLoop();
  RectanglePlein(90,90,100,20,'white');
  Texte(100,100,Ascii_vers_Caractere(c),'red');
}


var posx,poxy, vitX, vitY;
posx=100;
posy=200;
vitX = 1;
vitY = 1;
//Loop(-1);
