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
#include <string.h>
#include "altera_up_avalon_audio.h"

#include "sys/alt_irq.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <system.h>
#include <sys/alt_alarm.h>
#include <io.h>

#include "fatfs.h"
#include "diskio.h"

#include "ff.h"
#include "monitor.h"
#include "uart.h"

#include <unistd.h>

#include "ffconf.h"

#include "alt_types.h"

#include <altera_up_avalon_audio.h>
#include <altera_up_avalon_audio_and_video_config.h>

char filename[20][20];
long fileSize[20];
int fileCount = 0;

volatile int buttons;

volatile int next;

uint8_t res;
uint32_t ofs = 0;
DIR Dir;

uint8_t Buff[8192] __attribute__ ((aligned(4)));  /* Working buffer */

FIL File1;

FILINFO Finfo;
FATFS Fatfs[_VOLUMES];

// Variable to keep track of whether its paused or play
volatile int play = 0;
// Variable to keep track of how many times the play/pause button has been clicked
volatile int playCounter = 0;
// Flag for when the next button is pressed
volatile int next = 0;
// Flag for when the fast forward button is pressed
volatile int fastForward = 0;
// Initial increment of 4 bytes in normal play mode
volatile int fastForwardIncrement = 4;
// Flag for when the rewind button is pressed
volatile int rewindFlag = 0;
// Flag for when the previous button is pressed
volatile int prev = 0;
// Variable to keep track of how many times the next button has been clicked
volatile int nextCounter = 0;
// Variable to keep track of how many times the previous button has been clicked
volatile int previousCounter = 0;
// Flag for when the stop button is pressed
volatile int stop = 0;

// Song finished flag
volatile songFinished = 0;

int globalIndex = 0;

// Another flag for the stop button
int stopFlag;
// Variable to keep track of how many times the stop button is pressed
volatile int stopCounter;

// Variable to initially start playing data from the buffer at the beginning
volatile int start = 0;

alt_alarm alarmFlag;


void timerDebounce()
{

	// Stop the alarm
	alt_alarm_stop(&alarmFlag);

	// Interrupt Cases
	// Case 14: Next/Fast Forward
	// Case 13: Play/Pause
	// Case 11: Stop
	// Case 7: Previous/Rewind

	// Enable the interrupts
	IOWR(BUTTON_PIO_BASE, 2, 0xf);

	//ISR Code goes here
	// Read the value of the button when it is pressed and then and with 15
	// This is done so as to not trigger the button on both edges
	buttons = IORD(BUTTON_PIO_BASE, 0) & 0xf;

	// A little hack to distinguish between fastforward and next button
	// Initially when the file is playing play is 1 and fastForward is 0
	// When it is pressed it goes to the interrupt handler (see case 14)
	// When it is eventually released it will come to this if block where
	// we reset the increment to 4 and disable the flag
	// This resumes the song resumes playing at normal speed
	if(play && fastForward)
	{
		fastForward = 0;
		fastForwardIncrement = 4;
	}
	// The similar concept is used for rewind
	if(play && rewindFlag)
	{
		rewindFlag = 0;
		start = 0;
		fastForwardIncrement = 4;
	}
	// We check if buttons is not 15 because we don't want to trigger this switch block
	// when the button is released as well
	if(buttons != 15)
	{
		switch(buttons)
		{
			case 14:  // If the file is not playing and the next button is pressed
					  if(!play)
					  {
					  	 // Enable the flag
				  	  	 next = 1;
				  	  	 // Increment the counter
				  	  	 nextCounter++;

				  	  	 // Increment the index so you can go to the next file
						 globalIndex = (globalIndex + 1 ) % fileCount;
						 if(nextCounter != 1 && playCounter != 0 && play == 0 && stop == 0)
						 {
							 globalIndex = (globalIndex + 1 ) % fileCount;
						 }
						 if(stopFlag)
						 {
							 globalIndex = (globalIndex - 1) % fileCount;
							 if(globalIndex < 0)
							 {
								 globalIndex = fileCount - abs(globalIndex);
							 }
						 }

						 // Once you have incremented the file update the lcd display
						 lcddisplay(filename[globalIndex], globalIndex);

					  }
					  // This case is the fast forwarding case when the song is playing
					  // Enable the fast forward flag
					  // Set fastForwardIncrement to 8 to read data at double the rate
					  else
					  {
						  fastForward = 1;
						  fastForwardIncrement = 8;
					  }
					  break;
			case 13:  // Increment counter when the play button is hit
					  playCounter = playCounter + 1;
					  // If its an odd number its a play
					  // Set the appropriate flags that are required here
					  if(playCounter % 2 == 1)
					  {
						  stopFlag = 0;
						  stopCounter = 0;
						  play = 1;
					  }
					  // Otherwise its a pause
					  else
					  {
						  stopFlag = 0;
						  stopCounter = 0;
						  play = 0;
					  }
					  break;
			case 11:  // Have to disable stop if it is pressed immediately after a next or previous button
					  // Prevents Jamming of the stop button
					  if(playCounter == 0 || stopCounter > 0)
					  {
						  break;
					  }
					  // If the song is playing and the stop button is pressed
					  // Enable flags and increment counter
					  if(play)
					  {
				  	  	stop = 1;
				  	  	stopFlag = 1;
						stopCounter++;
					  }
					  // If the song is paused and the stop button is pressed
					  // Enable flags and increment counter
					  if(!play)
					  {
						  stop = 1;
						  stopFlag = 1;
						  stopCounter++;
						  playCounter+=1;
					  }

					  break;
			case 7:   // If the song is not playing and the previous button is pressed
					  if(!play)
					  {
					  	 // Use the same flag and enable it
						 next = 1;
						 // Increment counter
						 previousCounter++;
						 if(globalIndex == 0 && playCounter > 1 && play == 0)
						 {
							 globalIndex = abs(globalIndex);
						 }
						 if(playCounter > 1 && previousCounter != 1)
						 {
							 globalIndex = (globalIndex + 1 % fileCount);
						 }
						 globalIndex = globalIndex - 1 % fileCount;
						 if(globalIndex < 0)
						 {
						   globalIndex = fileCount - abs(globalIndex);
						 }
						 if(stopFlag)
						 {
							 globalIndex = (globalIndex - 1) % fileCount;
							 if(globalIndex < 0)
							 {
								 globalIndex = fileCount - abs(globalIndex);
							 }
						 }
						 // Once you have updated the index as appropriate and based on the case call
						 // the lcd function to update the display
						 lcddisplay(filename[globalIndex], globalIndex);

					  }
					  // This is the rewind case when the song is playing
					  // Set the increment to -4 so that it will loop backward
					  // Enable the flag
					  // start is now 508 as you want to start from that current point and go backwards
					  else
					  {
						  rewindFlag = 1;
						  fastForwardIncrement = -4;
						  start = 508;
					  }
			  	  	  break;
		}

	}

	// Clear edge capture
	IOWR(BUTTON_PIO_BASE, 3, 0x0);

}



