library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity LogicalStep_latency_tracker is
port(	response	: in std_logic;
		pulse		: in std_logic;
		clk 		: in std_logic;
		reset		: in std_logic;
		enable	: in std_logic;
		missed	: out std_logic_vector(15 downto 0) := (others => '0');
		latency 	: out std_logic_vector(15 downto 0) := (others => '0')
	);
end LogicalStep_latency_tracker;


	ARCHITECTURE a OF LogicalStep_latency_tracker IS
   TYPE STATE_TYPE IS (off, wait4pulse, wait4response1, wait4response2, missed_pulse1, missed_pulse2, responded1, responded2);
   SIGNAL state   											: STATE_TYPE;
	signal enabled 											: std_logic;
	signal responded										 	: std_logic;
	signal misses 												: integer := 0;
	signal currentLatency 									: integer := 0;
	
BEGIN


   PROCESS (clk)
   BEGIN
		IF (clk'EVENT AND clk = '1') THEN
			IF enable = '0' then 
				state <= off;
			else			
				CASE state IS
					WHEN off=>
						state <= wait4pulse;
					WHEN wait4pulse=>
						
						IF pulse = '1' THEN
							state <= wait4response1;
						ELSE
							state <= wait4pulse;
						END IF;
					WHEN wait4response1 =>
						
						IF response = '1' THEN
							state <= responded1;
						ELSIF pulse = '1' THEN
							state <= wait4response1;
						ELSE
							state <= wait4response2;
						END IF;
					WHEN wait4response2 =>
						IF response = '1' THEN
							state <= responded1;
						ELSIF pulse = '1' THEN
							state <= missed_pulse1;
						ELSE
							state <= wait4response2;
						END IF;
					WHEN missed_pulse1 =>
							state <= wait4response1;
					WHEN missed_pulse2 =>
						IF pulse = '0' THEN
							state <= wait4response1;
						ELSE
							state <= missed_pulse2;
						END IF;
					WHEN responded1 =>
						state <= responded2;
					WHEN responded2 =>
						IF ((response = '0') AND (PULSE = '0'))THEN
							state <= wait4pulse;
						ELSE
							state <= responded2;
						END IF;
				END CASE;
			END IF;
      END IF;
   END PROCESS;
	
	PROCESS (clk)
		variable count           	: integer := 0;
		
   BEGIN
		if rising_edge(clk) then 
			CASE state IS
				WHEN off =>
					if enable = '1' then
						misses <= 0;
						currentLatency <= 0;
					end if;
				WHEN wait4pulse =>
					count := 0;
				WHEN wait4response1 =>
					count := count + 1;
				WHEN wait4response2 =>
					count := count + 1;
				WHEN missed_pulse1 =>
					 misses <= misses + 1;
					 count := 0;
				WHEN missed_pulse2 => 
				WHEN responded1 =>
					if currentLatency = 0 then
						currentLatency <= count;
					else
						currentLatency <= currentLatency + ((count - currentLatency)/ 8);
					end if;
				WHEN responded2 =>
			END CASE;
		end if;

   END PROCESS;
	
	missed 	<= std_logic_vector(to_unsigned(misses, 16));
	latency 	<= std_logic_vector(to_unsigned(currentLatency, 16)); 
	

end a;