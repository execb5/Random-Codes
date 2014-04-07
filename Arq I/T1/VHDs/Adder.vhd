library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Adder is
	port
	(
		A, B, cin : in std_logic;
		S, cout : out std_logic
	);
end Adder;

architecture Somador of Adder is
begin
	S <= a xor b xor cin;
	cout <= (a and b) or (a and cin) or (b and cin);
end Somador;

