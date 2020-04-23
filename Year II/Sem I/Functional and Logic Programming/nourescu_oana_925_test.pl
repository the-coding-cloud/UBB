% Model matematic:
% max(a,b):
%  - a, if a>b
%  - b, if b>a
%
% flow model(i,i,o)
max(A,B,R):- A > B, R is A.
max(A,B,R):- A < B, R is B.
max(A,A,A).

% Model matematic:
% max_list(l1,l2,...,ln):
%  - l1, if n=1
%  - [], if the list is empty
%  - max(l1, max_list(l2,...,ln))
%
% flow model(i,o)
max_list([],[]).
max_list([X], X).
max_list([H|T], R):- max_list(T,R1), max(H,R1,R).

% Model matematic:
% insert(l1,...,ln, e, p, i):
%  - [], if the list is empty
%  - e U insert(l1,...,ln,e,p*3,i+1), if p=i
%  - l1 U insert(l2,...,ln,e,p*3,i+1), if p!=i
% flow model(i,i,i,i,o)
insert([],_,_,_,[]).
insert(L,E,Pos,Index,R):- Pos=:=Index, Pos2 is Pos*3, Index2 is Index, insert(L, E, Pos2, Index2, R1), R=[E|R1].
insert([H|T],E,Pos,Index,R):- Index2 is Index+1, insert(T, E, Pos, Index2, R1), R=[H|R1].


% flow model(i,o)
main2(L,R):- max_list(L,Max), insert(L,Max,1,1,R1), R = R1.

%main2([4,12,3,4,5,6,7,8,2,2],R).
