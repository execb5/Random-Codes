/*
23) Dada uma base de dados com nome, idade, matrícula e notas de 3 disciplinas para cada um de N alunos, encontrar
a) a idade do aluno com um determinado nome,
b) encontrar as notas de um aluno com determinada matrícula e
c) encontrar a nota da segunda disciplina de um aluno que tirou uma dada nota na primeira.
*/

aluno(
		nome('Fulano'),
		idade(17),
		matricula('12345678'),
		notas(9.5, 8.7, 10)
	).
aluno(
		nome('Beltrano'),
		idade(18),
		matricula('87654321'),
		notas(5.2, 6.6, 4.1)
	).

% Formule consultas para
% - idade do aluno, dado o nome do aluno
% ?- aluno(nome('Fulano'),idade(Idade),_,_).
% - as notas, dada a matricula do aluno
% ?- aluno(_,_,matricula('12345678'),notas(A,B,C)).
% - a nota da segunda disciplina, dada a nota da primeira
% ?- aluno(_,_,_,notas(9.5,B,_)).

/*
24) Dada uma base de dados com nome do produto, custo unitário e quantidade comprada de cada um de N produtos, calcular o total a ser pago.
*/

soma([], 0).
soma([X|R], T) :- soma(R, TR), T is TR + X.
compra('Produto1', 2.0, 5).
compra('Produto2', 3.0, 2).

calculaTotal(T) :-
	findall(P * Q, compra(_, P, Q), L), soma(L, T).

/*
25) Dada uma lista, substituir toda a ocorrência de um elemento por outro. Por exemplo: a lista[10,2,3,10,4] resulta da substituição de 1 por 10 na lista [1,2,3,1,4].
*/

substitui(_, [], _, []).

substitui(X, [X|L], A, [A|M]) :- !, substitui(X, L, A, M).
substitui(X, [Y|L], A, [Y|M]) :- substitui(X, L, A, M).

/*
26) Verificar se um número inteiro é primo.
*/

pri(X, N, D) :- M is N // 2, D > M
				| (
					R is N mod D,
					R \= 0,
					DD is D + 1,
					pri(X, N, DD)
				).

primo(N) :- pri(N, N, 2), !.

/*
27) Verificar se um número inteiro é perfeito. Inteiro perfeito é aquele cuja soma dos seus divisores (exceto ele próprio) é igual a si mesmo.
*/

somaDivisor(X, D, T) :- DD is X // 2, D > DD, T is 0, !.
somaDivisor(X, D, T) :- R is X mod D, R = 0, D1 is D + 1, somaDivisor(X, D1, T1), T is D + T1, !.
somaDivisor(X, D, T) :- D1 is D + 1, somaDivisor(X, D1, T).
perfeito(N) :- somaDivisor(N, 1, T), N = T.

/*
28) Dado um conjunto C1 e C2, verificar se o conjunto I é uma interseção deles. Por exemplo: C1 = [1,2,3,4,5], C2 = [3,5,7] e I = [3,5]
*/

intersec([X|Y], L, [X|Z]) :-
	member(X, L),
	intersec(Y, L, Z).
intersec([_|X], L, Y) :-
	intersec(X, L, Y).
intersec(_, _, []).

/*
29) Selecionar os elementos de uma lista L, cujas posições estão indicadas em uma lista P. Por exemplo: dadas as listas P = [2,4] e L = [1,2,3,4,5,6], devem ser selecionados os elementos [3,5] das posições 2 e 4.
*/

seleciona([], _, []).
seleciona([M|N], L, [X|Y]) :-
	nth1(M, L, X),
	seleciona(N, L, Y).
% seleciona([2, 4], [a, b, c, d, e], L).
%L = [b, d]

%nth1(M, L, X) -> M é a posição enésima do elemento X na lista L.

/*
30) Selecionar os elementos de uma lista de acordo com determinada propriedade. Por exemplo: os números pares selecionados de [1,2,3,4,5] são [2,4].
*/

prop(X, [X|_]) :- p(X).
prop(X, [_|R]) :- prop(X, R).
% exemplo de propriedade para prop considerar
p(X) :- X > 10.
% Exemplo de aplicação
% prop(N,[1,20,3,40]).
% N = 20 ;
% N = 40 ;
% false.

/*
31) Separar uma lista em duas, dado um elemento separador. Por exemplo: as listas [1,2] e [4,5,6] resultam da separação da lista [1,2,3,4,5,6], tendo o elemento separador igual a 3.
*/

separa(L, X, Antes, Depois) :-
	append(Antes, [X|Depois], L), !.
%separa([1,2,3,4,5,6], 3, L1, L2).
%L1 = [1,2]
%L2 = [4,5,6]

/*
32) Executar a rotação de uma lista. Por exemplo: dada a lista [1,2,3,4,5], uma rotação dela resultaria em [2,3,4,5,1].
*/

shift([], []).
shift([X|[]], [X]).
shift([X|R], L) :-
	append(R, [X], L).
% ?- shift([1,2,3,4,5], L1).
% L1 = [2,3,4,5,1]

/*
33) Verificar se um conjunto é subconjunto de outro. Por exemplo: [2,4] é subconjunto de [1,2,3,4,5,6].
*/

subconjunto([],[]).
subconjunto([X|L1],[X|L2]) :-
	subconjunto(L1,L2).
subconjunto(L1,[_|L2]) :-
	subconjunto(L1,L2).
% ?- subconjunto([1,3,4],[1,2,3,4,5,6]).
% true.