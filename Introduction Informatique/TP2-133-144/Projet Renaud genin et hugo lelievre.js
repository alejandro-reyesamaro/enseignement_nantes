Renaud Génin et hugo lelièvre

var posx,poxy,x,y, posbar;
x=1;
y=1;
posx=200;
posy=50;
Loop(-1);

function draw(c) {
  Initialiser();
  RectanglePlein(0,0,500,3,'black');
  RectanglePlein(500,0,3,500,'black');
  RectanglePlein(0,500,503,3,'black');

  CerclePlein(posx,posy,10,'red');
  posbar = Math.min(mouseY, 450);
  RectanglePlein(10,posbar-50,5,100,'blue');
  posx = posx + x;
  posy = posy + y;
  
  if (posx == 495 || ((posx == 15 && posy>mouseY-50 && posy<mouseY+50))){
    x = -x;
  }
  
  if (posy == 495 || (posy == 5)){
    y = -y;
  }
  
  if (posx < 10){
    noLoop();
	Rectangle(50,50,350,150,'black');
	RectanglePlein(51,51,348,148,'red');
	Texte(190,125,'Tu as perdu','black');
  }
    
}

function Keypressed(c) {
  noLoop();
}
  