// Interrupt Initialization
static void interruptRoutine(void *context, alt_u32 id)
{

	// Start the alarm
	alt_alarm_start(&alarmFlag , 30 , &timerDebounce , NULL);

	// Disable the interrupt
	IOWR(BUTTON_PIO_BASE, 2, 0);

	// Clear edge capture register
	IOWR(BUTTON_PIO_BASE, 3, 0x0);

}

/*
Function to check whether a given file is a .wav file or not
Returns 1 if it is a .wav file
Otherwise returns 0
*/

int isWav(char *filename)
{
	  char wav[5];
	  int start = strlen(filename) - 1;
	  int len = start;
	  for( ; start > len - 4 ; start--)
	  {
	      strcpy(wav, &filename[start]);
	  }
	  int comparison = strcmp(wav , ".WAV");
	  if(!comparison)
	  {
		  // It is a wav file return true
		  return 1;
	  }
	  else
	  {
		  // Else it is not a wav file return false
		  return 0;
	  }

}

/*
Puts the file name into the global filename array
*/
void putFileNameArray(char *filename1, int index)
{
	strcpy(filename[index], filename1);
}

/*
Puts the file size of the file into the global fileSize array
*/
void putFileSizeArray(long size, int index)
{
	fileSize[index] = size;
}

/*
Function to print the song list from the arrays
*/
void printSongList(int fileCount)
{
	int i = 0;
    for( ; i < fileCount ; i++)
    {
    	printf("%s---", filename[i]);
    	printf("%9lu\n", fileSize[i]);
    }
}

/*
Opens the file
*/
void fileOpen(long p1, char *ptr)
{
	 f_open(&File1, ptr, (uint8_t) p1);
}

