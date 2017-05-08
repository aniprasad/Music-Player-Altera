library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity LogicalStep_pulse_generator is
port(	clk 			: in std_logic;
		reset			: in std_logic;
		enable		: in std_logic;
		start			: in std_logic;
		period		: in std_logic_vector(15 downto 0) := (others => '0');
		duty_cycle 	: in std_logic_vector(15 downto 0) := (others => '0');	
		running		: out std_logic;
		pulse			: out std_logic
	);
end LogicalStep_pulse_generator;


	ARCHITECTURE a OF LogicalStep_pulse_generator IS
   TYPE STATE_TYPE IS (off, reset_count, pulse_high, pulse_low, stopped);
   SIGNAL state   											: STATE_TYPE;
	signal enabled 											: std_logic;
	signal responded										 	: std_logic;
	signal counter												: integer := 0;
	signal timer			 									: integer := 0;
	
BEGIN

   PROCESS (clk)
   BEGIN
		IF (clk'EVENT AND clk = '1') THEN
			IF reset = '1' then 
				state <= off;
			else			
				CASE state IS
					WHEN off=>
						If enable = '1' THEN
							state <= pulse_high;
						END IF;
					WHEN reset_count=>
						state <= pulse_high;
					WHEN pulse_high=>
						IF counter = to_integer(unsigned(duty_cycle)) THEN
							state <= pulse_low;
						END IF;
					WHEN pulse_low =>
						IF timer > 2000000 THEN
							state <= stopped;
						ELSIF counter = to_integer(unsigned(period)) THEN
							state <= reset_count;
						END IF;
					WHEN stopped =>
						IF enable = '0' THEN
							state <= off;
						END IF;
				END CASE;
			END IF;
      END IF;
   END PROCESS;
	
	PROCESS (clk)
		--variable count           	: integer := 0;
		
   BEGIN
		if rising_edge(clk) then 
			CASE state IS
				WHEN off =>
					counter <= 0;
					timer <= 0;
					pulse <= '0';
					running <= '0';
				WHEN reset_count =>
					counter <= 0;
					timer <= timer + 1;
					pulse <= '0';
					running <= '1';
				WHEN pulse_high =>
					counter <= counter + 1;
					timer <= timer + 1;
					pulse <= '1';
					running <= '1';					
				WHEN pulse_low =>
					counter <= counter + 1;
					timer <= timer + 1;
					pulse <= '0';
					running <= '1';					
				WHEN stopped =>
					counter <= 0;
					timer <= 0;
					pulse <= '0';
					running <= '0';
			END CASE;
		end if;

   END PROCESS;
	

end a;