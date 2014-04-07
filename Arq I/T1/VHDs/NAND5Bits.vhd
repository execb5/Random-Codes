library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity NAND5Bits is
	port
	(
		A, B: in std_logic_vector(4 downto 0);
		S: out std_logic_vector(4 downto 0)
	);
end NAND5Bits;

architecture NAND5Bits of NAND5Bits is

begin
	NAND_0: entity work.NAND1Bit port map(A=>A(0), B=>B(0), S=>S(0));
	NAND_1: entity work.NAND1Bit port map(A=>A(1), B=>B(1), S=>S(1));
	NAND_2: entity work.NAND1Bit port map(A=>A(2), B=>B(2), S=>S(2));
	NAND_3: entity work.NAND1Bit port map(A=>A(3), B=>B(3), S=>S(3));
	NAND_4: entity work.NAND1Bit port map(A=>A(4), B=>B(4), S=>S(4));
end NAND5Bits;

