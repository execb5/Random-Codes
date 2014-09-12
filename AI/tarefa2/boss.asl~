// Agent Boss in project tarefa2.mas2j

/* Initial beliefs and rules */

/* Initial goals */

!start.

/* Plans */

+!start : true
	<- .my_name(N);
	   .broadcast(tell,boss(N)).

+worker[source(W)] : true
	<- .puts("#{W} is a worker");
	   .random(T);
	   Ta=math.ceil(T*10);
	   .send(W,tell,do(Ta)).

