/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"

int main()
{
  int x,y;
  int buttons;
  x = 0;
  y = 10;



  while(1) {
	  buttons = IORD(BUTTON_PIO_BASE,0);
//	  if(buttons != 15)
//	  {
//		  printf("%d", buttons);
//		  break;
//	  }
	  switch(buttons)
	  {
	  	  case 14: IOWR(LED_PIO_BASE,0,0x1);
	  	  break;
	  	  case 13: IOWR(LED_PIO_BASE,0,0x2);
	  	  break;
	  	  case 11: IOWR(LED_PIO_BASE,0,0x4);
	  	  break;
	  	  case 7: IOWR(LED_PIO_BASE,0,0x8);
	  	  break;
	  	  default: IOWR(LED_PIO_BASE, 0, 0x00);
	  }
  }


//  while(buttons != 14)
//  {
//	  buttons = IORD(BUTTON_PIO_BASE,0);
//	  //printf("%d\n", buttons);
//	  if(buttons == 14)
//	  {
//	  	IOWR(LED_PIO_BASE,0,0xAA);
//	  }
//  }

  //printf("%d\n", buttons);


  // button pressed
  /*if(buttons == 14)
  {
	IOWR(LED_PIO_BASE,0,0xAA);
  }*/

  printf("Hello from Nios II!\n");

  printf("Sum is %d", (x+y));

  return 0;
}
