
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity N_O_T is
	port
	(
		A : in std_logic;
		S : out std_logic
	);
end N_O_T;

architecture N_O_T of N_O_T is
begin
	S <= not a;
end N_O_T;

