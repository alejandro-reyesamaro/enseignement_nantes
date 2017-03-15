//BENOIST Bettina 161561K
//COCHET Klervi 166470W


// Pong
var ballex, balley, sensx, sensy;

function setup() {
   ballex = 10;
   balley = 10;
   sensx = 7;
   sensy = 7;
}

function draw() {
   Initialiser();
   CerclePlein(ballex,balley,20,'blue');

   ballex = ballex + sensx;
   balley = balley + sensy;

   if (ballex<0 || ballex>800) {sensx=-sensx;}
   if (balley<0 || balley>800) {sensy=-sensy;}
 
   RectanglePlein(10,mouseY,10,100);
   if (ballex > 10 && ballex < 20 && balley > mouseY && balley < mouseY + 100) {
      sensx = -sensx;
   }
   RectanglePlein(500,mouseY,10,100);
   if (ballex > 500 && ballex < 510 && balley > mouseY && balley < mouseY + 100) {
      sensx = -sensx;
   }
   if (ballex > 550){
      Loop(-1);
      Texte(250,250,'Game over','red');
   }
}