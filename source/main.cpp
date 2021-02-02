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
// *  PROJECTID: gi6$b*E>*q%;    Revision: 00000000.17A
// *  TEST CODE:                 QACODE: A565              CENSORCODE: EQK6}Lc`:Eg>
// *
// ***************************************************************************************
// *  Programmer Notes:
// *
// *            Coder:  Robert Lebowski
// *    Support Coder:  None
// *  --- Apnd:
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
// * V 0.17 _210202
// *    - Hazard Light placeholder created.
// *    - End all repeating non door animations command created.
// *    - "`" or reverse apostrophe or whatever that button left of the 1 on a US 
// *        keyboard is, will be the end command command. Still trying to come up with a 
// *        good command set.  Thought of the way it is now, early on, and it seems to 
// *        be working, for the most part, well now. 
// *    - Hazard, Pulses, and Overhead extra animation statuss are now being reported to 
// *        to the system varibles, in case I ever want show the status on the console. 
// *
// * V 0.16 _210201
// *    - Changed Debug to Diagnosis, because debug info really isn't being shown. 
// *    - Added a DIAG indicator. 
// *    - Added a line to show command line size. 
// *    - Updated the SetToEnd documentation.
// *    - Created an Overhead Illumination animation (simple as it is a placeholder.)
// *    - Commands entered are now reported to the console.
// *
// * V 0.15 _210130
// *    - Assigned GPIO.22 (pin 31) to Door 1
// *    - Assigned GPIO.23 (pin 33) to Door 2
// *    - Assigned GPIO.24 (pin 35) to Door 3
// *    - Assigned GPIO.25 (pin 37) to Door 4
// *    - When in Debug mode, Pin Door Pin reads will be over written.
// *    - I've been putting this off because I don't like the risk associated to testing 
// *        hardware. 
// *
// * V 0.14 _210129
// *    - SetToEnd can now end Scheduled events.
// *    - Pulse commands will now repeat indefinitly.
// *    - "pe" command now added to stop all pulses on all channels.
// *    - Pulse colors available are Red, Green (Lyft), Blue, Purple (Uber), Cyan, 
// *        and Yellow.  Need to put an Orange (Lyft).
// *    - Pulses will automatically end when a door is opened.
// *
// * V 0.13 _210128
// *    - Created an "events" command to list all running events. I was going to have it 
// *        display more information, that is more than just the Event Identity, but ...
// *        wrote this routine because I couldn't find a stuck animation. Immediatly 
// *        after running it I found "... Animm" and it was suposed to be "... Anim".  :)
// *    - Moved debug hot keys to the Command Line.
// *    - Created a pulse white and blue for testing. Commands are "pp" and "pw". 
// *        Need to keep values below 128.  There is no extreme value checks on the Pulse.
// *
// * V 0.12 _210127
// *    - Command line now works as inteded. 
// *        This was fairly easy to do because I put most of it in the backbone already. 
// *    - Command line now accepts one command, "help".
// *    - Also, press enter to clear it.  This will make the command line HOT (not sure
// *        if there is tech word for this,) meaning, that as soon as a command is 
// *        recognized, it will execute.  The reasoning for this HOT Command line is I 
// *        dont want to be fuddling arround with the keyboard while driving when all 
// *        I want to do is turn on or off hazard lights.  This input method is 
// *        imprtant because its so easy and fast.  For example, press "Enter" a few 
// *        times in case the battery powered keyboard is assleep.  press "o" twice 
// *        to turn on the overhead lights.  Or, something like "ob" to turn overhead 
// *        lights on in the back.  Not yet implemented, but you see where this is 
// *        going. 
// *
// * V 0.11 _210126
// *    - Events can now have Identifiers.
// *    - Updated some both of the Guides.
// *    - SetToEnd event can now target events with certain Identifiers.  
// *        This will allow easier ways to turn off a set of events.  Especially when 
// *        events with seperate roles are running on the same strip, such as the 
// *        Overhead light running with the additional Overhead Door Open light. 
// *
// * V 0.10 _210125
// *    - Main routine now returns an int, for no programmed reason at all at this time,
// *        just as any C based program should. Still haven't programed any flags yet. 
// *        As of this writing, I cant think of any reason to do so, except for maybe 
// *        console dislay colors, for when I actually have a monitor in the car or 
// *        something. 
// *    - Went through some of the newer portions of the program and put a few lines of 
// *        comments and descriptions, for reference. 
// *    - Not seen or displayed in any of this code, but what was done. 
// *        Experimented with althernate ways of displaying and rending all the LEDS 
// *        that with alternate LED librarys.  This was important because I don't 
// *        like the one pin, LED strip limit.
// *        - Atttempted to utilize the second channel programmed in the library. 
// *            It failed because I just couldn't get it to work. Either it doesn't
// *            look as if the original programme finished it.  Also, it has been 
// *            years since he worked on it, so chance are it will never be finished. 
// *        - This following portion of my test was sucessful.  
// *            Instead of having the RPi hardware display the LEDs, I had the the Pi
// *            generate what was displayed, then I sent those values to Arduinos, who 
// *            were resonsible for their own LED strips.  
// *          This is great because it allowed the arduinos to work as modules. This is 
// *            primary intintions of the program.  It also allowed a, backup, failsafe, 
// *            mode for the LEDs to work, if a break in the line occured, and or, 
// *            limited operation when the RPI was offline and or booting up. 
// *            It would also allow (MANY!) more LED strips to be running at the same 
// *            time because the 90% of the clock cycles taken by this program is just 
// *            timing and pushing the LED values to the LED strips through that DMA 
// *            channel.  Also, I would get DMA 10 back so I could get my audio back. 
// *          Although I was sucessful, I stopped progress on this because I was limited 
// *            by the serial bus, which ran, at best, 14400 bytes per second.  Or, at 
// *            best, 14 kbs.  And thats, with errors.  LED strips run at about 800 kbs. 
// *            My best results yeilded at about 30 FPS with 130 LEDs without error 
// *            correction.
// *          I want to bring this back in the future.  I want to get Ethernet Hats 
// *            for the Arduinos and stupid little low power ENet hub. I could then 
// *            just attach and power an Arduino, directly to the LED strip via 
// *            a simple Ethernet and power cable.  But, only if it works properly. 
// *
// * V 0.09 _210119
// *    - Moved the Keys variable keywatch to the Console, since it is the part of the 
// *        console anyway.
// *    - Changed the look of the interface.
// *    - Normal operation will now disable debug inputs.
// *    - Moved more console related routines into the console class.
// *    - Created a Command Line on the interface.  This will be part of the routines 
// *        to call specific animations fly style.
// *
// * V 0.08 _210118
// *    - Converted the interface to utilize some of the, fancier, features of ncurses.
// *        Dynamic sized console window, suporting resizing.
// *        Started working on the better interface.
// *
// * V 0.07 _210117
// *    - Fixed the Sleep Timer to sleep and display the acurate times.
// *    - Built a simple console interface.
// *    - Changed Max FPS to 50. Best before at nearly 500 LEDs was 52.  A strange flicker
// *        now exist when maxing frame rate.  Will look into in the future.
// *    - Sending this to GitHub now before I break something.  
// *    - Interface not finished.  FYI: I nearly abandoned this project with the problems 
// *        I had with V.06.  It was that bad.  Except for the flicker, everything seems 
// *        to be running perfectly now.
// *
// * V 0.06 _210116
// *    - Corrected some major problems.
// *    - Reverted teEvents back to a simple array.  The events are still in a linked
// *        vector list that was the already accomplished goal. The reversion was a 
// *        byproduct of getting rid of the errors.  I may have seen the bug fly past 
// *        on my way to this, now working as I expect it to be, version.  But, I'm not 
// *        entirely sure.  I think its behind me and I am scared of letting it get near 
// *        me again.
// *    - More byproducts as a result:
// *        - Convert the stucts to classes.
// *        - ReDo the DoorMonitorAndAnimationControlModule to handle a a few thintgs more
// *            appropriately.
// *        - Port the GitHub page over from previous FLED project.
// *        - Learned, created, then completely destroy an interface designed with the 
// *            ncurses library.  After I feel like the bug isnt hiding, I may create 
// *            it again.  I liked what it could do, so I may try again.
// *        - Spent, maybe 36 hours of programming, in the past 2 days, only to revert 
// *            all the way back to the GitHub version (twice.)  Yes, I had major pointer 
// *            problems.  Did I get them all? Stay tuned.
// *
// * V 0.05 _210114
// *    - Convert the Event system to use Linked List Push, Pop method.  This would be 
// *        less work on the cpu, while both idle and running.
// *      Took all night, but the Event List in each Event has been converted to Vectors.
// *        The results is, program take <1% CPU while sleeping and I dont have to worry 
// *        about animations dropping because I kept the array small to keep the load 
// *        small.  
// *      The collateral damage:  teEvents is now partially converted to Vectors, and
// *        I learned how to program vectors.
// *
// * V 0.04 _210113
// *    - Minor Changes code.
// *    - Added and changed comments.
// *    - Removed unneeded commented code.
// *
// * V 0.03 _210112
// *    - Rebuilt all animations. These are slightly more interesting than the ones 
// *        before. ;)
// *    - Fixed a bunch of things
// *    - The animations are airly well tested now.  This could actually be installed 
// *        with a few minor tweeks.
// *
// * V 0.02 _210109
// *    - Added a simple text interface for testing.
// *    - Started making more advanced animations. I like the new door animations.
// *    - Corrected, fixed, and changed a bunch of things.
// *    - Code is still very dirty.
// *    - Created a ToDo list.
// *
// * V 0.01 _201223 - _210106
// *    - Holy Moley IT WORKS!!!
// *        Running all 4 doors, not just 2, at lightning speeds, with tons ov overhead
// *        resources.  And, better yet, it isn't just partially working, its a full  
// *        fledge conversion.
// *    - This is the dirty code, next will be cleaning it up.
// *    - Ported over from my Arduino FLED project https://github.com/briefnotion/Fled
// *
// ***************************************************************************************
// *
// *  ToDo:
// *    - Create an Better interface.
// *    - Get everything properly classified whith reference .h, supporting, and helper 
// *        libraries.
// *    - Try to decide whether I want everthing in retro c++ or classical c++.
// *    - Create a way to import all animations from an animations file.
// *    - Clean up 90% of the code.
// *    - Move all the main animations into their own subroutines.
// *    - Create animations for day and night running.
// *    - Create specialized animations for specific alerts and hazards.
// *    - Set up an animation ID tag.
// *    - Generate animations for shutting down animations.
// *    - Class the Doors.
// *    - Class the LED strips.
// *    - Convert the ControlModule to run on psudo events of DoorOpen, Door Closed, 
// *        ADoorIsOpen, and AllDoorsClosed. Monitor isHardware, Monitor Special Events.
// *    - Trace Flicker that occurs when sleep = 0 and doors are closing.
// *
// ***************************************************************************************


//#include <FastLED.h>
//#include <Wire.h>
#include <stdio.h>
#include <math.h>
//#include <time.h>
//#include <ctime>
#include <wiringPi.h>
#include <string>
#include <chrono>
#include <unistd.h>
#include <termio.h>
#include <vector>
#include <iostream>
#include <ncurses.h>




// Distros: Jeremy Garff <jer @ jers.net>
//  Zips at https://github.com/jgarff/rpi_ws281x
static char VERSION[] = "XX.YY.ZZ";

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
#include "version.h"

#include "ws2811.h"



// -------------------------------------------------------------------------------------
// DEFINITIONS
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
// CONSOLE AND INTEFACE SETUP

#define SCREENUPDATEDELAY 100
#define CONSOLESPLITSIZE  6

// Key Mapping
#define KEYEXIT           'X'

// Debugging and Diagnosis Keys
#define KEYDEBUG          '/' // Enter, Exit debug mode.
#define KEYLEDTEST        'c' // Turn all LEDs on
#define KEYLEDDRCYCL      't' // Cycle through the doors
#define KEYLEDUPLW        'l' // Cycle Upper or Lower limits of LEDs

// Testing and Debugging
#define BOOTEST       false       // Not Implemented - Fading Away

// -------------------------------------------------------------------------------------
// LED Strip Declarations

#define TARGET_FREQ             WS2811_TARGET_FREQ
#define GPIO_PIN                18
#define DMA                     10
//#define STRIP_TYPE            WS2811_STRIP_RGB		// WS2812/SK6812RGB integrated chip+leds
#define STRIP_TYPE              WS2812_STRIP		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE            SK6812_STRIP_RGBW		// SK6812RGBW (NOT SK6812RGB)

#define LED_COUNT               482

// -------------------------------------------------------------------------------------
// LED Strip Setup

// Door 1
//TOTAL NUM_LEDS    482     

// Door 1
#define NUM_LEDSs0    123     
#define s0As          0       // s0 A Start
#define s0Ae          69      // s0 A End
// Overhead
#define s0Bs          70      // s0 B Start
#define s0Be          121     // s0 B End

//Door 2
#define NUM_LEDSs1    118 
#define s1As          0       // s1 A Start
#define s1Ae          65      // s1 A End
// Overhead
#define s1Bs          66      // s1 B Start
#define s1Be          117     // s1 B End

// -------------------------------------------------------------------------------------
// Raspberry Pi switch pin for doors and switches. Defined as WiringPi id.
// console: gpio -v       (check installation)
// console: gpio readall  (check wiring pin numbers)

// On off buttons, door sensors, switches.
#define SWITCH_PINs0    22      // GPIO.22 - Pin 31 - Hardware Open Close Door Sensor 0
#define SWITCH_PINs1    23      // GPIO.23 - Pin 33 - Hardware Open Close Door Sensor 1
#define SWITCH_PINs2    24      // GPIO.24 - Pin 35 - Hardware Open Close Door Sensor 2
#define SWITCH_PINs3    25      // GPIO.25 - Pin 37 - Hardware Open Close Door Sensor 3

#define AUXDRLINGERFRT  15000    // How long the Front Door lights stay on after close
#define AUXDRLINGERBCK  25000    // How long the Back Door lights stay on after close


// -------------------------------------------------------------------------------------
// Hardware to Software definitions
// -------------------------------------------------------------------------------------

#define NUM_CHANNELS      4   // Amount of LED strips we will be controlling.
#define NUM_TIMED_EVENTS  50  // Untill I can remember how LL, this is being
//  Also, total number of this will be multiplied by the
//  amount of LED strips you have setup.  Watch your memory.
#define NUM_SWITCHES      4   

#define BRIGHTNESS        96  //96  Using Example Code.  Max unknown
#define FRAMES_PER_SECOND 50 // Will not be necessary, but keeping, for now, just in 
//  case.

// -------------------------------------------------------------------------------------
// Door Switch Reference
#define Door_Back     0 // Back Door Switch
#define Door_Front    1 // Front Door Switch
#define Door_Aux      2 // Aux Door Switch 

// -------------------------------------------------------------------------------------
// Strip Reference
#define Driver_Back_Door     0 // Driver Side Back Door 
#define Driver_Back_Over     1 // Driver Side Back Overhead 
#define Driver_Front_Door    2 // Driver Side Front Door 
#define Driver_Front_Over    3 // Driver Side Front Overhead 
#define Passenger_Back_Door  4 // Passenger Side Back Door 
#define Passenger_Back_Over  5 // Passenger Side Back Overhead 
#define Passenger_Front_Door 6 // Passenger Side Front Door 
#define Passenger_Front_Over 7 // Passenger Side Front Overhead 

// -------------------------------------------------------------------------------------
// Door Status Reference
#define StUnknown         0 // Door Open Animation

#define StDoorOpen        1 // Door Open Animation
#define StDoorCloseA      2 // Door Close Animation
#define StDoorCloseR      3 // Door Close Animation

#define stOverOpen        4 // Overhead Open Animation
#define stOverClose       5 // Overhead Close 1 Animation
#define StOverCloseCon    6 // Overhead Close 2 Animation

// -------------------------------------------------------------------------------------
// Event Animations
#define AnEvClear         0
#define AnEvClearRunning  8
#define AnEvSweep         1
#define AnEvSchedule      2
#define AnEvSetToEnd      3

// Pixel Animations
#define AnPiFade          4
#define AnPiFadeDith      5
#define AnPiPulse         6
#define AnPiPulseTo       7
#define AnPiTwinkle       8

// -------------------------------------------------------------------------------------
// Main Animations

// Events Have Identifies.  Can be anything but here are some typical ones I refer to.

//Door Open Anim                    - Runs on Door when it's opened.
//Door Close Anim                   - Runs on Door when it's closed.
//Door Close Active Anim            - Runs on All Doors when All Doors are closed.
//                                      (turns off and doesn't clear for passive 
//                                        illumination)

//Overhead Open Anim                - Runs on all doors overhead when door is open. 
//Overhead Close Anim               - Runs on all doors overhead when door is closed. 
//Overhead Close Convenience Anim   - Runs on door overhead when door is recently closed. 

//Open Additional Anim              - Runs on door overhead when door is opened. 
//Close Additional Anim             - Runs on door overhead when door is closed. 

//Channel Light Pulse Color         - Runs on channel (this is still experimental)


// Main Normal Animations
#define AnTavdOpenDoorNormal    110
#define AnTavdOpenOverNormal    111
#define AnTavdCloseDoorNormal   112
#define AnTavdCloseOverNormal   113
#define AnTavdCloseOve2Normal   114

// Main Halloween Animations
#define AnTavdOpenDoorHallow    120
#define AnTavdOpenOverHallow    121
#define AnTavdCloseDoorHallow   122
#define AnTavdCloseOverHallow   123
#define AnTavdCloseOve2Hallow   124

// Main Thanksgiving Animations
#define AnTavdOpenDoorThanks    130
#define AnTavdOpenOverThanks    131
#define AnTavdCloseDoorThanks   132
#define AnTavdCloseOverThanks   133
#define AnTavdCloseOverNormalCo 134


// Main TaOff
#define AnTaOff                 0

// Main Power On Animation
#define AnTaPowerOn             1

// -------------------------------------------------------------------------------------
// Scripts 

// Door Open Animation 
#define AnTaDoorOpen            2
#define AnTaDoorOpen00          20
#define AnTaDoorOpen01          21
#define AnTaDoorOpen02          22

// Door Close Animation 
#define AnTaDoorClose           3
#define AnTaDoorClose00         31
#define AnTaDoorClose01         32

// Over Conv Off Animation
#define AnTavdPaAnimClose00     4

// Over Off Animation
#define AnTaStripOverOff        5

// -------------------------------------------------------------------------------------
// Effects

//  Normal Effects  
#define AnTavdPacificaish       60
#define AnTavdPaAnimClose       61
#define AnTaChannelPulseColor   63
#define AnTaOverheadIllumColor  64
#define AnTaHazard              65

//  Halloween Effects
#define AnTavdCloud             70
#define AnTavdLightning         71
#define AnTavdCeilingLight      72
#define AnTavdHallowClose2      73
#define AnTavdHallowClose200    74
#define AnTavdChannelLightning  75

//  Thanksgiving Effects
#define AnTavdBlueSky           80
#define AnTavdNightSky          81
#define AnTavdNightSkyClose     82
#define AnTaStripOverOffThanks  83

//  Christma Effects
#define AnTavdChristmasTree     90
#define AnTavdChristmasTreeCo   91
#define AnTavdAddOpenChristm    92 
#define AnTavdAddCloseChristm   93
// Door Open Animation Christmas 
#define AnTaDoorOpen00Christmas 95
#define AnTaDoorOpen01Christmas 96
#define AnTaDoorOpen02Christmas 97

// StupidRandom Parameters
#define StuRNDsize              100


// ***************************************************************************************
// STRUCTURES
// ***************************************************************************************

// -------------------------------------------------------------------------------------
// All variables to keep track of the interface and program status.  All psssive.
class system_data
{
  // This is just a repository of data that the program will be accessing and storing 
  //  for displaying only.  Everyting here is very specific and not meant to be 
  //  friendly.  This data and functions is specific for this one program.  Also, 
  //  this class is very likely to fail if not maintained when program main is updated. 
  //  You have been warned.

  //using namespace std;
  
  private:
  
  struct stat_data
  {
    float data  = 0;
    float min   = 0; 
    float max   = 0;
  };
  

  public:
  stat_data fltCOMPUTETIME;   // Loop time spent while only proceessing.
  stat_data fltSLEEPTIME;     // Calculated time needed to sleep.
  stat_data fltCYCLETIME;     // Amount of time to complete an entire cycle.
  stat_data fltPREVSLEEPTIME; // Stored value returned on pref sleep cycle.

  std::string strLEDRANGE  = "";    // Text showing what LEDs will be Displayed.
  std::string strLEDLIMITS = "";    // Text showing what LEDd, upper or lower, displayed.

  int   intDoorsOpen = 0;           // Amount of doors open.
  bool  booPulsesRunning = false;   // Are exta anims running.
  bool  booOverheadRunning = false; // Are exta anims running.
  bool  booHazardRunning = false;   // Are exta anims running.

  // additional time measurements.
  // LED RENDER TIME
  // SCREEN OUTPUT TIME

  // store copies of displayed system data
  bool  boolDOORSENSORS[NUM_SWITCHES];
  int   intEVENTCOUNTS[NUM_SWITCHES];

  // Reference to the door values
  void store_door_switch_states(bool switches[])
  {
    for(int x=0; x < NUM_SWITCHES; x++)
    {
      boolDOORSENSORS[x] = switches[x];
    }
  }

  // Reference for the amount for events running.
  void store_event_counts(int EventCount0, int EventCount1, int EventCount2, int EventCount3)
  {
    intEVENTCOUNTS[0] = EventCount0;
    intEVENTCOUNTS[1] = EventCount1;
    intEVENTCOUNTS[2] = EventCount2;
    intEVENTCOUNTS[3] = EventCount3;
  }

