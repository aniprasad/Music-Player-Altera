/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'nios2_gen2_0' in SOPC Builder design 'LogicalStep'
 * SOPC Builder design path: ../../LogicalStep.sopcinfo
 *
 * Generated: Wed Sep 21 11:37:59 EDT 2016
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * Audio configuration
 *
 */

#define ALT_MODULE_CLASS_Audio altera_up_avalon_audio
#define AUDIO_BASE 0x10010e0
#define AUDIO_IRQ 2
#define AUDIO_IRQ_INTERRUPT_CONTROLLER_ID 0
#define AUDIO_NAME "/dev/Audio"
#define AUDIO_SPAN 16
#define AUDIO_TYPE "altera_up_avalon_audio"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x01000820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x19
#define ALT_CPU_DCACHE_BYPASS_MASK 0x80000000
#define ALT_CPU_DCACHE_LINE_SIZE 32
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_DCACHE_SIZE 2048
#define ALT_CPU_EXCEPTION_ADDR 0x00800020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_EXTRA_EXCEPTION_INFO
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INITDA_SUPPORTED
#define ALT_CPU_INST_ADDR_WIDTH 0x19
#define ALT_CPU_NAME "nios2_gen2_0"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00800000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x01000820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x19
#define NIOS2_DCACHE_BYPASS_MASK 0x80000000
#define NIOS2_DCACHE_LINE_SIZE 32
#define NIOS2_DCACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_SIZE 2048
#define NIOS2_EXCEPTION_ADDR 0x00800020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_EXTRA_EXCEPTION_INFO
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INITDA_SUPPORTED
#define NIOS2_INST_ADDR_WIDTH 0x19
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00800000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_LCD_16207
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_AVALON_UART
#define __ALTERA_NIOS2_GEN2
#define __ALTERA_UP_AVALON_AUDIO
#define __ALTERA_UP_AVALON_AUDIO_AND_VIDEO_CONFIG
#define __DUAL_7_SEGMENT
#define __EGM
#define __SPI_MASTER


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "MAX 10"
#define ALT_IRQ_BASE NULL
#define ALT_LEGACY_INTERRUPT_API_PRESENT
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart_0"
#define ALT_STDERR_BASE 0x1001140
#define ALT_STDERR_DEV jtag_uart_0
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart_0"
#define ALT_STDIN_BASE 0x1001140
#define ALT_STDIN_DEV jtag_uart_0
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart_0"
#define ALT_STDOUT_BASE 0x1001140
#define ALT_STDOUT_DEV jtag_uart_0
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "LogicalStep"


/*
 * audio_i2c_config configuration
 *
 */

#define ALT_MODULE_CLASS_audio_i2c_config altera_up_avalon_audio_and_video_config
#define AUDIO_I2C_CONFIG_BASE 0x10010f0
#define AUDIO_I2C_CONFIG_IRQ -1
#define AUDIO_I2C_CONFIG_IRQ_INTERRUPT_CONTROLLER_ID -1
#define AUDIO_I2C_CONFIG_NAME "/dev/audio_i2c_config"
#define AUDIO_I2C_CONFIG_SPAN 16
#define AUDIO_I2C_CONFIG_TYPE "altera_up_avalon_audio_and_video_config"


/*
 * button_pio configuration
 *
 */

#define ALT_MODULE_CLASS_button_pio altera_avalon_pio
#define BUTTON_PIO_BASE 0x1001120
#define BUTTON_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define BUTTON_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BUTTON_PIO_CAPTURE 1
#define BUTTON_PIO_DATA_WIDTH 4
#define BUTTON_PIO_DO_TEST_BENCH_WIRING 0
#define BUTTON_PIO_DRIVEN_SIM_VALUE 0
#define BUTTON_PIO_EDGE_TYPE "ANY"
#define BUTTON_PIO_FREQ 50000000
#define BUTTON_PIO_HAS_IN 1
#define BUTTON_PIO_HAS_OUT 0
#define BUTTON_PIO_HAS_TRI 0
#define BUTTON_PIO_IRQ 1
#define BUTTON_PIO_IRQ_INTERRUPT_CONTROLLER_ID 0
#define BUTTON_PIO_IRQ_TYPE "EDGE"
#define BUTTON_PIO_NAME "/dev/button_pio"
#define BUTTON_PIO_RESET_VALUE 0
#define BUTTON_PIO_SPAN 16
#define BUTTON_PIO_TYPE "altera_avalon_pio"


