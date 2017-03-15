 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%                 Debut...                                       %%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% I. UNIFICATION ('_' : variable anonyme):

e0(1,[X,Y]) :- f(X,a,Y) = f(b,Y,_).
e0(2,[X,Y]) :- f(X,_,h(Y,Y,c)) = f(Z,0,h(k(X),V,X)).
e0(3,[U]) :- f(X,h(X,X),k(Y,Y)) = f(g(0),Y,U).
e0(4,[X,Y,Z]) :- f(X,h(_,Y,Y),_) = f(Y,h(6,k(5),Z),c).
e0(5,_) :-
  f(X,[1,2]) = f([1|Y],X),
  write(X),
  nl,        % a la ligne
  write(Y).
e0(6,X) :- f(a,b) = f(X,X).
e0(7,X) :- f(X) = X.               % BOUCLES !!!!!
e0(8,X) :- [1|X] = X.
e0(9,X) :- [1|_] = X.

%% Unification au cours des appels:
e0(10,[X,Y]) :- p(X,[a|Y]).

p(a0,[a,b,c]).                     % definition de p/2 par un fait

e0(10,[X,Y]) :- p(X,[a,b|Y]).

%%%%%%%%%%%%%%%%%%%%%%%
%% II. FLUX DE CONTROLE

%% Comment marche Prolog :

pro :-
  step1,
  write('Tapez s pour passer au pas suivant ou bien une autre touche pour un ECHEC'),
  nl,
  get_single_char(K),
  (K=115;false),
  step2,
  write('Tapez s pour terminer ou bien une autre touche  pour un ECHEC'),
  nl,
  get_single_char(KK),
  (KK=115;false),
  nl,
  write('Terminaison reussite! Tapez une touche pour sortir'),
  nl,
  get_single_char(_),
  !.
  
step1 :-
  write('PAS 1 : '),
  nl.

step1 :-
  nl,
 write('Un echec en PAS 1! Pour voir une autre alternative tapez une touche'),
  get_single_char(_),
  nl,
  step1_1.

step2 :-
  write('PAS 2 : '),
  nl.
step2 :-
  nl,
  write('Un echec en PAS 2! Il n y a pas d autre alternative! Tapez une touche pour faire le BACKTRACKING'),
  get_single_char(_),
  nl,
  fail.
  
step1_1 :- 
  write('This is the second altrnative for step1'),
  nl,  
  write('Type s to proceed to the next step or other key for FAILURE'),
  nl,
  get_single_char(K),
  nl,
  (K=115;
   write('This is the deadend. Type a key to FAIL'),
   nl,
  get_single_char(_),
   false
  ).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

e1(a) :- write('a -> b '),
     nl,
     e1(b),
     nl,
     write(' b -> c '),
     nl,
     e1(c),
     nl,
     write('c -> fail '),                % ECHEC
     nl,
     write(' Backtrack... '),
     nl,
     fail.
e1(a) :- write(' deuxieme clause de a '),
     nl,
     write(' a -> e '),
     nl,
     e1(e).
e1(b) :- write(' b reussit ').
e1(c) :- write(' c -> e '),
     nl,
     e1(e).
e1(e) :- write(' e reussit ').

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%% INTERPRETEUR
% 2. Regle d interpretations des programmes en PROLOG
% Programme P+{:- but}. Etat initial <:-but ; identite>

