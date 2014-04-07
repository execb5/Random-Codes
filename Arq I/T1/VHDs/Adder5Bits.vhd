library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Adder5Bits is
	port
	(
		A, B : in std_logic_vector(4 downto 0);
		cin : in std_logic;
		cout, V : out std_logic;
		S : inout std_logic_vector(4 downto 0)
	);
end Adder5Bits;

architecture Somador of Adder5Bits is
	signal c: std_logic_vector(4 downto 0);
	signal g: std_logic_vector(4 downto 0);
begin
	g <= not B when cin='1' else B;
	A0: entity work.Adder port map(cin=>cin, A=>A(0), B=>g(0), cout=>c(0), s=>S(0));
	A1: entity work.Adder port map(cin=>c(0), A=>A(1), B=>g(1), cout=>c(1), s=>S(1));
	A2: entity work.Adder port map(cin=>c(1), A=>A(2), B=>g(2), cout=>c(2), s=>S(2));
	A3: entity work.Adder port map(cin=>c(2), A=>A(3), B=>g(3), cout=>c(3), s=>S(3));
	A4: entity work.Adder port map(cin=>c(3), A=>A(4), B=>g(4), cout=>c(4), s=>S(4));
	cout <= c(4);
	V <= (A(4) xor S(4)) and (B(4) xor S(4));
end Somador;