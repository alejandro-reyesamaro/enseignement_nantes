
// Algorithme : Solo Pong


//Variables : 
var posx,posy, dirX, dirY, // : entier
    gameOver; // : bool


//but :

Setup(); // Initialise les variables

function draw(c) {
  if(!gameOver) //Condition qui permet de continuer ou d'arreter le jeu
  {
    Initialiser();
    if(posx <= 55) // si la position de la balle sur x est inferieure55, alors ...
    { 
      if(posy >= mouseY && posy <= (mouseY+50)) // si la position de la balle sur y est sur la partie haute de la barre ...
      {
        dirX *= -1;
        dirY = -Math.abs(dirY);
      }
      else if(posy >= mouseY+50 && posy <= mouseY+100)// si la position de la balle sur y est sur la partie basse de la barre ...
      {
        dirX *= -1;
        dirY = Math.abs(dirY);
      }
      else // si on a passer la barre , si on a perdu, fin du jeu
      {
        gameOver = true;
        Texte(300, 300, 'GAME OVER', 'red');
      }
    }

    if(posx >= 600) // rebond sur le rectangle du fond (de droite)
    {
      dirX *= -1;
    }
    if(posy <= 3 || posy >= 600) // rebond sur le rectangle du haut et le rectangle du bas
    {
      dirY *= -1;
    }
    CerclePlein(posx,posy,10,'black');// balle
    RectanglePlein(0, 3, 600, 5, 'black');//rectangle du haut
    RectanglePlein(0, 600, 605, 5, 'black');// rectangle du bas
    RectanglePlein(600, 3, 5, 600, 'black');// rectagle de droite
    if(mouseY >= 500) // bloquer la barre a l'intrieur du rectangle de jeu
    {
      mouseY = 500;
    }
    RectanglePlein(50,mouseY,5,100,'blue');
    posx = posx + dirX;
    posy = posy + dirY;
  }
}
function Keypressed(c) { // permet l'arrt du jeu
  noLoop();
}

function Keypressed(a) // permet de relancer une partie
{
  if(gameOver)
  {
    Setup();
  }
}



function Setup() // fonction qui Initialise les variables
{
  dirX = -2;
  dirY = -2;
  posx=500;
  posy=500;
  gameOver = false;
  Loop(-1);
}

//FIN
