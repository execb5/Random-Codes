
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity XOR5Bits is
	port
	(
		A, B: in std_logic_vector(4 downto 0);
		S: out std_logic_vector(4 downto 0)
	);
end XOR5Bits;

architecture XOR5Bits of XOR5Bits is

begin
	XOR_0: entity work.XOR1Bit port map(A=>A(0), B=>B(0), S=>S(0));
	XOR_1: entity work.XOR1Bit port map(A=>A(1), B=>B(1), S=>S(1));
	XOR_2: entity work.XOR1Bit port map(A=>A(2), B=>B(2), S=>S(2));
	XOR_3: entity work.XOR1Bit port map(A=>A(3), B=>B(3), S=>S(3));
	XOR_4: entity work.XOR1Bit port map(A=>A(4), B=>B(4), S=>S(4));
end XOR5Bits;

