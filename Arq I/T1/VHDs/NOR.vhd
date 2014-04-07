library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity NOR1Bit is
	port
	(
		A, B: in std_logic;
		S: out std_logic
	);
end NOR1Bit;

architecture NOR1Bit of NOR1Bit is

begin
	S <= A nor B;
end NOR1Bit;