/*
 * egm configuration
 *
 */

#define ALT_MODULE_CLASS_egm egm
#define EGM_BASE 0x1001000
#define EGM_IRQ -1
#define EGM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define EGM_NAME "/dev/egm"
#define EGM_SPAN 32
#define EGM_TYPE "egm"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK SYSTEM_TIMER
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart_0 altera_avalon_jtag_uart
#define JTAG_UART_0_BASE 0x1001140
#define JTAG_UART_0_IRQ 0
#define JTAG_UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_0_NAME "/dev/jtag_uart_0"
#define JTAG_UART_0_READ_DEPTH 64
#define JTAG_UART_0_READ_THRESHOLD 8
#define JTAG_UART_0_SPAN 8
#define JTAG_UART_0_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_0_WRITE_DEPTH 64
#define JTAG_UART_0_WRITE_THRESHOLD 8


/*
 * lcd_display configuration
 *
 */

#define ALT_MODULE_CLASS_lcd_display altera_avalon_lcd_16207
#define LCD_DISPLAY_BASE 0x1001100
#define LCD_DISPLAY_IRQ -1
#define LCD_DISPLAY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_DISPLAY_NAME "/dev/lcd_display"
#define LCD_DISPLAY_SPAN 16
#define LCD_DISPLAY_TYPE "altera_avalon_lcd_16207"


/*
 * led_pio configuration
 *
 */

#define ALT_MODULE_CLASS_led_pio altera_avalon_pio
#define LED_PIO_BASE 0x1001130
#define LED_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define LED_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LED_PIO_CAPTURE 0
#define LED_PIO_DATA_WIDTH 8
#define LED_PIO_DO_TEST_BENCH_WIRING 0
#define LED_PIO_DRIVEN_SIM_VALUE 0
#define LED_PIO_EDGE_TYPE "NONE"
#define LED_PIO_FREQ 50000000
#define LED_PIO_HAS_IN 0
#define LED_PIO_HAS_OUT 1
#define LED_PIO_HAS_TRI 0
#define LED_PIO_IRQ -1
#define LED_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LED_PIO_IRQ_TYPE "NONE"
#define LED_PIO_NAME "/dev/led_pio"
#define LED_PIO_RESET_VALUE 0
#define LED_PIO_SPAN 16
#define LED_PIO_TYPE "altera_avalon_pio"


/*
 * response_out configuration
 *
 */

#define ALT_MODULE_CLASS_response_out altera_avalon_pio
#define RESPONSE_OUT_BASE 0x10010c0
#define RESPONSE_OUT_BIT_CLEARING_EDGE_REGISTER 0
#define RESPONSE_OUT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define RESPONSE_OUT_CAPTURE 0
#define RESPONSE_OUT_DATA_WIDTH 1
#define RESPONSE_OUT_DO_TEST_BENCH_WIRING 0
#define RESPONSE_OUT_DRIVEN_SIM_VALUE 0
#define RESPONSE_OUT_EDGE_TYPE "NONE"
#define RESPONSE_OUT_FREQ 50000000
#define RESPONSE_OUT_HAS_IN 0
#define RESPONSE_OUT_HAS_OUT 1
#define RESPONSE_OUT_HAS_TRI 0
#define RESPONSE_OUT_IRQ -1
#define RESPONSE_OUT_IRQ_INTERRUPT_CONTROLLER_ID -1
#define RESPONSE_OUT_IRQ_TYPE "NONE"
#define RESPONSE_OUT_NAME "/dev/response_out"
#define RESPONSE_OUT_RESET_VALUE 0
#define RESPONSE_OUT_SPAN 16
#define RESPONSE_OUT_TYPE "altera_avalon_pio"


/*
 * sdram_0 configuration
 *
 */

