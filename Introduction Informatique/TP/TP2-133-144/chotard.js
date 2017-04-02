function draw(c) {
  Initialiser();
   RectanglePlein(0,0,700,700,'red');
  CerclePlein(posx,posx,10,'black');

   RectanglePlein((mouseX),mouseY,5,100,'blue');
  posx = posx + x;
  posy = posy + y;

if ( mouseX-posx<5 && mouseY-posy<50) {  // condition selon laquelle la
balle est ou pas sur la raquette
  y=-y ;
  x=x; }
  if ( posx<0 ||  posy<0 || posx>700 || posy>700) // Pour éviter que la
balle sorte de l'ecran
  { x=-x ;
  y=-y ;   }

}
function Keypressed(c) {
  noLoop();
}
var W,N , x,y,posx,poxy;
posx=100;
posy=100;
Loop(-1);
x=1;
y=1;

