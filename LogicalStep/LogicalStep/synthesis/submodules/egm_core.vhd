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
--*  02.22.2016    First Version
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

entity egm is
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
			 STIM	: out	std_logic;
			 RESP	: in	std_logic
        );
end entity egm;

-- *****************************************************************************
-- *  Architecture                                                             *
-- *****************************************************************************

architecture syn of egm is

	COMPONENT LogicalStep_latency_tracker
		PORT(response : IN STD_LOGIC;
			 pulse : IN STD_LOGIC;
			 clk : IN STD_LOGIC;
			 reset : IN STD_LOGIC;
			 enable : IN STD_LOGIC;
			 latency : OUT STD_LOGIC_VECTOR(15 DOWNTO 0);
			 missed : OUT STD_LOGIC_VECTOR(15 DOWNTO 0)
		);
	END COMPONENT;

		 
	COMPONENT LogicalStep_pulse_generator
		PORT(clk : IN STD_LOGIC;
			 start : IN STD_LOGIC;
			 reset : IN STD_LOGIC;
			 enable : IN STD_LOGIC;
			 duty_cycle : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
			 period : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
			 running : OUT STD_LOGIC;
			 pulse : OUT STD_LOGIC
		);
	END COMPONENT;

	signal pulse_signal 				: std_logic;
	signal stimulus 					: std_logic;
	signal response 					: std_logic;
--	signal oneStep						: std_logic := '0';
	signal ENABLE						: std_logic;
	signal START						: std_logic;	
	signal RESET_IN					: std_logic;
	signal RUNNING						: std_logic;
	signal PERIOD 						: std_logic_vector(15 downto 0);
	signal DUTY_CYCLE 				: std_logic_vector(15 downto 0);
	signal MISSED_PULSES				: std_logic_vector(15 downto 0);
	signal LATENCY						: std_logic_vector(15 downto 0);
   
begin

   ----------------------------------------------
   -- Register File
   ----------------------------------------------

   process (clk)
   begin
      if rising_edge(clk) then
         if (write = '1') then
				if (address = "000") then
					ENABLE <= writedata(0);       --load the segment data from the bus
				end if;
--				if (address = "001") then
--					RESET_IN <= writedata(0);       --load the segment data from the bus
--				end if;
				if (address = "010") then
					PERIOD <= std_logic_vector(resize(unsigned(writedata),16));       --load the segment data from the bus
				end if;
				if (address = "011") then
					DUTY_CYCLE <= std_logic_vector(resize(unsigned(writedata),16));       --load the segment data from the bus
				end if;				
         end if;
			if (read = '1') then
				if (address = "001") then
					readdata <= ("0000000000000000000000000000000" & RUNNING);       --load the segment data from the bus
				end if;
				if (address = "100") then
					readdata <= std_logic_vector(resize(unsigned(LATENCY),32));       --load the segment data from the bus
				end if;
				if (address = "101") then
					readdata <= std_logic_vector(resize(unsigned(MISSED_PULSES),32));       --load the segment data from the bus
				end if;				
         end if;
      end if; 
   end process;
	
	
	STIM <= pulse_signal;


b2v_inst4 : LogicalStep_latency_tracker
PORT MAP(response => RESP,
		 pulse => pulse_signal,
		 clk => clk,
--		 reset => RESET_IN,
		 reset => reset,  -- connected to external switch reset 
		 enable => ENABLE,
		 latency => LATENCY,
		 missed => MISSED_PULSES);


b2v_inst5 : LogicalStep_pulse_generator
PORT MAP(clk => clk,
		 start => START,
--		 reset => RESET_IN,
		 reset => reset, -- connected to external switch reset
		 enable => ENABLE,
		 duty_cycle => DUTY_CYCLE,
		 period => PERIOD,
		 running => RUNNING,
		 pulse => pulse_signal);

end architecture syn;



-- *** EOF ***
--		response :  IN  STD_LOGIC;
--		clock :  IN  STD_LOGIC;
--		oneStep :  IN  STD_LOGIC;
--		reset :  IN  STD_LOGIC;
--		enable :  IN  STD_LOGIC;
--		duty_cycle :  IN  STD_LOGIC_VECTOR(3 DOWNTO 0);
--		period :  IN  STD_LOGIC_VECTOR(3 DOWNTO 0);
--		pulse :  OUT  STD_LOGIC;
--		latency :  OUT  STD_LOGIC_VECTOR(15 DOWNTO 0);
--		missed :  OUT  STD_LOGIC_VECTOR(15 DOWNTO 0)