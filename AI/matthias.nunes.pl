%prolog lab part 1
%Name: Matthias Oliveira de Nunes

parent(antonio,joaozinho).
parent(maria,joaozinho).
parent(antonio,luis).
parent(maria,luis).
parent(antonio, cristina).
parent(maria, cristina).
parent(carlos, antonio).
parent(fernanda, antonio).
parent(pedro, maria).
parent(mariana, maria).
parent(jose, mariana).
parent(sandra, mariana).
parent(carlos, alberto).
parent(fernanda, alberto).
parent(carlos, marcia).
parent(fernanda, marcia).


gender(joaozinho,male).
gender(antonio,male).
gender(luis,male).
gender(carlos,male).
gender(pedro,male).
gender(jose,male).
gender(alberto,male).

gender(maria,fem).
gender(cristina,fem).
gender(fernanda,fem).
gender(mariana,fem).
gender(sandra,fem).
gender(marcia,fem).


father(F, C) :- parent(F, C), gender(F, male).
mother(M, C) :- parent(M, C), gender(M, fem).
brother(B, P) :- parent(X, B), parent(X, P), gender(B, male).
sister(S, P) :- parent(X, S), parent(X, P), gender(S, fem).
uncle(U, P) :- parent(X, P), brother(U, X).
aunt(A, P) :- parent(X, P), sister(A, X).
grandfather(Gf, P) :- father(Gf, X), parent(X, P).
grandmother(Gm, P) :- mother(Gm, X), parent(X, P).
greatgrandfather(Ggf, P) :- father(Ggf, X), parent(X, Y), parent(Y, P).
greatgrandmother(Ggm, P) :- mother(Ggm, X), parent(X, Y), parent(Y, P).
ancestor(A, P) :- parent(A, P).
ancestor(A, P) :- parent(A, X), ancestor(X, P).
