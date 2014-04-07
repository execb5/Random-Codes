
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Shifter is
	port
	(
		A : in std_logic;
		S : out std_logic
	);
end Shifter;

architecture Shifter of Shifter is

begin
	S <= A;
end Shifter;

