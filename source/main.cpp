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

#ifndef MAIN_CPP
#define MAIN_CPP

#include "main.h"

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
void MatrixPrepare(Console &cons, system_data &sdSysData, CRGB crgbPrepedMatrix[], int intLEDCOUNT, int* DisplayMatrix, int &mcount)
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
void store_event_counts(system_data &sdSysData, ANIMATION_HANDLER Animations)
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

      sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(group) =
                  sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(group) +
                  (Animations.EVENTS[channel].teDATA.size());

    }
  }
}


// ***************************************************************************************
// The Following chunk of code is what handles the imported library's ability to put the 
// lights on and off or whatever.  Will not pretend to understand it.  Instead, will 
// squish it down as much as possible so that I can pretend its not there.
// ***************************************************************************************
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
// Global function for Main Loop Threads
// By passing the global variable, difficult to work with, ledstring to the, just as 
//  difficult to work with, ws2811_render routine, all led and values will be transmitted 
//  to the lights on a seperate thread.
void proc_render_thread()
{
  int ret = 0;  // contains fail or pass status of the render routine.
  ret = ws2811_render(&ledstring);  // Send values of ledstring to hardware.
}

void raw_window_player_draw_frame(string Buffer)
// Simply printf the Buffer string to the screen.
{
  printf("%s", Buffer.c_str());
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

  // Prepare Shared Memory Space.
  boost::interprocess::shared_memory_object shdmem{boost::interprocess::open_or_create, "Airband", boost::interprocess::read_write};
  shdmem.truncate(1024);
  boost::interprocess::mapped_region region_scan{shdmem, boost::interprocess::read_write};
  
  // ---------------------------------------------------------------------------------------
  // Is_Ready varibles for main loop.
  TIMED_IS_READY  input_from_switches;    // Delay for the hardware switches.
  TIMED_IS_READY  events_and_render;      // Delay for the events and render system.
  TIMED_IS_READY  input_from_user;        // Delay for the input from mouse and keyboard.
  TIMED_IS_READY  display;                // Delay for displaying information on the console.
  unsigned long   tmeSleep_Wake_time = 0; // Will contain time the cycle sleeper wakes.

  EFFICIANTCY_TIMER effi_timer;           // Diagnostic timer to measure cycle times.

  // Create Threads
  future<void> thread_render; // The thread containing function to send the led color array 
                              //  to the leds.
  bool thread_render_running = false; // Set to true when thread is active.

  // Control for the output thread. 
  //  The only part of output asynced is the printf function of the player 1001 type.
  //  Everything else in output will be paused if async is actively running and does 
  //  not need to be asynced because the interface is fast enough to run within one 
  //  cycle.
  future<void> thread_output;         // The thread containing function to printf a large 
                                      //  string.
  bool thread_output_running = false; // Set to true when thread is active.
  string raw_string_buffer = "";      // A string buffer to contain the Screen buffer. 
                                      //  Redundant. Possibly consolidate the line. 

  // Define System Data and Console
  int return_code = 0;
  Console cons;
  system_data sdSystem;
  
    // Open Shared memory regions to manager
  sdSystem.API_CHANNEL.open(region_scan);

  // Initialize wiring pi
  int intRet = wiringPiSetup(); 

  // Set is_ready variables
  input_from_switches.set(20);
  events_and_render.set(get_frame_interval(sdSystem.CONFIG.iFRAMES_PER_SECOND));
  input_from_user.set(100);
  display.set(SCREENUPDATEDELAY);

  // Console sub timer. Just a little faster to prevent blips.
  cons.Console_Display.set(SCREENUPDATEDELAY-1);

  // System LogFile Variables
  FILE_WATCH watcher_daemon_log;
  watcher_daemon_log.start(FILES_DEAMON_LOG);

  // System LogFile Variables
  FILE_WATCH watcher_aircraft_json;
  watcher_aircraft_json.PROP.READ_FROM_BEGINNING = true;
  watcher_aircraft_json.PROP.WATCH_SIZE_CHANGE = false;
  watcher_aircraft_json.PROP.WATCH_TIME_CHANGE = true;
  watcher_aircraft_json.start(FILES_AIRCRAFT_JSON);

  // Disposable Variables
  int count  = 0;
  
  // ---------------------------------------------------------------------------------------
  // Initialize the console

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

  // ---------------------------------------------------------------------------------------

  // Initialize Alert System
  cons.printi("Initializing Alert System ...");

  // Prepare Alerts
  sdSystem.ALERTS.PROP.SWITCH_COUNT = sdSystem.CONFIG.iNUM_SWITCHES;
  sdSystem.ALERTS.create();
  cons.printi("Initializing Timer ...");
  FledTime tmeFled;

  // Sleeping Loop Variables
  tmeFled.setframetime();
  
  double tmeStartTime = tmeFled.tmeFrameMillis;
  unsigned long tmeCurrentMillis = (unsigned long)tmeFled.tmeFrameMillis;
  sdSystem.store_Current_Frame_Time(tmeCurrentMillis);

  // ---------------------------------------------------------------------------------------
  // Load system configuration and set data
  
  cons.printi("Loading Configuration ...");

  // Set Running Color to white.
  sdSystem.init_running_color_list();
  sdSystem.set_running_color(CRGB(32,32,32),"White");

  // File System
  string Working_Directory = FILES_DIRECTORY;
  string Configuration_Files_JSON = FILES_CONFIGURATION;
  string Animations_Library_JSON = FILES_ANIMATIONS;
  //check_create_working_dir(FILES_DIRECTORY);

  //  -----
  // Create Filenames as Variables
  string Running_State_Filename = Working_Directory + FILES_RUNNING_STATE_SAVE;

  // Loading Configuration from files
  // yes, it resaves the file.  as is for now.

  if (load_json_configuration(cons, sdSystem, Working_Directory, Configuration_Files_JSON) == true)
  {
    cons.printi("  Configuration file loaded.");
  }
  else
  {
    cons.printi("  Configuration file not loaded.  Generating Working Configuration File.");
    sdSystem.ALERTS.add_generic_alert("Configuration file not loaded.  Generating Working Configuration File.");

    if (save_json_configuration(cons, sdSystem, Working_Directory, Configuration_Files_JSON) == true)
    {
      cons.printi("    Configuration file created.");
      sdSystem.ALERTS.add_generic_alert("Configuration file created.");
    }
    else
    {
      cons.printi("    Configuration file not created.");
      sdSystem.ALERTS.add_generic_alert("Configuration file not created.");
    }
  }
  
  // Loading Running State
  cons.printi("  Loading running state ...");
  // yes, it resaves the file.  as is for now.
  if (load_saved_running_state_json(cons, sdSystem, Running_State_Filename) != true)
  {
    cons.printi("    Running state file not loaded.");
    sdSystem.ALERTS.add_generic_alert("Running state file not loaded.");
  }

  // Loading Animations Library.
  ANIMATION_HANDLER animations;

  animations.create_events(sdSystem);
  
  if (animations.load_collections(Working_Directory, Animations_Library_JSON) == true)
  {
    cons.printi("  Animations file loaded.");
  }
  else
  {
    cons.printi("    Animations file not loaded.");
    sdSystem.ALERTS.add_generic_alert("Animations file not loaded.");
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
  // The Player
  fstream fsPlayer;
  bool sucess = false;

  string Playlist_Filename = Working_Directory + FILES_PLAYLIST;

  cons.printi("Initializing Player ...");
  if (load_playlist_json(cons, sdSystem, Playlist_Filename) == true)
  {
    if (cons.play_next_movie(fsPlayer) == true)
    {
      //cons.printi("  Loading Reel");
    }
    else
    { 
      cons.the_player.booDisable = true;
      cons.printi("FAILED - (Initializing Player)");
      sdSystem.ALERTS.add_generic_alert("FAILED - (Initializing Player)");
    }
  }

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

  // Set a few variables in sdSystem for the console display,
  sdSystem.init();

  // -------------------------------------------------------------------------------------
  // Aditional DEBUG line that could only be set after the channels were created.

  cons.keywatch.set((int)KEYLEDDRCYCL,sdSystem.CONFIG.iNUM_CHANNELS + 1);  // Test Doors

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
  tmpSwitch.set(true, sdSystem.tmeCURRENT_FRAME_TIME, DOOR_SWITCH_LEEWAY_TIME, true);
  for(int x=0; x<sdSystem.CONFIG.iNUM_SWITCHES; x++)
  {
    sdSystem.CONFIG.vhwDOORS.push_back(tmpSwitch);
  }

  // -------------------------------------------------------------------------------------

  // Start Power On Animation
  process_power_animation(cons, sdSystem, tmeCurrentMillis, animations, CRGB(0, 0, 25));
  
  // ---------------------------------------------------------------------------------------
  //  Repeating Sleeping Loop until eXit is triggered.
  // ---------------------------------------------------------------------------------------

  cons.printi("Starting System ...");

  // Start the the compute timer (stopwatch) for first iteration. 
  effi_timer.start_timer((unsigned long)tmeFled.tmeFrameMillis);
  
  // **************************************************************************************
  // **************************************************************************************
  // **************************************************************************************

  // MAIN LOOP START
  while( cons.keywatch.get(KEYEXIT) == 0 )
  {
    // Close all completed and active threads after sleep cycle is complete.

    // Before starting a new loop, close the render thread from the previous loop, if 
    //  render is complete
    if(thread_render_running == true)
    // Check to see if render thread was started before checking the completion status.
    {
      if(thread_render.wait_for(0ms) == future_status::ready)
      // Check to verify the thread is complete before allowing the render to start again. 
      {
        thread_render_running = false;
      }
    }

    // Before starting a new loop, close the console thread from the previous loop, if 
    //  data being printed to the screen has completed.
    if(thread_output_running == true)
    // Check to see if output thread was started before checking the completion status.
    {
      if(thread_output.wait_for(0ms) == future_status::ready)
      // Check to verify thte thread is complete before allowing the console to be updated again. 
      {
        thread_output_running = false;
      }
    }

    // --- Prpare the Loop ---

    //  Get current time.  This will be our timeframe to work in.
    tmeFled.setframetime();
    tmeCurrentMillis = (unsigned long)tmeFled.tmeFrameMillis;
    sdSystem.store_Current_Frame_Time(tmeCurrentMillis);
    
    //  Only update the hardware when changes have been detected.
    //    This vabiable will be checked at the end of the loop.  If nothing was updated,
    //    the loop will just walk on past any hardware updates that would otherwise be
    //    sent.

     // Are switches ready -----------------
    if (input_from_switches.is_ready(tmeCurrentMillis) == true)
    {    
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
      v_DoorMonitorAndAnimationControlModule2(cons, sdSystem, animations, tmeCurrentMillis);

    } // Are switches ready -----------------

    // ---------------------------------------------------------------------------------------
    // --- Check and Execute Timed Events That Are Ready ---

    // Is Events and Render ready -----------------
    if (events_and_render.is_ready(tmeCurrentMillis) == true)
    {
      // MOVE RENAME ELIMINATE ??? !!!
      bool booUpdate = false;

      //  Run ALL GLOBAL Timed Events
      animations.process_events(sdSystem, tmeCurrentMillis);

      for(int group=0; group < sdSystem.CONFIG.LED_MAIN.at(0).g_size(); group++)
      {
        for(int strip=0; strip < sdSystem.CONFIG.LED_MAIN.at(0).s_size(group); strip++)
        {
          int channel = sdSystem.CONFIG.LED_MAIN[0].vLED_GROUPS[group].vLED_STRIPS[strip].intCHANNEL;

          sdSystem.CONFIG.LED_MAIN[0].vLED_GROUPS[group].vLED_STRIPS[strip].booARRAY_UPDATED 
            = animations.EVENTS[channel].execute2(cons, sdSystem, sRND, 
                sdSystem.CONFIG.LED_MAIN[0].vLED_GROUPS[group].vLED_STRIPS[strip].crgbARRAY, 
                tmeCurrentMillis);
        }
      }
      
      // ---------------------------------------------------------------------------------------
      // Render all the LEDs if changes have been made.

      // --- Execute LED Hardware Changes If Anything Was Updated ---
      //  For now we are working with just one big LED strip.  So, just check to see if anything
      //    changed.  Then, Redraw the entire strip. 

      // Calculate LED values and update if enabled.
      if (sdSystem.Lights_On == true)
      {
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
          
          // Copy the prepared Matrixes to the display matrix
          if((cons.keywatch.getnoreset(KEYDEBUG) == 0) || (cons.keywatch.get(KEYLEDDRCYCL) == 0))
          {
            for(int group=0; group < sdSystem.CONFIG.LED_MAIN.at(0).g_size(); group++)
            {
              for(int strip=0; strip < sdSystem.CONFIG.LED_MAIN.at(0).s_size(group); strip++)
              {
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

          //  Are the lights enable to display.       
          //    Lights off will not turn the lights off and clear their values.  
          //      Instead, transmitting those color are to the lights disabled.
          
          // LED Library Renderer -- Recommend: DON'T TOUCH
          matrix_render(led_count);
          
          // Create a seperate thread only to render the LEDs with the hardware.  This process
          //  is very intensive for the system and is only one way.  The render thread only needs 
          //  to rejoin with the main program, at the end of the main loop, to signify its 
          //  completion, so that the loop can restart and begin computing its values and colors 
          //  again. 
          // A render thread should not be created if no changes have been made to the led values.
          if (thread_render_running == false)
          {
            thread_render = async(proc_render_thread);
            thread_render_running = true;
          }
        }
      }
    } // Is Events and Render ready -----------------
     

    // ---------------------------------------------------------------------------------------
    // Now that we have done all the hard work, read hardware, computed, generated, displayed 
    // all the lights, we will take the latter clock cycles to get keybord input and update 
    // console with status and so on.

    // Get store information from APIs.
    //cons.printwait(to_string(sdSystem.get_API_info(region_scan)));
    sdSystem.get_API_info(region_scan);

    // Is Keyboard or Mouse read ready -----------------
    if (input_from_user.is_ready(tmeCurrentMillis) == true)
    {
      // Read Hardware Status before printing to screen.
      sdSystem.read_hardware_status(1000);

      // Read System log files
      while (watcher_daemon_log.line_avail() == true)
      {
        cons.Screen.Log_Screen_TEXT_BOX.add_line(tmeCurrentMillis, watcher_daemon_log.get_next_line());
      }

      // Read ADS-B Aircraft JSON
      if (watcher_aircraft_json.changed() == true)
      {
        sdSystem.AIRCRAFT_COORD.process(file_to_string(FILES_AIRCRAFT_JSON));
      }

      // --- Grabbing Data From Keyboard and update whatever is associated to the key pressed.
      cons.readkeyboardinput2();

      // Process keyboard info before displaying the screen.
      // This will handle special redraw events such as screen resize.
      cons.processkeyboadinput(sdSystem);
      cons.processmouseinput(sdSystem);

      processcommandlineinput(cons, sdSystem, tmeCurrentMillis, animations);
      extraanimationdoorcheck2(cons, sdSystem, tmeCurrentMillis, animations);
      
    } // Is Keyboard or Mouse read ready -----------------

    // Is display to console ready -----------------
    if (display.is_ready(tmeCurrentMillis) == true)
    {
      // Call the Interface routine. (IO from user)
      if (thread_output_running == false)
      // If thread is not running, then update the screen display terminal interface.
      //  After the interface has an update, see if the player has a frame left over inside.
      //  the buffer. 
      //  Only start a thread and pause future screen updateas if the buffer contains a movie 
      //  frame to be displayed.
      {
        // Refresh console data storeage from main program. This will be a pass through buffer. 
        // so the console will not have to access any real data. 
        sdSystem.store_door_switch_states();

        store_event_counts(sdSystem, animations);

        // Radio - Update all radio gadgets with new data.
        cons.update_freqency_gadgets(sdSystem);

        // ADS-B - Update all ADS-B gadgets with new data.
        cons.update_ADS_B_gadgets(tmeCurrentMillis, sdSystem);

        // Update Switches to Alert system.
        for (int door=0; door < sdSystem.CONFIG.vhwDOORS.size(); door++)
        {
          sdSystem.ALERTS.update_switch(door, sdSystem.CONFIG.vhwDOORS.at(door).booVALUE);
        }
        
        // Redraw the console screen with what the screen determines needs to be displayed.
        cons.display(fsPlayer, sdSystem, tmeCurrentMillis);

        if (cons.the_player.get_next_frame_draw_time() > 0)
        {
          display.set_earliest_ready_time(cons.the_player.get_next_frame_draw_time());
        }

        // If anything in the screen buffer is waiting to be displayed, start a new thread 
        //  then print out the data. Likely to take a long time so pause further screen 
        //  updates while thread is running.
        if (cons.Screen.buffer_active == true)
        {
          raw_string_buffer = cons.Screen.buffer();
          thread_output = async(raw_window_player_draw_frame, raw_string_buffer);

          thread_output_running = true;
          cons.Screen.buffer_active = false;     
        }
      }
      
      // Also delayed, File maintenance.
      if (sdSystem.booRunning_State_File_Dirty == true)
      {
        save_running_state_json(cons, sdSystem, Running_State_Filename);

        // set false even if there was a save error to avoid repeats.
        sdSystem.booRunning_State_File_Dirty = false;
      }
    } // Is display to console ready -----------------

    // ________________________
    
    // Comm port proccessing will be the slowest. Process here after work is done.
    // Display received messages.

    sdSystem.COMMS.cycle();

    for (int pos = 0; pos < sdSystem.COMMS.READ_FROM_COMM.size(); pos++)
    {
      cons.printwait(sdSystem.COMMS.READ_FROM_COMM[pos]);
    }

    sdSystem.CAR_INFO.process(sdSystem.COMMS);


    // ________________________

    // Consider aborts on errors.
    // Check every cycle.
    if (return_code != 0)
    {
      cons.keywatch.in(KEYEXIT);
    }

    // ---------------------------------------------------------------------------------------
    // Now that the complete cycle is over, we need figure out how much time is remaining in 
    // the cycle and go to sleep for the appropriate amount of time. 
    // Calculate times and sleep till next frame is ready.

    // Determine how long to sleep and then sleep by 
    //  finding the earliest sleep wake time.
    tmeSleep_Wake_time = input_from_switches.get_ready_time();   
    if (events_and_render.get_ready_time() < tmeSleep_Wake_time)
    {
      tmeSleep_Wake_time = events_and_render.get_ready_time();
    }
    if (input_from_user.get_ready_time() < tmeSleep_Wake_time)
    {
      tmeSleep_Wake_time = input_from_user.get_ready_time();
    }
    if (display.get_ready_time() < tmeSleep_Wake_time)
    {
      tmeSleep_Wake_time = display.get_ready_time();
    }

    // Measure how much time has passed since the previous time the program was at 
    //  this point and store that value to be displayed in diag.
    sdSystem.dblCYCLETIME.set_data(effi_timer.elapsed_time(tmeFled.now()));

    // Reset the the compute timer (stopwatch) and store the value before the program sleeps. 
    sdSystem.dblCOMPUTETIME.set_data(effi_timer.elapsed_timer_time(tmeFled.now()));

    // Determine how long the program will sleep, store the value to be displayed in diag, and put the cycle
    //  to sleep.
    usleep ((int)(1000 * sdSystem.store_sleep_time(sdSystem.get_sleep_time(tmeFled.now(), tmeSleep_Wake_time))));

    // Start the the compute timer (stopwatch) before the program as the program wakes to measure the amount of 
    //  time the compute cycle is. 
    effi_timer.start_timer(tmeFled.now());

  }// End MAIN CYCLE WHILE loop.

  // ---------------------------------------------------------------------------------------
  // If we are here, then we are closing the program.
  
  // Wait for threads to end before continuing to shutdown.

  if(thread_render_running == true)
  // Check to see if render thread was started before checking the completion status.
  {
    while(thread_render.wait_for(10ms) != future_status::ready)
    {
      cons.printi("Shutting thread down.");
    }
    thread_render_running = false;
  }

  if(thread_output_running == true)
  // Check to see if output thread was started before checking the completion status.
  {
    while(thread_output.wait_for(10ms) != future_status::ready)
    {
      cons.printi("Shutting thread down.");
    }
    thread_output_running = false;
  }

  // Remove Shared Memory (if not active)
  sdSystem.API_CHANNEL.close(region_scan);

  /*
  if (sdSystem.API_CHANNEL.get_binds(region_scan) == 0) // FIXME Reenable at some point.
  {
    cons.printi("Closing API.");
    boost::interprocess::shared_memory_object::remove("Airband");
  }
  else
  {
    cons.printi("Leaving API.");
  }
  */

  // Force removal becauese rtl_airband side not created
  boost::interprocess::shared_memory_object::remove("Airband");

  
  // Shutdown RPI.
  shutdown();

  // close open files
  watcher_daemon_log.stop();

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
    try
    {
      ret = loop();
    }
    catch (std::exception const& e)
    {
      printf("An Error has occured in the main loop.\n");
      printf("Error Code: %d\n", ret);
      ret = 0;
    }
    
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
  else if (ret == 2)
  {
    printf("Controled Exit\n");
  }
  else
  {
    printf("Non Standard Exit\n");
  }

  // Exit the program.
  printf("RasFLED ... Exit\n");
  return ret;
  
}




#endif