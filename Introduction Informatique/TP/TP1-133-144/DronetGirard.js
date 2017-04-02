//Algorithme calcule âges
//variable
//j jour de la date de naissance : entier
//m mois de la date de naissance : entier
//a année de la date de naissance : entier
//f : entier
//d :entier
//p :entier
//q :entier

//Début
j=Saisie ('jour');
m=Saisie ('mois');
a=Saisie ('annee');

f=2020-a;
Ecrire ('âge au 31 décembre 2020 ='+f);
d=2000-a;
Ecrire ('âge au 31 décembre 2000='+d);
if (m<=8){
	p=d;
	Ecrire ('âge au 31 août 2000='+p);
}else
{
	p=d-1;
	Ecrire ('âge au 31 août 2000='+p);
}

if (m<8 || (m=8 && j<=15)){
	q=d;
	Ecrire ('âge au 15 août 2000='+q);
}else
{
	q=d-1;
	Ecrire ('âge au 15 août 2000='+q);
}
//Fin



//Algorithme nombre de jours dans le mois
//variables
//a année : entier
//m mois : mois

//Début
a=Saisie ('année');
m=Saisie ('mois');
if (a % 4 ==0 && m==2){
	Ecrire ('le mois a 29 jours');
}
if (a % 4 !=0 && m==2){
	Ecrire ('le mois a 28 jours');
}
if (m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12){
	Ecrire ('le mois a 31 jours');
}
if (m==4 || m==6 || m==9 || m==11){
	Ecrire ('le mois a 30 jours');
}
//Fin
