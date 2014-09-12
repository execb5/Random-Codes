// Agent ag2 in project Assignment1.mas2j

/* Initial beliefs and rules */

position(init).

/* Initial goals */

/* Plans */

+position(init) : true
   <- !announce(position);
      move(school);
	  shout("OHYEAH, NO MORE SCHOOL!");
      move(pub);
      move(club).

+hear(H) : true
     <- .puts("I just heard: #{H}").

+!announce(position) : position(P)
    <- shout("I am at position ",P).

