
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity TB is
end TB;

architecture TB of TB is
	signal oper1, oper2, soma, x_o_r, n_a_n_d, shiftLe, ShiftRi, n_o_r, complemento, Resultado, Saida : std_logic_vector(4 downto 0);
	signal operacao : std_logic_vector(2 downto 0);
	signal sub, flagC, flagV, Zz, Cc, Vv, Nn : std_logic;
begin
	sub <= '1' when operacao="000" else '0';	
	Somador: entity work.Adder5Bits port map(A=>oper1, B=>oper2, cin=> sub, cout=>flagC, V=>flagV, S=>soma);	
	ShiftLeft: entity work.Shifter5BitsLeft port map(A=>oper1, S=>shiftLe);	
	ShiftRight: entity work.Shifter5BitsRight port map(A=>oper1, S=>shiftRi);	
	Comple: entity work.Complemento port map(A=>oper1, S=>complemento);	
	N_OR5Bits: entity work.NOR5Bits port map(A=>oper1, B=>oper2, S=>n_o_r);	
	X_OR5Bits: entity work.XOR5Bits port map(A=>oper1, B=>oper2, S=>x_o_r);	
	N_AND5Bits: entity work.NAND5Bits port map(A=>oper1, B=>oper2, S=>n_a_n_d);	
	Multiplexador: entity work.MUX port map(OPER=>operacao, Comp=>complemento, ShiftR=>ShiftRi, ShiftL=>ShiftLe,
															N_OR=>n_o_r, N_AND=>n_a_n_d, Add=>soma, X_OR=>x_o_r, Ca=>flagC, oV=>flagV,
															Z=>Zz, C=>Cc, V=>Vv, N=>Nn, Result=>Resultado);
	oper1<="00000", "11001" after 1ns, "00100"after 3ns;
	oper2<="00000", "10100" after 1ns;
	operacao<="000", "001" after 2ns, "010" after 3ns, "011" after 4ns,
					"100" after 5ns, "101" after 6ns, "110" after 7ns, "111" after 8ns;
	saida<=Resultado;
end TB;

