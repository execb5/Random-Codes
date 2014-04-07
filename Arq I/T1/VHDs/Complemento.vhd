
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Complemento is
	port
	(
		A : in std_logic_vector(4 downto 0);
		S : out std_logic_vector(4 downto 0)
	);
end Complemento;

architecture Complemento of Complemento is
	signal g : std_logic_vector(4 downto 0);
	signal c : std_logic_vector(4 downto 0);
begin
	n_o_t0: entity work.N_O_T port map(A=>A(0), S=>g(0));
	n_o_t1: entity work.N_O_T port map(A=>A(1), S=>g(1));
	n_o_t2: entity work.N_O_T port map(A=>A(2), S=>g(2));
	n_o_t3: entity work.N_O_T port map(A=>A(3), S=>g(3));
	n_o_t4: entity work.N_O_T port map(A=>A(4), S=>g(4));
	
	A0: entity work.Adder port map(cin=>'0', A=>g(0), B=>'1', cout=>c(0), S=>S(0));
	A1: entity work.Adder port map(cin=>c(0), A=>g(1), B=>'0', cout=>c(1), S=>S(1));
	A2: entity work.Adder port map(cin=>c(1), A=>g(2), B=>'0', cout=>c(2), S=>S(2));
	A3: entity work.Adder port map(cin=>c(2), A=>g(3), B=>'0', cout=>c(3), S=>S(3));
	A4: entity work.Adder port map(cin=>c(3), A=>g(4), B=>'0', cout=>c(4), S=>S(4));
end Complemento;

