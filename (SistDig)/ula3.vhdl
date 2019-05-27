
		library ieee;
		use ieee.std_logic_1164.all;

		entity ula is
			port(a, b, S0, S1, M, c0 : in std_logic;
			                 f, c1 : out std_logic
			    );
		end ula;

		architecture ula_bhv of ula is
			begin
				f <= (S1 and b) xor ((S0 xor a) xor (M and c0));
				c1 <= ((M and c0) and (S0 xor a)) or ((S1 and b) and ((S0 xor a) xor (M and c0)));
			end ula_bhv;

 		-- Sw(6) = S0		-- Sw(3) = B0 		-- Sw(0) = A0 		-- LEDG(0) = F1 
 		-- Sw(7) = S1		-- Sw(4) = B1 		-- Sw(1) = A1 		-- LEDG(1) = F2 
 		-- Sw(8) = M		-- Sw(5) = B2 		-- Sw(2) = A2 		-- LEDG(2) = F3 
    	-- Sw(9) = c0
    	
		library ieee;
		use ieee.std_logic_1164.all;
		
		entity ula3 is
			port( SW : in std_logic_vector (9 downto 0);
				  HEX0 : out std_logic_vector (6 downto 0);
				  HEX1 : out std_logic_vector (6 downto 0);
				  HEX2 : out std_logic_vector (6 downto 0);
				  HEX3 : out std_logic_vector (6 downto 0);
				  LEDG: out std_logic_vector(2 downto 0)
				);
		end ula3;
		
		architecture ula3_bhv of ula3 is
			component ula
				port(	a, b, S0, S1, M, c0 : in std_logic;
						f, c1 : out std_logic);
			end component;
			
			signal C: std_logic_vector(3 downto 0);
			signal R: std_logic_vector(3 downto 0);
			signal a: std_logic_vector(2 downto 0);
			signal b: std_logic_vector(2 downto 0);

			begin
				U1: ula port map(a(0), b(0), SW(6), SW(7), SW(8), C(0), R(0), C(1));
				U2: ula port map(a(1), b(1), SW(6), SW(7), SW(8), C(1), R(1), C(2));
				U3: ula port map(a(2), b(2), SW(6), SW(7), SW(8), C(2), R(2), C(3));
				
				a(2 downto 0) <= SW(2 downto 0);
				b(2 downto 0) <= SW(5 downto 3);
				C(0) <= SW(9);
				R(3) <= C(3);

				LEDG (2 downto 0) <= R(2 downto 0);
				
				HEX1(6 downto 0) <= "0111110";

				with a select
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
	
				with b select
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

				with R select
				HEX0(6 downto 0) <=
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
			end ula3_bhv;