#define ALT_MODULE_CLASS_sdram_0 altera_avalon_new_sdram_controller
#define SDRAM_0_BASE 0x800000
#define SDRAM_0_CAS_LATENCY 3
#define SDRAM_0_CONTENTS_INFO
#define SDRAM_0_INIT_NOP_DELAY 0.0
#define SDRAM_0_INIT_REFRESH_COMMANDS 2
#define SDRAM_0_IRQ -1
#define SDRAM_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_0_IS_INITIALIZED 1
#define SDRAM_0_NAME "/dev/sdram_0"
#define SDRAM_0_POWERUP_DELAY 100.0
#define SDRAM_0_REFRESH_PERIOD 15.625
#define SDRAM_0_REGISTER_DATA_IN 1
#define SDRAM_0_SDRAM_ADDR_WIDTH 0x16
#define SDRAM_0_SDRAM_BANK_WIDTH 2
#define SDRAM_0_SDRAM_COL_WIDTH 8
#define SDRAM_0_SDRAM_DATA_WIDTH 16
#define SDRAM_0_SDRAM_NUM_BANKS 4
#define SDRAM_0_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_0_SDRAM_ROW_WIDTH 12
#define SDRAM_0_SHARED_DATA 0
#define SDRAM_0_SIM_MODEL_BASE 0
#define SDRAM_0_SPAN 8388608
#define SDRAM_0_STARVATION_INDICATOR 0
#define SDRAM_0_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_0_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_0_T_AC 5.5
#define SDRAM_0_T_MRD 3
#define SDRAM_0_T_RCD 20.0
#define SDRAM_0_T_RFC 70.0
#define SDRAM_0_T_RP 20.0
#define SDRAM_0_T_WR 14.0


/*
 * seven_seg_pio configuration
 *
 */

#define ALT_MODULE_CLASS_seven_seg_pio dual_7_segment
#define SEVEN_SEG_PIO_BASE 0x1001020
#define SEVEN_SEG_PIO_IRQ -1
#define SEVEN_SEG_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEVEN_SEG_PIO_NAME "/dev/seven_seg_pio"
#define SEVEN_SEG_PIO_SPAN 32
#define SEVEN_SEG_PIO_TYPE "dual_7_segment"


/*
 * spi_master configuration
 *
 */

#define ALT_MODULE_CLASS_spi_master spi_master
#define SPI_MASTER_BASE 0x1001040
#define SPI_MASTER_IRQ -1
#define SPI_MASTER_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SPI_MASTER_NAME "/dev/spi_master"
#define SPI_MASTER_SPAN 32
#define SPI_MASTER_TYPE "spi_master"


/*
 * stimulus_in configuration
 *
 */

#define ALT_MODULE_CLASS_stimulus_in altera_avalon_pio
#define STIMULUS_IN_BASE 0x10010d0
#define STIMULUS_IN_BIT_CLEARING_EDGE_REGISTER 0
#define STIMULUS_IN_BIT_MODIFYING_OUTPUT_REGISTER 0
#define STIMULUS_IN_CAPTURE 1
#define STIMULUS_IN_DATA_WIDTH 1
#define STIMULUS_IN_DO_TEST_BENCH_WIRING 0
#define STIMULUS_IN_DRIVEN_SIM_VALUE 0
#define STIMULUS_IN_EDGE_TYPE "ANY"
#define STIMULUS_IN_FREQ 50000000
#define STIMULUS_IN_HAS_IN 1
#define STIMULUS_IN_HAS_OUT 0
#define STIMULUS_IN_HAS_TRI 0
#define STIMULUS_IN_IRQ 6
#define STIMULUS_IN_IRQ_INTERRUPT_CONTROLLER_ID 0
#define STIMULUS_IN_IRQ_TYPE "EDGE"
#define STIMULUS_IN_NAME "/dev/stimulus_in"
#define STIMULUS_IN_RESET_VALUE 0
#define STIMULUS_IN_SPAN 16
#define STIMULUS_IN_TYPE "altera_avalon_pio"


/*
 * switch_pio configuration
 *
 */

