--*****************************************************************************
--*  Copyright (C) 2016 by Trevor Smouter
--*
--*  All rights reserved.
--*
--*  Redistribution and use in source and binary forms, with or without 
--*  modification, are permitted provided that the following conditions 
--*  are met:
--*  
--*  1. Redistributions of source code must retain the above copyright 
--*     notice, this list of conditions and the following disclaimer.
--*  2. Redistributions in binary form must reproduce the above copyright
--*     notice, this list of conditions and the following disclaimer in the 
--*     documentation and/or other materials provided with the distribution.
--*  3. Neither the name of the author nor the names of its contributors may 
--*     be used to endorse or promote products derived from this software 
--*     without specific prior written permission.
--*
--*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
--*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
--*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
--*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL 
--*  THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
--*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
--*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
--*  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
--*  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
--*  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF 
--*  THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
--*  SUCH DAMAGE.
--*
--*****************************************************************************
--*  History:
--*
--*  04.02.2016    First Version
--*****************************************************************************


-- ****************************************************************************
-- *  Library                                                                 *
-- ****************************************************************************

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;


-- ****************************************************************************
-- *  Entity                                                                  *
-- ****************************************************************************

entity dual7segment is
   port (
          --
          -- Avalon Slave bus
          --
          clk        : in  std_logic := '0';
          reset      : in  std_logic := '0';
          chipselect : in  std_logic := '0';
          address    : in  std_logic_vector(2 downto 0) := (others => '0');
          write      : in  std_logic := '0';
          writedata  : in  std_logic_vector(31 downto 0) := (others => '0');
          read       : in  std_logic := '0';
          readdata   : out std_logic_vector(31 downto 0);
      
          -- 
          -- External bus
          --
			 DOUT	: out	std_logic_vector(7 downto 0);
			 DIG1	: out	std_logic;
			 DIG2	: out	std_logic
        );
end entity dual7segment;

-- *****************************************************************************
-- *  Architecture                                                             *
-- *****************************************************************************

architecture syn of dual7segment is
	
	signal toggle 					: std_logic;
	signal DIN0_TEMP 				: std_logic_vector(15 downto 0);
	signal DIN0 					: std_logic_vector(15 downto 0);	
	signal DIN1 					: std_logic_vector(15 downto 0);
	signal DIN 						: std_logic_vector(15 downto 0);
	signal DOUT_TEMP				: std_logic_vector(7 downto 0);
   
begin

   ----------------------------------------------
   -- Register File
   ----------------------------------------------

   process (clk)
   begin
      if rising_edge(clk) then
         if (write = '1') then
			   if (address = "000") then --board diagnostics
					DIN(0) <= NOT std_logic_vector(resize(unsigned(writedata),16))(6);--load the segment data from the bus
					DIN(1) <= NOT std_logic_vector(resize(unsigned(writedata),16))(5);
					DIN(2) <= NOT std_logic_vector(resize(unsigned(writedata),16))(4); 
					DIN(3) <= NOT std_logic_vector(resize(unsigned(writedata),16))(3);
					DIN(4) <= NOT std_logic_vector(resize(unsigned(writedata),16))(2); 
					DIN(5) <= NOT std_logic_vector(resize(unsigned(writedata),16))(1);
					DIN(6) <= NOT std_logic_vector(resize(unsigned(writedata),16))(0);
					DIN(7) <= NOT std_logic_vector(resize(unsigned(writedata),16))(7);
					DIN(8) <= NOT std_logic_vector(resize(unsigned(writedata),16))(14);
					DIN(9) <= NOT std_logic_vector(resize(unsigned(writedata),16))(13);
					DIN(10) <= NOT std_logic_vector(resize(unsigned(writedata),16))(12); 
					DIN(11) <= NOT std_logic_vector(resize(unsigned(writedata),16))(11);
					DIN(12) <= NOT std_logic_vector(resize(unsigned(writedata),16))(10); 
					DIN(13) <= NOT std_logic_vector(resize(unsigned(writedata),16))(9);
					DIN(14) <= NOT std_logic_vector(resize(unsigned(writedata),16))(8);
					DIN(15) <= NOT std_logic_vector(resize(unsigned(writedata),16))(15);				
				else
					DIN <= std_logic_vector(resize(unsigned(writedata),16));       --load the segment data from the bus
				end if;
         end if;
      end if; 
   end process;

  	clk_proc:process(CLK)
  	variable COUNT			:unsigned(10 downto 0) := "00000000000";
  	begin 
  		if (CLK'EVENT AND CLK = '1') then
  			COUNT := COUNT + 1;
  		end if;
		DIG1 <= COUNT(10);
		DIG2 <= NOT COUNT(10);
		toggle <= COUNT(10);
  	end process clk_proc;
	
	DOUT_TEMP(0) <= DIN(0) WHEN (toggle = '1')	ELSE DIN(8);
	DOUT_TEMP(1) <= DIN(1) WHEN (toggle = '1')	ELSE DIN(9);
	DOUT_TEMP(2) <= DIN(2) WHEN (toggle = '1')	ELSE DIN(10);
	DOUT_TEMP(3) <= DIN(3) WHEN (toggle = '1')	ELSE DIN(11);
	DOUT_TEMP(4) <= DIN(4) WHEN (toggle = '1')	ELSE DIN(12);
	DOUT_TEMP(5) <= DIN(5) WHEN (toggle = '1')	ELSE DIN(13);
	DOUT_TEMP(6) <= DIN(6) WHEN (toggle = '1')	ELSE DIN(14);
	DOUT_TEMP(7) <= DIN(7) WHEN (toggle = '1')	ELSE DIN(15);

	DOUT(0) <= '0' WHEN (DOUT_TEMP(0) = '0')	ELSE '1';
	DOUT(1) <= '0' WHEN (DOUT_TEMP(1) = '0')	ELSE 'Z'; --open drain
	DOUT(2) <= '0' WHEN (DOUT_TEMP(2) = '0')	ELSE '1'; 
	DOUT(3) <= '0' WHEN (DOUT_TEMP(3) = '0')	ELSE '1'; 
	DOUT(4) <= '0' WHEN (DOUT_TEMP(4) = '0')	ELSE '1'; 
	DOUT(5) <= '0' WHEN (DOUT_TEMP(5) = '0')	ELSE 'Z'; --open drain
	DOUT(6) <= '0' WHEN (DOUT_TEMP(6) = '0')	ELSE 'Z'; --open drain
	DOUT(7) <= '0' WHEN (DOUT_TEMP(7) = '0')	ELSE '1'; 

	

	

end architecture syn;
