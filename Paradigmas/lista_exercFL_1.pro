/*
1 e 2) Dado um número X inteiro, calcular X3.
*/

cubo(X,C) :- C is X*X*X.

/*
3) Verificar se um número é positivo.
*/

eh_positivo(X) :- X > 0.

/*
4) Calcular a área de um retângulo com base e altura conhecidas (área = base * altura).
*/

areaRetangulo(Base,Altura,Area) :- Area is Base*Altura.

/*
5) Calcular a capacitância de capacitor com carga e tensão conhecidas (capacitância = carga / tensão).
*/

capacitancia(Carga,Tensao,Capacitancia) :- Capacitancia is Carga/Tensao.

/*
6) Calcular a distância entre dois pontos com coordenadas conhecidas.
*/

distanciaDoisPontos(X1,Y1,X2,Y2,D) :- 
	A is X1 - X2,
	B is Y1-Y2,
	AA is A*A,
	BB is B*B,
	AB is AA + BB,
	D is sqrt(AB).

/*
7) Transformar a medida de tempo dada em horas, minutos e segundos nos correspondentes segundos.
Por exemplo, 1h, 1m e 1s corresponde a 3661s.
*/

hms_s(H,M,S,Segundos) :- Segundos is H * 3600 + M * 60 + S.

/*
8) Transformar a medida de tempo dada em segundos nos correspondentes horas, minutos e segundos.
Por exemplo, 3661s corresponde a 1h, 1m e 1s.
*/

s_hms(Segundos,H,M,S) :- 
	H is Segundos // 3600,
	Maux is Segundos mod 3600,
	M is Maux // 60, 
	S is Maux mod 60.

/*
9) Calcular a soma de N números.
*/

soma([],0).
soma([X|R],T) :-
	soma(R,TR),
	T is TR + X.

/*
10) Calcular o produto de N números.
*/

produto1([],0).
produto1([X],X).
produto1([X|R],P) :-
	produto1(R,Pparcial),
	P is Pparcial * X.

/*
11) Calcular a média de N números.
*/

media([],0).
media(L,M) :-
	soma(L,S),
	length(L,T),
	M is S / T.