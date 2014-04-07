
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity MUX is
	port
	(
		Comp, ShiftR, ShiftL, N_OR, N_AND, Add, X_OR : in std_logic_vector(4 downto 0);
		OPER : in std_logic_vector(2 downto 0);
		Ca, oV : in std_logic;
		Result : inout std_logic_vector(4 downto 0);
		Z, C, V, N : out std_logic
	);
end MUX;

architecture MUX of MUX is

begin
	WITH OPER SELECT
	result <= Add when "000",
				 Add when "001",
				 ShiftL when "010",
				 ShiftR when "011",
				 Comp when "100",
				 N_OR when "101",
				 X_OR when "110",
				 N_AND when "111";
	Z <= '1' when Result="00000" else '0';
	C <= Ca;
	V <= oV;
	N <= '1' when Result(4)='1' else '0';
end MUX;

