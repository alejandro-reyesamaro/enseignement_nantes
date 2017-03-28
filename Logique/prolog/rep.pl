noc0(File,N) :-
  see(File),                 % ouvre le fichier File pour la lecture
  repeat,                    % PCH
  get0(B),
  sa(B > -1,                % lecture d'un octet ; faux a la fin
                             % le fichier n'est pas termine
     (sas(B == 48,           % 0 lu
          lect(N),
          fail
          ),
          fail
      )
     ),
     !,
  seen,                      % fermeture du fichier
  !.

%% tell/1 : ouverture pour l'ecriture
%% told/0 : fermeture

boucle0 :-
  repeat,                    % PCH
  get0(B),
  sa(B > -1,                % lecture d'un octet ; faux a la fin
                             % le fichier n'est pas termine
     (sas(B == 48,           % 0 lu
          lect(N),
          fail
          ),
          fail
      )
     ),
     !.

lect(N) :-
  retract((compt(N))),
  N1 is N+1,
  assert((compt(N1))),
  !.