  // Reference for the time (elapsed) since program start.
  void store_compute_time(float fltComputeTime)
  {
    fltCOMPUTETIME.data = fltComputeTime;
  }

  void store_cycle_time(float fltCycleTime)
  {
    fltCYCLETIME.data = fltCycleTime;
    if (fltCycleTime > fltCYCLETIME.max)
    {
      fltCYCLETIME.max = fltCycleTime;
    }
  }

  // Reference since sleep started and wake up time elapsed. 
  float getsleeptime(int intFPS)
  {
    // Return, in milliseconds, the amount of time required to sleep 
    //  before returning to the next cycle. 
    float sleeptime = (1000 / intFPS) - fltCOMPUTETIME.data;
    
    if (sleeptime < 0)
    {
      sleeptime = 0;
    }

    fltPREVSLEEPTIME.data = sleeptime;
    return (sleeptime);
  }

  // reset monitor times.
  void refresh()
  {
    fltCOMPUTETIME.min  = 0;
    fltCOMPUTETIME.max  = 0;
    fltSLEEPTIME.min    = 0;
    fltSLEEPTIME.max    = 0;
    fltCYCLETIME.min    = 0;
    fltCYCLETIME.max    = 0;
  }

};

// -------------------------------------------------------------------------------------
// Tacks all key presses and remembers data associated to whatever key is pressed.
class Keys
{
  private:
  struct Letter
  // For each letter, assign a behavior and type for it.
  {
    int LETTER;           // Letter, keypress, main value
    int COUNT = 0;        // set up how many times the key can be pressed brofor reset.
    int VALUE = 0;        // with every press, this value increases, this is value returned.
    bool PRESSED = true;  // Assume anything could have been press when 
                          //   program starts.
    bool ACTIVE = true ;  // Only process keys that are set to active.
  };

  // Full Command Line value(as is)
  struct CommandLine
  {
    std::string COMMANDLINE = "";
    bool PRESSED = true;
    bool CLEARED = true;
  };

  public:
  Letter Chars[256];      // Full array of all letters
  CommandLine Command;    // Command Line Reference.

  void cmdClear()
  // Clear Command line
  {
    Command.COMMANDLINE = "";
    Command.PRESSED = true;
    Command.CLEARED = true;
  }

  bool cmdPressed()
  // Return if Command Line Recently Changed.
  {
    return Command.PRESSED;
  }
  
  bool cmdCleared()
  // Return if the Command was cleared. Reset it after read if it was.
  {
    if (Command.CLEARED == false)
    {
      return false;
    }
    else
    {
      Command.CLEARED = false;
      return true;
    }
  }

  std::string cmdRead()
  // Read Command Line and sets recently changed to false (no longer dirty)
  {
    Command.PRESSED = false;
    return(Command.COMMANDLINE);
  }

  void cmdIn(int c)
  // Add another character to the command line.
  {
    if(c == (char)'\n')
    {
      // If enter pressed, clear the line.
      cmdClear();
    }
    else
    {
      //if( (c>47 && c<57) || (c>65 && c<90) || (c>97 && c<122) )
      if( (c>32 && c<126) )
      {
        // only accept letters and numbers.
        Command.COMMANDLINE = Command.COMMANDLINE + (char)c;
        Command.PRESSED = true;

        // Limit Command Line Size. Clear when too big.
        if (Command.COMMANDLINE.size() > 10)
        {
          cmdClear();
        }
      }
    }
  }

  void set(int letter, int size)
  // Set behavior of letter to be watched.
  {
    Chars[letter].COUNT = size - 1;
    Chars[letter].VALUE = 0;
  }

  void in(int c)
  // Letter watched is pressed, change its value atnd set pressed (dirty)
  {
    if (Chars[c].ACTIVE == true)
    {
      Chars[c].VALUE++;
      Chars[c].PRESSED = true;
      if (Chars[c].VALUE > Chars[c].COUNT)
      {
        Chars[c].VALUE = 0;
      }
    }
  }

  int get(int c)
  // return value of letter and reset pressed (clean)
  {
    Chars[c].PRESSED = false;
    return Chars[c].VALUE;
  }

  int getnoreset(int c)
  // return value of letter and reset pressed (clean)
  {
    return Chars[c].VALUE;
  }

  // returns true false value of letter, reset pressed (clean)
  bool getTF(int c)
  {
    Chars[c].PRESSED = false;
    if (Chars[c].VALUE == 0)
      return false;
    else
      return true;
  }

  // returns pressed value (clean or dirty)
  bool pressed(int c)
  {
    return (Chars[c].PRESSED);
  }
};


// -------------------------------------------------------------------------------------
// NCurses Console.  Responsible for all screen and user interfaces.
class Console  
{
  private:

  // Keyboard input variable
  int key = -1;

  // NCurses Variables
  int YMax = 0;
  int XMax = 0;
  int Xmid = 0;
  
  WINDOW * winTop;
  WINDOW * winBot;
  std::vector<std::string> ou;

  std::string strBotLine;

  // Display Variables
  int YSeperator = 0;
  int YConOut = 0;

  unsigned long Update_Time = 0;
  
  public:
  Keys keywatch;

  void set(int intSeperator)
  {
    getmaxyx(stdscr, YMax, XMax);

    YSeperator = intSeperator;
    Xmid = XMax / 2;
  
    winTop = newwin(YSeperator, XMax, 0, 0);
    winBot = newwin(YMax - YSeperator, XMax, YSeperator, 0);
    refresh();

    //wborder(winTop,'|','|','-','-','/','\\','\\','/') ;
    //wborder(winBot,'|','|','-','-','/','\\','\\','/') ;
    
    //wborder(winTop,' ',' ','_','_','┌','┐','└','┘') ;
    //wborder(winBot,' ',' ','_','_','┌','┐','└','┘') ;

    wborder(winTop,' ',' ',' ','_',' ',' ',' ',' ') ;
    wborder(winBot,' ',' ',' ','_',' ',' ',' ',' ') ;

    wrefresh(winBot);
    wrefresh(winTop);
    
    strBotLine = "";
    strBotLine = strBotLine.append(XMax-1, '_');
    // cbreak();
	  // raw();
	  noecho();
  }

  void printout()
  // Print out console.
  {
    std::string strTemp;

    while(ou.size() > 0)
    {
      if ((YConOut > YMax - YSeperator - 2) || (YConOut < 1) )
      {
        YConOut = 1;
      }

      wmove(winBot, YConOut,0);
      wclrtoeol(winBot);
      mvwprintw(winBot, YConOut, 0, "%s", ou[0].c_str());

      wmove(winBot, YConOut +1,0);
      wclrtoeol(winBot);
      mvwprintw(winBot, YConOut +1 , 0, "%s", strBotLine.c_str());

      ou.erase(ou.begin());
      YConOut++;

      wrefresh(winBot);      
    }
  }

  void printi (std::string in)
  // Print to console immediatly to console without waiting for refresh.
  {
    ou.push_back(in);
    printout();
  }

  void printwait (std::string in)
  // Print out a line to console during next refresh.
  {
    ou.push_back(in);
  }

  bool isready(unsigned long time, int intmsWaitTime)
  {
    //Check to see if enough time has passed to refresh the console. (wait is in ms)
    if(time > Update_Time + intmsWaitTime)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  void readkeyboardinput()
  // read keyboard for keypresses.  Just exit if nothing is being pressed.
  {
    key = wgetch(stdscr);
    if (key != -1)
    {
      // Check for special characters first.
      if (key == KEY_RESIZE)
      {
        keywatch.in(key);
      }
      else
      {
        // Put all remaining input into the Command Line.
        keywatch.cmdIn(key); 
      }
    }
  }

  void processkeyboadinput()
  // Run through this routine before before the console is refreshed.
  {
    // Check for screen resize.
    if (keywatch.get(KEY_RESIZE) == 1)
    {
      printwait("RESIZING SCREEN");
      keywatch.Chars[KEY_RESIZE].VALUE = 0;
      set(CONSOLESPLITSIZE);
    }
  }

  void update_displayed_time(unsigned long time)
  // Set the consoles last redraw time, a now should be passed in.
  {
    Update_Time = time;
  }

  // Draw the console, starting with status window, then update console with pending
  // console prints.
  void output(system_data sdSysData)
  {
    bool RedrawTestParts = false;

    // Check to see if we have just toggled the debug mode.  
    // If we have toggled DEBUG, then we will need to clean up things on the screan.
    if (keywatch.pressed(KEYDEBUG) == true)
    {
      RedrawTestParts = true;
    }
        
    // Debug Stuff: Display Compute Times
    if (keywatch.get(KEYDEBUG) == 1)
    {
      mvwprintw(winTop, 2, 26, "Compute: %fms", sdSysData.fltCOMPUTETIME.data);
      mvwprintw(winTop, 3, 26, "  Sleep: %fms", sdSysData.fltPREVSLEEPTIME.data);
      mvwprintw(winTop, 4, 26, "  Cycle: %fms", sdSysData.fltCYCLETIME.data);

      mvwprintw(winTop, 4, 47, "(m:%fms)", sdSysData.fltCYCLETIME.max);
    }
    else if ( RedrawTestParts == true )
    // If exiting debug mode, clean out what was printed in when in debug mode.
    {
      mvwprintw(winTop, 2, 26, "                       ");
      mvwprintw(winTop, 3, 26, "                       ");
      mvwprintw(winTop, 4, 26, "                       ");

      mvwprintw(winTop, 2, 47, "                      ");
      mvwprintw(winTop, 3, 47, "                      ");
      mvwprintw(winTop, 4, 47, "                      ");
    }
    
    // Debug stuff: Display Range and Seleced Strips to Diplay
    if(keywatch.get(KEYDEBUG) == 1)
    {
      // Display LED range selected to display.
      std::string strRange;
      std::string strLevel;

      // Displaying LEDs selected to be displayed CYCLE selected.
      switch (keywatch.get(KEYLEDDRCYCL))
      {
        case 0:   // Show all lights.  This is normal.
        {
          strRange = "A ";
          break;
        }
        case 1:   // Show only Light Set 1
        {
          strRange = "D1";
          break;
        }
        case 2:   // Show only Light Set 2
        {
          strRange = "D2";
          break;
        }
        case 3:   // Show only Light Set 3
        {
          strRange = "D3";
          break;
        }
        case 4:   // Show only Light Set 4
        {
          strRange = "D4";
          break;
        }

      }    

      // Check for Upper or Lower Range
      if (keywatch.get(KEYLEDUPLW) == 0)
      {
        strLevel = "L";
      }
      else
      {
        strLevel = "U";
      }

      // Draw RANGE and UPPER OR LOWER VALUES selected.
      mvwprintw(winTop, 2, 19, "RNG:%s", strRange.c_str());
      mvwprintw(winTop, 3, 19, "LVL:%s", strLevel.c_str());
    }    
    else if ( RedrawTestParts == true )
    // If exiting debug mode, clean out what was printed in when in debug mode.
      {
        mvwprintw(winTop, 2, 19, "      ");
        mvwprintw(winTop, 3, 19, "      ");
      }
    // ------

    //Display Door Statuses, highlighting values that are on (doors open)
    if (sdSysData.boolDOORSENSORS[0] == true) {wattron(winTop, A_REVERSE);}
    mvwprintw(winTop, 3, 7, "D1");
    if (sdSysData.boolDOORSENSORS[0] == true) {wattroff(winTop, A_REVERSE);}
    
    if (sdSysData.boolDOORSENSORS[1] == true) {wattron(winTop, A_REVERSE);}
    mvwprintw(winTop, 2, 7, "D2");
    if (sdSysData.boolDOORSENSORS[1] == true) {wattroff(winTop, A_REVERSE);}
    
    if (sdSysData.boolDOORSENSORS[2] == true) {wattron(winTop, A_REVERSE);}
    mvwprintw(winTop, 3, 10, "D3");
    if (sdSysData.boolDOORSENSORS[2] == true) {wattroff(winTop, A_REVERSE);}

    if (sdSysData.boolDOORSENSORS[3] == true) {wattron(winTop, A_REVERSE);}
    mvwprintw(winTop, 2, 10, "D4");
    if (sdSysData.boolDOORSENSORS[3] == true) {wattroff(winTop, A_REVERSE);}


    // Debug stuff: Display the amount of events, assoicated to each door, runnng .
    if (keywatch.get(KEYDEBUG) == 1)
    {
      mvwprintw(winTop, 3, 1, "%03d:E", sdSysData.intEVENTCOUNTS[0]);
      mvwprintw(winTop, 2, 1, "%03d:E", sdSysData.intEVENTCOUNTS[1]);
      mvwprintw(winTop, 3, 13, "E:%03d", sdSysData.intEVENTCOUNTS[2]);
      mvwprintw(winTop, 2, 13, "E:%03d", sdSysData.intEVENTCOUNTS[3]);
    }
    else if ( RedrawTestParts == true )
    // If exiting debug mode, clean out what was printed in when in debug mode.
    {
      mvwprintw(winTop, 3, 1, "     ");
      mvwprintw(winTop, 2, 1, "     ");
      mvwprintw(winTop, 3, 13, "     ");
      mvwprintw(winTop, 2, 13, "     ");
    }

    // Display Status
    if (RedrawTestParts == true)
    {
      if (keywatch.get(KEYDEBUG) == 1)
      {
        wattron(winTop, A_REVERSE);
        mvwprintw(winTop, 0, XMax - 5, "DIAG");
        wattroff(winTop, A_REVERSE);
      }
      else
      {
        mvwprintw(winTop, 0, XMax - 5, "    ");
      }
    }    

    mvwprintw(winTop, 0, 18, "REPEAT");
    mvwprintw(winTop, 0, 26, "DOORAWARE");

    // ----------------------------
    // Display Command Line
    if (keywatch.cmdPressed() == true)
    {
      if (keywatch.cmdCleared() == true)
      {
        // Blank out the line before redraw.
        wmove(winTop, 0, 1);
        //wclrtoeol(winTop);
        mvwprintw(winTop, 0, 1, "CMD: __________");
      }
      mvwprintw(winTop, 0, 1, "CMD: %s", keywatch.cmdRead().c_str());
    }
    
    // ----------------------------

    // Commit all our changes to the status portion of the screen (winTop)
    wrefresh(winTop);

    // Now that we are finished drawing the Console Status part of the screen, 
    // we needd to go to the console portion of the screen and update it.
    printout();
  }
};


// -------------------------------------------------------------------------------------
// Keeps track of timing variables
class FledTime
{
  private:
  std::chrono::time_point<std::chrono::system_clock> tmeStart;
  std::chrono::time_point<std::chrono::system_clock> tmeFrame;

  public:

  double tmeFrameMillis;

  void set()
  {
    // Initialize as Start of Program Time.
    tmeStart = std::chrono::system_clock::now();
  }

  double now()
  {
    // Returns now time in milliseconds.
    // Should be Unsigned Long.
    std::chrono::time_point<std::chrono::system_clock> tmeNow = std::chrono::system_clock::now();
    std::chrono::duration<double>  dur = tmeNow - tmeStart;

    double nowtime = dur.count();
    nowtime = nowtime * 1000;
    
    return nowtime;
  }

  void setframetime()
  {
    // Sets the Start of a Frame Time to now. 
    tmeFrame = std::chrono::system_clock::now();
    std::chrono::duration<double>  dur = tmeFrame - tmeStart;

    tmeFrameMillis = dur.count();
    tmeFrameMillis = tmeFrameMillis * 1000;
  }

  double tmeFrameElapse()
  {
    // Returns, in milliseconds, the amount of time passed since frame time.
    double elapsed;
    std::chrono::time_point<std::chrono::system_clock> tmeNow = std::chrono::system_clock::now();
    std::chrono::duration<double>  dur = tmeNow - tmeFrame;
    
    elapsed = dur.count();
    elapsed = elapsed * 1000;

    return elapsed;
  }
};


// -------------------------------------------------------------------------------------
// Stupid Random Generator Structure
class stupid_random
//  This is a simple solution to random numbers not being randomly generated.
//    Generate a string of random numbers to be used and referenced throughout the
//    entirity of the program run.
{
  private:
  char  stupidnumbers[StuRNDsize];

  public:
  void set()
  {
    long number;
    int pos = 0;
    bool found = false;

    // Create seed onece.
    srand((unsigned int)time(NULL));

    // Clear Array.
    for (int x = 0; x < StuRNDsize; x++)
    {
      stupidnumbers[x] = 255;
    }
    
    // Fill the array with random numbers.
    while(pos < StuRNDsize)
    {
      // Get a number.
      number = rand() % StuRNDsize;
      number = floor(number);

      found = false;

      // If number already in list then seach for a new
      //  random number.
      for (int x = 0; x <= pos; x++)
      {
        if (number == (int)(stupidnumbers[x]))
        {
          found = true;
        }
      }

      // If number not in list then add it.
      if (found == false)
      {
        stupidnumbers[pos] =(char )(number);
        pos ++;
      }
    }
  }

  // Return random char  from list based on seed.
  char getB(unsigned long seed, int size)
  {
    int pos = (seed % StuRNDsize);

    return (stupidnumbers[pos] % size);  
    
   }

  // Return random unsigned long from list based on seed.
  //  Number will evenly distributed from other numbers 
  //    based on list size.  Precision is way off, but should
  //    be random
  // Size is the Upper Limit. Lower Limit is 0.
  unsigned long getUL(unsigned long seed, int size)
  {
    int pos = (seed % StuRNDsize);

    return (stupidnumbers[pos] % size) * (size / StuRNDsize);
  }
};



// -------------------------------------------------------------------------------------
// LedStrip Structures 

// Defines a basic LED Strip
class led_strip
{
  public:
  int Cl = 0; // Channel
  int St = 0; // Start Led Pos
  int Ed = 0; // End Led Pos
  int AnimationStatus = 0;

  void set(int intChannel, int intStart, int intEnd)
  {
    Cl = intChannel;
    St = intStart;
    Ed = intEnd;
  }

