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
// *  PROJECTID: gi6$b*E>*q%;    Revision: 00000000.53A
// *  TEST CODE:                 QACODE: A565              CENSORCODE: EQK6}Lc`:Eg>
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
#include <pthread.h>
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


// RASFled related header files
#include "definitions.h"
#include "helper.h"
#include "files.h"
#include "consoleanddata.h"
#include "LEDstuff.h"
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
void MatrixPrepare(Console cons, system_data &sdSysData, CRGB crgbPrepedMatrix[], int intLEDCOUNT, int* DisplayMatrix, int &mcount)
{
  for (int lcount = 0; lcount < intLEDCOUNT; lcount++)
  {
    // Normal Display
    DisplayMatrix[mcount]=crgbPrepedMatrix[lcount].b + (crgbPrepedMatrix[lcount].g << 8) + (crgbPrepedMatrix[lcount].r << 16) + (0 << 24);
    mcount++;
  }
}

void MatxixFill(CRGB crgbPreparedMatix[], int intLEDCOUNT, CRGB crgbColor)
{
  for (int lcount = 0; lcount < intLEDCOUNT; lcount++)
  {
    if ((lcount +1 ) == 1)
    {
      crgbPreparedMatix[lcount] = CRGB(25,0,25);
    }
    else if (((lcount +1 ) % 100) == 0)
    {
      crgbPreparedMatix[lcount] = CRGB(25,25,0);
    }
    else if (((lcount +1 ) % 50) == 0)
    {
      crgbPreparedMatix[lcount] = CRGB(25,0,0);
    }
    else if (((lcount +1 ) % 20) == 0)
    {
      crgbPreparedMatix[lcount] = CRGB(0,25,0);
    }
    else if (((lcount +1 ) % 5) == 0)
    {
      crgbPreparedMatix[lcount] = CRGB(0,0,25);
    }
    else
    {
      crgbPreparedMatix[lcount] = crgbColor;
    }
  }
}



// -------------------------------------------------------------------------------------
// Console Update

// Reference for the amount for events running.
void store_event_counts(system_data &sdSysData, timed_event teEvent[])
{
  for(int channel=0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(channel) = 0;
  }

  for(int group=0; group<sdSysData.CONFIG.LED_MAIN.at(0).g_size(); group++)
  {
    for(int strip=0; strip<sdSysData.CONFIG.LED_MAIN.at(0).s_size(group); strip++)
    {
      int channel = sdSysData.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.at(strip).intCHANNEL;

      sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(group) 
        = sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(group) 
        + (teEvent[channel].teDATA.size());
    }
  }
}


// ***************************************************************************************
// The Following chunk of code is what handles the imported library's ability to put the 
// lights on and off or whatever.  Will not pretend to understand it.  Instead, will 
// squish it down as much as possible so that I can pretend its not there.
// ***************************************************************************************
ws2811_t ledstring;
int *matrix;
static char running = 1;
void matrix_render(int led_count)
{
    int x;

    for (x = 0; x < led_count; x++)
    {
		ledstring.channel[0].leds[x] = matrix[x];
    }
}
static void ctrl_c_handler(int signum)
{
	(void)(signum);
    running = 0;
}
static void setup_handlers(void)
{
    struct sigaction sa;
      sa.sa_handler = ctrl_c_handler;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
}
void ledprep(ws2811_t *ws2811, int led_count)
{
	ws2811->channel[0].count = led_count;
}

// ***************************************************************************************



// ***************************************************************************************
// MAIN PROGRAM
// ***************************************************************************************

// ---------------------------------------------------------------------------------------

void shutdown()
{
  // Shutdown the LED strip routine.
  ws2811_fini(&ledstring);

  // Shutdown NCurses.
  endwin();
}

// ---------------------------------------------------------------------------------------
void setup()
{
  // Keeping this for now to remind me of what I haven't implementd, from the preport, 
  //  yet.
}

// ---------------------------------------------------------------------------------------
// Global function for Main Loop
// By passing the global variable, difficult to work with, ledstring to the, just as 
//  difficult to work with, ws2811_render routine, all led and values will be transmitted 
//  to the lights on a seperate thread.
void *proc_render_thread(void *ptr)
{
  int ret = 0;  // contains fail or pass status of the render routine.
  ret = ws2811_render(&ledstring);  // Send values of ledstring to hardware.
  return (void *)ret; // return ws2811_render status.
}