/*
Function to play the file
*/
void filePlay(long filelength, long fomode, char *ptr)
{

	// Initialize Audio 
	alt_up_audio_dev * audio_dev;
	/* used for audio record/playback */
	unsigned int l_buf;
	unsigned int r_buf;

	// open the Audio port
	audio_dev = alt_up_audio_open_dev ("/dev/Audio");

	// p1 now stores the filelength
	long p1 = filelength;
	// Variable that uses p1 / 180000 to determine how much time has elapsed
	int initialBytesPerSecond = p1/176000;

	int cnt;
	int fifospace;

	int trackposition = 0;

	// Before doing file play open the file first
	// ptr has the name of the file
	fileOpen(fomode, ptr);


	ofs = File1.fptr; // Initial position of the file pointer

	//p1 is the number of bytes to read from the file

	while (p1>0) {
		// If the stop button is pressed immediately exit out of the loop
		if(stop)
		{
			play = 0;
			break;
		}
		// Start the process of reading the file
		// The file length keeps decreasing by 512
		// whereas the file pointer keeps incrementing
		// by 512 as the file is being read
		if ((uint32_t) p1 >= 512) {
			cnt = 512;
			p1 -= cnt;
			trackposition+=512;
		}
		// When the end of the file is reached, cnt is now the file length
		// whereas p1 which stored the length of the file initially is now
		// 0
		else {
			cnt = p1;
			p1 = 0;
			trackposition+=512;
			songFinished = 1;
		}

		// If the rewind button is pressed move the file pointer back
		// before you start reading the file
		// This ensures that every time you are feeding data from the buffer
		// into the audio you are going back a bit in the file and then playing
		// that data
		if(rewindFlag)
		{
			f_lseek(&File1, ofs);
		}
		// Start reading the file
		res = f_read(&File1, Buff, cnt, &cnt);

		// This variable tries to determine the number of seconds elapsed
		int display = initialBytesPerSecond - (p1/ 176000);
		// If this value is greater than 176000 then a second has elapsed
		// Reset the trackposition variable to 0
		// Call lcddisplay to update as each second has elapsed
		if(trackposition > 176000)
		{
			lcddisplay(filename[globalIndex], globalIndex, display);
		    trackposition = 0;
		}

		// Start feeding data from the buffer into the audio
		// start is 0 in Normal Play Mode
		// start is 508 in Rewind Mode
		// fastForwardIncrement is 4 in Normal Play Mode
		// fastForwardIncrement is 8 in Fast Forward Mode
		// fastForwardIncrement is -4 in Rewind Mode
		// If it is in rewind mode we loop until i is greater than 0
		// If it is in fast forward mode we loop until i is less than cnt
		int i;
		for(i = start; (rewindFlag) ? i > 0 : i < cnt ; i += fastForwardIncrement)
		{
			// If the stop button is pressed exit the loop immediately
			if(stop)
			{
				play = 0;
				break;
			}
			// Start looping to feed the data
			while(1) {

				// If the stop button is pressed exit the loop immediately
				if(stop)
				{
					play = 0;
					break;
				}
				// Check the fifospace
				int fifospace = alt_up_audio_write_fifo_space(audio_dev, ALT_UP_AUDIO_RIGHT);

				// If the next button is pressed and the file is currently paused or stopped
				if(next && !play) {
					// Open the next file so it is ready
					fileOpen(1, filename[globalIndex]);
					p1 = fileSize[globalIndex];
					while (p1>0) {
						if ((uint32_t) p1 >= 512) {
							cnt = 512;
							p1 -= cnt;
						} else {
							cnt = p1;
							p1 = 0;
						}
					}
					// Disable the next flag
					next = 0;
					prev = globalIndex;
					// Decrement the count by 1 as towards the end of the loop
					// it is incremented by 1
				    globalIndex = globalIndex - 1;
				}

				// If there is space in the fifo buffer and the play flag is true
				// Start feeding data into the buffer
				// If the play flag is 0 that means the song is paused, so when play
				// flag is 1 again, it will resume from the same spot
				if(fifospace && play) {
					// Shift data by 8 bits and then OR and write into the audio device
					r_buf = (Buff[i + 1] << 8);
					r_buf = r_buf | Buff[i];

					l_buf = (Buff[i + 3] << 8);
					l_buf = l_buf | Buff[i + 2];

					alt_up_audio_write_fifo(audio_dev, &(l_buf), 1, ALT_UP_AUDIO_LEFT);
					alt_up_audio_write_fifo(audio_dev, &(r_buf), 1, ALT_UP_AUDIO_RIGHT);

					break;
				}

			}

		 // Write data into the audio device
		 }

		// If the file is in normal play mode
		// Increment the file pointer to grab the next chunk of data
		if(!rewindFlag)
		{
			ofs = ofs + cnt;
			trackposition += 512;
		}
		// Otherwise if it is in rewind mode decrement the file pointer
		// to keep going backwards until the the rewind button has been released
		else
		{
			// If the ofs is less than 512
			// ie. you're reaching the beginning of the file
			// keep setting it to 512 as in the beginning of the loop it will decrement by 512 again
			// Set p1 to the file length as you have reached the beginning of the file
			if(ofs < 512)
			{
				ofs = 512;
				p1 = filelength;
			}
			// Otherwise you are still in rewind mode and you're still moving backwards through the file
			// Decrement the ofs by cnt
			// Set p1 to p1 + 2*cnt as it is decremented by cnt at the beginning of the loop
			// Essentially add 512 to p1
			else
			{
				ofs = ofs - cnt;
				p1 = p1 + (2*cnt);
				trackposition -= 512;
			}

		}

	}
	// If the music file is not stopped increment the index to go to the next file
	// Reset the counter for the next and previous buttons
	if(!stop)
	{
		globalIndex = (globalIndex + 1) % fileCount;
		nextCounter = 0;
		previousCounter = 0;
	}
	// Otherwise the file has been stopped
	// Disable the flag so that stop may be pressed again if required
	// Increment the play counter so that the next click of play/pause button
	// Starts playing the file from the beginning
	else
	{
		playCounter+=1;
		stop = 0;
	}

	if(songFinished)
	{
		lcddelaydisplay();
		songFinished = 0;
	}

}

