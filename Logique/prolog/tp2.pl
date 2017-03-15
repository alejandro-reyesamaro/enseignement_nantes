%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%% TP2 %%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% 1. Elements pairs d'une liste d'une longueur paire
%% membp(+Liste,-Pairs) :
membp([],[]).
membp([_],[]).
membp([_,E|L],[E|T]) :-
  membp(L,T).

%% 2. PROGRAMMER : Elements impairs d'une liste d'une longueur paire
% membi(+Liste,-Impaires)

membi([],[]).
membi([X],[X]).
membi([E,_|L],[E|T]) :-
  membi(L,T).

%% 3. Choix nondeterministe d'un element d'une liste (predicat bibl. select/3)
%% sele(+List,?Element,?Rest): enumere les elements de la
%% Liste a travers le backtracking. Rest = List \ {Element}.

sele([E|L],E,L).             % point de choix
sele([E1|L],E,[E1|L1]) :-
     sele(L,E,L1).

e1(Liste) :-
  sele(Liste,E,R),
  write(E),
  tab(1),
  write(R),
  nl,
  fail;
  true.

%% 4. Enumeration des elements d'une liste avec ses positions
%% lstel(+List,?Position,?Element):
lstel(L,I,E) :-
     l0(L,1,I,E).
l0([E|_],I,I,E).
l0([_|R],I,I2,E1) :-
     I1 is I+1,
     l0(R,I1,I2,E1).

%% 5. PROGRAMMEZ l'enumeration des positions d'une liste ou on
%% trouve Y = X pour un X donne.
%% occ(+Liste,+X,-I).

occ(L,OCC,E) :-
   occur(L,0,OCC,E),!.

occur([],R,R,E).
occur([E|T],O,R,E) :- 
	O1 is O+1,
	occur(T,O1,R,E).
occur([_|T],O,R,E) :-
	occur(T,O,R,E).

%% A. Enumeration des elements impairs d'une liste avec ses positions
lstei(L,I,E) :-
     le1(L,1,I,E).
le1([E,_|_],I,I,E).
le1([_,_|R],I,I2,E1) :-
     I1 is I+2,
     le1(R,I1,I2,E1).

%% 6. PROPRIETE : Les elements impaires d'une liste
%% paires coincident avec ces elements impaires
%% pegi(+List)
pegi(L) :-
  foral(
         lstei(L,I,X),
         ( I1 is I+1,
           lstel(L,I1,X))
         ).

%% Tests :
e2(N,P,D) :-
  gnp(N,L0),
  write([P,D|L0]),
  nl,
  write('Appuyez sur une touche'),
  get_single_char(_),
  (pegi([P,D|L0]),
   write('OUI');
   write('NON')
  ).

%% 7. app(?List1,?List2,?Concatenation): Concatenation = List1*List2.

app([],L,L).            % point de choix
app([E|L],L1,[E|L2]) :-
  app(L,L1,L2).

e3(L) :- app([1,2,3],[4,5],L).
e4(L1,L2) :- app(L1,L2,[1,2,3]).  % effectuez un echec en appuyant ';'.
e5(L) :- app([1,2],[3,4|X],L).
e6(L) :- app([1,2|X],[3,4],L).
e7 :-
  app([1,2|X],[3,4],L),
  write(L),
  nl,
  fail.

%% 8. Enumeration des prefixes d'une liste.
%% prefs(-Pref,+Liste)

prefs([],L).            % point de choix
prefs([E|L],[E|L1]) :-
  prefs(L,L1).

e8(P) :-
  prefs(P,[a,b,c,d]),
  write(P),
  nl,
  fail;
  true.

%% 9. Les definir a travers app/3 
%% prf(-Prefs,+Liste) 

prf(P,L) :-
	app(P,_,L).
%prf([],L).
%prf([E|L],P) :-
	%app([E],K,P),prf(L,K).

e9(P) :-
  prf(P,[a,b,c,d]),
  write(P),
  nl,
  fail;
  true.

%% 10. PROGRAMMEZ : Enumeration des suffixes d'une liste.
%% suff(-Pref,+Liste)

suff(S,L) :- 
	app(_,S,L).

e10(S) :-
  suff(S,[a,b,c,d]),
  write(S),
  nl,
  fail;
  true.

%% 11. La factorielle naive :
fct(0,1).
fct(N,F) :-
  N1 is N-1,
  fct(N1,F1),
  F is N*F1.

e11(F) :-
  write(' > Tapez un entier, puis le point  '),
  read(I),
  integer(I),
  fct(I,F).

%% 12a. Sous-listes:
subl(L1,L2) :-
  prefs(Pref,L2),
  suff(L1,Pref).

e12(S) :-
  subl(S,[a,b,c,d,e]),
  write(S),
  nl,
  fail;
  true.

%% 12b. Sous-listes:
subls(L1,L2) :-
  suff(L1,Suff),
  prefs(Suff,L2).

e13(S) :-
  subls(S,[a,b,c,d,e]),
  write(S),
  nl,
  fail;
  true.

%% 13. PROGRAMMEZ l'inversion d'une liste
%% rvs(+Liste,-IListe)

rvs([],[]).
rvs(L,[A|B]) :-
	rvs(K,B),
	app(K,[A],L).
	

e14(R) :-
  L=[1,2,3,4,5,6],
  write('Liste initiale: '),
  write(L),
  nl,
  write('Liste inversee: '),
  rvs(L,R),
  write(R).

%%%%%%%%%%%%%%%%%% BIBL %%%%%%%%%%%%%%%%%%%%
foral(C,B) :-
  not((C,not(B))).

%% Generateur de tests pour pegi/1 :
gnp(N,L) :-
  genp(N,[],L).
genp(0,L,L).
genp(N,L1,L) :-
  N1 is N-1,
  genp(N1,[N,N|L1],L).

for(N,I) :-
 fr(N,1,I).
fr(N,N,N) :- !.
fr(N,I,I) :-
  I < N.
fr(N,I,I1) :-
  I2 is I+1,
  fr(N,I2,I1).
