library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity NOR5Bits is
	port
	(
		A, B: in std_logic_vector(4 downto 0);
		S: out std_logic_vector(4 downto 0)
	);
end NOR5Bits;

architecture NOR5Bits of NOR5Bits is

begin
	NOR_0: entity work.NOR1Bit port map(A=>A(0), B=>B(0), S=>S(0));
	NOR_1: entity work.NOR1Bit port map(A=>A(1), B=>B(1), S=>S(1));
	NOR_2: entity work.NOR1Bit port map(A=>A(2), B=>B(2), S=>S(2));
	NOR_3: entity work.NOR1Bit port map(A=>A(3), B=>B(3), S=>S(3));
	NOR_4: entity work.NOR1Bit port map(A=>A(4), B=>B(4), S=>S(4));
end NOR5Bits;