/*
Display Function
Takes in the name of the file, the index, and the amount of time elapsed
*/

void lcddisplay(char *ptr, int index, int posdis)
{
	// LCD object
	FILE *lcd;

	// Calculate total length of the file
	int tracklength = fileSize[index] / 176000;

    lcd = fopen("/dev/lcd_display", "w");
	if (lcd != NULL )
	{
		// Displays the index and the file name
		fprintf(lcd, "%d.%s\n", index, ptr);
		// Displays the elapsed time minutes, elapsed time seconds / total time minutes , total time seconds
		// Eg: 00:01 / 00:03
		fprintf(lcd, "0%d:%.02d / 0%d:%.02d\n", posdis / 60, posdis % 60, tracklength / 60, tracklength % 60);
	}
	// Closes the lcd file object
	fclose(lcd);
}


void lcddelaydisplay()
{
	// LCD stuff
	FILE *lcd;
	// LCD stuff

	// Calculate total length of the file
	// int tracklength = fileSize[index] / 176000;

	// Disable the interrupt
	IOWR(BUTTON_PIO_BASE, 2, 0);

    lcd = fopen("/dev/lcd_display", "w");
	if (lcd != NULL )
	{
		//usleep(1000000);
		fprintf(lcd, "%s : %d\n\n", "Next song in", 3);
		usleep(1000000);
		fprintf(lcd, "%s : %d\n\n", "Next song in", 2);
		usleep(1000000);
		fprintf(lcd, "%s : %d\n\n", "Next song in", 1);
		usleep(1000000);
	}
	// Closes the lcd file object
	fclose(lcd);

	// Enable the interrupt
	IOWR(BUTTON_PIO_BASE, 2, 0xF);
}


int main(void)
{
	// Enable the interrupt
	IOWR(BUTTON_PIO_BASE, 2, 0xf);

	// Clear the flag
	IOWR(BUTTON_PIO_BASE, 3, 0);

	// Register the interrupt
	alt_irq_register(BUTTON_PIO_IRQ, (void *)0, interruptRoutine);

	long p1;
	uint32_t s1, s2;
	int cnt;
	int count = 0;
	char *ptr;

	int i = 0;

	int open = 0;

	// di 0 command
	p1 = 0;
	(uint16_t) disk_initialize((uint8_t) p1);

	// fi 0 command
	f_mount((uint8_t) p1, &Fatfs[p1]);

	*ptr = 0;
	while(*ptr == ' ')
		ptr++;
    res = f_opendir(&Dir, ptr);
    p1 = s1 = s2 = 0;
    for( ; ; ) {
    	res = f_readdir(&Dir, &Finfo);
    	if ((res != FR_OK) || !Finfo.fname[0]) {
    		break;
    	}

    	if (Finfo.fattrib & AM_DIR) {
    		s2++;
    	} else {
    		s1++;
    		p1 += Finfo.fsize;
    	}
    	// Checks if the file is a wav file and if so
    	// Stores the file name and the file size into separate arrays
    	if(isWav(&(Finfo.fname[0])))
    	{
    		putFileNameArray(&(Finfo.fname[0]) , fileCount);
    		putFileSizeArray(Finfo.fsize, fileCount);
    		fileCount += 1;
    	}
    }

    // Prints the song name and the size
    printSongList(fileCount);

    // Displays the first file on the LCD
    lcddisplay(filename[globalIndex], globalIndex, 0);

    int j = 0;
    // Starts the infinite loop
    while(1)
    {
    	prev = globalIndex;
    	// If the play button is pressed
    	if(play)
    	{
    		// Call the filePlay function
			filePlay(fileSize[globalIndex], 1, filename[globalIndex]);
		    // Call LCD as the filePlay function keeps iterating through the files
		    // to update the display
		    if(globalIndex != 0)
		    	lcddisplay(filename[globalIndex], globalIndex, 0);
    	}
    }

	return 0;
}