  int Ct()
  {
    int count;
    return Ed - St + 1;
  }
};


// -------------------------------------------------------------------------------------
// Color class RGB byte, byte, byte

class CRGB
// RGB varible.
{
public: 
  char r = 0;
  char g = 0;
  char b = 0;

  CRGB()
  {
	  char r = 0;
	  char g = 0;
	  char b = 0;
  }
  
  // cRGB override for passing non varible to varible. 
  CRGB(char R,char G,char B)
  {
	  r = R;
	  g = G;
	  b = B;
  }
  
  //Compare two cRGB values.
  bool operator== (CRGB color)
  {
    if ((r == color.r) && (g == color.g) && (b == color.b))
      return true;
    else
      return false;
  }
};


// -------------------------------------------------------------------------------------
class bigCRGB
// Color class RGB int, int, int

// This color class is used for preprocessing byte RGB values so computation can be 
// negative or more than 256.  Not displayable but useful in calculations.
{
  public:
  int r = 0;
  int g = 0;
  int b = 0;
  bool complete = true;
};

// -------------------------------------------------------------------------------------

// Timed Event Data Variable

class timed_event_data
// Varibles to control the timed_event.
{
  public:
  std::string strIdent = "";
  unsigned long tmeSTARTTIME = 0;
  int intDURATION = 0;
  int intSPEED= 0;
  char  bytANIMATION = 0;
  char  bytLEDANIMATION = 0;
  CRGB crgbCOLORSTART1 = CRGB(0,0,0);
  CRGB crgbCOLORSTART2 = CRGB(0,0,0);
  CRGB crgbCOLORDEST1 = CRGB(0,0,0);
  CRGB crgbCOLORDEST2 = CRGB(0,0,0);
  int  intSTARTPOS = 0;
  int  intENDPOS = 0;
  bool booINVERTCOLOR = false;
  bool booREPEAT = false;
  bool booCLEARONEND = true;

  bool booCOMPLETE = true;


  void PostCheck(unsigned long tmeCurrent)
  // Check to see if the event is over, unlock and release Start Colors.
  {
    //  (num of led * speed + duration)
    // Grabbing actual current time to process decayed events, because alot could've happened
    // since then.

    if (booCOMPLETE == true)
    {
      // The event repeats, collision is irrelevant.
      if (booREPEAT == true)
      {
        // Keep the event active by resetting its start time and setting it
        //  to be incomplete.
        booCOMPLETE = false;
        tmeSTARTTIME = tmeCurrent;  // Using current time here because we want
        //  to keep the frames the same.
      }
    }
  }
};

// -------------------------------------------------------------------------------------

// Timed Event Variable

class timed_event
//  Create a Timed LED Event:
//    Controls when a group of LEDs are to begin their individual light path animation.
//    If an event is over written the previous animation will be lost.
{
  public:
  //timed_event_data teDATA[NUM_TIMED_EVENTS];
  std::vector<timed_event_data> teDATA;
  int      intLEDCOUNT;

  void create(int intLedCount)
  // On startup, define the amount of LEDs in this event list.
  {
    intLEDCOUNT = intLedCount;
  }

  void set(std::string strIedntity, unsigned long tmeCurrentTime,
           int tmeStartInTime, int intDuration, int intSpeed, 
           char  bytAnimation, char  bytLEDAnimation, bool booInvertColor, 
           CRGB crgbStart1, CRGB crgbDest1, CRGB crgbStart2, CRGB crgbDest2, 
           int intStartPos, int intEndPos, bool booRepeat, bool booClearOnEnd)
  // Prepare an animation to start at a specific time.
  {

    bool booCreated = false;

    unsigned long tmeStartTime = tmeCurrentTime + tmeStartInTime;

    timed_event_data newteDATA;

    newteDATA.strIdent = strIedntity;
    newteDATA.tmeSTARTTIME = tmeStartTime;
    newteDATA.intDURATION = intDuration;
    newteDATA.intSPEED = intSpeed;
    newteDATA.bytANIMATION = bytAnimation;
    newteDATA.bytLEDANIMATION = bytLEDAnimation;

    newteDATA.booINVERTCOLOR = booInvertColor;

    newteDATA.crgbCOLORSTART1 = crgbStart1;
    newteDATA.crgbCOLORSTART2 = crgbStart2;
    newteDATA.crgbCOLORDEST1 = crgbDest1;
    newteDATA.crgbCOLORDEST2 = crgbDest2;

    newteDATA.intSTARTPOS = intStartPos;
    newteDATA.intENDPOS = intEndPos;
    newteDATA.booREPEAT = booRepeat;
    newteDATA.booCLEARONEND = booClearOnEnd;

    newteDATA.booCOMPLETE = false;

    teDATA.push_back(newteDATA);

    booCreated = true;
    //printf("Event create: Anim:%d LED:%d P1:%d P2:%d\n", bytAnimation, bytLEDAnimation, intStartPos, intEndPos);
  }

  // -------------------------------------------------------------------------------------
  // Clear events in channel

  void ClearAll(int intStartPos, int intEndPos)
  //Remove all timed event animations on a specific animation strip.
  {

    for (int x = 0; x < teDATA.size(); x++)

    if (teDATA[x].booCOMPLETE == false && 
        (  ((teDATA[x].intSTARTPOS >= intStartPos)  
          && (teDATA[x].intSTARTPOS <= intEndPos))
                ||
          ((teDATA[x].intENDPOS >= intStartPos)  
          && (teDATA[x].intENDPOS <= intEndPos))  ) )
    {
      
      {
        teDATA[x].booCOMPLETE = true;
        //printf("Cleared Event: E%d S%d E%d\n", x, intStartPos, intEndPos);
      }
    }
  }

  // -------------------------------------------------------------------------------------
  // Common routines to find pixel color values from 2 seperate pixel colors.

  // Compute from Power of pixel with from time start to time end.
  float ComputePower(float fltElapsed, float FltDuration)
  {
    return (fltElapsed / FltDuration);
  }

  // Compute from Power of pixel with from time start to time end.
  //  For pixels that are split to behave differently on first half of time.
  //  Compute First half or Bottom half value.
  float ComputePowerHalfBot(float fltElapsed, float FltDuration)
  {
    return (fltElapsed * 2 / FltDuration);
  }

  // Compute from Power of pixel with from time start to time end.
  //  For pixels that are split to behave differently on first half of time.
  //  Compute Second half or Top half value.
  float ComputePowerHalfTop(float fltElapsed, float FltDuration)
  {
    //1 - (((float)((tmeElapsed * 2) - EventInfo.intDURATION) / (float)EventInfo.intDURATION));
    return (1 - (((fltElapsed *2 ) - FltDuration) / FltDuration));
  }

  // Merge two pixel colors based on Power.  Returns the bigCRGB value from CRGB.
  bigCRGB Dither(float fltPower, CRGB crgbColor1, CRGB crgbColor2)
  {
    bigCRGB tmpColor;
    
    tmpColor.r = (fltPower * crgbColor2.r) + ((1 - fltPower) * crgbColor1.r);
    tmpColor.g = (fltPower * crgbColor2.g) + ((1 - fltPower) * crgbColor1.g);
    tmpColor.b = (fltPower * crgbColor2.b) + ((1 - fltPower) * crgbColor1.b);

    return tmpColor;
  }            

  // Merge two pixel colors based on Power.  Returns the bigCRGB value from CRGB.
  CRGB DitherSmall(float fltPower, CRGB crgbColor1, CRGB crgbColor2)
  {
    CRGB tmpColor;
    
    tmpColor.r = (fltPower * crgbColor2.r) + ((1 - fltPower) * crgbColor1.r);
    tmpColor.g = (fltPower * crgbColor2.g) + ((1 - fltPower) * crgbColor1.g);
    tmpColor.b = (fltPower * crgbColor2.b) + ((1 - fltPower) * crgbColor1.b);

    return tmpColor;
  }      


  // -------------------------------------------------------------------------------------
  // Timed Event LED Animations

  bigCRGB crgb_anim_color(stupid_random sRND, unsigned long tmeCurrentTime, unsigned long tmeAnimTime,
                          int intLED, int intEvent, timed_event_data &EventInfo)
  //  Returns a CRGB value of the single LED respective to what its value should
  //    be as it is in its time path.

  //  LED Animations:
  //    0 - Clear:  Clears future animation and sets to no future animation.
  //    1 - Fade:   Fades single LED from its initial value to its destination value from
  //                  start of animation, and completed and end of its duration.
  //    2 - Pulse:  Pulses the LED to desired value.  The LED will have its requested
  //                  full value at half duration time, and will return to its origional
  //                  value at the end of the duration.
  {

    // Only run pixel animation if it is ready.

    unsigned long tmeElapsed = tmeCurrentTime - tmeAnimTime;
    float fltPower;
    bigCRGB tmpColor;

    switch (EventInfo.bytLEDANIMATION)
    {
      case AnPiFade:
        // Fade Animation Path
        {
          if (tmeCurrentTime >= tmeAnimTime + EventInfo.intDURATION)
          {
            tmpColor.r = EventInfo.crgbCOLORDEST1.r;
            tmpColor.g = EventInfo.crgbCOLORDEST1.g;
            tmpColor.b = EventInfo.crgbCOLORDEST1.b;
            
            tmpColor.complete = EventInfo.booCLEARONEND;

            return tmpColor;
            break;
          }
          else
          {
            fltPower = ComputePower(tmeElapsed, EventInfo.intDURATION);
            tmpColor = Dither(fltPower, EventInfo.crgbCOLORSTART1, EventInfo.crgbCOLORDEST1);
            
            tmpColor.complete = false;

            return tmpColor;
            break;
          }
        } // END CASE AnPiFade
              
        case AnPiFadeDith:
        // Fade Animation Path (Dither, this is duplicate code!)
        {
          CRGB crgbTempStart;
          CRGB crgbTempDest;

          // Grab Event Data that may change or be processed within this switch 
            //  statement. We will be calculating the change of the pixel color, not 
            //  the actual color.

          // Dither the Dither
          if ((EventInfo.intENDPOS - EventInfo.intSTARTPOS)  == 0)
          {
            fltPower = 0;
          }
          else
          {
            fltPower = ComputePower(abs(intLED - EventInfo.intSTARTPOS), abs(EventInfo.intENDPOS - EventInfo.intSTARTPOS));
          }
          crgbTempStart = DitherSmall(fltPower, EventInfo.crgbCOLORSTART1, EventInfo.crgbCOLORSTART2);
          crgbTempDest = DitherSmall(fltPower, EventInfo.crgbCOLORDEST1, EventInfo.crgbCOLORDEST2);

          // Get value of light based on animation at current time.
          if (tmeCurrentTime >= tmeAnimTime + EventInfo.intDURATION)
          {
            tmpColor.r = crgbTempDest.r;
            tmpColor.g = crgbTempDest.g;
            tmpColor.b = crgbTempDest.b;
            
            tmpColor.complete = EventInfo.booCLEARONEND;

            return tmpColor;
            break;
          }
          else
          {
            fltPower = ComputePower(tmeElapsed, EventInfo.intDURATION);
            tmpColor = Dither(fltPower, crgbTempStart, crgbTempDest);
            
            tmpColor.complete = false;

            return tmpColor;
            break;
          }
        } // END CASE AnPiFadeDith

      case AnPiPulse:
        // Pulse Animation Path
        // This can be done beter with a simple ABS function.
        {
          if (tmeCurrentTime >= tmeAnimTime + EventInfo.intDURATION)
          {
            tmpColor.complete = true;
            
            return tmpColor;
            break;
          }
          else
          {
            if ((tmeElapsed * 2) <= (EventInfo.intDURATION))
            {
              fltPower = ComputePowerHalfBot(tmeElapsed,EventInfo.intDURATION);
            }
            else
            {
              fltPower = ComputePowerHalfTop(tmeElapsed,EventInfo.intDURATION);
            }

            //  Swap to second color at mid point
            tmpColor = Dither(fltPower, CRGB(0,0,0), EventInfo.crgbCOLORDEST1);
            
            tmpColor.complete = false;

            return tmpColor;
            break;
          }
        } // END CASE AnPiPulse

      case AnPiPulseTo:
        // PulseTo Animation Path
        // This can be done beter with a simple ABS function.
        {
          if (tmeCurrentTime >= tmeAnimTime + EventInfo.intDURATION)
          {
            tmpColor.r = EventInfo.crgbCOLORDEST2.r;
            tmpColor.g = EventInfo.crgbCOLORDEST2.g;
            tmpColor.b = EventInfo.crgbCOLORDEST2.b;
            
            tmpColor.complete = EventInfo.booCLEARONEND;

            return tmpColor;
            break;
          }
          else
          {
            CRGB crgbA;
            CRGB crgbB;
            //  Swap to second color and power down at mid point.
            if ((tmeElapsed * 2) <= (EventInfo.intDURATION))
            {
              fltPower = ComputePowerHalfBot(tmeElapsed,EventInfo.intDURATION);

              crgbA = CRGB(0,0,0);
              crgbB = EventInfo.crgbCOLORDEST1;
            }
            else
            {
              fltPower = ComputePowerHalfTop(tmeElapsed,EventInfo.intDURATION);

              crgbA = EventInfo.crgbCOLORDEST2;
              crgbB = EventInfo.crgbCOLORDEST1;
            }

            tmpColor = Dither(fltPower, crgbA, crgbB);
            
            tmpColor.complete = false;

            return tmpColor;
            break;
          }
        } // END CASE AnPiPulseTo

      
      case AnPiTwinkle:
        // Random Sparkling Twinkly Lights 
        {

          if (tmeCurrentTime >= tmeAnimTime + EventInfo.intDURATION)
          {
            tmpColor.complete = true;
            
            return tmpColor;
            break; 
          }
          else
          {
            CRGB crgbTwinkleColor;

            // Using crgbDest2 to pass twinkle parameters.
            int intOdds       = EventInfo.crgbCOLORDEST2.r;  // Chance that the light will twinkle.
            int intTimeReduce = EventInfo.crgbCOLORDEST2.g;  // Percentage of Time Duration Light is On. 
            int intColorCount = EventInfo.crgbCOLORDEST2.b;  // Amount of colors passed through the Event. 

            // We will need a signed Elapsed time.  Half as small, but we need to 
            //  subtract things from it. 
            int NewElapsedTime = tmeElapsed;

            // Generate Random Number Seed.  The random numbers generated from 
            //  the picked position is sequential from the start. Also, the generated 
            //  random number is time dependant. Neither of these two things help 
            //  when we need to restart this sequence thousands of time within the 
            //  same milisecond. 
            //  randomSeed(tmeAnimTime + intEvent + intLED);

            // Pick 1 of 3 colors and determine if we will turn on the light.
            unsigned long seed = tmeAnimTime + intLED + intEvent;
            char  Odds = sRND.getB(seed, intOdds);

            // Determine if the light was lucky enough to be turned on then assign it 
            //  one of the random colors of the draw. 
            if (Odds == 0)
            {

              // If the light will not be illuminated during its entire duration cycle, 
              // then pick a random time it is to start its illumination. 
              if (intTimeReduce != 0)
              {
                // Pick a random delay. 
                long NewTimeStart = sRND.getUL(seed, floor(EventInfo.intDURATION * (float)intTimeReduce / 100)); 

                // Calculate how much long the light will on from the percentage of 
                //  of the duration. 
                intTimeReduce = 100 - intTimeReduce;
                EventInfo.intDURATION = EventInfo.intDURATION * (float)(intTimeReduce) / 100;

                // Figure out the new time to turn on the light.
                NewElapsedTime = NewElapsedTime - NewTimeStart;
              }


              char  Color = sRND.getB(seed, intColorCount);
              // Assign 1 of the 3 colors. 
              if (Color == 0)
              {
                crgbTwinkleColor = EventInfo.crgbCOLORSTART1; 
              }
              else if (Color == 1)
              {
                crgbTwinkleColor = EventInfo.crgbCOLORDEST1;
              }
              else
              {
                crgbTwinkleColor = EventInfo.crgbCOLORSTART2;
              }


              // Continue with the lights illumination if it was lucky enough to be 
              //  turned on and if it was lucky enough to fall within the time to be turned on.
              if ((NewElapsedTime >= 0) && (NewElapsedTime <= NewElapsedTime + EventInfo.intDURATION))
              {
                // Modified Pulse Routine ----  Pulse routine used offten.  I should function it. 
                if ((NewElapsedTime * 2) <= (EventInfo.intDURATION))
                { 
                  // Not working with ComputePower function.              
                  fltPower = (float)(NewElapsedTime) * 2 / ((float)EventInfo.intDURATION);
                }
                else
                {
                  // Not working with ComputePower function.
                  fltPower = 1 - (((float)((NewElapsedTime * 2) - EventInfo.intDURATION) / (float)EventInfo.intDURATION));
                }

                // No Negative Colors
                if ( (fltPower > 0) && (fltPower < 1) )
                {
                  //  Swap to second color at mid point
                  tmpColor = Dither(fltPower, CRGB(0,0,0), crgbTwinkleColor);
                }

                tmpColor.complete = false;
              }
            }

            return tmpColor;  
            break;
          }
        } // END CASE AnPiTwinkle

    } // END SWITCH STATEMENT
    return tmpColor;
  }

  // -------------------------------------------------------------------------------------

  bool execute(Console &cons, stupid_random sRND, CRGB hwLEDArray[], unsigned long tmeCurrentTime)
  //  Sets all requested light paths, start to end position, to begin their animation
  //    at a future time.

  //  Event Animations:
  //    0 - Clear:  Clears future event and sets to no future future.
  //    1 - Sweep:  Sets light paths for all LEDs from start to end posion.
  //                  Speed is the time difference in miliseconds between each adjacent
  //                  light path.
  //                  Duration, destination color, and LED animation will also be passed
  //                  to its light path.
  {
    bool booPixelColorChanged;
    int activeeventcount;
    
    bool booEventActive[teDATA.size()];
    bool booEventComplete[teDATA.size()];
    
    bigCRGB bigcrgbNewColor;
    bigCRGB tempColor;

    bool booChanged = false;
    unsigned long tmeStartAnim;

    // Process Event Animations  
    // Prepare Arrays
    if (teDATA.size() > 0)
    {
    for (int e = 0; e < teDATA.size(); e++) //Duplicate
      {
        // Prepare Temporary Complete Array With Events That May Run
        if (tmeCurrentTime >= teDATA[e].tmeSTARTTIME  && teDATA[e].booCOMPLETE == false)
        {
          booEventComplete[e] = true;
        }

        // Clear Active Event Array
        booEventActive[e] = false;
      }
      // Process LEDs, one by one.
      for (int led = 0; led < intLEDCOUNT; led++)
      {
        //  Attempt to restrict the amount of times the activity tracker routine is ran.
        activeeventcount = 0;

        // Clear the value of the new LED color.  Should only update when it has changed.
        bigcrgbNewColor.r = 0;
        bigcrgbNewColor.g = 0;
        bigcrgbNewColor.b = 0;

        booPixelColorChanged = false;

        // Process each event, one by one.
        for (int event = 0; event < teDATA.size(); event++)
        {
          // Clear the tmp colors, in case they have data in them at the start of each 
          //  event process.
          tempColor.r = 0;
          tempColor.g = 0;
          tempColor.b = 0;

          // Only continue processing the event if the event hasnt been completed.
          if (teDATA[event].booCOMPLETE == false)
          {
            // Is the LED we are processing within the event?
            if (((led >= teDATA[event].intSTARTPOS) && (led <= teDATA[event].intENDPOS))
                || ((led <= teDATA[event].intSTARTPOS) && (led >= teDATA[event].intENDPOS)))
            {
              // OK, so an event is schedule, but is it ready to start?
              if (tmeCurrentTime >= teDATA[event].tmeSTARTTIME)
              {
                // Collision Tracker
                activeeventcount++;   //  Attempt to restrict the amount of times this 
                                      //    routine is ran.
                booEventActive[event] = true;

                // Figure out when the LED is suposed to start doing something.
                tmeStartAnim = teDATA[event].tmeSTARTTIME
                              + (abs((led - teDATA[event].intSTARTPOS))
                                  * teDATA[event].intSPEED);

                // The Pixel on this Event is ready to change.
                if ((tmeCurrentTime >= tmeStartAnim))
                {
                  // -------------------------------------------------------------------
                  // This Routine can be applied to all animation types. Itsjust not
                  //  implemented until needed.  Also kept seperate becuase it uses
                  //  a few more clock cycles. e.g. PulseDither and PulseToDither 
                  //  can be created.  But not the Twinkle.  Twinkle is passing direct
                  //  colors. 

                  // Preprocess Dest 2 for dynamic DEST2 on Pixel Fade.
                  if (teDATA[event].bytLEDANIMATION == AnPiFadeDith)
                  {

                  }
                  // -------------------------------------------------------------------

                  switch (teDATA[event].bytANIMATION)
                  {
                    case AnEvSweep:
                      {
                        // Calculate how much this Event will chaange the pixel.
                        //  Breaking the norm, but also passing the led ID and
                        //  original 4 colors to ... (consider rewrite)
                        tempColor = crgb_anim_color(sRND, tmeCurrentTime, tmeStartAnim, 
                                                    led, event, teDATA[event]);

                        //  Update the events completeness if its still active.
                        if (tempColor.complete == false)
                        {
                          booEventComplete[event] = false;
                        }

                        // Check for inverted color and invert if necessary.
                        if (teDATA[event].booINVERTCOLOR == false)
                        {
                          bigcrgbNewColor.r = bigcrgbNewColor.r + tempColor.r;
                          bigcrgbNewColor.g = bigcrgbNewColor.g + tempColor.g;
                          bigcrgbNewColor.b = bigcrgbNewColor.b + tempColor.b;
                        }
                        else
                        {
                          bigcrgbNewColor.r = bigcrgbNewColor.r - tempColor.r;
                          bigcrgbNewColor.g = bigcrgbNewColor.g - tempColor.g;
                          bigcrgbNewColor.b = bigcrgbNewColor.b - tempColor.b;
                        }

                        booPixelColorChanged = true;
                        break;
                      } // End Case AnEvSweep
                  } // End Switch Statement
                }
              } // End Time Check
            } // End LED Postion Check
          } // End Expiration Check
        } // End For Event Loop

        // Now that all event are processeds, update the Main LED to the new value.
        // But only if it changed.
        if (booPixelColorChanged == true)
        {
          // Calclulate the color of LED by adding the colors togegher.

          // If the lights are out range, either put them at full on or full off.
          if (bigcrgbNewColor.r > 255)
          {
            bigcrgbNewColor.r = 255;
          }
          if (bigcrgbNewColor.g > 255)
          {
            bigcrgbNewColor.g = 255;
          }
          if (bigcrgbNewColor.b > 255)
          {
            bigcrgbNewColor.b = 255;
          }
          if (bigcrgbNewColor.r  < 0)
          {
            bigcrgbNewColor.r = 0;
          }
          if (bigcrgbNewColor.g  < 0)
          {
            bigcrgbNewColor.g = 0;
          }
          if (bigcrgbNewColor.b  < 0)
          {
            bigcrgbNewColor.b = 0;
          }

          // Set the color of the LED on the strip.
          hwLEDArray[led].r = (char)bigcrgbNewColor.r;
          hwLEDArray[led].g = (char)bigcrgbNewColor.g;
          hwLEDArray[led].b = (char)bigcrgbNewColor.b;

          booChanged = true;
        }
      } // End For LED Loop

      // All Leds Processed

      //  Check to see if any events expire or repeats.
      int e = 0;
      while ( e < teDATA.size() )
      {

        if (booEventActive[e] == true && booEventComplete[e] == true)
        {
          teDATA[e].booCOMPLETE = true;
          teDATA[e].PostCheck(tmeCurrentTime);
        }
        e++;
      }

      e = 0;
      while ( e < teDATA.size() )
      {
        if (teDATA[e].booCOMPLETE == true)
        {
          //printf("Removing Event %d\n", e);
          teDATA.erase(teDATA.begin() + e);
        }
        else
        {
          e++;
        }
      }

    } // End teDATA size check.

  return booChanged;
  
  }
};


// ---------------------------------------------------------------------------------------
// Hardware Monitor Variable

class hardware_monitor
// Create a hardware switch or button varable type.
{
  public:
  // External
  bool booVALUE = false;
  unsigned long tmeTOGGLEDTIME = 0;
  bool ISHARDWARE = false;

  private:
  // Internal
  unsigned long tmeCHANGEDETECTEDTIME = 0;
  bool booPREVCHANGEDETECTED = false;
  unsigned int tmeLEEWAY = 0;
  bool booFIRSTRUN = true;

  public:
  void set(bool booValue, unsigned long tmeCheckTime, int tmeLeeWay, bool isHardware)
  // Prepare the switch.
  {
    tmeCHANGEDETECTEDTIME = tmeCheckTime;
    tmeLEEWAY = tmeLeeWay;
    booVALUE = booValue;
    booPREVCHANGEDETECTED = false;
    ISHARDWARE = isHardware;
  }

  bool changed(bool booValue, unsigned long tmeCheckTime)
  // Return true if the switch state change from on to off or off to on.
  {
    unsigned long tmeTme = tmeCheckTime;

    // If the switch was just activated then run any set up its initial state and run
    //  any special routines.
    if (booFIRSTRUN == true)
    {
      booVALUE = booValue;
      booPREVCHANGEDETECTED = false;
      tmeCHANGEDETECTEDTIME = tmeTme;
      booFIRSTRUN = false;

      if (BOOTEST == false)
      {
        return booValue;  // Comment this line out when testing
        //return false;   // Comment this line out when not testing
      }
      else
      {
        //return booValue;// Comment this line out when testing
        return false;     // Comment this line out when not testing
      }
    }
    else if (booVALUE == booValue)
    {
      booPREVCHANGEDETECTED = false;
      return false;
    }
    else if (booPREVCHANGEDETECTED == false)
    {
      tmeCHANGEDETECTEDTIME = tmeTme;
      booPREVCHANGEDETECTED = true;
      return  false;
    }
    // Only report change of status when Leeway time is passed.  This is a essentially a
    //  debouncer.
    else if (tmeTme < (tmeCHANGEDETECTEDTIME + tmeLEEWAY))
    {
      return false;
    }
    else
    {
      booVALUE = booValue;
      booPREVCHANGEDETECTED = false;
      tmeCHANGEDETECTEDTIME = tmeTme;
      tmeTOGGLEDTIME = tmeTme;
      return true;
    }
  }
};


// ***************************************************************************************
// FUNCTION AND PROCEDURES
// ***************************************************************************************


int intRandomHD(int intBase)
// Generate a random number between half and double of the base
{
  int intLowerOffset = intBase / 2;
  int intUpperOffset = (intBase * 2) - intLowerOffset;
  return ((rand() % intUpperOffset) + intLowerOffset);
}

// Clear events on a channel 
void vdClearAllTimedEvent(timed_event teEvent[], int intPos, int intStartPos, int intEndPos)
//  Sort through the timed event list a create an event at the first slot available.
{
  teEvent[intPos].ClearAll(intStartPos, intEndPos);
}

// --- ANIMATIONS ------------------------------------------------------------------------

// PARAMETER REFFERENCE

//  Reference:
//TIMED EVENT  PARAMETERS
//light_path lpLightPaths[],
//unsigned long tmeCurrentTime,
//unsigned long tmeStartInTime,
//unsigned int intDuration,
//unsigned int intSpeed,
//char  bytAnimation,
//char  bytLEDAnimation,
//CRGB crgbColor,
//int intStartPos,
//int intEndPos,
//bool booRepeat,
//bool booClearOnEnd,

// -------------------------------------------------------------------------------------

// Calculate time it takes for an animation event to run.

int intAnTmDly(int intTm, int intDur, int intCt, int intSp)
// Calculate and return the next delay time based on duration of event, number of pixels,
//  and animation speed of each pixel.
//  Value in return statement is buffer time.
{
  //return (1 + (RESTTIME) + intTm + intDur + (intSp * intCt));
  return (1 + intTm + intDur + (intSp * intCt));
}

/*
// -------------------------------------------------------------------------------------
void vdTESTFLASHAnimation(Console &cons, led_strip lsStrips[], led_strip lsSt, timed_event teEvent[], unsigned long tmeCurrentTime)
{
  int intTm;
  int intDur;
  int intCt;
  int intSp;

  intDur = 500; intSp = 50; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 50, intDur, intSp, AnEvSweep, AnPiPulseTo, CRGB(20, 20, 20), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
}
*/

// -------------------------------------------------------------------------------------
// Animations and Animation Scripts
// -------------------------------------------------------------------------------------

// Normal Animations (Main Procedures)



void vdOpenDoorNormal(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdOpenDoorNormal
{
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTaDoorOpen00, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdOpenOverNormal(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdOpenOverNormal
{
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdPacificaish, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseDoorNormal(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdCloseDoorNormal
{
  teEvent[lsStrips[intStripID].Cl].set("Door Close Anim", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColor, false, CRGB(125,125,0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverNormal(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdCloseOverNormal
{
  teEvent[lsStrips[intStripID].Cl].set("Overhead Close Anim", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTaStripOverOff, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverCoNormal(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdCloseOve2Normal
{
  int intTm;
  int intDur;
  int intSp;

  //Restore the privouse Blue to fade out
  intTm = 200; intDur = 6000; intSp = 5;

  teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm , intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 60), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, false, true);
  teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdPaAnimClose, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

/*
// Halloween Animations (Main Procedures)

void vdOpenOverHallow(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdOpenOverHallow
{
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdCloud, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdCeilingLight, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdLightning, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverHallow(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdCloseOverHallow
{
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdChannelLightning, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdHallowClose2(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Halloween Overhead Close 2 - Orange Ambiant and Off Routine
{
  // AnTavdHallowClose2

  // Stop the animation.
  // Schedule clear animation events ahead of time in case animations don't get completed.
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, AUXDRLINGERBCK + 2000, 0, 0, AnEvClearRunning, 0, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, AUXDRLINGERBCK + 2100, 3000, 30, AnEvSweep, AnPiFade, CRGB(4, 6, 10), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);

  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdChannelLightning, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 50, 0, 0, AnEvSchedule, AnTavdCloud, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[lsStrips[intStripID].Cl].St, lsStrips[lsStrips[intStripID].Cl].Ed, false, true);
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------


// Thanksgiving Animations (Main Procedures)

void vdOpenOverThanks(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdOpenOverThanks
{
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdBlueSky, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverThanks(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdCloseOverThanks
{
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTaStripOverOffThanks, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverThanksCo(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdCloseOverThanksCo
{
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdNightSkyClose, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdAddOpenThanks(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavd----  // Simple
{
  teEvent[lsStrips[intStripID +1].Cl].set("Nothing", tmeCurrentTime, 4000, 1000, 40, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(125,125,0), lsStrips[intStripID +1].St, lsStrips[intStripID +1].Ed, false, false);
}

void vdAddCloseThanks(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavd----  // Simple
{
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 4000, 1000, 40, AnEvSweep, AnPiFade, CRGB(0, 0, 0), CRGB(0, 0, 30), CRGB(0, 0, 0), CRGB(0, 0, 30), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(125), AnEvSweep, AnPiPulse, CRGB(30, 30, 30), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
}
*/


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// Christmas Animations (Main Procedures)

// Normal Animations (Main Procedures)

void vdOpenDoorChristmas(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// ---
{
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTaDoorOpen00Christmas, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdOpenOverChristmas(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// ---
{
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdChristmasTree, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseDoorChristmas(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// ---
{
  teEvent[lsStrips[intStripID].Cl].set("Door Close Anim", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColor, false, CRGB(64,64,0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverChristmas(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// ---
{
  teEvent[lsStrips[intStripID].Cl].set("Overhead Close Anim", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColor, false, CRGB(64,64,0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverCoChristmas(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// ---
{
  teEvent[lsStrips[intStripID].Cl].set("Overhead Close Anim", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdChristmasTreeCo, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);  
}

void vdAddOpenChristmas(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavd----  // Simple
{
  teEvent[lsStrips[intStripID].Cl].set("Open Additional Anim", tmeCurrentTime, 500, 0, 0, AnEvSchedule, AnTavdAddOpenChristm, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);  
}

void vdAddCloseChristmas(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavd----  // Simple
{
  teEvent[lsStrips[intStripID].Cl].set("Door Open Anim", tmeCurrentTime, 500, 0, 0, AnEvSchedule, AnTavdAddCloseChristm, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);    
 }

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// Test Animations (Main Procedures)

void vdOpenDoorTest(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdOpenDoorNormal
{
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 500, 8000, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(1, 90, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 1500, 8000, 0, AnEvSweep, AnPiTwinkle, CRGB(64, 64, 0), CRGB(64, 0, 64), CRGB(0, 64, 64), CRGB(1, 90, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);

  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 500, 8000, 0, AnEvSweep, AnPiTwinkle, false, CRGB(64, 64, 64), CRGB(64, 0, 64), CRGB(0, 64, 64), CRGB(4, 90, 1), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);

  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 400, 350, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(4, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 500, 475, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(4, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 600, 525, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(4, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);

  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 500, 4000, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(2, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 400, 6237, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(2, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 300, 8713, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(20, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 200, 11031, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(20, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// Standard Animations and Effects 

/*
void vdPowerOnAnimation(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Just to show the lights work when the program starts.
{
  // Update Animation Status 
  lsStrips[Driver_Back_Door].AnimationStatus = Unknown;
  lsStrips[Driver_Back_Over].AnimationStatus = Unknown;
  lsStrips[Driver_Front_Door].AnimationStatus = Unknown;
  lsStrips[Driver_Front_Over].AnimationStatus = Unknown;
  lsStrips[Passenger_Back_Door].AnimationStatus = Unknown;
  lsStrips[Passenger_Back_Over].AnimationStatus = Unknown;
  lsStrips[Passenger_Front_Door].AnimationStatus = Unknown;
  lsStrips[Passenger_Front_Over].AnimationStatus = Unknown;


  int intTm;
  int intDur;
  int intCt;
  int intSp;

  intDur = 250; intSp = 5; intCt = 118;
  // Pulse Front Door
  teEvent[1].set("Nothing", tmeCurrentTime, 50, intDur, intSp, AnEvSweep, AnPiPulseTo, false,  CRGB(125, 125, 125),CRGB(0, 0, 25), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[Front_Over].Ed, lsStrips[Front_Door].St, false, true);
  // Pulse Back Door
  teEvent[0].set("Nothing", tmeCurrentTime, 640, intDur, intSp, AnEvSweep, AnPiPulseTo, false, CRGB(125, 125, 125), CRGB(0, 0, 25), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[Back_Over].Ed, lsStrips[Back_Door].St, false, true);


  intDur = 2000; intSp = 15; intCt = 71;
  // Clear Front Door
  teEvent[1].set("Nothing", tmeCurrentTime, 890, intDur, intSp, AnEvSweep, AnPiFade, false, CRGB(0, 0, 25), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[Front_Over].Ed, lsStrips[Front_Door].St, false, true);
  // Clear Back Door
  teEvent[0].set("Nothing", tmeCurrentTime, 1480, intDur, intSp, AnEvSweep, AnPiFade, false, CRGB(0, 0, 25), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[Back_Over].Ed, lsStrips[Back_Door].St, false, true);
}
*/

// -------------------------------------------------------------------------------------

// Pulse strip Color then fade out.

void vdStripOverOff(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn (force) Lights Off ona Strip
{
  int intTm;
  int intDurW;
  int intDurG;
  int intSp;

  int intDelay;

    // Swap sweep start and end, depending on front or back.
  int start;
  int end;
  if (lsStrips[intStripID].Cl == 0)
  {
    start = lsStrips[intStripID].St;
    end = lsStrips[intStripID].Ed;
  }
  else
  {
    start = lsStrips[intStripID].Ed;
    end = lsStrips[intStripID].St;
  }

  // Clear and Pulse colors background to color then ending in color, starting with the center.
  intTm = 50; intDurW = 200; intDurG = 1500; intSp = 5;
  intDelay = intAnTmDly(intTm, 0, lsStrips[intStripID].Ct(), intSp);

  // Door White
  //teEvent[lsStrips[intStripID].Cl].set("vdStripOverOff", tmeCurrentTime, intTm + 50, intDurW, intSp, AnEvSweep, AnPiPulse, CRGB(64, 128, 64), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[lsStrips[intStripID].Cl].St, lsStrips[lsStrips[intStripID].Cl].Ed, false, true);
  // Overhead White
  teEvent[lsStrips[intStripID].Cl].set("vdStripOverOff", tmeCurrentTime, intTm + intDelay + 50, intDurW, intSp, AnEvSweep, AnPiPulse, false, CRGB(64, 128, 64), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0),  start, end, false, true);
 
  // Door Green Fadeout
  //teEvent[lsStrips[intStripID].Cl].set("vdStripOverOff", tmeCurrentTime, intTm, intDurG, intSp, AnEvSweep, AnPiPulse, CRGB(0, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[lsStrips[intStripID].Cl].St, lsStrips[lsStrips[intStripID].Cl].Ed, false, true);
  // Overhead Green Fadeout
  teEvent[lsStrips[intStripID].Cl].set("vdStripOverOff", tmeCurrentTime, intTm + intDelay, intDurG, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0),  start, end, false, true);
}

// -------------------------------------------------------------------------------------

// Pulse channel Specific Color then fade out.

void vdChannelLightPulseColor(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor)
// Turn (force) Green Pulse on Full Channel. Strip Length Aware. 
// AnTaChannelPulseColor
{
  cons.printwait("vdChannelLightPulseColor (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");
  int intTm;
  int intDurW;
  int intDurG;
  int intCt;
  int intSp;

  int intDelay;

  // Set the fadeout color 
  CRGB crgbColor4;
  crgbColor4.r = crgbColor.r + 128;
  crgbColor4.g = crgbColor.g + 128;
  crgbColor4.b = crgbColor.b + 128;

  // Swap sweep start and end, depending on front or back.
  int start;
  int end;
  if (lsStrips[intStripID].Cl == 0)
  {
    start = lsStrips[intStripID +1 ].St;
    end = lsStrips[intStripID +1 ].Ed;
  }
  else
  {
    start = lsStrips[intStripID +1 ].Ed;
    end = lsStrips[intStripID +1 ].St;
  }

  // Clear and Pulse colors background to bright then param color, starting with the center.
  intTm = 50; intDurW = 500; intDurG = 1500; intSp = 30; intCt = 36;
  intDelay = intAnTmDly(intTm, 0, lsStrips[intStripID].Ct(), intSp);

  // Door Color with White
  teEvent[lsStrips[intStripID].Cl].set("Channel Light Pulse Color", tmeCurrentTime, intTm + 50, intDurW, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor4, CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  // Overhead Color with White
  teEvent[lsStrips[intStripID].Cl].set("Channel Light Pulse Color", tmeCurrentTime, intTm + intDelay + 50, intDurW, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor4, CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, true);
 
  // Door Color Fadeout
  teEvent[lsStrips[intStripID].Cl].set("Channel Light Pulse Color", tmeCurrentTime, intTm, intDurG, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  // Overhead Color Fadeout
  teEvent[lsStrips[intStripID].Cl].set("Channel Light Pulse Color", tmeCurrentTime, intTm + intDelay, intDurG, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, true);

  // Set the pulse to timed repeat
  teEvent[lsStrips[intStripID].Cl].set("Channel Light Pulse Color", tmeCurrentTime, 1500, 0, 0, AnEvSchedule, AnTaChannelPulseColor, false, crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true);  
}


void vdOverheadIllum(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor)
// Blue Waves. Much more interesting than the old version of this.
{
  cons.printwait("vdOverheadIllum (CL: " + std::to_string(lsStrips[intStripID  +1].Cl) + " ID:"+ std::to_string(intStripID  +1) + " S:" + std::to_string(lsStrips[intStripID  +1].St) + " E:" + std::to_string(lsStrips[intStripID  +1].Ed) + ")");

  // Swap sweep start and end, depending on front or back.
  int start;
  int end;

  if (lsStrips[intStripID  +1].Cl == 0)
  {
    start = lsStrips[intStripID  +1].St;
    end = lsStrips[intStripID  +1].Ed;
  }
  else
  {
    start = lsStrips[intStripID  +1].Ed;
    end = lsStrips[intStripID  +1].St;
  }
  
  // Set the background color.
  teEvent[lsStrips[intStripID  +1].Cl].set("Overhead Illumination", tmeCurrentTime, 1000, 500, 30, AnEvSweep, AnPiFade, false, CRGB(0, 0, 0), crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, false);
}


void vdHazard(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Blue Waves. Much more interesting than the old version of this.
{
  cons.printwait("vdHazard (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID  +1) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");

  // Swap sweep start and end, depending on front or back.
  int start;
  int end;

  if (lsStrips[intStripID + 1].Cl == 0)
  {
    start = lsStrips[intStripID + 1].St;
    end = lsStrips[intStripID + 1].Ed;
  }
  else
  {
    start = lsStrips[intStripID + 1].Ed;
    end = lsStrips[intStripID + 1].St;
  }
  
  // Set the background color.
  teEvent[lsStrips[intStripID].Cl].set("Hazard", tmeCurrentTime, 100, 900, 0, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(25, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  teEvent[lsStrips[intStripID + 1].Cl].set("Hazard", tmeCurrentTime, 100, 900, 0, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(25, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, true);

  // Set the hazard to timed repeat
  teEvent[lsStrips[intStripID].Cl].set("Hazard", tmeCurrentTime, 1500, 0, 0, AnEvSchedule, AnTaHazard, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true);  
}



// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// Normal door open animation script

// Mock Normal Open Door Animation
void vdDoorOpenAnimation(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door Open 
// Door is open, engage safety lights and start door overhead lights.
{
  //Door Animation
  // Clear Events On Door
  vdClearAllTimedEvent(teEvent, lsStrips[intStripID].Cl, lsStrips[intStripID].St, lsStrips[intStripID].Ed);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTaDoorOpen00, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);

  // Clear Events for the Overhead Animation
  vdClearAllTimedEvent(teEvent, lsStrips[intStripID].Cl, lsStrips[intStripID +1 ].St, lsStrips[intStripID +1 ].Ed);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdPacificaish, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

// -------------------------------------------------------------------------------------

void vdDoorOpenAnimation00(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door Open Stage 0
// Prepare red backgrounds and puddle lights for the caution lights, and start shimmer effect.
{
  cons.printwait("vdDoorOpenAnimation00 (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");
  int intTm;
  int intDur;
  int intCt;
  int intSp;
  // Door Open Animation
  intTm = 100; intDur = 500; intSp = 10; intCt = lsStrips[intStripID].Ct(); // was 60

  // Clear set background to door open colors.
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(255, 255, 255), CRGB(0, 0, 0), CRGB(255, 64, 64), lsStrips[intStripID].St, lsStrips[intStripID].St + 4, false, false);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(255, 64, 64), CRGB(0, 0, 0), CRGB(25, 0, 0), lsStrips[intStripID].St + 5, lsStrips[intStripID].St + 10, false, false);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFade, false, CRGB(0, 0, 0), CRGB(25, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St + 11, lsStrips[intStripID].Ed - 6, false, false);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm + 500, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(25, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed - 5, lsStrips[intStripID].Ed, false, false);

  // Shimmer
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, 10000, 500, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(15, 20, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, 6000, 280, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(15, 20, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);

  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, 0, 0, AnEvSchedule, AnTaDoorOpen01, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

// -------------------------------------------------------------------------------------

void vdDoorOpenAnimation01(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door Open Stage 1
{
  cons.printwait("vdDoorOpenAnimation01 (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");
  int intTm = 50;
  int intDur;
  int intCt;
  int intSp;

  // Caution Door Open Flash
  intDur = 100; intSp = 2; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  intDur = 600; intSp = 12; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  intDur = 1500; intSp = 30; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(128, 128, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);

  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, 0, 0, AnEvSchedule, AnTaDoorOpen02, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

// -------------------------------------------------------------------------------------

void vdDoorOpenAnimation02(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door Open Stage 2
{
  cons.printwait("vdDoorOpenAnimation02 (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");
  int intTm = 0;
  int intDur;
  int intCt;
  int intSp;
  int intMid = lsStrips[intStripID].Ct() / 2;

  // Repeat Pulse
  intDur = 1500; intSp = 125; intCt = lsStrips[intStripID].Ct(); // was 36
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(255, 255, 0), CRGB(255, 255, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].St + intMid, true, true);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(255, 255, 0), CRGB(255, 255, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].Ed - intMid, true, true);
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// Normal close door animation script.

// Mock Normal Close Door Animation
void vdDoorCloseAnimation(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door Close Stage 0
// Door is closed, disengage safety lights and stop door overhead lights.
{
  cons.printwait("vdDoorCloseAnimation (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");
  int intTm;
  int intDur;
  int intSp;

  //  Clear Currently Running Animations First
  //  Door
  vdClearAllTimedEvent(teEvent, lsStrips[intStripID].Cl, lsStrips[intStripID].St, lsStrips[intStripID].Ed);
  //  Overhead
  vdClearAllTimedEvent(teEvent, lsStrips[intStripID +1 ].Cl, lsStrips[intStripID +1 ].St, lsStrips[intStripID +1 ].Ed);

  // Pulse Clear All Animations
  teEvent[lsStrips[intStripID].Cl].set("Door Close Anim", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColor, false, CRGB(125,125,0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  
  //Restore the privouse Blue to fade out
  intTm = 200; intDur = 6000; intSp = 5;
  teEvent[lsStrips[intStripID].Cl].set("Door Close Anim", tmeCurrentTime, intTm , intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 60), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID +1 ].Ed, lsStrips[intStripID +1 ].St, false, true);

  // Door Animation
  //  No Need While Green Whipe Is Clearing

  // Overhead Animation
  teEvent[lsStrips[intStripID].Cl].set("Door Close Anim", tmeCurrentTime, 1500, 0, 0, AnEvSchedule, AnTavdPaAnimClose, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID +1 ].St, lsStrips[intStripID +1 ].Ed, false, true);
}

// -------------------------------------------------------------------------------------

void vdDoorCloseAnimation00(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door closed.  Quick animation to show and turn off lights.
{
  // Fade remaining colors out.

  //  // Not Necesary because clearing door with Green Whipe
  //intTm = intAnTmDly(intTm, intDur, intCt, intSp) + 300;
  //intDur = 5000; intSp = 100; intCt = 36;
  //teEvent[intPos].set("Door Close Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFade, CRGB(0, 20, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

/*
// Close overhead animation script

void vdPacificaishAnimationClose(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
{
  // Stop the currently running Pacificaish animation.
  // Schedule clear animation events ahead of time in case animations don't get completed.
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, AUXDRLINGERBCK + 2000, 0, 0, AnEvClearRunning, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, AUXDRLINGERBCK + 2100, 3000, 30, AnEvSweep, AnPiFade, false, CRGB(20, 4, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);

  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 50, 0, 0, AnEvSchedule, AnTavdPaAnimClose00, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[lsStrips[intStripID].Cl].St, lsStrips[lsStrips[intStripID].Cl].Ed, false, true);
}

// -------------------------------------------------------------------------------------

// Amber wave animations on strip.

void vdPacificaishAnimationClose00(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Amber Waves
{
  // Swap sweep start and end, depending on front or back.
  int start;
  int end;
  if (lsStrips[intStripID].Cl == 0)
  {
    start = lsStrips[intStripID].St;
    end = lsStrips[intStripID].Ed;
  }
  else
  {
    start = lsStrips[intStripID].Ed;
    end = lsStrips[intStripID].St;
  }
  // Set the background color to Amber.
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 50 + 2000, 3000, 30, AnEvSweep, AnPiFade, false, CRGB(0, 0, 0), CRGB(20, 4, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, false);

  // Amber waves.
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000) + 2000, intRandomHD(3500), intRandomHD(250), AnEvSweep, AnPiPulse, false, CRGB(20, 4, 0), CRGB(20, 4, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000) + 2000, intRandomHD(1500), intRandomHD(150), AnEvSweep, AnPiPulse, false, CRGB(16, 20, 0), CRGB(16, 20, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000) + 2000, intRandomHD(3600), intRandomHD(270), AnEvSweep, AnPiPulse, false, CRGB(15, 6, 0), CRGB(20, 4, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000) + 2000, intRandomHD(3200), intRandomHD(200), AnEvSweep, AnPiPulse, false, CRGB(25, 2, 0), CRGB(20, 4, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// Blue wave animations on strip.

void vdPacificaishAnimation(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Blue Waves
{
  // Swap sweep start and end, depending on front or back.
  int start;
  int end;
  if (lsStrips[intStripID].Cl == 0)
  {
    start = lsStrips[intStripID].St;
    end = lsStrips[intStripID].Ed;
  }
  else
  {
    start = lsStrips[intStripID].Ed;
    end = lsStrips[intStripID].St;
  }
  
  // Set the background color.
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 1000, 500, 30, AnEvSweep, AnPiFade, false, CRGB(0, 0, 0), CRGB(0, 0, 60), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, false);

  // The waves.
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(3500), intRandomHD(250), AnEvSweep, AnPiPulse, false, CRGB(40, 200, 160), CRGB(40, 200, 160), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(1500), intRandomHD(150), AnEvSweep, AnPiPulse, false, CRGB(160, 200, 40), CRGB(40, 200, 160), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(3600), intRandomHD(270), AnEvSweep, AnPiPulse, false, CRGB(20, 200, 180), CRGB(40, 200, 160), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(3200), intRandomHD(200), AnEvSweep, AnPiPulse, false, CRGB(60, 200, 140), CRGB(40, 200, 160), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
}
*/


// -------------------------------------------------------------------------------------
// Advanced Animations
// -------------------------------------------------------------------------------------

void vdEndAllAnimationsADV(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Run this routine on all Doors after all doors are closed to ensure no lingering animations have not been ended for whatever reason.
{
  cons.printwait("vdEndAllAnimationsADV (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");
  teEvent[lsStrips[intStripID].Cl].set("", tmeCurrentTime, 20000, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID + 1].Ed, true, true);
}


void vdDoorOpenAnimationADV00(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door Open Stage 0
// Prepare red backgrounds and puddle lights for the caution lights, and start shimmer effect.
{
  cons.printwait("vdDoorOpenAnimationADV00 (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");
  int intTm;
  int intDur;
  int intCt;
  int intSp;

  // Give strip a fresh start.
  vdClearAllTimedEvent(teEvent, lsStrips[intStripID].Cl, lsStrips[intStripID].St, lsStrips[intStripID].Ed);

  CRGB lead = CRGB(20, 20, 20);
  CRGB shadow = CRGB(50 ,50, 50);

  // Door Open Animation
  intTm = 100; intDur = 500; intSp = 10; intCt = lsStrips[intStripID].Ct(); // was 60

  // Clear set background to door open colors.
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(255, 255, 255), CRGB(0, 0, 0), CRGB(255, 64, 64), lsStrips[intStripID].St, lsStrips[intStripID].St + 4, false, false);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(255, 64, 64), CRGB(0, 0, 0), CRGB(25, 0, 0), lsStrips[intStripID].St + 5, lsStrips[intStripID].St + 10, false, false);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm + 500, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(25, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St + 11, lsStrips[intStripID].Ed, false, false);

  // Shimmer
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, 10000, 500, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(15, 20, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, 6000, 280, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(15, 20, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);

  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  
  // Reverse Shadow Blink
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm + intDur, intDur, intSp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), shadow, CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, true, true);

  // Caution Door Open Flash
  intDur = 50; intSp = 1; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, 50, intSp, AnEvSweep, AnPiPulse, false, lead, lead, CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, false, true);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, false, true);
  
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);

  intDur = 100; intSp = 2; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, 50, intSp, AnEvSweep, AnPiPulse, false, lead, lead, CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, false, true);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, false, true);
  
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);

  intDur = 200; intSp = 4; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, 50, intSp, AnEvSweep, AnPiPulse, false, lead, lead, CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, false, true);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, false, true);
  
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);

  intDur = 400; intSp = 8; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, 50, intSp, AnEvSweep, AnPiPulse, false, lead, lead, CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, false, true);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, false, true);
  
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);

  intDur = 800; intSp = 16; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, 100, intSp, AnEvSweep, AnPiPulse, false, lead, lead, CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, false, true);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(128, 128, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, false, true);
  
  //intTm = intAnTmDly(intTm, intDur, intCt, intSp);

  // Repeat Pulse
  intDur = 1500; intSp = 125; intCt = lsStrips[intStripID].Ct();
  int intMid = lsStrips[intStripID].Ct() / 2;
  int intTm2Off = (intMid * intSp + intDur) /2;
  
  // Pulse up to mid
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(128, 128, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed - intMid, true, true);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm + intTm2Off, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(128, 128, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed - intMid, true, true);

  // Pulse down to mid
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(128, 128, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St + intMid, true, true);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm + intTm2Off, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(128, 128, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St + intMid, true, true);
}


void vdDoorCloseRunningADV(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Effect to run on doors when all doors are closed. Animation will start then end, leaving lights in final state without proceessing anything else.
{
  cons.printwait("vdDoorCloseRunningADV (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");

  // Give strip a fresh start.
  vdClearAllTimedEvent(teEvent, lsStrips[intStripID].Cl, lsStrips[intStripID].St, lsStrips[intStripID].Ed);

  int intTm;
  int intDur;
  int intCt;
  int intSp;

  CRGB lead = CRGB(20, 20, 20);
  CRGB shadow = CRGB(50 ,50, 50);

  intTm = 600; intDur = 5000; intSp = 50; intCt = lsStrips[intStripID].Ct();

  // Clear set background colors.
  teEvent[lsStrips[intStripID].Cl].set("Door Close Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(0, 0, 32), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}


void vdDoorCloseActiveADV(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Effect to run on doors when all closed doors at least one other door is open.
{
  cons.printwait("vdDoorCloseActiveADV (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");

  // Give strip a fresh start.
  vdClearAllTimedEvent(teEvent, lsStrips[intStripID].Cl, lsStrips[intStripID].St, lsStrips[intStripID].Ed);

  int intTm;
  int intDur;
  int intSp;

  CRGB lead = CRGB(20, 20, 20);

  // Door Open Animation
  intTm = 100; intDur = 5000; intSp = 5;

  // Clear set background to door open colors.
  teEvent[lsStrips[intStripID].Cl].set("Door Close Active Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(40, 8, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);

  // Pulse to white (accumulation of prev color and this color = CRGP(70, 70, 70) then back to original color.
  teEvent[lsStrips[intStripID].Cl].set("Door Close Active Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false,  CRGB(0, 0, 0), CRGB(30, 62, 70) , CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
}


void vdPacificaishAnimationADV(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Blue Waves. Much more interesting than the old version of this.
{
  cons.printwait("vdPacificaishAnimationADV (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");

  // Give strip a fresh start.
  //vdClearAllTimedEvent(teEvent, lsStrips[intStripID].Cl, lsStrips[intStripID].St, lsStrips[intStripID].Ed);
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, 25, 0, 0, AnEvClearRunning, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);

  // Swap sweep start and end, depending on front or back.
  int start;
  int end;

  if (lsStrips[intStripID].Cl == 0)
  {
    start = lsStrips[intStripID].St;
    end = lsStrips[intStripID].Ed;
  }
  else
  {
    start = lsStrips[intStripID].Ed;
    end = lsStrips[intStripID].St;
  }
  
  // Set the background color.
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, 1000, 500, 30, AnEvSweep, AnPiFade, false, CRGB(0, 0, 0), CRGB(0, 0, 60), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, false);

  // The waves.
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(3500), intRandomHD(125), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(20, 100, 80), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(1500), intRandomHD(75), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(40, 50, 40), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(3600), intRandomHD(135), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(10, 30, 90), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(3200), intRandomHD(100), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(30, 40, 70), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);

  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(3500), intRandomHD(125), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(20, 100, 80), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(1500), intRandomHD(75), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(40, 50, 40), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(3600), intRandomHD(135), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(10, 30, 90), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(3200), intRandomHD(100), AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(30, 40, 70), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);

  // Counter waves.
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(3500), intRandomHD(125), AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(40, 100, 80), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(1500), intRandomHD(75), AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(50, 50, 40), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(3600), intRandomHD(135), AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(20, 30, 90), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(3200), intRandomHD(100), AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(40, 40, 70), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
}


void vdCloseOverADV(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Overhead Lights Off
{
  cons.printwait("vdCloseOverADV (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");

  // Just set all the current over head lights to fade away.
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, 0, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
}

void vdCoADV(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Conviencance Lights On then Off.
{
  cons.printwait("vdCoAD (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");
  int intTm;
  int intDur;
  int intSp;

  int bgonedly;

  // Assign the top and bottom of the strip
  int top;
  int bot;
  if (lsStrips[intStripID].Cl == 0)
  {
    // Back Door
    top = lsStrips[intStripID].St;
    bot = lsStrips[intStripID].Ed;
  }
  else
  {
    // Front Door
    top = lsStrips[intStripID].Ed;
    bot = lsStrips[intStripID].St;
  }
  
  // Background Color Fade out.
  // Set the background color.
  CRGB background = CRGB(40, 8, 0);
  CRGB backgroundbgone = CRGB(20, 4, 0);
  
  intTm = 500; intDur = 3000; intSp = 250;

  // Set the currently running animations to fade away. (NOTE: CLEARONEND = true to end scheduled future animations end on complete, also.)
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, 0, 999, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);

  //Set All the animations to end after the code 4 lines down, is finished fading away  
  bgonedly = (lsStrips[intStripID].Ct() * intSp + intDur);
  teEvent[lsStrips[intStripID].Cl].set("", tmeCurrentTime, bgonedly, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);

  // Fading away by writing a color as background, then slowly sweeping in the same color in reverse color, to make it disappear slowly. 
  teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, 500, 500, 0, AnEvSweep, AnPiFade, false,  CRGB(0, 0, 0), background, CRGB(0, 0, 0), CRGB(0, 0, 0), bot, top, false, false);
  teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFade, true,  CRGB(0, 0, 0), background, CRGB(0, 0, 0), CRGB(0, 0, 0), bot, top, false, false);

  // The Pulses.  Timed according to their own speed.
  intTm = 500; intSp = 30;
  intDur = intSp * 6;

  bgonedly = (lsStrips[intStripID].Ct() * intSp + intDur) /3;
  teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm + (0 * bgonedly), intDur, intSp, AnEvSweep, AnPiPulse, false,  CRGB(0, 0, 0), backgroundbgone, CRGB(0, 0, 0), CRGB(0, 0, 0), top, bot, true, false);
  teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm + (1 * bgonedly), intDur, intSp, AnEvSweep, AnPiPulse, false,  CRGB(0, 0, 0), backgroundbgone, CRGB(0, 0, 0), CRGB(0, 0, 0), top, bot, true, false);
  teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, intTm + (2 * bgonedly), intDur, intSp, AnEvSweep, AnPiPulse, false,  CRGB(0, 0, 0), backgroundbgone, CRGB(0, 0, 0), CRGB(0, 0, 0), top, bot, true, false);
  // Schedule all lights to turn ahead of time at end of cycle
  // teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, AUXDRLINGERBCK - 6000, 9000, 0, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  // !!! Need to get AUXDRLINGERBACK back into the code.
}


void vdAddOpenADV(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn (force) Additional Lights On on to show the door is open.
{
  cons.printwait("vdAddOpenADV (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");
  //teEvent[lsStrips[intStripID +1].Cl].set("Open Additional Anim", tmeCurrentTime, 1000, 1000, 80, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(125,124,16), CRGB(0, 0, 0), CRGB(0, 0, 0), top, top + lsStrips[intStripID +1].Ct() /2, false, false);

  int intTm, intDur, intSp, intCt; 

  // Repeat Pulse
  intTm = 50; intDur = 700; intSp = 125; intCt = lsStrips[intStripID].Ct();
  int intMid = lsStrips[intStripID].Ct() / 2;
  int intTm2Off = (intMid * intSp + intDur) /2;
  int IntTrlDly = intDur*2/3;

  // Yellow Guide 1
  teEvent[lsStrips[intStripID].Cl].set("Open Additional Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(254, 254, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed - intMid, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Open Additional Anim", tmeCurrentTime, intTm + intTm2Off, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(254, 254, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed - intMid, true, true);
  // Dark Guide 1
  teEvent[lsStrips[intStripID].Cl].set("Open Additional Anim", tmeCurrentTime, intTm + IntTrlDly, intDur, intSp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(254, 254, 254), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed - intMid, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Open Additional Anim", tmeCurrentTime, intTm + intTm2Off + IntTrlDly, intDur, intSp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(254, 254, 254), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed - intMid, true, true);
  
  // Yellow Guide 2
  teEvent[lsStrips[intStripID].Cl].set("Open Additional Anim", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(254, 254, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St + intMid, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Open Additional Anim", tmeCurrentTime, intTm + intTm2Off, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(254, 254, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St + intMid, true, true);
  // Dark Guide 2
  teEvent[lsStrips[intStripID].Cl].set("Open Additional Anim", tmeCurrentTime, intTm + IntTrlDly, intDur, intSp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(254, 254, 254), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St + intMid, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Open Additional Anim", tmeCurrentTime, intTm + intTm2Off + IntTrlDly, intDur, intSp, AnEvSweep, AnPiPulse, true, CRGB(0, 0, 0), CRGB(254, 254, 254), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St + intMid, true, true);
  
}


void vdAddCloseADV(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn (force) Additional Lights Off on a Strip
{
  cons.printwait("vdAddCloseADV (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");

  // Seach the strip for light colors and set them to end after animation completes.  
  //teEvent[lsStrips[intStripID].Cl].set("Open Additional Anim", tmeCurrentTime, 50, 1000, 80, AnEvSetToEnd, 0, false, CRGB(254, 254, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  //teEvent[lsStrips[intStripID].Cl].set("Open Additional Anim", tmeCurrentTime, 50, 1000, 80, AnEvSetToEnd, 0, false, CRGB(254, 254, 254), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Open Additional Anim", tmeCurrentTime, 50, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
}


/*
// -------------------------------------------------------------------------------------
// Halloween Effects
// -------------------------------------------------------------------------------------


// Dim clouds on strip.

void vdCloudAnimation(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Halloween Overhead Open - Drifting Grey Clouds.  
{
  // AnTavdCloud
  // Swap sweep start and end, depending on front or back.
  int start;
  int end;
  if (lsStrips[intStripID].Cl == 0)
  {
    start = lsStrips[intStripID].St;
    end = lsStrips[intStripID].Ed;
  }
  else
  {
    start = lsStrips[intStripID].Ed;
    end = lsStrips[intStripID].St;
  }
  
  // Set the background color.
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 1000, 500, 5, AnEvSweep, AnPiFade, CRGB(0, 0, 0), CRGB(4, 6, 10), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, false);

  // The Clouds.
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(500), AnEvSweep, AnPiPulse, CRGB(10, 17, 20), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(1000), AnEvSweep, AnPiPulse, CRGB(10, 20, 20), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(500), AnEvSweep, AnPiPulse, CRGB(10, 27, 33), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(1000), AnEvSweep, AnPiPulse, CRGB(10, 22, 31), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, true, true);
  }

// -------------------------------------------------------------------------------------

// Dingy yellow light on strip end.

void vdCeilingLightAnimation(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Halloween Overhead Open - Simple Light Overhead in Corner
{
  // AnTavdCloud
  // Swap sweep start and end, depending on front or back.
  int start;
  int end;
  if (lsStrips[intStripID].Cl == 0)
  {
    start = lsStrips[intStripID].St;
    end = start + 13;
  }
  else
  {
    start = lsStrips[intStripID].Ed;
    end = start - 13;
  }

  // Set the background color.
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 1000, 500, 20, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), CRGB(64, 64, 30), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, false);
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), CRGB(255, 255, 255), CRGB(0, 0, 0), CRGB(255, 64, 64), lsStrips[intStripID].St, lsStrips[intStripID].St + 4, false, false);
}

// -------------------------------------------------------------------------------------

// Random lightning strike on strip.

void vdLightning(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Halloween Overhead Open - Lightning
{
  // AnTavdLightning
  // Ocasional Lightining Flashes.
  int intTm;
  int intDur;
  int intSp;
  int StartTime = intRandomHD(12000);
  int BlinkTime;
  int BlinkInterval = 1000;


  intDur = 150; intSp = 2;

  // Repeat
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, StartTime + 5000, 0, 0, AnEvSchedule, AnTavdLightning, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  
  // Thunder
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkInterval, 1500, 3, AnEvSweep, AnPiFade, CRGB(32, 32, 49), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);

  // Flash 1
  intSp = intRandomHD(2);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkInterval, intDur, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  
  // Flash 2
  BlinkTime = intRandomHD(BlinkInterval); intSp = intRandomHD(2);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkTime, intDur, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);

  // Flash 3
  // BlinkTime = intRandomHD(BlinkInterval); intSp = intRandomHD(2);
  // teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkTime, intDur, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

// -------------------------------------------------------------------------------------

// Random lightning strike on channel.

void vdChannelLightning(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn (force) Ligtning on Entire Channel. Strip Length Aware. 
{
  // AnTavdChannelLightning
  int intTm;
  int intCt;
  int intSp;
  int BlinkTime;
  int BlinkInterval;
  int StartTime = 50;

  int intDelay;

    // Swap sweep start and end, depending on front or back.
  int start;
  int end;
  if (lsStrips[intStripID].Cl == 0)
  {
    start = lsStrips[intStripID +1 ].St;
    end = lsStrips[intStripID +1 ].Ed;
  }
  else
  {
    start = lsStrips[intStripID +1 ].Ed;
    end = lsStrips[intStripID +1 ].St;
  }

  // Clear and Pulse colors background to green then ending in blueish, starting with the center.
  intTm = 50; BlinkInterval = 1000;
  intDelay = intAnTmDly(intTm, 0, lsStrips[intStripID].Ct(), intSp);

  // Thunder
  // Door 
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkInterval, 1500, 3, AnEvSweep, AnPiFade, CRGB(32, 32, 49), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  // Overhead 
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkInterval + intDelay, 1500, 3, AnEvSweep, AnPiFade, CRGB(32, 32, 49), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, true);
 
  // Flash 1
  intSp = intRandomHD(2);
  // Door
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkInterval, 150, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  // Overhead
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkInterval + intDelay, 150, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, true);

  // Flash 2
  BlinkTime = intRandomHD(BlinkInterval); intSp = intRandomHD(2);
  // Door
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkTime, 150, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  // Overhead
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkTime + intDelay, 150, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, true);

  // Flash 3
  BlinkTime = intRandomHD(BlinkInterval); intSp = intRandomHD(2);
  // Door
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkTime, 150, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  // Overhead
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime,  StartTime + BlinkTime + intDelay, 150, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, true);
}


//------------------------------------------------------------------------------------
// Thanksgiving Effects
// -------------------------------------------------------------------------------------

// Blue sky with white clouds

void vdBlueSky(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Halloween Overhead Open - Drifting Grey Clouds.  
{
  // AnTavdBlueSky
  // Swap sweep start and end, depending on front or back.
  int start;
  int end;
  if (lsStrips[intStripID].Cl == 0)
  {
    start = lsStrips[intStripID].St;
    end = lsStrips[intStripID].Ed;
  }
  else
  {
    start = lsStrips[intStripID].Ed;
    end = lsStrips[intStripID].St;
  }
  
  // Set the background color.
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 1000, 1000, 40, AnEvSweep, AnPiFade, CRGB(0, 0, 0), CRGB(0, 0, 30), CRGB(0, 0, 0), CRGB(0, 0, 30), start, end, false, false);

  // The Clouds.
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(125), AnEvSweep, AnPiPulse, CRGB(30, 30, 30), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(6000), intRandomHD(250), AnEvSweep, AnPiPulse, CRGB(30, 30, 30), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(500), AnEvSweep, AnPiPulse, CRGB(10, 27, 33), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, true, true);
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(1000), AnEvSweep, AnPiPulse, CRGB(10, 22, 31), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, true, true);
  }


// 
void vdNightSkyClose(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
{

  int intTm;
  int intDur;
  int intSp;


  // Stop the currently running Pacificaish animation.
  // Schedule clear animation events ahead of time in case animations don't get completed.
  //teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, AUXDRLINGERBCK + 2000, 0, 0, AnEvClearRunning, 0, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);

  // Schedule Animations to Fade Out
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, AUXDRLINGERBCK + 1000, 3000, 0, AnEvSetToEnd, 0, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID -1 ].St, lsStrips[intStripID].Ed, false, false);

  //Restore the privouse Color to fade out
  intTm = 200; intDur = 6000; intSp = 5;

  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, intTm , intDur, intSp, AnEvSweep, AnPiPulse, CRGB(0, 0, 30), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, false, true);
  teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 50, 0, 0, AnEvSchedule, AnTavdNightSky, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[lsStrips[intStripID].Cl].St, lsStrips[lsStrips[intStripID].Cl].Ed, false, true);
}

// Night Sky

void vdNightSky(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Halloween Overhead Open - Drifting Grey Clouds.  
{
  // AnTavdBlueSky
  // Swap sweep start and end, depending on front or back.
  int start;
  int end;

  CRGB Sun = CRGB(130, 130, 0);
  CRGB Set1 = CRGB(40, 10, 5);
  CRGB Set2 = CRGB(20, 5, 0);
  CRGB Set3 = CRGB(10, 2, 0);
  CRGB Set4 = CRGB(0, 0, 5);
  CRGB Set5 = CRGB(10, 10, 10);

  if (lsStrips[intStripID].Cl == 0)
  {
    // Back Door Light Strip
    start = lsStrips[intStripID].St;
    end = lsStrips[intStripID].Ed;
      
    // Set the background color.
    teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 1000, 8000, 20, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), Set3, CRGB(0, 0, 0), Set2, start, end -25, false, false);
    teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 1000, 8000, 20, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), Set2, CRGB(0, 0, 0), Set1, end -24, end -6, false, false);
    teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 1000, 8000, 20, AnEvSweep, AnPiFade, CRGB(0, 0, 0), Sun, CRGB(0, 0, 0), Sun, end -6, end, false, false);
  }
  else
  {
    // Front Door Light Strip
    start = lsStrips[intStripID].Ed;
    end = lsStrips[intStripID].St;

    teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 1000, 5000, 20, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), Set3, CRGB(0, 0, 0), Set4, start, end + 15, false, false);
    teEvent[lsStrips[intStripID].Cl].set("Nothing", tmeCurrentTime, 1000, 5000, 20, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), Set4, CRGB(0, 0, 0), Set5, end + 14, end, false, false);
  }

}

// -------------------------------------------------------------------------------------
*/


//------------------------------------------------------------------------------------
// Christmas Effects
// -------------------------------------------------------------------------------------

void vdChristmasTree(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Christmas Overhead Open
{
  cons.printwait("vdChristmasTree (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");
  // AnTavdChristmasTree

  // Assign the top and bottom of the strip
  int top;
  int bot;
  if (lsStrips[intStripID].Cl == 0)
  {
    // Back Door
    top = lsStrips[intStripID].St;
    bot = lsStrips[intStripID].Ed;

    // Set the background color.
    teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, 500, 2000, 100, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(0, 45, 20), CRGB(0, 0, 0), CRGB(0, 0, 4), bot, top +15, false, false);

    // Star
    teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, 6000, 10000, 0, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(128, 128, 16), top +5, top, false, false);
  }
  else
  {
    // Front Door
    top = lsStrips[intStripID].Ed;
    bot = lsStrips[intStripID].St;

    // Set the background color.
    teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, 500, 2000, 100, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(0, 45, 20), CRGB(0, 0, 0), CRGB(0, 0, 4), bot, top -15, false, false);

    // Star 
    teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, 10000, 10000, 0, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(128, 128, 16), top -5, top, false, false);
  }
  
  // The Lights.
  teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, 3000, 8000, 0, AnEvSweep, AnPiTwinkle, false, CRGB(200, 0, 0), CRGB(0, 200, 0), CRGB(0, 0, 200), CRGB(2, 75, 3), lsStrips[intStripID].St +6, lsStrips[intStripID].Ed -6, true, false);

  // Variance
  //teEvent[lsStrips[intStripID].Cl].set("Overhead Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(500), AnEvSweep, AnPiPulse, true, CRGB(20, 20, 20), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), bot, top, true, true);
}

// -------------------------------------------------------------------------------------

void vdChristmasTreeCo(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn (force) Lights Off ona Strip

// AnTavdChristmasTreeCo

{
  cons.printwait("vdChristmasTreeCo (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");
  int intTm;
  int intDurW;
  int intDurG;
  int intSp;

  int intDelay;

  // Assign the top and bottom of the strip
  int top;
  int bot;
  if (lsStrips[intStripID].Cl == 0)
  {
    // Back Door
    top = lsStrips[intStripID].St;
    bot = lsStrips[intStripID].Ed;

    // Background Color Fade out.
    teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, 500, 10000, 0, AnEvSweep, AnPiFadeDith, false, CRGB(0, 45, 20), CRGB(0, 0, 0), CRGB(0, 0, 4),CRGB(0, 0, 0),  bot, top +15, false, false);
  
    // Star
    teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, 500, 0, 0, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(125,124,16), top + lsStrips[intStripID].Ct() /2, top, false, false);
  }
  else
  {
    // Front Door
    top = lsStrips[intStripID].Ed;
    bot = lsStrips[intStripID].St;

    // Background Color Fade out.
    teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, 500, 10000, 0, AnEvSweep, AnPiFadeDith, false, CRGB(0, 45, 20), CRGB(0, 0, 0), CRGB(0, 0, 4),CRGB(0, 0, 0),  bot, top - 15, false, false);
  
    // Star 
    teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, 500, 0, 0, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(125,124,16), top - lsStrips[intStripID].Ct() /2, top, false, false);
  }

  // Background Color Fade out.

  // Schedule all lights to turn ahead of time at end of cycle
  teEvent[lsStrips[intStripID].Cl].set("", tmeCurrentTime, AUXDRLINGERBCK - 6000, 9000, 0, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);

  // The Lights.
  teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, 500, 15000, 0, AnEvSweep, AnPiTwinkle, false, CRGB(200, 0, 0), CRGB(0, 200, 0), CRGB(0, 0, 200), CRGB(2, 75, 3), lsStrips[intStripID].St +6, lsStrips[intStripID].Ed -6, false, false);
  // with Sparkle
  teEvent[lsStrips[intStripID].Cl].set("Overhead Close Convenience Anim", tmeCurrentTime, 500, 5500, 0, AnEvSweep, AnPiTwinkle, false, CRGB(128, 128, 128), CRGB(64, 0, 64), CRGB(0, 64, 64), CRGB(2, 85, 1), lsStrips[intStripID].St +6, lsStrips[intStripID].Ed -6, true, false);
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
//  Christmas Door Open Animation

void vdDoorOpenAnimation00Christmas(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door Open Stage 0
// Prepare red backgrounds and puddle lights for the caution lights, and start shimmer effect.
{
  cons.printwait("vdDoorOpenAnimation00Christmas (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");

  int intTm;
  int intDur;
  int intCt;
  int intSp;
  // Door Open Animation
  intTm = 100; intDur = 500; intSp = 10; intCt = lsStrips[intStripID].Ct(); // was 60

  // Clear set background to door open colors.
  
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(255, 255, 255), CRGB(0, 0, 0), CRGB(255, 32, 32), lsStrips[intStripID].St, lsStrips[intStripID].St + 10, false, false);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(255, 32, 32), CRGB(0, 0, 0), CRGB(25, 0, 0), lsStrips[intStripID].St + 5, lsStrips[intStripID].St + 10, false, false);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFade, false, CRGB(0, 0, 0), CRGB(25, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St + 11, lsStrips[intStripID].Ed - 6, false, false);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm + 500, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(25, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed - 5, lsStrips[intStripID].Ed, false, false);
 
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, 0, 0, AnEvSchedule, AnTaDoorOpen01Christmas, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdDoorOpenAnimation01Christmas(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door Open Stage 1
{
  cons.printwait("vdDoorOpenAnimation01Christmas (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");
  int intTm = 50;
  int intDur;
  int intCt;
  int intSp;

  // Caution Door Open Flash
  intDur = 100; intSp = 2; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  intDur = 600; intSp = 12; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  intDur = 1500; intSp = 30; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(128, 128, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);

  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, 0, 0, AnEvSchedule, AnTaDoorOpen02Christmas, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

// -------------------------------------------------------------------------------------

void vdDoorOpenAnimation02Christmas(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door Open Stage 2
{
  cons.printwait("vdDoorOpenAnimation02Christmas (CL: " + std::to_string(lsStrips[intStripID].Cl) + " ID:"+ std::to_string(intStripID) + " S:" + std::to_string(lsStrips[intStripID].St) + " E:" + std::to_string(lsStrips[intStripID].Ed) + ")");
  int intTm = 0;
  int intDur;
  int intCt;
  int intSp;
  int intMid = lsStrips[intStripID].Ct() / 2;

  // Repeat Pulse
  intDur = 1500; intSp = 125; intCt = lsStrips[intStripID].Ct(); // was 36
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(255, 255, 0), CRGB(255, 255, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].St + intMid, true, true);
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(255, 255, 0), CRGB(255, 255, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].Ed - intMid, true, true);

  // Sparkle
  teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, 500, 10000, 0, AnEvSweep, AnPiTwinkle, false, CRGB(128, 128, 128), CRGB(64, 0, 64), CRGB(0, 64, 64), CRGB(3, 85, 1), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set("vdOpenDoor", tmeCurrentTime, 500, 5500, 0, AnEvSweep, AnPiTwinkle, false, CRGB(128, 128, 128), CRGB(64, 0, 64), CRGB(0, 64, 64), CRGB(2, 95, 1), lsStrips[intStripID].St +20, lsStrips[intStripID].Ed -20, true, false);
}

void vdAddOpenChristm(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn (force) Lights Off ona Strip

// AnTavdvdAddOpenChristm
{
  int top;
  int bot;
  if (lsStrips[intStripID +1].Cl == 0)
  {
    // Back Door
    top = lsStrips[intStripID +1].St;
    bot = lsStrips[intStripID +1].Ed;

    // Star
    teEvent[lsStrips[intStripID +1].Cl].set("Open Additional Anim", tmeCurrentTime, 1000, 1000, 80, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(125,124,16), CRGB(0, 0, 0), CRGB(0, 0, 0), top, top + lsStrips[intStripID +1].Ct() /2, false, false);
  }
  else
  {
    // Front Door
    top = lsStrips[intStripID +1].Ed;
    bot = lsStrips[intStripID +1].St;
    
    // Star
    teEvent[lsStrips[intStripID +1].Cl].set("Open Additional Anim", tmeCurrentTime, 1000, 1000, 80, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(125,124,16), CRGB(0, 0, 0), CRGB(0, 0, 0), top, top - lsStrips[intStripID +1].Ct() /2, false, false);
  }
}


void vdAddCloseChristm(Console &cons, led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn (force) Lights Off on a Strip

// AnTavdvdAddCloseChristm
{
  // Set the background color.
  //teEvent[lsStrips[intStripID].Cl].set("Door Open Anim", tmeCurrentTime, 500, 200, 100, AnEvSweep, AnPiFade, false, CRGB(0, 0, 0), CRGB(0, 45, 20), CRGB(0, 0, 0), CRGB(0, 0, 4), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);

  // The Sparkle.
  //teEvent[lsStrips[intStripID].Cl].set("Door Open Anim", tmeCurrentTime, 3000, 15000, 0, AnEvSweep, AnPiTwinkle, false, CRGB(200, 0, 0), CRGB(0, 200, 0), CRGB(0, 0, 200), CRGB(2, 75, 3), lsStrips[intStripID].St , lsStrips[intStripID].Ed, true, false);
  teEvent[lsStrips[intStripID].Cl].set("Door Open Anim", tmeCurrentTime, 500, 10000, 0, AnEvSweep, AnPiTwinkle, false, CRGB(128, 128, 128), CRGB(64, 0, 64), CRGB(0, 64, 64), CRGB(3, 85, 1), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  
  // Variance
  //teEvent[lsStrips[intStripID].Cl].set("Door Open Anim", tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(500), AnEvSweep, AnPiPulse, true, CRGB(20, 20, 20), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);

  // Fade out the bright star.
  teEvent[lsStrips[intStripID +1].Cl].set("", tmeCurrentTime, 3000, 1000, 80, AnEvSetToEnd, 0, false, CRGB(125,124,16), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID +1].St, lsStrips[intStripID +1].Ed, false, true);
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------


// -------------------------------------------------------------------------------------

// System event system for non animations.

void teSystem(Console &cons, led_strip lsStripList[], timed_event teEvent[], unsigned long tmeCurrentTime)
//void teSystem(Console &cons, led_strip lsStripList[], timed_event teEvent[], unsigned long tmeCurrentTime)
// Example:
//  teEvent[0].set(tmeCurrentMillis, X, 0, 0, AnEvSchedule, AnTaDoorCloseBack, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), X, X, false, false);
//    or      ( X is the values that can be set )
//  teEvent[0].set(tmeCurrentMillis, X, X, 0, AnEvSchedule, AnEvSetToEnd, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(X, X, X), CRGB(X, X, X), 0, 0, false, false);
//                  if booRepeat set to true then pulse animations will continue till end of cycle.
//    or 
//  teEvent[0].set(tmeCurrentMillis, X, 0, 0, AnEvClear, 0, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), X, X, false, false);

// Guide: (tmeCurrentTime, tmeStartInTime, intDuration, intSpeed, bytAnimation, bytLEDAnimation, crgbStart1, crgbDest1, crgbStart2, crgbDest2, intStartPos, intEndPos, booRepeat, booClearOnEnd)
{

  for (int channel = 0; channel < NUM_CHANNELS; channel++)
  {
    if (teEvent[channel].teDATA.size() > 0)
    {
      for (int event = 0; event < teEvent[channel].teDATA.size(); event++)
      {
        if (tmeCurrentTime >= teEvent[channel].teDATA[event].tmeSTARTTIME && teEvent[channel].teDATA[event].booCOMPLETE == false)
        {
          // Process Timed System Events (keeping the LED type event scheduler format for 
          //  now)

          switch (teEvent[channel].teDATA[event].bytANIMATION)
          {
            case AnEvClear:   // Clear all events, whether running or not, if event is within Start and End Position.
            {
              cons.printwait("Event: AnEvClear");
              teEvent[channel].teDATA[event].booCOMPLETE = true;
              teEvent[channel].ClearAll(teEvent[channel].teDATA[event].intSTARTPOS,teEvent[channel].teDATA[event].intENDPOS);
              break;
            }
            
            case AnEvClearRunning:  // Clear all active events if event is within Start and End Position.
            {                       // Possible problem if InTime is set to 0.
              cons.printwait("Event: AnEvClearRunning");
              teEvent[channel].teDATA[event].booCOMPLETE = true;

              for (int eventscan = 0; eventscan < teEvent[channel].teDATA.size(); eventscan++)
              {
                if(tmeCurrentTime >= teEvent[channel].teDATA[eventscan].tmeSTARTTIME)
                {
                  if (  ((teEvent[channel].teDATA[eventscan].intSTARTPOS >= teEvent[channel].teDATA[event].intSTARTPOS)  
                        && (teEvent[channel].teDATA[eventscan].intSTARTPOS <= teEvent[channel].teDATA[event].intENDPOS))
                              ||
                        ((teEvent[channel].teDATA[eventscan].intENDPOS >= teEvent[channel].teDATA[event].intSTARTPOS)  
                        && (teEvent[channel].teDATA[eventscan].intENDPOS <= teEvent[channel].teDATA[event].intENDPOS))  )
                  {
                    if (event != eventscan)
                    {
                      teEvent[channel].teDATA[eventscan].booCOMPLETE = true;
                    }
                  }
                }
              } 
              break;
            }

            case AnEvSchedule:
            //  Schedule an animation
            {  
              cons.printwait("Event: AnEvSchedule");
              // Clear the Event whether the event ran or not.
              teEvent[channel].teDATA[event].booCOMPLETE = true;
              
              switch (teEvent[channel].teDATA[event].bytLEDANIMATION)
              // Activate an Animation Set
              {

                // Special Animations

                /*
                case AnTaPowerOn:
                // Animation on startup
                {
                  vdPowerOnAnimation(cons, lsStripList, 0, teEvent, tmeCurrentTime);
                  break;
                }
                */

                case AnTaChannelPulseColor:
                // Color Specific Channel Pulse
                {
                  vdChannelLightPulseColor(cons, lsStripList, channel *2, teEvent, tmeCurrentTime, teEvent[channel].teDATA[event].crgbCOLORSTART1);
                  break;
                }

                case AnTaOverheadIllumColor:
                // Color Specific Illumination
                {
                  vdOverheadIllum(cons, lsStripList, channel *2, teEvent, tmeCurrentTime, teEvent[channel].teDATA[event].crgbCOLORSTART1);
                  break;
                }

                case AnTaHazard:
                // Color Specific Illumination
                {
                  vdHazard(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }

                // Open Door
                case AnTaDoorOpen:
                {
                  vdDoorOpenAnimation(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }
                case AnTaDoorOpen00:
                {
                  vdDoorOpenAnimation00(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }
                case AnTaDoorOpen01:
                {
                  vdDoorOpenAnimation01(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }
                case AnTaDoorOpen02:
                {
                  vdDoorOpenAnimation02(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }

                // Close Back Door
                case AnTaDoorClose:
                {
                  vdDoorCloseAnimation(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }
                case AnTaDoorClose00:
                {
                  vdDoorCloseAnimation00(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }
                
                case AnTaStripOverOff:
                {
                  vdStripOverOff(cons, lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                  break;
                }

                /*
                case AnTavdPacificaish:
                {
                  vdPacificaishAnimation(cons, lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                  break;
                }

                case AnTavdPaAnimClose:
                {
                  vdPacificaishAnimationClose(cons, lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                  break;
                }

                case AnTavdPaAnimClose00:
                {
                  vdPacificaishAnimationClose00(cons, lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                  break;
                }
                */

                /*
                // Halloween Animations 

                case AnTavdHallowClose2:
                {
                  vdHallowClose2(cons, lsStripList, (channel *2) +1 , teEvent, tmeCurrentTime);
                  break;
                }

                case AnTavdCloud:
                {
                  vdCloudAnimation(cons, lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                  break;
                }

                case AnTavdLightning:
                {
                  vdLightning(cons, lsStripList, (channel *2) +1 , teEvent, tmeCurrentTime);
                  break;
                }

                case AnTavdCeilingLight:
                {
                  vdCeilingLightAnimation(cons, lsStripList, (channel *2) +1 , teEvent, tmeCurrentTime);
                  break;
                }

                case AnTavdChannelLightning:
                {
                  vdChannelLightning(cons, lsStripList, (channel *2) , teEvent, tmeCurrentTime);
                  break;
                }

                // Thanksgiving Animations 

                case AnTavdBlueSky:
                {
                  vdBlueSky(cons, lsStripList, (channel *2) +1 , teEvent, tmeCurrentTime);
                  break;
                }

                case AnTavdNightSkyClose:
                {
                  vdNightSkyClose(cons, lsStripList, (channel *2) +1 , teEvent, tmeCurrentTime);
                  break;
                }

                case AnTavdNightSky:
                {
                  vdNightSky(cons, lsStripList, (channel *2) +1 , teEvent, tmeCurrentTime);
                  break;
                }
                
                case AnTaStripOverOffThanks:
                {
                  vdStripOverOffThanks(cons, lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                  break;
                }
                */


              // Christmas Animtions
                case AnTavdChristmasTree:
                {
                  vdChristmasTree(cons, lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                  break; 
                }
                case AnTavdChristmasTreeCo:
                {
                  vdChristmasTreeCo(cons, lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                  break; 
                }
                // Christmas Door Open Animations 
                case AnTaDoorOpen00Christmas:
                {
                  vdDoorOpenAnimation00Christmas(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }
                case AnTaDoorOpen01Christmas:
                {
                  vdDoorOpenAnimation01Christmas(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }
                case AnTaDoorOpen02Christmas:
                {
                  vdDoorOpenAnimation02Christmas(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }
                case AnTavdAddOpenChristm:
                {
                  vdAddOpenChristm(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }
                case AnTavdAddCloseChristm:
                {
                  vdAddCloseChristm(cons, lsStripList, channel *2, teEvent, tmeCurrentTime);
                  break;
                }


              } // End Case Animation Set
              break;
            } // End Case AnEvSchedule

            case AnEvSetToEnd:  // Schedules an animation to end. Fades out Fades and stops repeat on Pulses.
            {                   // Possible problem if InTime is set to 0.  
              cons.printwait("Event: AnEvSetToEnd");
              // Clear the Event whether the event ran or not.
              teEvent[channel].teDATA[event].booCOMPLETE = true;   

              // Step through each event in this channel. 
              for (int eventscan = 0; eventscan < teEvent[channel].teDATA.size(); eventscan++)
              {
                // Has the event started running yet, or do we plan on ending future scheduled events also?
                if(teEvent[channel].teDATA[eventscan].tmeSTARTTIME <= tmeCurrentTime || teEvent[channel].teDATA[eventscan].booCLEARONEND == true)   // May Have Fixed It.  IDK
                {
                  // is the event we are currently looking at within, or overlapping, the targeted event range.
                  if (  ((teEvent[channel].teDATA[eventscan].intSTARTPOS >= teEvent[channel].teDATA[event].intSTARTPOS)  
                        && (teEvent[channel].teDATA[eventscan].intSTARTPOS <= teEvent[channel].teDATA[event].intENDPOS))
                              ||
                        ((teEvent[channel].teDATA[eventscan].intENDPOS >= teEvent[channel].teDATA[event].intSTARTPOS)  
                        && (teEvent[channel].teDATA[eventscan].intENDPOS <= teEvent[channel].teDATA[event].intENDPOS))  )
                  {
                    // Are we targeting only specific events to end or all events.
                    bool cont = false;

                    bool booCheckColor = true;
                    bool booCheckIdent = true;
                    // Trying not to complicate the code too much.

                    // Check for specific Targeted Color or Targeted Identifier.  
                    // We are targeting events with any color by passing CRGB(0,0,0), and any I dentifier by passing "" 
                    // continue on.

                    // Warning: This is not an AND condition, even though it probably should be. Not needed at this time 
                    //            so I didn't implement it.  There are just too many other things to do.

                    // Figure out what we are checking.
                    if (teEvent[channel].teDATA[event].crgbCOLORSTART1 == CRGB(0,0,0))
                    {
                      booCheckColor = false;
                    }
                    if (teEvent[channel].teDATA[event].strIdent == "")
                    {
                      booCheckIdent = false;
                    }

                    // Look for matches
                    if ((booCheckColor == false) && (booCheckIdent == false))
                    {
                      // Nothing targeted. Continue with STE.
                      cont = true;
                    }
                    else if (booCheckColor == true)
                    {
                      //We are only targeting events with specific color.  Need a match on any.
                      if (teEvent[channel].teDATA[event].crgbCOLORSTART1 == teEvent[channel].teDATA[eventscan].crgbCOLORSTART1)
                      {
                        cont = true;
                      }
                      else if (teEvent[channel].teDATA[event].crgbCOLORSTART1 == teEvent[channel].teDATA[eventscan].crgbCOLORSTART2)
                      {
                        cont = true;
                      }
                      else if (teEvent[channel].teDATA[event].crgbCOLORSTART1 == teEvent[channel].teDATA[eventscan].crgbCOLORDEST1)
                      {
                        cont = true;
                      }
                      else if (teEvent[channel].teDATA[event].crgbCOLORSTART1 == teEvent[channel].teDATA[eventscan].crgbCOLORDEST2)
                      {
                        cont = true;
                      }
                    }
                    else if (booCheckIdent == true)
                    {
                      //We are only targeting events with specific Identification.  Need a match on any.
                      if (teEvent[channel].teDATA[event].strIdent == teEvent[channel].teDATA[eventscan].strIdent)
                      {
                        cont = true;
                      }
                    }

                    // Only continue with setting the event to end if it passed the above criteria.
                    if (cont == true)
                    {
                      // Check the event we are stopping to make sure its not the event calling the SetToEnd.
                      if (event != eventscan)
                      {
                        // Manage the Fade Animations to End.
                        if (  (teEvent[channel].teDATA[eventscan].bytLEDANIMATION == AnPiFade)     ||
                              (teEvent[channel].teDATA[eventscan].bytLEDANIMATION == AnPiFadeDith) ||
                              (teEvent[channel].teDATA[eventscan].bytANIMATION == AnEvSchedule) )
                        {
                          // Stop the event.
                          teEvent[channel].teDATA[eventscan].booREPEAT = false;
                          teEvent[channel].teDATA[eventscan].booCLEARONEND = true;
                          
                          teEvent[channel].teDATA[eventscan].intDURATION = teEvent[channel].teDATA[event].intDURATION;
                          teEvent[channel].teDATA[eventscan].tmeSTARTTIME = tmeCurrentTime;

                          //teEvent[channel].teDATA[eventscan].intSPEED =  teEvent[channel].teDATA[event].intSPEED;
                          teEvent[channel].teDATA[eventscan].intSPEED =  0;
                        // The above two lines will need to be addressed at a future date. 
                        //  Problem occurs when an event current time is before the start 
                        //  pixel update begins. This mean that the start color will not be set until current 
                        //  time is past start time.  Need to choose: apples or oranges during 
                        //  the crgb_anim_color and event routine.

                          teEvent[channel].teDATA[eventscan].crgbCOLORSTART1 = teEvent[channel].teDATA[eventscan].crgbCOLORDEST1;
                          teEvent[channel].teDATA[eventscan].crgbCOLORSTART2 = teEvent[channel].teDATA[eventscan].crgbCOLORDEST2;
                          teEvent[channel].teDATA[eventscan].crgbCOLORDEST1 = teEvent[channel].teDATA[event].crgbCOLORDEST1;
                          teEvent[channel].teDATA[eventscan].crgbCOLORDEST2 = teEvent[channel].teDATA[event].crgbCOLORDEST2;
                        }
                        // Manage the Pulse Animations to End
                        if (  (teEvent[channel].teDATA[eventscan].bytLEDANIMATION == AnPiPulse)    ||
                              (teEvent[channel].teDATA[eventscan].bytLEDANIMATION == AnPiPulseTo)  )
                        {
                          // Tell the pulse to stop.
                          if (teEvent[channel].teDATA[event].booREPEAT == false)
                          {
                            // For now, we will just kill it and hope another animation clears the artifacts.
                            // It would be nice to have a gracreful end and let the pixel end its animation,
                            // but, thats for another time.
                            
                            // Stop the event.
                            teEvent[channel].teDATA[eventscan].booREPEAT = false;
                            teEvent[channel].teDATA[eventscan].booCLEARONEND = true;
                            
                            teEvent[channel].teDATA[eventscan].booCOMPLETE = true;
                          }
                          else
                          {
                            // Pulse will end on its on at end of animation.
                            teEvent[channel].teDATA[eventscan].booREPEAT = false;
                            teEvent[channel].teDATA[eventscan].booCLEARONEND = true;
                          }
                        }
                      }
                    }
                  }
                }
              }        
              break;
            } // End Case AnEvSetToEnd
          } // End Switch 
        } // End If time check
      } // End FOR event
    } // If datasize >0
  } // End FOR strip
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

//  AuxLightControlModule

void DoorMonitorAndAnimationControlModule(Console &cons, system_data &sdSysData, led_strip lsStrips[], timed_event teEvent[], hardware_monitor hwmDoor[], bool booSensors[], unsigned long tmeCurrentTime)
// This routine is designed to scan all the doors or switches.  If anthing is open, opened 
//  closed or closed (odd twist of english there) then set the appropriate or maintain
//  animations.  
// Works like this.  If any door is open then make sure the overhead lights are on.  
//  If all the doors are closed, turn all the lights off.  Run door animations like 
//  normal.
{
   using namespace std;

  int opencount = 0;
  int strip;
  bool changedetected = false;

  // Scan Through Doors and Check for Changes

  // DO NOT CLEAR ANIMATIONS HERE!  CLEAR ANIMATIONS IN ANIMATION SCRIPT!
  //              (easier to track and debug that way)

  // Check for newly opened and run animation on them.
  for (int door=0; door < NUM_SWITCHES; door++)
  {
    if (hwmDoor[door].changed(booSensors[door], tmeCurrentTime) == true)
    {
      changedetected = true; 
      if (hwmDoor[door].booVALUE)
      {
        // Door Just Opened
        // Start Open Door Animation on This Door
        if (hwmDoor[door].ISHARDWARE == true)  // Only if its real switch (with lights attached to it)
        {
          strip = door *2;
          
          // Door Animation
          cons.printwait("  Door " + std::to_string(door) + " Open ... ");
          lsStrips[strip].AnimationStatus = StDoorOpen;
          vdDoorOpenAnimationADV00(cons, lsStrips,strip,teEvent,tmeCurrentTime);

          // Turn on additional lights overhead
          cons.printwait("  Add On Strip:" + std::to_string(strip + 1));
          vdAddOpenADV(cons, lsStrips,strip + 1,teEvent,tmeCurrentTime);
        }
      }
      else
      {
        // Door Just Closed
        if (hwmDoor[door].ISHARDWARE == true)  // Only if its real switch (with lights attached to it)
        {
          strip = door *2;
          
          // Replace Open or Current door animation to closed door animation
          cons.printwait("  Door " + std::to_string(door) + " Close ... ");
          lsStrips[strip].AnimationStatus = StDoorCloseA;        
          vdDoorCloseActiveADV(cons, lsStrips,strip,teEvent,tmeCurrentTime);

          // Turn off additional lights overhead
          cons.printwait("  Add Off Strtip:" + std::to_string(strip));
          vdAddCloseADV(cons, lsStrips,strip + 1,teEvent,tmeCurrentTime);
        }
      }
    }
  }

  // Check To See If Any Door Opened or Closed.
  if (changedetected == true)
  {
    // Count the amount of open doors
    for (int door=0; door < NUM_SWITCHES; door++)
    {
      if (hwmDoor[door].booVALUE  == true)
      {
        opencount = opencount  + 1;
      }
    }
    cons.printwait("Open Door Count: " + std::to_string(opencount));
    sdSysData.intDoorsOpen = opencount;
    // -----

    if (opencount > 0)
    {
      // There are open Doors
      for (int door=0; door < NUM_SWITCHES; door++)
      {
        strip = (door *2); // Determine Strip from Door aka Channel
        if (hwmDoor[door].ISHARDWARE == true)  // Only if its real switch (with lights attached to it)
        {

          // If a door is open
          if (lsStrips[strip].AnimationStatus != StDoorOpen && lsStrips[strip].AnimationStatus != StDoorCloseA)
          {
            // If this door is not open then make sure the closed door animation is running on it.
            cons.printwait("  Door " + std::to_string(door) + " Running Active Closed: ");

            // Closed Active Doors animation
            lsStrips[strip].AnimationStatus = StDoorCloseA;        
            vdDoorCloseActiveADV(cons, lsStrips,strip,teEvent,tmeCurrentTime);
          }

          // If  a door is open
          if (lsStrips[strip + 1].AnimationStatus != stOverOpen)
          {
            // Make sure this door has the overhead animation running on it.
            cons.printwait("  Door " + std::to_string(door) + " Running Overhead: ");

            // Normal Overhead Animation 
            lsStrips[strip + 1].AnimationStatus = stOverOpen;
            vdPacificaishAnimationADV(cons, lsStrips,strip + 1,teEvent,tmeCurrentTime);
          }
        }
      }      
    }
    else 
      {
      // All doors are closed.
      cons.printwait("  All Doors Closed: ");

      for (int door=0; door < NUM_SWITCHES; door++)
      {
        strip = (door *2); // Determine Strip from Door aka Channel
          // Strip will be the door strip
          // Strip +1 is the door overhead strip
        
        // Finalize additionall animations on newley closed doors
        if (hwmDoor[door].ISHARDWARE == true)  // Only if its real switch (with lights attached to it)
        {
          //  Guarantee all animations end in 15 seconds. This is a fall back method to
          //    make sure everythings stops in case a clear animation fails to start.
          vdEndAllAnimationsADV(cons, lsStrips,strip,teEvent,tmeCurrentTime);

          // Start the Doors Running Mode on each door.
          lsStrips[strip].AnimationStatus = StDoorCloseR;
          vdDoorCloseRunningADV(cons, lsStrips,strip,teEvent,tmeCurrentTime);

          //cons.printwait("All Doors Closed HWLVL: D%d AS%d" + std::to_string(door) + std::to_string(lsStrips[strip + 1].AnimationStatus));
          
          // Make sure lights are off or turning off and Amber Up the newly closded doors.
          if (lsStrips[strip + 1].AnimationStatus == stOverOpen)
          {
            // Start Overhead Turn On Convenience Animation.
            // See when the door was closed
            // cons.printwait("Door Toggle Time (current time - toggle time): %d - %dms < 1500", tmeCurrentTime, hwmDoor[door].tmeTOGGLEDTIME);
            if ((tmeCurrentTime - hwmDoor[door].tmeTOGGLEDTIME) < 15000)
            {
              // The door was recently closed. Run the Convienance lights on it.
              cons.printwait("  Door " + std::to_string(door) + " Conviencance Lights On: ");
              
              // Turn on Convienance Lights 
              lsStrips[strip + 1].AnimationStatus = StOverCloseCon;  
              vdCoADV(cons, lsStrips,strip + 1,teEvent,tmeCurrentTime);
            }
            else
            {
              // The door was closed for a while, just turn off the lights.
              // Start the Close Door Overhead Animation
              cons.printwait("  Door " + std::to_string(door) + " Conviencance Lights Off: ");

              // Just turn off the lights.
              lsStrips[strip + 1].AnimationStatus = stOverClose;
              vdCloseOverADV(cons, lsStrips,strip + 1,teEvent,tmeCurrentTime);
            }
          }
        }
      }
    }
  }
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------


// -------------------------------------------------------------------------------------

// Procedures related to the Command Line.

// Display the help screen.
void consoleprinthelp(Console &cons)
{
  cons.printwait("");
  cons.printwait("HELP SCREEN ------------");
  cons.printwait("");
  cons.printwait("x or exit - Safely exits the RasFLED.");
  cons.printwait("");
  cons.printwait("help    - Prints this help screen.");
  cons.printwait("events  - Prints all active events.");
  cons.printwait("");
  cons.printwait("     hh - Hazard Lights");
  cons.printwait("     `` - End All Repeating Lights");
  cons.printwait("");
  cons.printwait("Colors:");
  cons.printwait(" r - Red    u - Purple");
  cons.printwait(" g - Green  y - Yellow");
  cons.printwait(" b - Blue   c - Cyan    e - End");
  cons.printwait("");
  cons.printwait("pX  - Pulse       (X is the color)");
  cons.printwait("oX  - Pulse       (X is the color)");
  cons.printwait("X`  - End Command (X is the Command Ended)");
  cons.printwait("  Double animations will be White.");
  cons.printwait("");
  cons.printwait("  Not all colors implemented for all commands.");
  cons.printwait("");
  cons.printwait("\\   - Turn on diagnosis mode.");
  cons.printwait("a - Cycle Doors  l - Cycle Upper Lower  c - Test LEDs");
  cons.printwait("");
}

// Display all running events.
void consoleprintevents(Console &cons, timed_event teEvent[])
{
  for (int channel = 0; channel < NUM_CHANNELS; channel++)
  {
    cons.printwait("Channel " + std::to_string(channel));
    if (teEvent[channel].teDATA.size() == 0)
    {
      cons.printwait("No Events");
    }
    else
    {
      for (int event = 0; event < teEvent[channel].teDATA.size(); event++)
      {
        cons.printwait(" ID:\"" + teEvent[channel].teDATA[event].strIdent + "\" Anim:" + std::to_string(teEvent[channel].teDATA[event].bytANIMATION)  + " LEDanim:" + std::to_string(teEvent[channel].teDATA[event].bytLEDANIMATION)  + " Strt:" + std::to_string(teEvent[channel].teDATA[event].intSTARTPOS) + " End:" + std::to_string(teEvent[channel].teDATA[event].intENDPOS));
      }
    }
  }
}

// Pulses

// Set To End All Pulses
void processcommandpulseend(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[])
{
  for (int channel = 0; channel < NUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Channel Light Pulse Color", tmeCurrentTime, 0, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 255, true, true);
  }
  sdSysData.booPulsesRunning = false;
}

// Pulse Color All Channels
void processcommandpulse(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor)
{
  for (int channel = 0; channel < NUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Channel Light Pulse Color", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColor, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true);  
  }
  sdSysData.booPulsesRunning = true;
}

// Overhead Illum

// Set To End All Pulses
void processcommandoverheadillumend(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[])
{
  for (int channel = 0; channel < NUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Overhead Illumination", tmeCurrentTime, 0, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 255, true, true);
  }
  sdSysData.booOverheadRunning = false;
}

// Pulse Color All Channels
void processcommandoverheadillum(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor)
{
  for (int channel = 0; channel < NUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Overhead Illumination", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaOverheadIllumColor, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true);  
  }
  sdSysData.booOverheadRunning = true;
}

// Hazard

// Set To End All Hazard
void processcommandhazardend(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[])
{
  for (int channel = 0; channel < NUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Hazard", tmeCurrentTime, 0, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 255, true, true);
  }
  sdSysData.booHazardRunning = false;
}

// Hazard
void processcommandhazard(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor)
{
  for (int channel = 0; channel < NUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Hazard", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaHazard, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true);  
  }
  sdSysData.booHazardRunning = true;
}


// Process and call routines as entered on the command line.
void processcommandlineinput(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[])
{
  if(cons.keywatch.cmdPressed() == true)
  {
    // Color Palettes
    CRGB crgbWhite  = CRGB(64,64,64);
    CRGB crgbRed    = CRGB(64,0,0);
    CRGB crgbGreen  = CRGB(0,64,0);
    CRGB crgbBlue   = CRGB(0,0,64);
    CRGB crgbPurple = CRGB(64,0,64);
    CRGB crgbYellow = CRGB(64,64,0);
    CRGB crgbCyan   = CRGB(0,64,64);
    
    // Call routines that match the info on the command line.
    
    // Program Exit
    if((cons.keywatch.Command.COMMANDLINE[0] == KEYEXIT) || (cons.keywatch.Command.COMMANDLINE == "exit"))
    {
      cons.keywatch.in(KEYEXIT);
      cons.keywatch.cmdClear();
    }

    // help
    if(cons.keywatch.Command.COMMANDLINE == "help")
    {
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      consoleprinthelp(cons);
      cons.keywatch.cmdClear();
    }

    // events
    if(cons.keywatch.Command.COMMANDLINE == "events")
    {
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      consoleprintevents(cons, teEvent);
      cons.keywatch.cmdClear();
    }

    // End All Extra Repeating Lights
    if(cons.keywatch.Command.COMMANDLINE == "``")
    {
      // end all pulses on all strips
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpulseend(cons, sdSysData, tmeCurrentTime, teEvent);
      processcommandoverheadillumend(cons, sdSysData, tmeCurrentTime, teEvent);
      processcommandhazardend(cons, sdSysData, tmeCurrentTime, teEvent);
      cons.keywatch.cmdClear();
    }

    // -------------
    // PULSES

    // pulse end
    if(cons.keywatch.Command.COMMANDLINE == "p`")
    {
      // end all pulses on all strips
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpulseend(cons, sdSysData, tmeCurrentTime, teEvent);
      cons.keywatch.cmdClear();
    }

    // pulse White
    if(cons.keywatch.Command.COMMANDLINE == "pp")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpulse(cons, sdSysData, tmeCurrentTime, teEvent, crgbWhite);
      cons.keywatch.cmdClear();
    }

    // pulse Red
    if(cons.keywatch.Command.COMMANDLINE == "pr")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpulse(cons, sdSysData, tmeCurrentTime, teEvent, crgbRed);
      cons.keywatch.cmdClear();
    }

    // pulse Green
    if(cons.keywatch.Command.COMMANDLINE == "pg")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpulse(cons, sdSysData, tmeCurrentTime, teEvent, crgbGreen);
      cons.keywatch.cmdClear();
    }

    // pulse Blue
    if(cons.keywatch.Command.COMMANDLINE == "pb")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpulse(cons, sdSysData, tmeCurrentTime, teEvent, crgbBlue);
      cons.keywatch.cmdClear();
    }

    // pulse Purple
    if(cons.keywatch.Command.COMMANDLINE == "pu")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpulse(cons, sdSysData, tmeCurrentTime, teEvent, crgbPurple);
      cons.keywatch.cmdClear();
    }

    // pulse Yellow
    if(cons.keywatch.Command.COMMANDLINE == "py")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpulse(cons, sdSysData, tmeCurrentTime, teEvent, crgbYellow);
      cons.keywatch.cmdClear();
    }

    // pulse Cyan
    if(cons.keywatch.Command.COMMANDLINE == "pc")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpulse(cons, sdSysData, tmeCurrentTime, teEvent, crgbCyan);
      cons.keywatch.cmdClear();
    }

    // Overhead Illumination
    
    // pulse end overhead illum
    if(cons.keywatch.Command.COMMANDLINE == "o`")
    {
      // end all pulses on all strips
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandoverheadillumend(cons, sdSysData, tmeCurrentTime, teEvent);
      cons.keywatch.cmdClear();
    }

    // Overhead White
    if(cons.keywatch.Command.COMMANDLINE == "oo")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandoverheadillum(cons, sdSysData, tmeCurrentTime, teEvent, crgbWhite);
      cons.keywatch.cmdClear();
    }

    // Hazard
    
    // Hazard illum end
    if(cons.keywatch.Command.COMMANDLINE == "h`")
    {
      // end all pulses on all strips
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandhazardend(cons, sdSysData, tmeCurrentTime, teEvent);
      cons.keywatch.cmdClear();
    }

    // Hazard
    if(cons.keywatch.Command.COMMANDLINE == "hh")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandhazard(cons, sdSysData, tmeCurrentTime, teEvent, crgbWhite);
      cons.keywatch.cmdClear();
    }
    
    // -------------

    // Debug Characters only active when debug mode is on
    // debug
    if(cons.keywatch.Command.COMMANDLINE[0] == KEYDEBUG)
    {
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      cons.keywatch.in(KEYDEBUG);
      cons.keywatch.cmdClear();
    }

    // Only accept debug keys if debug is on.
    if (cons.keywatch.getnoreset(KEYDEBUG) == 1)
    {
      // LED DOOR CYCLE
      if(cons.keywatch.Command.COMMANDLINE[0] == KEYLEDDRCYCL)
      {
        cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
        cons.keywatch.in(KEYLEDDRCYCL);
        cons.keywatch.cmdClear();
      }

      // LED RANGE UPer or LOWer.
      if(cons.keywatch.Command.COMMANDLINE[0] == KEYLEDUPLW)
      {
        cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
        cons.keywatch.in(KEYLEDUPLW);
        cons.keywatch.cmdClear();
      }

      // LED TEST toggle all lights on to static value.
      if(cons.keywatch.Command.COMMANDLINE[0] == KEYLEDTEST)
      {
        cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
        cons.keywatch.in(KEYLEDTEST);
        cons.keywatch.cmdClear();
      }

      // Toggle door open or closed.
      if(cons.keywatch.Command.COMMANDLINE[0] == '1')
      {
        cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
        cons.keywatch.in('1');
        cons.keywatch.cmdClear();
      }

      // Toggle door open or closed.
      if(cons.keywatch.Command.COMMANDLINE[0] == '2')
      {
        cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
        cons.keywatch.in('2');
        cons.keywatch.cmdClear();
      }

      // Toggle door open or closed.
      if(cons.keywatch.Command.COMMANDLINE[0] == '3')
      {
        cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
        cons.keywatch.in('3');
        cons.keywatch.cmdClear();
      }

      // Toggle door open or closed.
      if(cons.keywatch.Command.COMMANDLINE[0] == '4')
      {
        cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
        cons.keywatch.in('4');
        cons.keywatch.cmdClear();
      }
    }

    // Turn on and off debug. Deactivate debug keys when off.
    // Store behavior values for debug info.
    if (cons.keywatch.pressed(KEYDEBUG) == true)
    {
      if (cons.keywatch.getnoreset(KEYDEBUG) == 0)
      {
        // Draw values for debug LED CYCLE through displayed range (all, Door #)
        cons.keywatch.Chars[KEYLEDDRCYCL].VALUE = 0;
        cons.keywatch.Chars[KEYLEDDRCYCL].ACTIVE = false;
        
        // Draw values for debug LED RANGE UPer or LOWer.
        cons.keywatch.Chars[KEYLEDUPLW].VALUE = 0;
        cons.keywatch.Chars[KEYLEDUPLW].ACTIVE = false;

        // Draw values for debug LED TEST toggle all lights on to static value.
        cons.keywatch.Chars[KEYLEDTEST].VALUE = 0;
        cons.keywatch.Chars[KEYLEDTEST].ACTIVE = false;

        // Draw values for toggle door open or closed.
        cons.keywatch.Chars['1'].VALUE = 0;
        cons.keywatch.Chars['1'].ACTIVE = false;
        
        // Draw values for toggle door open or closed.
        cons.keywatch.Chars['2'].VALUE = 0;
        cons.keywatch.Chars['2'].ACTIVE = false;

        // Draw values for toggle door open or closed.
        cons.keywatch.Chars['3'].VALUE = 0;
        cons.keywatch.Chars['3'].ACTIVE = false;

        // Draw values for toggle door open or closed.
        cons.keywatch.Chars['4'].VALUE = 0;
        cons.keywatch.Chars['4'].ACTIVE = false;
      }
      else
      {
        // Reset console debug values to default values if debug turned off.
        cons.keywatch.Chars[KEYLEDDRCYCL].ACTIVE = true;
        cons.keywatch.Chars[KEYLEDUPLW].ACTIVE = true;
        cons.keywatch.Chars[KEYLEDTEST].ACTIVE = true;
        cons.keywatch.Chars['1'].ACTIVE = true;
        cons.keywatch.Chars['2'].ACTIVE = true;
        cons.keywatch.Chars['3'].ACTIVE = true;
        cons.keywatch.Chars['4'].ACTIVE = true;
      }
    }
  }
}

// If a door is opened and DOORAWARE is on, we want to end these animations when the door
//  has been opened.
void extraanimationdoorcheck(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[] )
{
  if ( (sdSysData.intDoorsOpen > 0)  && (sdSysData.booPulsesRunning == true) )
  {
    // End pulses when door is opened.
    processcommandpulseend(cons, sdSysData, tmeCurrentTime, teEvent);
    processcommandoverheadillumend(cons, sdSysData, tmeCurrentTime, teEvent);
  }
}


// ***************************************************************************************
// The Following chunk of code is what handles the imported library's ability to put the 
// lights on and off or whatever.  Will not pretend to understand it.  Instead, will 
// squish it down as much as possible so that I can pretend its not there.
// ***************************************************************************************
int led_count = LED_COUNT;
ws2811_t ledstring;
int *matrix;
static char running = 1;
void matrix_render(void)
{
    int x;

    for (x = 0; x < LED_COUNT; x++)
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
void ledprep(ws2811_t *ws2811)
{
	ws2811->channel[0].count = LED_COUNT;
}
// ***************************************************************************************


// ***************************************************************************************
// MAIN PROGRAM
// ***************************************************************************************
void setup()
{
  // Keeping this for now to remind me of what I haven't implementd, from the preport, 
  //  yet.



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

  // Define Console
  Console cons;
  
  initscr();
  cons.set(CONSOLESPLITSIZE);
  nodelay(stdscr, true);
  
  cons.printi("Initializing Console");
  cons.printi("RasFLED Loop ('x' to Exit) ...");
  
  // Console Key Watch
  cons.keywatch.set((int)KEYEXIT,2);  // Exit the program.

  // Debugging keys
  cons.keywatch.set((int)KEYDEBUG,2);  // Testing Mode Toggle
  cons.keywatch.set((int)KEYLEDDRCYCL,5);  // Test Doors
  cons.keywatch.set((int)KEYLEDUPLW,2);   // Swap LED limits
  cons.keywatch.set((int)KEYLEDTEST,2);  // Test LEDs.  Turn all on low level white.
  cons.keywatch.set((int)'1',2);  // Door Toggles
  cons.keywatch.set((int)'2',2);  // 
  cons.keywatch.set((int)'3',2);  // 
  cons.keywatch.set((int)'4',2);  // 

  // Console resize key (automatic detection)
  cons.keywatch.set(KEY_RESIZE,2);

  // ---------------------------------------------------------------------------------------
  // LED Library Vars and Init
  cons.printi("Initializing LEDS ... ");
  ledstring.freq = TARGET_FREQ;
  ledstring.dmanum = DMA;
  ledstring.channel[0].gpionum = GPIO_PIN;
  ledstring.channel[0].count = LED_COUNT;
  ledstring.channel[0].brightness = 255;
  ledstring.channel[0].invert = 0;
  ledstring.channel[0].strip_type = STRIP_TYPE;
  // I was told a second channel doesnt work.
  /*
  ledstring.channel[1].gpionum = 0;
  ledstring.channel[1].count = 0;
  ledstring.channel[1].invert = 0;
  ledstring.channel[1].brightness = 0;
  ledstring.channel[1].strip_type = 0;
  */
  ws2811_return_t ret;
  ledprep(&ledstring);
  matrix = (int*)malloc(sizeof(ws2811_led_t) * LED_COUNT);
  setup_handlers();
  if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS)
  {
      fprintf(stderr, "ws2811_init failed: %s\n", ws2811_get_return_t_str(ret));
      return ret;
  }
  cons.printi("OK");

  // ---------------------------------------------------------------------------------------

  // Define Door Sensors.
  int intRet = wiringPiSetup();    // Initialize wiringPI.
  pinMode(SWITCH_PINs0, INPUT);
  pinMode(SWITCH_PINs1, INPUT);
  pinMode(SWITCH_PINs2, INPUT);
  pinMode(SWITCH_PINs3, INPUT);
  // Set resistors in pins to Pull Up to the 3.5v rail.
  pullUpDnControl(SWITCH_PINs0, PUD_UP);
  pullUpDnControl(SWITCH_PINs1, PUD_UP);
  pullUpDnControl(SWITCH_PINs2, PUD_UP);
  pullUpDnControl(SWITCH_PINs3, PUD_UP);

  // Define System Data
  system_data sdSystem;

  // FLED
  cons.printi("Initializing Timer");
  FledTime tmeFled;
  tmeFled.set();
  
  // Light Strip Event System
  cons.printi("Initializing Channels");
  timed_event teEvent[NUM_CHANNELS];

  // Define Led Strips
  cons.printi("Initializing LED Strips");
  led_strip lsStrips[8];
  
  // Define Light Strips
  lsStrips[Driver_Back_Door].set(0, s0As, s0Ae);      // Driver Back Door
  lsStrips[Driver_Back_Over].set(0, s0Bs, s0Be);      // Driver Back Overhead
  lsStrips[Driver_Front_Door].set(1, s1As, s1Ae);     // Driver Front Door
  lsStrips[Driver_Front_Over].set(1, s1Bs, s1Be);     // Driver Front Overhed
  lsStrips[Passenger_Back_Door].set(2, s0As, s0Ae);   // Passenger Back Door
  lsStrips[Passenger_Back_Over].set(2, s0Bs, s0Be);   // Passenger Back Overhead
  lsStrips[Passenger_Front_Door].set(3, s1As, s1Ae);  // Passenger Front Door
  lsStrips[Passenger_Front_Over].set(3, s1Bs, s1Be);  // Passenger Front Overhed

  // Define the Supid Random Numbers
  cons.printi("Initializing Random Number Generator");
  stupid_random sRND;
  // Initialize the Stupid Random Numbers
  sRND.set();

  // FLED LED Array
  cons.printi("Initializing LED Arrays");
  CRGB crgbMainArrays0[NUM_LEDSs0];
  CRGB crgbMainArrays1[NUM_LEDSs1];
  CRGB crgbMainArrays2[NUM_LEDSs0];
  CRGB crgbMainArrays3[NUM_LEDSs1];
  
  cons.printi("Initializing Event System");
  teEvent[0].create(NUM_LEDSs0);
  teEvent[1].create(NUM_LEDSs1);
  teEvent[2].create(NUM_LEDSs0);
  teEvent[3].create(NUM_LEDSs1);

  // Door Sensor
  cons.printi("Initializing Sensors");
  hardware_monitor hwDoors[NUM_SWITCHES];
  bool boAuxLightsIsOn = false;

  // Define Door Sensors.
  hwDoors[0].set(true, (unsigned long)tmeFled.now(), 50, true);
  hwDoors[1].set(true, (unsigned long)tmeFled.now(), 50, true);
  hwDoors[2].set(true, (unsigned long)tmeFled.now(), 50, true);
  hwDoors[3].set(true, (unsigned long)tmeFled.now(), 50, true);
  
  cons.printi("Starting System");
  // Sleeping Loop Variables
  tmeFled.setframetime();
  
  double tmeStartTime = tmeFled.tmeFrameMillis;
  unsigned long tmeCurrentMillis = (unsigned long)tmeFled.tmeFrameMillis;

  /*
  // False events
  teEvent[lsStrips[0].Cl].set(tmeCurrentMillis, 50, 50, 20, AnEvSweep, AnPiPulse, false, CRGB(255, 0, 0), CRGB(255, 0, 0), CRGB(255, 0, 0), CRGB(255, 0, 0), 0, 10, false, false);
  teEvent[lsStrips[2].Cl].set(tmeCurrentMillis, 50, 50, 20, AnEvSweep, AnPiPulse, false, CRGB(255, 0, 0), CRGB(255, 0, 0), CRGB(255, 0, 0), CRGB(255, 0, 0), 0, 10, false, false);
  teEvent[lsStrips[4].Cl].set(tmeCurrentMillis, 50, 50, 20, AnEvSweep, AnPiPulse, false, CRGB(255, 0, 0), CRGB(255, 0, 0), CRGB(255, 0, 0), CRGB(255, 0, 0), 0, 10, false, false);
  teEvent[lsStrips[6].Cl].set(tmeCurrentMillis, 50, 50, 20, AnEvSweep, AnPiPulse, false, CRGB(255, 0, 0), CRGB(255, 0, 0), CRGB(255, 0, 0), CRGB(255, 0, 0), 0, 10, false, false);
  */

  // ---------------------------------------------------------------------------------------
  //  Repeating Sleeping Loop until eXit is triggered.
  // ---------------------------------------------------------------------------------------
  while( cons.keywatch.get(KEYEXIT) == 0 )
  {
    // --- Prpare the Loop ---

    // Measure how much time has passed since last frame time read.
    // Store the amount of time it tooke to run a frame
    sdSystem.store_cycle_time(tmeFled.tmeFrameElapse());

    //  Get current time.  This will be our timeframe to work in.
    tmeFled.setframetime();
    tmeCurrentMillis = (unsigned long)tmeFled.tmeFrameMillis;
    
    //  Only update the hardware when changes have been detected.
    //    This vabiable will be checked at the end of the loop.  If nothing was updated,
    //    the loop will just walk on past any hardware updates that would otherwise be
    //    sent.

    bool booUpdates0 = false;
    bool booUpdates1 = false;
    bool booUpdates2 = false;
    bool booUpdates3 = false;

    // Sensor Array (QUICK FIX)
    bool booSensors[NUM_SWITCHES];

    booSensors[0] = digitalRead(SWITCH_PINs0);
    booSensors[1] = digitalRead(SWITCH_PINs1);
    booSensors[2] = digitalRead(SWITCH_PINs2);
    booSensors[3] = digitalRead(SWITCH_PINs3);
    
    // Override the digital pins if in debugging mode.
    if(cons.keywatch.getnoreset(KEYDEBUG) == 1)
    {
      // Toggle on and off the door sensors with keyboard.
      booSensors[0] = cons.keywatch.getTF('1');
      booSensors[1] = cons.keywatch.getTF('2');
      booSensors[2] = cons.keywatch.getTF('3');
      booSensors[3] = cons.keywatch.getTF('4');
    }


    // Check the doors and start or end all animations
    DoorMonitorAndAnimationControlModule(cons, sdSystem, lsStrips, teEvent, hwDoors, booSensors, tmeCurrentMillis);

    // ---------------------------------------------------------------------------------------
    // --- Check and Execute Timed Events That Are Ready ---

    //  Run ALL GLOBAL Timed Events
    teSystem(cons, lsStrips, teEvent, tmeCurrentMillis);

    //  Run ANIMATION EVENT ON LEDS - 0
    booUpdates0 = teEvent[0].execute(cons, sRND, crgbMainArrays0, tmeCurrentMillis);
    //  Run ANIMATION EVENT ON LEDS - 1
    booUpdates1 = teEvent[1].execute(cons, sRND, crgbMainArrays1, tmeCurrentMillis);
    //  Run ANIMATION EVENT ON LEDS - 2
    booUpdates2 = teEvent[2].execute(cons, sRND, crgbMainArrays2, tmeCurrentMillis);
    //  Run ANIMATION EVENT ON LEDS - 3
    booUpdates3 = teEvent[3].execute(cons, sRND, crgbMainArrays3, tmeCurrentMillis);



    // ---------------------------------------------------------------------------------------
    // Render all the LEDs if changes have been made.

    // This part of the code needs to be clean up and consolidated, but it works for now 
    // and I havent decided how to future handle this yet, so it stays for now.

    // --- Execute LED Hardware Changes If Anything Was Updated ---
    if ((booUpdates0 == true) || (booUpdates1 == true) || (booUpdates2 == true) || (booUpdates3 == true))
    {
      //  Do I need to move the whole thing or can I just move the changed pixels?

      int mcount = 0;

      // If debug mode Display all lights static color are selectted, replace all generated led colors
      // with a static color

      CRGB cRGBstaticdisplaycolor =  CRGB(25,25,25);

      if (cons.keywatch.get(KEYLEDTEST) !=0)
      {
        for (int lcount = 0; lcount < NUM_LEDSs0;lcount++)
        {
          crgbMainArrays0[lcount] = cRGBstaticdisplaycolor;
        }
          for (int lcount = 0; lcount < NUM_LEDSs1;lcount++)
        {
          crgbMainArrays1[lcount] = cRGBstaticdisplaycolor;
        }
          for (int lcount = 0; lcount < NUM_LEDSs0;lcount++)
        {
          crgbMainArrays2[lcount] = cRGBstaticdisplaycolor;
        }
          for (int lcount = 0; lcount < NUM_LEDSs1;lcount++)
        {
          crgbMainArrays3[lcount] = cRGBstaticdisplaycolor;
        }
      }

      // Determine and display which lights get shown.
      if (cons.keywatch.get(KEYLEDDRCYCL) == 0 || cons.keywatch.get(KEYLEDDRCYCL) == 1)
      {
        for (int lcount = 0; lcount < NUM_LEDSs0;lcount++)
        {
          if(cons.keywatch.get(KEYLEDUPLW) == 0)
            matrix[mcount]=crgbMainArrays0[lcount].b + (crgbMainArrays0[lcount].g << 8) + (crgbMainArrays0[lcount].r << 16) + (0 << 24);
          else
            matrix[mcount]=crgbMainArrays0[NUM_LEDSs0 - lcount].b + (crgbMainArrays0[NUM_LEDSs0 - lcount].g << 8) + (crgbMainArrays0[NUM_LEDSs0 - lcount].r << 16) + (0 << 24);
          mcount++;
        }
      }

      if (cons.keywatch.get(KEYLEDDRCYCL) == 0 || cons.keywatch.get(KEYLEDDRCYCL) == 2)
      {
        for (int lcount = 0; lcount < NUM_LEDSs1;lcount++)
        {
          if(cons.keywatch.get(KEYLEDUPLW) == 0)
            matrix[mcount]=crgbMainArrays1[lcount].b + (crgbMainArrays1[lcount].g << 8) + (crgbMainArrays1[lcount].r << 16) + (0 << 24);
          else
            matrix[mcount]=crgbMainArrays1[NUM_LEDSs1 - lcount].b + (crgbMainArrays1[NUM_LEDSs1 - lcount].g << 8) + (crgbMainArrays1[NUM_LEDSs1 - lcount].r << 16) + (0 << 24);
          mcount++;
        }
      }

      if (cons.keywatch.get(KEYLEDDRCYCL) == 0 || cons.keywatch.get(KEYLEDDRCYCL) == 3)
      {
        for (int lcount = 0; lcount < NUM_LEDSs0;lcount++)
        {
          if(cons.keywatch.get(KEYLEDUPLW) == 0)
            matrix[mcount]=crgbMainArrays2[lcount].b + (crgbMainArrays2[lcount].g << 8) + (crgbMainArrays2[lcount].r << 16) + (0 << 24);
          else
            matrix[mcount]=crgbMainArrays2[NUM_LEDSs0 - lcount].b + (crgbMainArrays2[NUM_LEDSs0 - lcount].g << 8) + (crgbMainArrays2[NUM_LEDSs0 - lcount].r << 16) + (0 << 24);
            mcount++;
        }
      }

      if (cons.keywatch.get(KEYLEDDRCYCL) == 0 || cons.keywatch.get(KEYLEDDRCYCL) == 4)
      {
        for (int lcount = 0; lcount < NUM_LEDSs1;lcount++)
        {
          if(cons.keywatch.get(KEYLEDUPLW) == 0)
            matrix[mcount]=crgbMainArrays3[lcount].b + (crgbMainArrays3[lcount].g << 8) + (crgbMainArrays3[lcount].r << 16) + (0 << 24);
          else
            matrix[mcount]=crgbMainArrays3[NUM_LEDSs1 - lcount].b + (crgbMainArrays3[NUM_LEDSs1 - lcount].g << 8) + (crgbMainArrays3[NUM_LEDSs1 - lcount].r << 16) + (0 << 24);
          mcount++;
        }
      }


      // LED Library Renderer -- Recommend: DON'T TOUCH        
      matrix_render();
      if ((ret = ws2811_render(&ledstring)) != WS2811_SUCCESS)
      {
          fprintf(stderr, "ws2811_render failed: %s\n", ws2811_get_return_t_str(ret));
          break;
      }
    }   // End Delayless Loop


    // ---------------------------------------------------------------------------------------
    // Now that we have done all the hard work, read hardware, computed, generated, displayed 
    // all the lights, we will take the latter clock cycles to get keybord input and update 
    // console with status and so on. 


    // --- Grabbing Data From Keyboard and update whatever is associated to the key pressed.
    cons.readkeyboardinput();

    // Displaying and updating the screen, but only when its ready.  
    //  This will be every SCREENUPDATEDELAY ms.
    if (cons.isready(tmeCurrentMillis, SCREENUPDATEDELAY))
    {
      // Process keyboard info before displaying the screen.
      // This will handle special redraw events such as screen resize.
      cons.processkeyboadinput();
      processcommandlineinput(cons, sdSystem, tmeCurrentMillis, teEvent);
      extraanimationdoorcheck(cons, sdSystem, tmeCurrentMillis, teEvent);
      // Refresh console data storeage from main program. This will be a pass through buffer. 
      // so the console will not have to access any real data. 
      sdSystem.store_door_switch_states(booSensors);
      sdSystem.store_event_counts(teEvent[0].teDATA.size(),teEvent[1].teDATA.size(),teEvent[2].teDATA.size(),teEvent[3].teDATA.size());

      cons.output(sdSystem);
      cons.update_displayed_time(tmeCurrentMillis);
      sdSystem.refresh();
    }


    // ---------------------------------------------------------------------------------------
    // Now that the complete cycle is over, we need figure out how much time is remaining in 
    // the cycle and go to sleep for the appropriate amount of time. 
    // Calculate times and sleep till next frame is ready.

    // For the next display cycle, we need to store info to the console about how things went.
    // Determine how long it took to compute before sleep.
    sdSystem.store_compute_time(tmeFled.tmeFrameElapse());
    
    // Determine how long to sleep and then sleep.
    usleep (1000 * sdSystem.getsleeptime(FRAMES_PER_SECOND));
    
  }// End MAIN CYCLE WHILE loop.


  // ---------------------------------------------------------------------------------------
  // If we are here, then we are closing the program.
  
  // Shutdown the LED strip routine.
  ws2811_fini(&ledstring);

  // Shutdown NCurses.
  endwin();

  // Just print we have ended the program.
  printf ("\nRasFLED Loop ... Exit\n");

  return ret;
}


// ---------------------------------------------------------------------------------------


int main(int argc, char *argv[])
{
  //printf("RasFLED Start ... \n");

  // Setup the Program
  setup();

  // Start the main loop.
  loop();

  // Exit the program.
  // return 0;

}