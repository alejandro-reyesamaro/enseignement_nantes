var posx, posy, vitx, vity;

function setup() {
   posx = 10;//Position de la balle au lancement
   posy = 10;//Position de la balle au lancement
   vitx = 10; //vitesse de la balle en x
   vity = 10;//vitesse de la balle en y
}

function draw() {
Initialiser();
CerclePlein(posx,posy,10,'red');

posx = posx + vitx;
posy = posy + vity;

if (posx>500) {vitx=-vitx;}
if (posy<0 || posy>500) {vity=-vity;}

RectanglePlein(10,mouseY,10,100);
  if (mouseY > 400) {
    (mouseY = 400);
  }
Rectangle(5,5,500,500,'blue');
   if (posx<10) {
      posx=Hasard(400)+100; //La balle réaparrait à un chiffre au hasard +100 dans x
      posy=Hasard(400)+100; //La balle réapparait à un chiffre au hasard +100 dans y
   }
   if (posx > 10 && posx < 20 && posy > mouseY && posy < mouseY + 100) {
      vitx = -vitx;
   }
}
Loop(-1);