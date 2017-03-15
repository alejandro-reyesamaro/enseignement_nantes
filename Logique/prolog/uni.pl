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