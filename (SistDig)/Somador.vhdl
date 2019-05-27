library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_signed.all;

entity SomadorCompleto is
  generic (k: integer:= 3 );
  port (
			SW: in std_logic_vector(6 downto 0);
			LEDG: out std_logic_vector(3 downto 0);
			HEX0: out std_logic_vector(6 downto 0);
			HEX1: out std_logic_vector(6 downto 0);
			HEX2: out std_logic_vector(6 downto 0);
			HEX3: out std_logic_vector(6 downto 0)
		);
end SomadorCompleto;

architecture Comportamental of SomadorCompleto is
	signal soma: std_logic_vector(k downto 0);
	signal X, Y: std_logic_vector(k-1 downto 0);
	signal vem_um:  std_logic;
	
	begin
		x <= SW (2 downto 0);
		y <= SW (5 downto 3);
		vem_um <= SW (6);
		soma <= ('0' & X) + ('0' & Y) + vem_um;
		LEDG <= soma;
		
		HEX0(6 downto 0) <= "1111111";
		
		with soma select
			HEX1(6 downto 0) <=
				"1000000" when "0000",
				"1111001" when "0001",
				"0100100" when "0010",
				"0110000" when "0011",
				"0011001" when "0100",
				"0010010" when "0101",
				"0000010" when "0110",
				"1111000" when "0111",
				"0000000" when "1000",
				"0010000" when "1001",
				"0001000" when "1010",
				"0000011" when "1011",
				"1000110" when "1100",
				"0100001" when "1101",
				"0000110" when "1110",
				"0001110" when others;

		with x select
			HEX3(6 downto 0) <=
				"1000000" when "000",
				"1111001" when "001",
				"0100100" when "010",
				"0110000" when "011",
				"0011001" when "100",
				"0010010" when "101",
				"0000010" when "110",
				"1111000" when "111",
				"0001110" when others;

		with y select
			HEX2(6 downto 0) <=
				"1000000" when "000",
				"1111001" when "001",
				"0100100" when "010",
				"0110000" when "011",
				"0011001" when "100",
				"0010010" when "101",
				"0000010" when "110",
				"1111000" when "111",
				"0001110" when others;
				
end Comportamental;