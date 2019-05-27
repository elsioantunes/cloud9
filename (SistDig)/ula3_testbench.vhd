-- Listing 1.1b - Testbench (adaptação)
library ieee;
use ieee.std_logic_1164.all;

entity ula3_testbench is
end ula3_testbench;

architecture tb_arch of ula3_testbench is
   signal test_SW : std_logic_vector (9 downto 0);
   signal test_HEX0 : std_logic_vector (6 downto 0);
   signal test_HEX1 : std_logic_vector (6 downto 0);
   signal test_HEX2 : std_logic_vector (6 downto 0);
   signal test_HEX3 : std_logic_vector (6 downto 0);
   signal test_LEDG : std_logic_vector(2 downto 0);
begin
   -- instancia o circuito sob test (uut - unit under test)
   uut: entity work.ula3(ula3_bhv)
      port map(
         SW=>test_SW, 
         HEX0=>test_HEX0, 
         HEX1=>test_HEX1, 
         HEX2=>test_HEX2, 
         HEX3=>test_HEX3, 
         LEDG=>test_LEDG
      );
   -- gerador dos vetores de teste
   process
   begin
      -- b - a
      -- ~a + b + 1
      -- resulstado esperado na imagem n1
      test_SW <= "1111011100";
      wait for 200 ns;
      
      -- a xor b
      -- xor entre 0 e 2 que resulta 2
      test_SW <= "0010010000";
      wait for 200 ns;
      
      -- xor entre numeros iguais que resulta zero
      -- fotos 2a e 2b
      test_SW <= "0010010010";
      wait for 200 ns;
      
      wait;
end process;
end tb_arch;
