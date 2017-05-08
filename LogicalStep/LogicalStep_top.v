// Copyright (C) 2016 Trevor Smouter


`define LCD
`define LED
`define SlideSwitches
`define PushButtons
`define SevenSegment
`define AudioCodec
`define UART
`define SDCard 
`define SDRAM 

module LogicalStep_top
(
	input				rst_n,		//reset in
	input          clkin_50,	//clock in

`ifdef LCD
	inout		[7:0] lcd_d,
	output			lcd_en,
	output			lcd_rw,
	output			lcd_rs,
`endif

`ifdef LED
	output	[7:0]	leds,
`endif

`ifdef SlideSwitches
	input		[7:0]	sw,
`endif

`ifdef PushButtons
	input		[3:0]	pb,
`endif

`ifdef SevenSegment
	output	[7:0]	seg7_data,
	output			seg7_char1,
	output			seg7_char2,
`endif

`ifdef AudioCodec
	output			aud_scl,
	inout				aud_sda,
	output			aud_mclk,
	input				aud_bclk,
	output			aud_dac_dat,
	input				aud_dac_lrck,
	input				aud_adc_dat,
	input				aud_adc_lrck,	
`endif

`ifdef UART
	input				uart_rx,
	output			uart_tx,
`endif

`ifdef SDCard
	inout				sd_cmd,
	output			sd_clk,
	inout				sd_dat3,
	inout				sd_dat0,
`endif

`ifdef SDRAM
	output	[12:0]sdram_a,
	output	[1:0]	sdram_ba,
	output			sdram_clk,
	output			sdram_cke,
	output			sdram_cs_n,
	output			sdram_ras_n,
	output			sdram_cas_n,
	inout		[15:0]sdram_dq,
	output	[1:0] sdram_dqm,
	output			sdram_we_n
`endif


);

	//these are used as intermediate signals
	wire 				stimulus;
	wire				response;

	

//place Qsys instance below here

	LogicalStep u0 (
		.clk_50_clk                 (clkin_50),                 //        clk_50.clk
		.reset_reset_n              (rst_n),              //         reset.reset_n
		.sdram_clk_clk              (sdram_clk),              //     sdram_clk.clk
		.audio_mclk_clk             (aud_mclk),             //    audio_mclk.clk
		.sdram_0_addr               (sdram_a),               //       sdram_0.addr
		.sdram_0_ba                 (sdram_ba),                 //              .ba
		.sdram_0_cas_n              (sdram_cas_n),              //              .cas_n
		.sdram_0_cke                (sdram_cke),                //              .cke
		.sdram_0_cs_n               (sdram_cs_n),               //              .cs_n
		.sdram_0_dq                 (sdram_dq),                 //              .dq
		.sdram_0_dqm                (sdram_dqm),                //              .dqm
		.sdram_0_ras_n              (sdram_ras_n),              //              .ras_n
		.sdram_0_we_n               (sdram_we_n),               //              .we_n
		.led_pio_export             (leds),             //       led_pio.export
		.button_pio_export          (pb),          //    button_pio.export
		.switch_pio_export          (sw),          //    switch_pio.export
		.lcd_display_RS             (lcd_rs),             //   lcd_display.RS
		.lcd_display_RW             (lcd_rw),             //              .RW
		.lcd_display_data           (lcd_d),           //              .data
		.lcd_display_E              (lcd_en),              //              .E
		.audio_i2c_SDAT             (aud_sda),             //     audio_i2c.SDAT
		.audio_i2c_SCLK             (aud_scl),             //              .SCLK
		.audio_out_ADCDAT           (aud_adc_dat),           //     audio_out.ADCDAT
		.audio_out_ADCLRCK          (aud_adc_lrck),          //              .ADCLRCK
		.audio_out_BCLK             (aud_bclk),             //              .BCLK
		.audio_out_DACDAT           (aud_dac_dat),           //              .DACDAT
		.audio_out_DACLRCK          (aud_dac_lrck),          //              .DACLRCK
		.uart_rxd                   (uart_rx),                   //          uart.rxd
		.uart_txd                   (uart_tx),                   //              .txd
		.spi_master_cs              (sd_dat3),              //    spi_master.cs
		.spi_master_sclk            (sd_clk),            //              .sclk
		.spi_master_mosi            (sd_cmd),            //              .mosi
		.spi_master_miso            (sd_dat0),            //              .miso
		.spi_master_cd              (),              //              .cd
		.spi_master_wp              (),              //              .wp
		.segment_drive_segment_data (seg7_data), // segment_drive.segment_data
		.segment_drive_digit1       (seg7_char1),       //              .digit1
		.segment_drive_digit2       (seg7_char2),       //              .digit2
		.egm_interface_stimulus     (stimulus),     // egm_interface.stimulus
		.egm_interface_response     (response),     //              .response
		.stimulus_in_export         (stimulus),         //   stimulus_in.export
		.response_out_export        (response)         //  response_out.export
	);



		
//place Qsys instance above here
		
	

endmodule
