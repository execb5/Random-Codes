/*
12) Dados dois números, verificar se o maior é múltiplo do menor.
*/

multiplo(A,B) :-
	(A > B, Maior is A | Maior is B),
	Menor is A + B - Maior, R is Maior mod Menor, R = 0.

/*
13) Verificar se um retângulo (com conhecidas base e altura) tem área menor que uma determinada área.
*/

areaRetangulo(Base,Altura,Area) :- Area is Base * Altura.

areaRetMenor(Base,Altura,AreaMaxima) :-
	areaRetangulo(Base,Altura,Area),
	Area < AreaMaxima.

/*
14) Remover um elemento de uma lista.
*/

remover(X, [], []).
remover(X, [X|R], R).
remover(X, [Y|C], [Y|D]) :- remover(X, C, D).

/*
15) Inserir um elemento em uma lista.
*/

inserir(X, L, L1) :- remover(X, L1, L).

inserir(X, [X], [X]).
inserir(X, L, L1) :- L1 is [X|L].

/*
16) Dada uma lista L, verificar se uma lista P é seu prefixo. Por exemplo: P = [1,2,3] é prefixo de L = [1,2,3,4,5].
*/

prefixo([],_).
prefixo([X|P], [X|R]) : - prefixo(P, R).

/*
17) Dada uma lista L, verificar se uma lista S é seu sufixo. Por exemplo: S = [4,5] é sufixo de L = [1,2,3,4,5].
*/

sufixo([],_).
sufixo(R, [_|R]).
sufixo([S], [_|R]) :- sufixo(S, R).

/*
18) Calcular a soma dos inteiros de 1 a N. Por exemplo, a soma dos inteiros de 1 a 4 é igual a 1 + 2 + 3 + 4 = 10.
*/

somaAteN(0,0) :- !.
somaAteN(N, S) :- M is N - 1, somaAteN(M, R) :- S is N + R.

/*
19) Dado um número de 1 a 7, traduzir este número no dia da semana correspondente, sendo 1 correspondente a domingo e 7 correspondente a sábado.
*/

nome(1, domingo).
nome(2, segunda).
nome(3, terca).
nome(4, quarta).
nome(5, quinta).
nome(6, sexta).
nome(7, sabado).

/*
20) Calcular a média de N inteiros, descartando os negativos.
*/

soma([], 0).
soma([X|R], T) :- soma(R, TR), T is TR + X.
media([], 0).
media(L, M) :- soma(L, S), length(L,T), M is S / T.
descartaNeg([], []).
descartaNeg([X|R], L) :- X >= 0, descartaNeg(R, L1),
	append([X], L1, L), !.
descartaNeg([_|R], L) :- descartaNeg(R, L).
mediaListaDescartaNeg(L,M) :- descartaNeg(L, L1), media(L1, M).

/*
21) Encontrar o maior de N números.
*/

maiorDeLista([X|[]], X) :- !.
maiorDeLista([X|R], M) :- maiorDeLista(R, MR), X > Mr, M is X, !.
maiorDeLista([_|R], M) :- maiorDeLista(R, M).

/*
22) Dados N elementos, retirar o último.
*/

menosUlt([], []) :- !.
menosUlt([X|[]], []) :- !.
menosUlt([X|R], L) :- menosUlt(R, L1), append([X], L1, L).