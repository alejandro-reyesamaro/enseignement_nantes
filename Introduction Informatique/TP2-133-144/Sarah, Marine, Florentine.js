//jeu pong 
function draw(c) {
Initialiser();
CerclePlein(posx,posy,10,'red'); //Dessin de la boule

  if (posx < 3)
  Texte(400,400, 'GAMEOVER', 'red'); // Si la boule passe deriere la barre bleu, c'est perdu 
  
  if ( posy < 3){ // Si la balle arrive sur le rectangle du haut, elle rebondit
    diry *= -1 ;}
  
  if (posx > 1000){// Si la balle arrive sur le rectangle de droite, elle rebondit
    dirx *= -1;}
  
  if ( posy > 700){ // Si la balle arrive sur le rectangle du bas, elle rebondit
    diry *= -1 ;}
  
  
  if(posx < 100)
  {
    if(posy >= mouseY && posy <= mouseY+100)   // Si la balle arrive sur toute la hauteur la barre bleu, la balle rebondit
    {
      dirx *= -1;
    }
  }
  
   
  
RectanglePlein(100,mouseY,5,100,'blue'); // délimitation du terrain de jeu 
RectanglePlein(0,3,1000,5,'black');
RectanglePlein(1000,3,5,700,'black');
RectanglePlein(3,700,1000,5,'black');
  
posx = posx + dirx; // avancement de la balle 
posy = posy + diry;
}

function Keypressed(c) {   // stopper la balle si on appuie sur une touche de clavier 
noLoop();
}

var posx,poxy;
var dirx,diry;
dirx=4;  // vitesse de la balle 
diry=4;
posx=300; //position de départ de la balle 
posy=300;
Loop(-1); // Avancement de la balle en continue 