%% I. Pas de RESOLUTION.
%  Soit un etat S_i = <:- G_i; s_i >
%     ( :- G_i le but actuel, s_i - la substitution actuelle)
%     SI G_i = [], ALORS EXIT. Resultat: (s_i | vars(G));
%     SI G_i = p(args),G' ET
%       r_i = (p(args') :- corps) est la premiere clause de la definition
%       de 'p', qui n'a pas ete utilisee aux pas precedants, et dont la
%       tete p(args') s'unifie avec p(args) via la substitution s_i:
%                  p(args) * s_i * u = p(args') * u
%       (u etant l'unificateur le plus general)
%     ALORS l'etat suivant est <:- corps, G'; s_i * u> ;
%     ENSUITE on passe au pas de resolution.
%     SI il n'existe pas de clause unifiable dans la definition de 'p',
%     ALORS un ECHEC se produit, ET on passe au pas de BACKTRACKING.
%% II. Pas de BACKTRACKING.
%  Soit un etat < :- G_i; s_i >
%   SI i=1, ALORS EXIT. L'ECHEC GENERAL du calcul.
%   SI i>1 ET il n'y a plus des clauses unifiables dans la definition de 'p'
%      (c'est-a-dire le sous-but p(args) est deterministe),
%   ALORS l'etat precedant S(i-1) est recupere (donc, l'unificateur u est
%   oublie) ET on passe au pas de BACKTRACKING;
%   SI i>1 ET il existe dans la definition de 'p' des clauses, qui n'ont
%      jamais ete utilisees aux pas precedants (c'est-a-dire le sous-but
%      p(args) est un point de choix),
%   ALORS l'etat precedant S(i-1) est recupere (donc, l'unificateur u est
%   oublie) ET on passe au pas de RESOLUTION.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% III. Example : Relations de parente %%%%%%%%%

fils(X,Y) :-
  pere(Y,X),
  sexe(X,m).
fils(X,Y) :-
  mere(Y,X),
  sexe(X,m).

fille(X,Y) :-
  pere(Y,X),
  sexe(X,f).
fille(X,Y) :-
  mere(Y,X),
  sexe(X,f).

parent_de(X,Y) :-
  pere(X,Y);
  mere(X,Y).

ancetre_de(X,Y) :-
  parent_de(X,Y).
ancetre_de(X,Y) :-
  parent_de(X,Z),
  ancetre_de(Z,Y).

frere_de(X,Y) :-
  parent_de(Z,X),
  parent_de(V,Y),
  (couple(Z,V);
   couple(V,Z)),
  sexe(X,m).

%% Programmer le predicat    soeur_de(X,Y)

%%%%%%%%%%%%%%  Base de donnee : une famille %%%%%%%%%%%%%%%%%%%%%
sexe(marie, f).
sexe(eve, f).
sexe(bea, f).
sexe(chantal, f).
sexe(elodie, f).
sexe(maggy, f).
sexe(aline, f).

sexe(pierre, m).
sexe(adam, m).
sexe(jean, m).
sexe(thomas, m).
sexe(pierre, m).
sexe(claude, m).
sexe(yannick, m).
sexe(basile, m).
sexe(edouard, m).
sexe(fabian, m).

pere(adam,chantal).
pere(adam,jean).

mere(eve,chantal).
mere(eve,jean).

pere(pierre,elodie).
pere(pierre,thomas).
pere(pierre,fabien).

mere(chantal,elodie).
mere(chantal,thomas).
mere(chantal,fabien).

pere(jean,marie).
pere(jean,christian).

mere(bea,marie).
mere(bea,christian).

pere(christian,maggy).
mere(elodie,maggy).

mere(maggy,yannick).
mere(maggy,basile).
mere(maggy,aline).

pere(claude,yannick).
pere(claude,basile).
pere(edouard,aline).

couple(eve,adam).
couple(pierre,chantal).
couple(jean,bea).
couple(elodie,christian).
couple(claude,maggy).
couple(maggy,edouard).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% IV. Programmes sans recursion, avec le backtracking.
%
e2(X) :- b(X,X),
        write(X),
        nl,
        fail.
b(1,2).
b(2,2).
b(6,1).
b(_,8).

% Expliquer la solution :
c(1).
c(2).
c(3).
c(4).
c(5).
c(6).
c(7).

e3 :-
      c(X),
      c(Y),
      X<Y,
      write(X),
      write(Y),
      nl,
      fail;
      true.

%% Programmer un algo e4 qui ecrit le 2eme, 4eme et 7eme elements de la liste
%% dans le fait   blist(List).

blist([1,2,3,4,5,6,7,8]).

e4(2,A,B):- blist([_,A|B]).
e4(4,C,D):- e4(2,_,B), B=[_,C|D].
e4(7,E):- e4(4,_,D), D=[_,_,E|_].

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% V. Programmes recursifs.
%% Modes des variables: +V - liee au moment d'appel.
%%                      -V - libre au moment d'appel.
%%                      ?V veut dire +V ou -V

%% Predicat de l'inclusion (equivalent au pred. bibl. member/2).
%% memb(?Element,?List): Element appartient a List.

memb(E,[E|_]).       % point de choix !
memb(E,[_|L]) :-
     memb(E,L).

e5(X) :- memb(2,[1,2|X]).
e6(X) :-
  memb(X,[1,2,3]), % POINT DE CHOIX
  write(X),
  fail;            % un echec et le bactracking au point
                   % de choix le plus proche
  true.
