// Cossard Florian 161645B
// Rigaut Ulysse 168920J

// Algorithme : Pong 1 joueur
// Variables
var racketY, ballX, ballY;
var speedX, speedY;
var score;

// Fonction : Dessiner et modifier les positions
function draw()
{
  Initialiser();

  // Aide
  Texte(50, 30, 'Utiliser la souris pour bouger la raquette et Q pour quitter.', 'black');

  // Terrain
  Line(50, 50, 850, 50, 'black');
  Line(50, 450, 850, 450, 'black');
  Line(850, 50, 850, 450, 'black');

  // Raquette
  racketY = mouseY;

  if(racketY < 51)
    racketY = 51;
  else if(racketY > 369)
    racketY = 369;

  RectanglePlein(80, racketY, 5, 80, 'blue');

  // Balle
  ballX += speedX;
  ballY += speedY;

  if(ballY - 5 < 51)
  {
    ballY = 56;
    speedY = -speedY;
  }
  else if(ballY + 5 > 449)
  {
    ballY = 444;
    speedY = -speedY;
  }

  if(ballX + 5 > 849)
  {
    ballX = 844;
    speedX = -speedX;
  }
  else if(ballX - 5 < 85)
  {
    if((ballY + 5 > racketY) && (ballY - 5 < racketY + 80))
    {
      ballX = 90;
      speedX = -speedX;
    }
    else
    {
      score += 1;

      ballX = 450;
      ballY = 250;

      speedX = Hasard(5) + 8; // speedX = 8; 9; 10; 11 ou 12
      speedY = Hasard(5) + 8; // speedY = 8; 9; 10; 11 ou 12
    }
  }

  CerclePlein(ballX, ballY, 10, 'black'); // diametre = 10 pixels

  // Score
  Texte(50, 480, 'Balles perdues : ' + score, 'black');
}

// Fonction : Gerer le clavier
function Keypressed(c)
{
  c = Ascii_vers_Caractere(c);
  if(c == 'Q')
    noLoop();
}

//Debut
racketY = 210;
ballX = 450;
ballY = 250;

speedX = Hasard(5) + 8; // speedX = 8; 9; 10; 11 ou 12
speedY = Hasard(5) + 8; // speedY = 8; 9; 10; 11 ou 12

score = 0;

FrameRate = 60;
Loop(-1);
// Fin
