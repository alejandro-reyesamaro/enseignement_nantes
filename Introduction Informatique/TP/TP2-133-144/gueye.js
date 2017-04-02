Amaury GUEYE, Théo POUPARD 133 A 

// Programme Pong
// Variables
var posx,posy,bouleX,bouleY;
posx=100;
posy=100;
Loop(-1);
bouleX=2;
bouleY=2;

//Début
function draw(c) {
  Initialiser();
  CerclePlein(posx,posy,10,'black');
  RectanglePlein(1300,mouseY,5,100,'blue');
  Rectangle(0,0,1300,600);
function Keypressed(c) {
  noLoop();
  
   
}

 if(posx>mouseX-1 && posx<mouseX+5 && posy>mouseY-1 && posy<mouseY+100) 
 {
   bouleX=bouleX+1;
 }
  
  if(posx<10)
  {
  bouleX=bouleX+1;
  }
  
  if(bouleX%2==0) 
  {   
  posx = posx+5;
  }
  
  else{
    posx=posx-5;
  }
 
  if(posy<0)
     {
     bouleY=bouleY-1;
    }
 if(posy>600)
  {
    bouleY=bouleY+1;
  }
  
 if(bouleY%2==0)
 {
   posy=posy+2;
 }
 else{
   posy=posy-2;
 }
}

//Fin
