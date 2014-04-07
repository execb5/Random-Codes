library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity NAND1Bit is
	port
	(
		A, B: in std_logic;
		S: out std_logic
	);
end NAND1Bit;

architecture NAND1Bit of NAND1Bit is

begin
	S <= A nand B;
end NAND1Bit;

