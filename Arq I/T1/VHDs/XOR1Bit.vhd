
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity XOR1Bit is
	port
	(
		A, B: in std_logic;
		S: out std_logic
	);
end XOR1Bit;

architecture XOR1Bit of XOR1Bit is

begin
	S <= A xor B;
end XOR1Bit;

