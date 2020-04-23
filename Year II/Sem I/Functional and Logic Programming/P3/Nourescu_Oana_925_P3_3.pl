% Are given n points in a plan (represented using its coordinates).
% Write a predicate to determine all subsets of collinear points
%
% Model matematic:
% sublists(l1,...,ln)=
%  - [], if n = 0
%  - l1 U sublists(l2,...,ln), if n>=1
%  - sublists(l2,...,ln), if n>=1
%
% flow model: (i,o)

sublists([], []).
sublists([H|T], [H|R]):-
	sublists(T, R).
sublists([_|T], R):-
	sublists(T, R).


% Model matematic:
% collinear(x1,y1,x2,y2,x3,y3)=
% - true, if x1=x2=x3
% - true, if y1=y2=y3
% - true, if (y3-y1)/(y2-y1) = (x3-x1)/(x2-x1)
% - false, otherwise
%
% flow model:(i,i,i,i,i,i)
collinear(X,_,X,_,X,_):-!.
collinear(_,Y,_,Y,_,Y):-!.
collinear(X1,Y1,X2,Y2,X3,Y3):-
    X1 =\= X2, Y1 =\= Y2,
    P1 is (Y3-Y1)/(Y2-Y1),
    P2 is (X3-X1)/(X2-X1),
    P1 =:= P2.

% flow model: (i, o)
check_collinear_sublist(L,[[X1,Y1],[X2,Y2],[X3,Y3]]):-
	sublists(L, [[X1,Y1],[X2,Y2],[X3,Y3]]),
        collinear(X1,Y1,X2,Y2,X3,Y3).

% collinear_points(i, o)
collinear_points(L,R):-
	findall(AUX, check_collinear_sublist(L, AUX), R).
