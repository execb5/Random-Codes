library ieee ;
	use ieee.std_logic_1164.all ;
	use ieee.numeric_std.all ;

entity TestBench is
end entity ; -- TestBench

architecture TB of TestBench is
	signal TM025, TM050, TM100, TDEV, TSUCO, TAGUA, Treset,
			Tck, TD025, TD050, TD100, TL_SUCO, TL_AGUA, insu : std_logic;
	signal Tcentena, Tdezena, Tunidade : std_logic_vector(3 downto 0);
	constant ck_period : time := 50 ns;
begin
	--Instantiate the Unit Under Test (UUT)
	uut: entity work.SodaMachine port map (
		M025 => TM025,
		M050 => TM050,
		M100 => TM100,
		DEV => TDEV,
		SUCO => TSUCO,
		AGUA => TAGUA,
		reset => Treset,
		ck => Tck,
		D025 => TD025,
		D050 => TD050,
		D100 => TD100,
		L_SUCO => TL_SUCO,
		L_AGUA => TL_AGUA,
		centena => Tcentena,
		dezena => Tdezena,
		unidade => Tunidade,
		insuficienteOut => insu
		);

	--Clock process definitions
	Ck_process : process
	begin
		Tck <= '0';
        wait for ck_period/2;
        Tck <= '1';
        wait for ck_period/2;
	end process ; -- Ck_process

	TM025 <= '0';
	TM050 <= '0', '1' after 320 ns, '0' after 330 ns, '1' after 370 ns, '0' after 380 ns, '1' after 420 ns, '0' after 430 ns;
	TM100 <= '0', '1' after 120 ns, '0' after 130 ns, '1' after 170 ns, '0' after 180 ns;
	TDEV <= '0', '1' after 70 ns, '0' after 80 ns;
	TSUCO <= '0', '1' after 220 ns, '0' after 230 ns, '1' after 270 ns, '0' after 280 ns;
	TAGUA <= '0', '1' after 470 ns, '0' after 480 ns;
	Treset <= '0', '1' after 20 ns, '0' after 30 ns;

end architecture ; -- TB