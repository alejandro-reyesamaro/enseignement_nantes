//VARIABLES
var posx,poxy;
posx=100;
posy=100;
movx = 20;
movy = 20;

//INITIALISATION
function draw(c) {
  Initialiser();
  CerclePlein(posx,posy,20,'black');
  RectanglePlein(20,mouseY,10,100,'blue');
  posx = posx + movx;
  posy = posy + movy;
  
  
  //DEBUT PROGRAMME
  if (posy>=screen.height-40) {
    movy=-movy;
  }
  if (posx>=screen.width-20) {
    movx=-movx;
  }
  if (posy<=20) {
    movy=-movy;
  }
  if (posx>=30 && posx<=40 && posy>=mouseY && posy<=mouseY+100) {
    movx=-movx;
  }
  if (posx<=0) {
    setCanvasFont('helvetica', '50pt','bold');
    Text((screen.width/2)-300,(screen.height/2)-50,'Vous avez perdu !', 'red');
  }
}
//FIN PROGRAMME
function Keypressed(c) {
  noLoop();
}
Loop(-1);  
