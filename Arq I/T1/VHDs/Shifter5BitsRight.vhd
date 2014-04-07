
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Shifter5BitsRight is
	port
	(
		A : in std_logic_vector(4 downto 0);
		S : out std_logic_vector(4 downto 0)
	);
end Shifter5BitsRight;

architecture Shifter5BitsRight of Shifter5BitsRight is

begin
	S0: entity work.Shifter port map(A=>A(1), S=>S(0));
	S1: entity work.Shifter port map(A=>A(2), S=>S(1));
	S2: entity work.Shifter port map(A=>A(3), S=>S(2));
	S3: entity work.Shifter port map(A=>A(4), S=>S(3));
	S4: entity work.Shifter port map(A=>'0', S=>S(4));
end Shifter5BitsRight;