// ---------------------------------------------------------------------------------------
// MAIN LOOP
int loop()
//  Main Loop:
//    Events and Light Path animations should only be called when their time is up.

// This was once the main() program.  Ever since we abandoned global variable, the setup 
//  portion of this program has become convoluted.  It could use a good reorganize and 
//  maybe a way to get some of this stuff out, subroutine, much of these routines. 
{
  using namespace std;

  // ---------------------------------------------------------------------------------------
  // Create Threads
  pthread_t thread_render;

  // Define System Data and Console
  int return_code = 0;
  Console cons;
  system_data sdSystem;
  int intRet = wiringPiSetup(); 

  // Disposable Variables
  int count  = 0;
  
  // ---------------------------------------------------------------------------------------
  // Initialize the console

  // Prep Timers
  cons.console_timer.set(SCREENUPDATEDELAY);

  // Init and prepare screen
  initscr();
  cons.Screen.init();   // Prepare console.
  //cons.Screen.set(CONSOLESPLITSIZE);
  cons.set_screen(sdSystem);
  
  // Print Start Info
  cons.printi("Console Initialized ...  OK");
  cons.printi("");
  cons.printi("RasFLED");
  cons.printi("  'X'    - Exit");
  cons.printi("  'help' - Command List)");
  cons.printi("");
  
  // Console Key Watch
  cons.keywatch.set((int)KEYEXIT,2);  // Exit the program.

  // Debugging keys
  cons.keywatch.set((int)KEYDEBUG,2);  // Testing Mode Toggle
  cons.keywatch.set((int)KEYLEDTEST,2);  // Test LEDs.  Turn all on low level white.
  cons.keywatch.set((int)'1',2);  // Door Toggles
  cons.keywatch.set((int)'2',2);  // 
  cons.keywatch.set((int)'3',2);  // 
  cons.keywatch.set((int)'4',2);  // 

  // Console resize key (automatic detection)
  cons.keywatch.set(KEYRESIZE,2);

  // ---------------------------------------------------------------------------------------
  // System Init

  cons.printi("Initializing Timer ...");
  FledTime tmeFled;
  tmeFled.set();

  // Sleeping Loop Variables
  tmeFled.setframetime();
  
  double tmeStartTime = tmeFled.tmeFrameMillis;
  unsigned long tmeCurrentMillis = (unsigned long)tmeFled.tmeFrameMillis;
  sdSystem.store_Current_Frame_Time(tmeCurrentMillis);

  // ---------------------------------------------------------------------------------------
  // Load system configuration and set data
  
  cons.printi("Loading Configuration and Initializing LED Arrays ...");

  // Set Running Color to white.
  sdSystem.init_running_color_list();
  sdSystem.set_running_color(CRGB(32,32,32),"White");

  // File System
  string Working_Directory = FILES_DIRECTORY;
  check_create_working_dir(cons);

  // Create Filenames as Variables
  string Configuration_Filename = Working_Directory + FILES_CONFIGURATION;
  string Running_State_Filename = Working_Directory + FILES_RUNNING_STATE_SAVE;

  // Loading Configuration from files
  // yes, it resaves the file.  as is for now.
  if (load_configuration(cons, sdSystem, Configuration_Filename) != true)
  {
    // generate a configuration file to be edited from static defaults
    cons.printi("  Configuration file not loaded.  Generating Configuration File.");
    if (save_configuration(cons, sdSystem, Configuration_Filename) == true)
    {
      cons.printi("    Configuration file created.");
    }
    else
    {
      cons.printi("    Configuration file not created.");
    }
  }

  // Loading Running State
  cons.printi("  Loading running state ...");
  // yes, it resaves the file.  as is for now.
  if (load_saved_running_state(cons, sdSystem, Running_State_Filename) != true)
  {
    cons.printi("    Running state file not loaded.");
  }

  // ---------------------------------------------------------------------------------------
  // LED Library Vars and Init
  cons.printi("Initializing LEDS ...");

  int led_count = sdSystem.CONFIG.LED_MAIN.at(0).led_count();

  ledstring.freq = TARGET_FREQ;
  ledstring.dmanum = DMA;
  ledstring.channel[0].gpionum = GPIO_PIN;
  ledstring.channel[0].count = led_count;
  ledstring.channel[0].brightness = 255;
  ledstring.channel[0].invert = 0;
  ledstring.channel[0].strip_type = STRIP_TYPE;

  ws2811_return_t ret;
  ledprep(&ledstring, led_count);
  matrix = (int*)malloc(sizeof(ws2811_led_t) * led_count);
  setup_handlers();
  if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS)
  {
    fprintf(stderr, "ws2811_init failed: %s\n", ws2811_get_return_t_str(ret));
    //return ret;
    //cons.printi("ws2811_init failed: " + ws2811_get_return_t_str(ret))
    return_code = (int)ret;
  }
  else
  {
    cons.printi("  LED count: " + to_string(led_count));
  }

  // ---------------------------------------------------------------------------------------

  // Define Door Sensors.
  cons.printi("Initializing Hardware Sensors ...");
  for(int x=0; x<sdSystem.CONFIG.iNUM_SWITCHES; x++)
  {
    pinMode(sdSystem.CONFIG.vSWITCH_PIN_MAP.at(x).pin, INPUT);
    pullUpDnControl(sdSystem.CONFIG.vSWITCH_PIN_MAP.at(x).pin, PUD_UP);
  }

  // -------------------------------------------------------------------------------------
  // Door Sensor
  cons.printi("Initializing Hardware Sensor Interface ...");

  // Initialize Switches
  hardware_monitor tmpSwitch;
  tmpSwitch.set(true, sdSystem.tmeCURRENT_FRAME_TIME, 50, true);
  for(int x=0; x<sdSystem.CONFIG.iNUM_SWITCHES; x++)
  {
    sdSystem.CONFIG.vhwDOORS.push_back(tmpSwitch);
  }

  // ---------------------------------------------------------------------------------------
  // The Player
  fstream fsPlayer;
  bool sucess = false;

  string Playlist_Filename = Working_Directory + FILES_PLAYLIST;

  cons.printi("Initializing Player ...");
  if (load_playlist(cons, sdSystem, Playlist_Filename) == true)
  {
    if (cons.play_next_movie(fsPlayer) == true)
    {
      //cons.printi("  Loading Reel");
    }
    else
    { 
      cons.the_player.booDisable = true;
      cons.printi("FAILED - (Initializing Player)");
    }
  }

  // ---------------------------------------------------------------------------------------
  // TEST AREA

  /*  
  WORDLINE testline;
  std::string strtestline = "1 this is a  Test    to see what happens.";
  testline.storeline(strtestline);
  cons.printi("'" + strtestline + "'");
  while(testline.empty() == false)
  {
    //cons.printi(std::to_string( testline.size()) );
    cons.printi("'" + testline.pop() + "'");
    //cons.printi(" : ");
  }
  */

  // ---------------------------------------------------------------------------------------
  // Define the Supid Random Numbers
  cons.printi("Initializing Random Number Generator ...");
  stupid_random sRND;
  // Initialize the Stupid Random Numbers
  sRND.set();

  // ---------------------------------------------------------------------------------------
  // Light Strip Event System
  cons.printi("Initializing Event System ...");

  // count number of strips
  // Count the amount of events needed
  count = 0;
  for(int x=0; x<sdSystem.CONFIG.LED_MAIN.at(0).g_size(); x++)
  {
    for(int y=0; y<sdSystem.CONFIG.LED_MAIN.at(0).s_size(x); y++)
    {
      count++;
    }
  }
  sdSystem.CONFIG.iNUM_CHANNELS = count;

  // Create event array
  timed_event teEvents[sdSystem.CONFIG.iNUM_CHANNELS];

  // Create and initialize each event (may not be needed anymore)
  // Tell each strip whitch event is associated to it.
  int channel = 0;
  for(int x=0; x<sdSystem.CONFIG.LED_MAIN.at(0).g_size(); x++)
  {
    for(int y=0; y<sdSystem.CONFIG.LED_MAIN.at(0).s_size(x); y++)
    {
      teEvents[channel].create(sdSystem.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(x).vLED_STRIPS.at(y).led_count());
      sdSystem.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(x).vLED_STRIPS.at(y).intCHANNEL = channel;
      channel++;
    }
  }

  // Set a few variables in sdSystem for the console display,
  sdSystem.init();

  // -------------------------------------------------------------------------------------
  // Aditional DEBUG line that could only be set after the channels were created.

  cons.keywatch.set((int)KEYLEDDRCYCL,sdSystem.CONFIG.iNUM_CHANNELS + 1);  // Test Doors

  // -------------------------------------------------------------------------------------
  /*
  // False events for testing.
  teEvent[lsStrips[0].Cl].set(tmeCurrentMillis, 50, 50, 20, AnEvSweep, AnPiPulse, false, CRGB(255, 0, 0), CRGB(255, 0, 0), CRGB(255, 0, 0), CRGB(255, 0, 0), 0, 10, false, false);
  teEvent[lsStrips[2].Cl].set(tmeCurrentMillis, 50, 50, 20, AnEvSweep, AnPiPulse, false, CRGB(255, 0, 0), CRGB(255, 0, 0), CRGB(255, 0, 0), CRGB(255, 0, 0), 0, 10, false, false);
  teEvent[lsStrips[4].Cl].set(tmeCurrentMillis, 50, 50, 20, AnEvSweep, AnPiPulse, false, CRGB(255, 0, 0), CRGB(255, 0, 0), CRGB(255, 0, 0), CRGB(255, 0, 0), 0, 10, false, false);
  teEvent[lsStrips[6].Cl].set(tmeCurrentMillis, 50, 50, 20, AnEvSweep, AnPiPulse, false, CRGB(255, 0, 0), CRGB(255, 0, 0), CRGB(255, 0, 0), CRGB(255, 0, 0), 0, 10, false, false);
  */

  // ---------------------------------------------------------------------------------------
  //  Repeating Sleeping Loop until eXit is triggered.
  // ---------------------------------------------------------------------------------------

  cons.printi("Starting System ...");

  while( cons.keywatch.get(KEYEXIT) == 0 )
  {
    // --- Prpare the Loop ---

    // Measure how much time has passed since last frame time read.
    // Store the amount of time it tooke to run a frame
    sdSystem.store_cycle_time(tmeFled.tmeFrameElapse());

    //  Get current time.  This will be our timeframe to work in.
    tmeFled.setframetime();
    tmeCurrentMillis = (unsigned long)tmeFled.tmeFrameMillis;
    sdSystem.store_Current_Frame_Time(tmeCurrentMillis);
    
    //  Only update the hardware when changes have been detected.
    //    This vabiable will be checked at the end of the loop.  If nothing was updated,
    //    the loop will just walk on past any hardware updates that would otherwise be
    //    sent.

    // MOVE RENAME ELIMINATE ??? !!!
    bool booUpdate = false;

    // Read values of switches
    for(int x=0; x<sdSystem.CONFIG.iNUM_SWITCHES; x++)
    {
      sdSystem.CONFIG.vSWITCH_PIN_MAP.at(x).value = digitalRead(sdSystem.CONFIG.vSWITCH_PIN_MAP.at(x).pin);
    }

    // Override the digital pins if in debugging mode.
    if(cons.keywatch.getnoreset(KEYDEBUG) == 1)
    {
      // Toggle on and off the door sensors with keyboard.
      sdSystem.CONFIG.vSWITCH_PIN_MAP.at(0).value = cons.keywatch.getTF('1');
      sdSystem.CONFIG.vSWITCH_PIN_MAP.at(1).value = cons.keywatch.getTF('2');
      sdSystem.CONFIG.vSWITCH_PIN_MAP.at(2).value = cons.keywatch.getTF('3');
      sdSystem.CONFIG.vSWITCH_PIN_MAP.at(3).value = cons.keywatch.getTF('4');
    }

    // Check the doors and start or end all animations
    v_DoorMonitorAndAnimationControlModule(cons, sdSystem, teEvents, tmeCurrentMillis);

    // ---------------------------------------------------------------------------------------
    // --- Check and Execute Timed Events That Are Ready ---

    //  Run ALL GLOBAL Timed Events
    teSystem(cons, sdSystem, teEvents, tmeCurrentMillis);
  
    for(int group=0; group < sdSystem.CONFIG.LED_MAIN.at(0).g_size(); group++)
    {
      for(int strip=0; strip < sdSystem.CONFIG.LED_MAIN.at(0).s_size(group); strip++)
      {
        int channel = sdSystem.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.at(strip).intCHANNEL;
        sdSystem.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.at(strip).booARRAY_UPDATED 
          = teEvents[channel].execute(cons, sdSystem, sRND, 
              sdSystem.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.at(strip).crgbARRAY, 
              tmeCurrentMillis);
      }
    }


    // ---------------------------------------------------------------------------------------
    // Render all the LEDs if changes have been made.

    // --- Execute LED Hardware Changes If Anything Was Updated ---
    //  For now we are working with just one big LED strip.  So, just check to see if anything
    //    changed.  Then, Redraw the entire strip. 

    // Update?
    for(int group=0; group < sdSystem.CONFIG.LED_MAIN.at(0).g_size(); group++)
    {
      for(int strip=0; strip < sdSystem.CONFIG.LED_MAIN.at(0).s_size(group); strip++)
      {
        if (sdSystem.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.at(strip).booARRAY_UPDATED == true)
        {
          booUpdate = true;
        }
      }
    }


    if (booUpdate == true)
    {
      //  Do I need to move the whole thing or can I just move the changed pixels?

      int mcount = 0;

      // If debug mode Display all lights static color are selectted, replace all generated led colors
      // with a static color
      if ((cons.keywatch.getnoreset(KEYDEBUG) != 0) && (cons.keywatch.get(KEYLEDTEST) !=0))
      {
        for(int group=0; group < sdSystem.CONFIG.LED_MAIN.at(0).g_size(); group++)
        {
          for(int strip=0; strip < sdSystem.CONFIG.LED_MAIN.at(0).s_size(group); strip++)
          {
            MatxixFill(sdSystem.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.at(strip).crgbARRAY, 
            sdSystem.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.at(strip).led_count(), 
            CRGB(25,25,25));
          }
        }
      }
      
      // Copy the prepaird Matrixes to the display matrix
      if((cons.keywatch.getnoreset(KEYDEBUG) == 0) || (cons.keywatch.get(KEYLEDDRCYCL) == 0))
      {
        for(int group=0; group < sdSystem.CONFIG.LED_MAIN.at(0).g_size(); group++)
        {
          for(int strip=0; strip < sdSystem.CONFIG.LED_MAIN.at(0).s_size(group); strip++)
          {
            // Build LED Array to display
            // FUTER !!! - Only update portions of LED array that has changed. First, group. Second individual LEDs.
                // Probably not needed because I'v only seen .5ms time needed for full matrix copy.
            MatrixPrepare(cons, sdSystem, 
                  sdSystem.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.at(strip).crgbARRAY, 
                  sdSystem.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.at(strip).led_count(), 
                  matrix, mcount);
          }
        }
      }
      else
      {
        // Build TEST array to display
        int selected_test_array = cons.keywatch.get(KEYLEDDRCYCL) - 1;
        int pos = 0;
        int g = 0; 
        int s = 0;

        // Find Strip
        for(int group=0; group < sdSystem.CONFIG.LED_MAIN.at(0).g_size(); group++)
        {
          for(int strip=0; strip < sdSystem.CONFIG.LED_MAIN.at(0).s_size(group); strip++)
          {
            if (selected_test_array == pos)
            {
              g = group;
              s = strip;
              sdSystem.t_group = group;
              sdSystem.t_strip = strip;
            }
            pos++;
          }
        }

        // Draw fround strip
        MatrixPrepare(cons, sdSystem, 
                          sdSystem.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(g).vLED_STRIPS.at(s).crgbARRAY, 
                          sdSystem.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(g).vLED_STRIPS.at(s).led_count(), 
                          matrix, mcount);
      }


      // LED Library Renderer -- Recommend: DON'T TOUCH        
      matrix_render(led_count);

      // Create a seperate thread only to render the LEDs with the hardware.  This process
      //  is very intensive for the system and is only one way.  The render thread only needs 
      //  to rejoin with the main program, at the end of the main loop, to signify its 
      //  completion, so that the loop can restart and begin computing its values and colors 
      //  again. 
      // A render thread should not be created if no changes have been made to the led values. 
      return_code = pthread_create(&thread_render, NULL, *proc_render_thread, (void *)  &ledstring);
      if (return_code != 0)
      {
        cons.printi("Thread Create Error");
      }
    }


    // ---------------------------------------------------------------------------------------
    // Now that we have done all the hard work, read hardware, computed, generated, displayed 
    // all the lights, we will take the latter clock cycles to get keybord input and update 
    // console with status and so on. 

    // Read Hardware Status before printing to screen.
    sdSystem.read_hardware_status(1000);

    // --- Grabbing Data From Keyboard and update whatever is associated to the key pressed.
    //cons.readkeyboardinput();
    cons.readkeyboardinput2();

    // Process keyboard info before displaying the screen.
    // This will handle special redraw events such as screen resize.
    cons.processkeyboadinput();
    cons.processmouseinput(sdSystem);
    processcommandlineinput(cons, sdSystem, tmeCurrentMillis, teEvents);
    extraanimationdoorcheck(cons, sdSystem, tmeCurrentMillis, teEvents);

    // Refresh console data storeage from main program. This will be a pass through buffer. 
    // so the console will not have to access any real data. 
    sdSystem.store_door_switch_states();
    store_event_counts(sdSystem, teEvents);

    // Call the Interface routine. (IO from user)
    cons.display(fsPlayer, sdSystem, tmeCurrentMillis);

      // Also delayed, File maintenance.
    if (sdSystem.booRunning_State_File_Dirty == true)
    {
      save_running_state(cons, sdSystem, Running_State_Filename);

      // set false even if there was a save error to avoid repeats.
      sdSystem.booRunning_State_File_Dirty = false;
    }

    // Reconnect the Renderi Thread.
    //  Check for Render Errors.
    if (booUpdate == true)
    {
      pthread_join(thread_render, (void **)&return_code);
      if (return_code != 0)
      {
        string ret_code = ws2811_get_return_t_str(ret);
        cons.printi("ws2811_render failed: " + ret_code);
      }
    }

    // Consider aborts on errors.
    if (return_code != 0)
    {
      cons.keywatch.in(KEYEXIT);
    }


    // ---------------------------------------------------------------------------------------
    // Now that the complete cycle is over, we need figure out how much time is remaining in 
    // the cycle and go to sleep for the appropriate amount of time. 
    // Calculate times and sleep till next frame is ready.

    // For the next display cycle, we need to store info to the console about how things went.
    // Determine how long it took to compute before sleep.
    sdSystem.store_compute_time(tmeFled.tmeFrameElapse());
    
    // Determine how long to sleep and then sleep.
    usleep (1000 * sdSystem.getsleeptime(sdSystem.CONFIG.iFRAMES_PER_SECOND));

  }// End MAIN CYCLE WHILE loop.

  // ---------------------------------------------------------------------------------------
  // If we are here, then we are closing the program.
  
  // Shutdown.
  shutdown();

  printf("\033[?1003l\n"); // Disable mouse movement events, as l = low

  if(sdSystem.booREBOOT == false)
  {
    // Just print we have ended the program.
    printf ("\nRasFLED Loop ... Exit\n");
  }
  else
  {
    // Just print are restarting the program.
    printf ("\nRasFLED Loop ... Rebooting\n");
    return_code = 9999;
  }

  return return_code;
}

// ---------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  int ret = 1;  // Run

  printf("RasFLED Start ... \n");

  // Setup the Program
  setup();

  // Start the main loop.
  while (ret == 1)
  {
    ret = loop();

    // Reboot?
    if(ret == 9999)
    {
      ret = 1;
    }
  }

  printf("Exit Code: %d: ", ret);

  if (ret == 0)
  {
    printf("Standard Exit\n");
  }
  else if (ret == 1)
  {
    printf("Exit For Reboot\n");
  }
  else
  {
    printf("Non Standard Exit\n");
  }

  // Exit the program.
  printf("RasFLED ... Exit\n");
  return ret;
  
}