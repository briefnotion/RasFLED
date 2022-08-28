// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************
// *
/* *  PROJECTID: gi6$b*E>*q%; */
/* *  TEST CODE:              */ // CENSORCODE: EQK6}Lc`:Eg>
// *
// ***************************************************************************************
// *  Programmer Notes:
// *
// *            Coder:  Robert Lebowski
// *    Support Coder:  None
// *  --- And:
// *    Other Sources:  None
// *
// *  Description:
// *    LED is an acronym for Light Emitting Diode. My goal for this little project is
// *    to create a control module multi colored light strips. The individual modules,
// *    running on an Arduino board, will be able to run as stand alone and or, while
// *    working together, as a single device. The module will be able to be
// *    preprogrammed to display certain effects when triggered by different
// *    preprogrammed events.
// *
// *    The first step in the project is to create a single working module.  It will
// *    need to be easily configured. It will need to be able to handle timed events,
// *    triggers events, calculated events, and possibly a combination of events triggers.
// *
// *    The second goal will be too create a communication system between the modules
// *    so that Multiple modules can be triggered by different events all module will
// *    be able to function independently or in parallel while working together.
// *
// *    The third goal will be to create a control module within each device. This
// *    control module device will just be added to each device as just another type of
// *    triggered event and will not be external code. It will just be another way to
// *    configure the device.
// *
// *    The fourth goal will be to determine a way to easily configure all devices in its
// *    system without the need to re flash each device independently. This goal is
// *    basically a central and easy way to setup all triggered events and reactions on
// *    all devices on its system by reading a simple program.
// *
// *    The F in FLED stands of Failed, as in I failed to receive backing for this
// *    project, and I failed to assemble a team to assist me with this. Because of
// *    this, the F can also stand for fiction, because at the time of writing this
// *    description, and having neither of those 2 things, that may be all this amounts
// *    to being.
// *
// *  Background:
// *    https://github.com/briefnotion/Fled/blob/master/Description%20and%20Background.txt
// *
// ***************************************************************************************


#include <stdio.h>
#include <math.h>
#include <future>
#include <wiringPi.h>
#include <string>
#include <chrono>
#include <unistd.h>
#include <termio.h>
#include <vector>
#include <iostream>


// Distros: Jeremy Garff <jer @ jers.net>
//  Zips at https://github.com/jgarff/rpi_ws281x
//static char VERSION[] = "XX.YY.ZZ";
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>
#include <stdarg.h>
#include <getopt.h>

#include "clk.h"
#include "gpio.h"
#include "dma.h"
#include "pwm.h"
//#include "version.h"

#include "ws2811.h"

// Boost libraries
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>


// RASFled related header files
#include "definitions.h"
#include "helper.h"
#include "files.h"
#include "rasapi.h"
#include "consoleanddata.h"
#include "LEDstuff.h"
#include "fled_time.h"
#include "fledcore.h"
#include "timedeventsystem.h"
#include "animations.h"
#include "hardware_module_door.h"
#include "interface.h"



// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************


// ***************************************************************************************
// FUNCTION AND PROCEDURES
// ***************************************************************************************


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// Matrix Manipulation

// -------------------------------------------------------------------------------------
// Display Materix Prepare.

//  Copy the Prepared Matrix to the Display Matrix.
void MatrixPrepare(Console &cons, system_data &sdSysData, CRGB crgbPrepedMatrix[], int intLEDCOUNT, int* DisplayMatrix, int &mcount);

void MatxixFill(CRGB crgbPreparedMatix[], int intLEDCOUNT, CRGB crgbColor);



// -------------------------------------------------------------------------------------
// Console Update

// Reference for the amount for events running.
void store_event_counts(system_data &sdSysData, timed_event teEvent[]);


// ***************************************************************************************
// The Following chunk of code is what handles the imported library's ability to put the 
// lights on and off or whatever.  Will not pretend to understand it.  Instead, will 
// squish it down as much as possible so that I can pretend its not there.
// ***************************************************************************************
ws2811_t ledstring;
int *matrix;
static char running = 1;
void matrix_render(int led_count);
static void ctrl_c_handler(int signum);
static void setup_handlers(void);
void ledprep(ws2811_t *ws2811, int led_count);

// ***************************************************************************************



// ***************************************************************************************
// MAIN PROGRAM
// ***************************************************************************************

// ---------------------------------------------------------------------------------------

void shutdown();

// ---------------------------------------------------------------------------------------
void setup();

// ---------------------------------------------------------------------------------------
// Global function for Main Loop Threads
// By passing the global variable, difficult to work with, ledstring to the, just as 
//  difficult to work with, ws2811_render routine, all led and values will be transmitted 
//  to the lights on a seperate thread.
void proc_render_thread();

void raw_window_player_draw_frame(string Buffer);

// ---------------------------------------------------------------------------------------
// MAIN LOOP
int loop();

// ---------------------------------------------------------------------------------------
int main(int argc, char *argv[]);