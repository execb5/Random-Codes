// Agent worker in project tarefa2.mas2j

/* Initial beliefs and rules */

/* Initial goals */

!start.

/* Plans */

+!start : true
	<- .print("Ready to work.").

+boss(N) : true
	<- .my_name(T);
	   worker(T);
	   .send(N,tell,worker(T)).

+do(T) : not done(T)
	<- .puts("off I go then");
	   do(T);
	   done(T).

+done(T) : true
	<- .puts("Task #{T} is done.").