#define ALT_MODULE_CLASS_switch_pio altera_avalon_pio
#define SWITCH_PIO_BASE 0x1001110
#define SWITCH_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define SWITCH_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SWITCH_PIO_CAPTURE 0
#define SWITCH_PIO_DATA_WIDTH 8
#define SWITCH_PIO_DO_TEST_BENCH_WIRING 0
#define SWITCH_PIO_DRIVEN_SIM_VALUE 0
#define SWITCH_PIO_EDGE_TYPE "NONE"
#define SWITCH_PIO_FREQ 50000000
#define SWITCH_PIO_HAS_IN 1
#define SWITCH_PIO_HAS_OUT 0
#define SWITCH_PIO_HAS_TRI 0
#define SWITCH_PIO_IRQ -1
#define SWITCH_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SWITCH_PIO_IRQ_TYPE "NONE"
#define SWITCH_PIO_NAME "/dev/switch_pio"
#define SWITCH_PIO_RESET_VALUE 0
#define SWITCH_PIO_SPAN 16
#define SWITCH_PIO_TYPE "altera_avalon_pio"


/*
 * sysid_qsys_0 configuration
 *
 */

#define ALT_MODULE_CLASS_sysid_qsys_0 altera_avalon_sysid_qsys
#define SYSID_QSYS_0_BASE 0x1001148
#define SYSID_QSYS_0_ID 0
#define SYSID_QSYS_0_IRQ -1
#define SYSID_QSYS_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_QSYS_0_NAME "/dev/sysid_qsys_0"
#define SYSID_QSYS_0_SPAN 8
#define SYSID_QSYS_0_TIMESTAMP 1474466847
#define SYSID_QSYS_0_TYPE "altera_avalon_sysid_qsys"


/*
 * system_timer configuration
 *
 */

#define ALT_MODULE_CLASS_system_timer altera_avalon_timer
#define SYSTEM_TIMER_ALWAYS_RUN 0
#define SYSTEM_TIMER_BASE 0x1001080
#define SYSTEM_TIMER_COUNTER_SIZE 32
#define SYSTEM_TIMER_FIXED_PERIOD 0
#define SYSTEM_TIMER_FREQ 50000000
#define SYSTEM_TIMER_IRQ 4
#define SYSTEM_TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SYSTEM_TIMER_LOAD_VALUE 49999
#define SYSTEM_TIMER_MULT 0.001
#define SYSTEM_TIMER_NAME "/dev/system_timer"
#define SYSTEM_TIMER_PERIOD 1
#define SYSTEM_TIMER_PERIOD_UNITS "ms"
#define SYSTEM_TIMER_RESET_OUTPUT 0
#define SYSTEM_TIMER_SNAPSHOT 1
#define SYSTEM_TIMER_SPAN 32
#define SYSTEM_TIMER_TICKS_PER_SEC 1000
#define SYSTEM_TIMER_TIMEOUT_PULSE_OUTPUT 0
#define SYSTEM_TIMER_TYPE "altera_avalon_timer"


/*
 * timer_0 configuration
 *
 */

#define ALT_MODULE_CLASS_timer_0 altera_avalon_timer
#define TIMER_0_ALWAYS_RUN 0
#define TIMER_0_BASE 0x1001060
#define TIMER_0_COUNTER_SIZE 32
#define TIMER_0_FIXED_PERIOD 0
#define TIMER_0_FREQ 50000000
#define TIMER_0_IRQ 5
#define TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_0_LOAD_VALUE 49999
#define TIMER_0_MULT 0.001
#define TIMER_0_NAME "/dev/timer_0"
#define TIMER_0_PERIOD 1
#define TIMER_0_PERIOD_UNITS "ms"
#define TIMER_0_RESET_OUTPUT 0
#define TIMER_0_SNAPSHOT 1
#define TIMER_0_SPAN 32
#define TIMER_0_TICKS_PER_SEC 1000
#define TIMER_0_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_0_TYPE "altera_avalon_timer"


/*
 * uart configuration
 *
 */

#define ALT_MODULE_CLASS_uart altera_avalon_uart
#define UART_BASE 0x10010a0
#define UART_BAUD 115200
#define UART_DATA_BITS 8
#define UART_FIXED_BAUD 1
#define UART_FREQ 50000000
#define UART_IRQ 3
#define UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define UART_NAME "/dev/uart"
#define UART_PARITY 'N'
#define UART_SIM_CHAR_STREAM ""
#define UART_SIM_TRUE_BAUD 0
#define UART_SPAN 32
#define UART_STOP_BITS 1
#define UART_SYNC_REG_DEPTH 2
#define UART_TYPE "altera_avalon_uart"
#define UART_USE_CTS_RTS 0
#define UART_USE_EOP_REGISTER 0

#endif /* __SYSTEM_H_ */
