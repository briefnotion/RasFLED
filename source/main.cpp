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
// *  PROJECTID: gi6$b*E>*q%;    Revision: 00000000.01
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

//#include <FastLED.h>
//#include <Wire.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ctime>
#include <chrono>
#include <unistd.h>
#include <termio.h>
//#include <stdbool.h> 

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
// HARDWARE SETUP

// Console Escape Codes.
#define SCRCLEAR "\33[2J\r"
#define SCRPOS "\33[%d;%dH\r"
  // Example:
    // printf(SCRCLEAR);
    // printf(SCRPOS, 1, 1);
#define SCRCOL4 "\33[0;%dm\r"     // http://www.cplusplus.com/forum/unices/36461/
                                    // 30 -black
                                    // 31 -red
                                    // 32 -green
                                    // 33 -brown
                                    // 34 -blue
                                    // 35 -magenta
                                    // 36 -cyan
                                    // 37 -lightgray
#define SCRCOL8 "\33[38;5;%dm\r"  // https://en.wikipedia.org/wiki/ANSI_escape_code
                                    // 208 -orange

// Testing and Debugging
#define BOOTEST       false       // Not Implemented - Fading Away

//!!!!!!!!!! NEEDS TO GO  !!!!!!!!!!!!!!
#define RESTTIME      25      // Ok, 125 FPS, max and estimated.      

// -------------------------------------------------------------------------------------
// LED Strip Declarations

#define TARGET_FREQ             WS2811_TARGET_FREQ
#define GPIO_PIN                18
#define DMA                     10
//#define STRIP_TYPE            WS2811_STRIP_RGB		// WS2812/SK6812RGB integrated chip+leds
#define STRIP_TYPE              WS2812_STRIP		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE            SK6812_STRIP_RGBW		// SK6812RGBW (NOT SK6812RGB)

#define LED_COUNT               482

/*
// -------------------------------------------------------------------------------------
// Arduino LED data pins to transmit on off and colors for strip s0 and s1

#define DATA_PINs0    3       // 3 // A3 - Data Pin for Strip 1
#define DATA_PINs1    4       // 4 // A4 - Data Pin for Strip 2
*/

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




/*
// TEST
#define NUM_LEDSs0    123     
// Door 2
#define s0As          0       // s0 A Start
#define s0Ae          30      // s0 A End
// Overhead 1
#define s0Bs          31      // s0 B Start
#define s0Be          60     // s0 B End

#define NUM_LEDSs1    118
// Door 2
#define s1As          122     // 0 s1 A Start   // was 0
#define s1Ae          187     // 65 s1 A End    // was 65
// Overhead 2
#define s1Bs          188     // 66 s1 B Start  // was 66
#define s1Be          239     // 117 s1 B End   // was 117

#define NUM_LEDSs2    123
// Door 3
#define s2As          240     // s0 A Start     // was 0
#define s2Ae          309     // s0 A End       // was 69
// Overhead 3
#define s2Bs          310     // s0 B Start     // was 70
#define s2Be          361     // s0 B End       // was 121

#define NUM_LEDSs3    118
// Door 4
#define s3As          362     // 0 s1 A Start   // was 0
#define s3Ae          427     // 65 s1 A End    // was 65
// Overhead 4
#define s3Bs          430     // 66 s1 B Start  // was 66
#define s3Be          481     // 117 s1 B End   // was 117
*/

// -------------------------------------------------------------------------------------
// Arduino switch pin for doors and switches

/*
// On off buttons, door sensors, switches.
#define SWITCH_PINs0    8       // 8 // A8 - Hardware Open Close Door Sensor 1
#define SWITCH_PINs1    9       // 9 // A9 - Hardware Open Close Door Sensor 2
#define SWITCH_PINs2    10      // 9 // A9 - Hardware Open Close Door Sensor 3
#define SWITCH_PINs3    11      // 9 // A9 - Hardware Open Close Door Sensor 3
*/
#define AUXDRLINGERFRT  15000    // How long the Front Door lights stay on after close
#define AUXDRLINGERBCK  25000    // How long the Back Door lights stay on after close


// -------------------------------------------------------------------------------------
// Hardware to Software definitions
// -------------------------------------------------------------------------------------

#define NUM_CHANNELS      4   // Amount of LED strips we will be controlling.
#define NUM_TIMED_EVENTS  32  //15  // Untill I can remember how LL, this is being
//  Also, total number of this will be multiplied by the
//  amount of LED strips you have setup.  Watch your memory.
#define NUM_SWITCHES      4   // 4

#define BRIGHTNESS        1  //96  Using Example Code.  Max unknown
#define FRAMES_PER_SECOND 60 // Will not be necessary, but keeping, for now, just in 
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
#define Unknown       0 // Door Open Animation
#define OpenDoor      1 // Door Open Animation
#define CloseDoor     2 // Door Close Animation
#define OpenOver      3 // Overhead Open Animation
#define CloseOver     4 // Overhead Close 1 Animation
#define CloseOve2     5 // Overhead Close 2 Animation

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

// Effects

//  Normal Effects  
#define AnTavdPacificaish       60
#define AnTavdPaAnimClose       61
#define AnTaChannelPulseColor   63

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

// -------------------------------------------------------------------------------------

// COMMUNICATIONS
/*
  // Handled by Wire library I2C/TWI.  Pins are hardwired and only defined here for
  //  reference.
  #define COMMDATA      D4      // D4 - Data line.
  #define COMMCLK       D5      // D5 - Clock line.

  #define SLAVEID       5       // ID of this device on the bus.  Needs to change for
  //  every device.  A percistand unique ID would make
  //  this much easier during deployment.
  #define DATASIZE      1       // The size of the data packet.
*/


// ***************************************************************************************
// STRUCTURES
// ***************************************************************************************

class Keys
{
  private:
  struct Letter
  {
    char Letter;
    int Count = 0;
    int Value = 0;
    int Pressed = false;
  };

  public:
  Letter Chars[26];

  void set(char letter, int size)
  {
    Chars[letter].Letter = letter;
    Chars[letter].Count = size - 1;
    Chars[letter].Value = 0;
  }

  void in(char c)
  {
    Chars[c].Value++;
    Chars[c].Pressed = true;
    if (Chars[c].Value > Chars[c].Count)
    {
      Chars[c].Value = 0;
    }
  }

  int get(char c)
  {
    Chars[c].Pressed = false;
    return Chars[c].Value;
  }

  bool getTF(char c)
  {
    Chars[c].Pressed = false;
    if (Chars[c].Value == 0)
      return false;
    else
      return true;
  }

  bool pressed(char c)
  {
    return (Chars[c].Pressed);
  }
};

class FledTime
{
  private:
  std::chrono::time_point<std::chrono::system_clock> tmeStart;
  std::chrono::time_point<std::chrono::system_clock> tmeFrame;

  public:
  //using namespace std::chrono;

  double tmeFrameMillis;

  void set()
  {
    tmeStart = std::chrono::system_clock::now();
  }

  void setframetime()
  {
    tmeFrame = std::chrono::system_clock::now();
    std::chrono::duration<double>  dur = tmeFrame - tmeStart;

    tmeFrameMillis = dur.count();
    tmeFrameMillis = tmeFrameMillis * 1000;
  }

  double tmeFrameElapse()
  {
    double elapsed;
    std::chrono::time_point<std::chrono::system_clock> tmeNow = std::chrono::system_clock::now();
    std::chrono::duration<double>  dur = tmeNow - tmeFrame;
    
    elapsed = dur.count();
    elapsed = elapsed * 1000;

    return elapsed;
  }
};



// Stupid Random Generator Structure
struct stupid_random
//  This is a simple solution to random numbers not being randomly generated.
//    Generate a string of random numbers to be used and referenced throughout the
//    entirity of the program run.
{
  char  stupidnumbers[StuRNDsize];

  void init()
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
      //number = rand(StuRNDsize);

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
  char  getB(unsigned long seed, int size)
  {
    int pos = (seed % StuRNDsize);

    return (stupidnumbers[pos] % size);  
    
   }

  // Return random unsigned long from list based on seed.
  //  Number will evenly distributed from other numbers 
  //    based on list size.  Precision is way off, but should
  //    be ranndom
  unsigned long getUL(unsigned long seed, int size)
  {
    int pos = (seed % StuRNDsize);

    return (stupidnumbers[pos] % size) * (size / StuRNDsize);
  }
};


// LedStrip Structures 

// -------------------------------------------------------------------------------------
// Defines a basic LED Strip
struct led_strip
{
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


// Large color variable. 

class CRGB
// RGB varible.
{
public: 
  char r;
  char g;
  char b;

  CRGB()
  {
	  char r = 0;
	  char g = 0;
	  char b = 0;
  }
  
  CRGB(char R,char G,char B)
  {
	  r = R;
	  g = G;
	  b = B;
  }
  
  bool operator== (CRGB color)
  {
    if ((r == color.r) && (g == color.g) && (b == color.b))
      return true;
    else
      return false;
  }
};


struct bigCRGB
// Simple RGB varible for computation.
{
  int r = 0;
  int g = 0;
  int b = 0;
  bool complete = true;
};


// -------------------------------------------------------------------------------------

// Timed Event Data Variable

struct timed_event_data
// Varibles to control the timed_event.
{
  unsigned long tmeSTARTTIME;
  unsigned int intDURATION;
  unsigned int intSPEED;
  char  bytANIMATION;
  char  bytLEDANIMATION;
  CRGB crgbCOLORSTART1;
  CRGB crgbCOLORSTART2;
  CRGB crgbCOLORDEST1;
  CRGB crgbCOLORDEST2;
  char  intSTARTPOS;
  char  intENDPOS;
  bool booINVERTCOLOR = false;
  bool booREPEAT;
  bool booCLEARONEND = true;

  bool booCOMPLETE = true;


  void PostCheck(unsigned long tmeCurrent)
  // Check to see if the event is over, unlock and release Start Colors.
  {
    //  (num of led * speed + duration)
    // Grabbing actual current time to process decayed events, because alot could've happened
    // since then.

    if (booCOMPLETE == true)
      //if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() >= tmeSTARTTIME + intDURATION +
      //    ((abs(intENDPOS - intSTARTPOS) + 1) * intSPEED))
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

struct timed_event
//  Create a Timed LED Event:
//    Controls when a group of LEDs are to begin their individual light path animation.
//    If an event is over written the previous animation will be lost.
{
  timed_event_data teDATA[NUM_TIMED_EVENTS];
  unsigned int      intLEDCOUNT;

  void create(unsigned intLedCount)
  // On startup, define the amount of LEDs in this event list.
  {
    intLEDCOUNT = intLedCount;
  }

  void set(unsigned long tmeCurrentTime,
           unsigned long tmeStartInTime, unsigned long intDuration, unsigned int intSpeed, 
           char  bytAnimation, char  bytLEDAnimation, bool booInvertColor, 
           CRGB crgbStart1, CRGB crgbDest1, CRGB crgbStart2, CRGB crgbDest2, 
           int intStartPos, int intEndPos, bool booRepeat, bool booClearOnEnd)
  // Prepare an animation to start at a specific time.
  {

    bool booCreated = false;

    for (int x = 0; ((x < NUM_TIMED_EVENTS) && (booCreated == false)) ; x++)
    {
      if (teDATA[x].booCOMPLETE == true)
      {
        unsigned long tmeStartTime = tmeCurrentTime + tmeStartInTime;

        teDATA[x].tmeSTARTTIME = tmeStartTime;
        teDATA[x].intDURATION = intDuration;
        teDATA[x].intSPEED = intSpeed;
        teDATA[x].bytANIMATION = bytAnimation;
        teDATA[x].bytLEDANIMATION = bytLEDAnimation;

        teDATA[x].booINVERTCOLOR = booInvertColor;

        teDATA[x].crgbCOLORSTART1 = crgbStart1;
        teDATA[x].crgbCOLORSTART2 = crgbStart2;
        teDATA[x].crgbCOLORDEST1 = crgbDest1;
        teDATA[x].crgbCOLORDEST2 = crgbDest2;

        teDATA[x].intSTARTPOS = intStartPos;
        teDATA[x].intENDPOS = intEndPos;
        teDATA[x].booREPEAT = booRepeat;
        teDATA[x].booCLEARONEND = booClearOnEnd;

        teDATA[x].booCOMPLETE = false;

        booCreated = true;
        printf("Event created: StartTime: %d, Anim: %d, LEDanim: %d\n", tmeStartTime, bytAnimation, bytLEDAnimation);
      }
    }
    if (booCreated == false)
    {
      printf("Event failed to be created\n");
    }
  }

  // -------------------------------------------------------------------------------------
  // Clear events in channel

  void ClearAll(int intStartPos, int intEndPos)
  //Remove all timed event animations on a specific animation strip.
  {
    printf("Clearing Events with LEDs between (%d and %d)\n", intStartPos, intEndPos);
    for (int x = 0; x < NUM_TIMED_EVENTS; x++)

    if (teDATA[x].booCOMPLETE == false && 
        (  ((teDATA[x].intSTARTPOS >= intStartPos)  
          && (teDATA[x].intSTARTPOS <= intEndPos))
                ||
          ((teDATA[x].intENDPOS >= intStartPos)  
          && (teDATA[x].intENDPOS <= intEndPos))  ) )
    {
      
      {
        teDATA[x].booCOMPLETE = true;
        printf("Cleared Event: %d\n", x);
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
                          int intLED, int intEvent, timed_event_data EventInfo)
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
  }

  // -------------------------------------------------------------------------------------

  bool execute(stupid_random sRND, CRGB hwLEDArray[], unsigned long tmeCurrentTime)
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
    
    bool booEventActive[NUM_TIMED_EVENTS];
    bool booEventComplete[NUM_TIMED_EVENTS];
    bigCRGB bigcrgbNewColor;
    bigCRGB tempColor;

    bool booChanged = false;
    unsigned long tmeStartAnim;

    // Process Event Animations  
    // Prepare Arrays

    for (int e = 0; e < NUM_TIMED_EVENTS; e++) //Duplicate
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
      for (int event = 0; event < NUM_TIMED_EVENTS; event++)
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
        hwLEDArray[led].r = bigcrgbNewColor.r;
        hwLEDArray[led].g = bigcrgbNewColor.g;
        hwLEDArray[led].b = bigcrgbNewColor.b;

        booChanged = true;
      }
    } // End For LED Loop

    // All Leds Processed

    //  Check to see if any events expire or repeats.
    for (int e = 0; e < NUM_TIMED_EVENTS; e++)
    {
      if (booEventActive[e] == true && booEventComplete[e] == true)
      {
        teDATA[e].booCOMPLETE = true;
        //teDATA[e].PostCheck(tmeCurrentTime, booEventColision[e]);
        teDATA[e].PostCheck(tmeCurrentTime);
      }
    }

  return booChanged;
  
  }
};


// ---------------------------------------------------------------------------------------


// Hardware Monitor Variable

struct hardware_monitor
// Create a hardware switch or button varable type.
{
  // External
  bool booVALUE;
  unsigned long tmeTOGGLEDTIME;
  bool ISHARDWARE = false;

  // Internal
  unsigned long tmeCHANGEDETECTEDTIME;
  bool booPREVCHANGEDETECTED;
  unsigned int tmeLEEWAY;
  bool booFIRSTRUN = true;

  void set(bool booValue, int tmeLeeWay, bool isHardware)
  // Prepare the switch.
  {
    tmeCHANGEDETECTEDTIME = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    tmeLEEWAY = tmeLeeWay;
    booVALUE = booValue;
    booPREVCHANGEDETECTED = false;
    ISHARDWARE = isHardware;
  }

  bool changed(bool booValue)
  // Return true if the switch state change from on to off or off to on.
  {
    unsigned long tmeTme = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

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
    // Only report change of status when Leeway time is passed.  This is a essentially and
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
  //if (booRandom == false) {booRandom = booRandomSet(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(););}
  //return (random((intBase / 2),(intBase * 2)));
  return 1;
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
  return (1 + (RESTTIME) + intTm + intDur + (intSp * intCt));
}

/*
// -------------------------------------------------------------------------------------
void vdTESTFLASHAnimation(led_strip lsStrips[], led_strip lsSt, timed_event teEvent[], unsigned long tmeCurrentTime)
{
  int intTm;
  int intDur;
  int intCt;
  int intSp;

  intDur = 500; intSp = 50; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 50, intDur, intSp, AnEvSweep, AnPiPulseTo, CRGB(20, 20, 20), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
}
*/

// -------------------------------------------------------------------------------------
// Animations and Animation Scripts
// -------------------------------------------------------------------------------------

// Normal Animations (Main Procedures)



void vdOpenDoorNormal(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdOpenDoorNormal
{
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTaDoorOpen00, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdOpenOverNormal(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdOpenOverNormal
{
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdPacificaish, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseDoorNormal(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdCloseDoorNormal
{
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColor, false, CRGB(125,125,0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverNormal(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdCloseOverNormal
{
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTaStripOverOff, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverCoNormal(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdCloseOve2Normal
{
  int intTm;
  int intDur;
  int intSp;

  //Restore the privouse Blue to fade out
  intTm = 200; intDur = 6000; intSp = 5;

  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm , intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 60), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, false, true);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdPaAnimClose, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

/*
// Halloween Animations (Main Procedures)

void vdOpenOverHallow(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdOpenOverHallow
{
  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdCloud, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdCeilingLight, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdLightning, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverHallow(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdCloseOverHallow
{
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdChannelLightning, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdHallowClose2(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Halloween Overhead Close 2 - Orange Ambiant and Off Routine
{
  // AnTavdHallowClose2

  // Stop the animation.
  // Schedule clear animation events ahead of time in case animations don't get completed.
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, AUXDRLINGERBCK + 2000, 0, 0, AnEvClearRunning, 0, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, AUXDRLINGERBCK + 2100, 3000, 30, AnEvSweep, AnPiFade, CRGB(4, 6, 10), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);

  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdChannelLightning, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 50, 0, 0, AnEvSchedule, AnTavdCloud, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[lsStrips[intStripID].Cl].St, lsStrips[lsStrips[intStripID].Cl].Ed, false, true);
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------


// Thanksgiving Animations (Main Procedures)

void vdOpenOverThanks(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdOpenOverThanks
{
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdBlueSky, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverThanks(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdCloseOverThanks
{
  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTaStripOverOffThanks, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverThanksCo(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdCloseOverThanksCo
{
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdNightSkyClose, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdAddOpenThanks(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavd----  // Simple
{
  teEvent[lsStrips[intStripID +1].Cl].set(tmeCurrentTime, 4000, 1000, 40, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(125,125,0), lsStrips[intStripID +1].St, lsStrips[intStripID +1].Ed, false, false);
}

void vdAddCloseThanks(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavd----  // Simple
{
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 4000, 1000, 40, AnEvSweep, AnPiFade, CRGB(0, 0, 0), CRGB(0, 0, 30), CRGB(0, 0, 0), CRGB(0, 0, 30), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(125), AnEvSweep, AnPiPulse, CRGB(30, 30, 30), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
}
*/


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// Christmas Animations (Main Procedures)

// Normal Animations (Main Procedures)

void vdOpenDoorChristmas(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// ---
{
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTaDoorOpen00Christmas, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdOpenOverChristmas(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// ---
{
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdChristmasTree, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseDoorChristmas(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// ---
{
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColor, false, CRGB(64,64,0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverChristmas(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// ---
{
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColor, false, CRGB(64,64,0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdCloseOverCoChristmas(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// ---
{
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdChristmasTreeCo, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);  
}

void vdAddOpenChristmas(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavd----  // Simple
{
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 500, 0, 0, AnEvSchedule, AnTavdAddOpenChristm, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);  
}

void vdAddCloseChristmas(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavd----  // Simple
{
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 500, 0, 0, AnEvSchedule, AnTavdAddCloseChristm, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);    
 }

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// Test Animations (Main Procedures)

void vdOpenDoorTest(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// AnTavdOpenDoorNormal
{
  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 500, 8000, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(1, 90, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 1500, 8000, 0, AnEvSweep, AnPiTwinkle, CRGB(64, 64, 0), CRGB(64, 0, 64), CRGB(0, 64, 64), CRGB(1, 90, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);

  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 500, 8000, 0, AnEvSweep, AnPiTwinkle, false, CRGB(64, 64, 64), CRGB(64, 0, 64), CRGB(0, 64, 64), CRGB(4, 90, 1), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);

  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 400, 350, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(4, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 500, 475, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(4, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 600, 525, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(4, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);

  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 500, 4000, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(2, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 400, 6237, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(2, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 300, 8713, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(20, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 200, 11031, 0, AnEvSweep, AnPiTwinkle, CRGB(128, 0, 0), CRGB(0, 128, 0), CRGB(0, 0, 128), CRGB(20, 0, 3), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// Standard Animations and Effects 

/*
void vdPowerOnAnimation(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
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
  teEvent[1].set(tmeCurrentTime, 50, intDur, intSp, AnEvSweep, AnPiPulseTo, false,  CRGB(125, 125, 125),CRGB(0, 0, 25), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[Front_Over].Ed, lsStrips[Front_Door].St, false, true);
  // Pulse Back Door
  teEvent[0].set(tmeCurrentTime, 640, intDur, intSp, AnEvSweep, AnPiPulseTo, false, CRGB(125, 125, 125), CRGB(0, 0, 25), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[Back_Over].Ed, lsStrips[Back_Door].St, false, true);


  intDur = 2000; intSp = 15; intCt = 71;
  // Clear Front Door
  teEvent[1].set(tmeCurrentTime, 890, intDur, intSp, AnEvSweep, AnPiFade, false, CRGB(0, 0, 25), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[Front_Over].Ed, lsStrips[Front_Door].St, false, true);
  // Clear Back Door
  teEvent[0].set(tmeCurrentTime, 1480, intDur, intSp, AnEvSweep, AnPiFade, false, CRGB(0, 0, 25), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[Back_Over].Ed, lsStrips[Back_Door].St, false, true);
}
*/

// -------------------------------------------------------------------------------------

// Pulse white then green fadeout

/*
void vdSimplePulse(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Just to show the lights work when the program starts.        
// vdSimplePulse(teEvent, 1, tmeCurrentTime);
{
  int intTm;
  int intDur;
  int intSp;

  intDur = 250; intSp = 5;
  // Pulse Front Door
  teEvent[1].set(tmeCurrentTime, 50, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(125, 125, 125), CRGB(0, 0, 25), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[Front_Over].Ed, lsStrips[Front_Door].St, false, true);
  // Pulse Back Door
  teEvent[0].set(tmeCurrentTime, 50, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(125, 125, 125), CRGB(0, 0, 25), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[Back_Over].Ed, lsStrips[Back_Door].St, false, true);
}
*/

// -------------------------------------------------------------------------------------

// Pulse strip Color then fade out.

void vdStripOverOff(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
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
  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm + 50, intDurW, intSp, AnEvSweep, AnPiPulse, CRGB(64, 128, 64), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[lsStrips[intStripID].Cl].St, lsStrips[lsStrips[intStripID].Cl].Ed, false, true);
  // Overhead White
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm + intDelay + 50, intDurW, intSp, AnEvSweep, AnPiPulse, false, CRGB(64, 128, 64), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0),  start, end, false, true);
 
  // Door Green Fadeout
  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, intDurG, intSp, AnEvSweep, AnPiPulse, CRGB(0, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[lsStrips[intStripID].Cl].St, lsStrips[lsStrips[intStripID].Cl].Ed, false, true);
  // Overhead Green Fadeout
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm + intDelay, intDurG, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0),  start, end, false, true);
}

// -------------------------------------------------------------------------------------

// Pulse channel Specific Color then fade out.

void vdChannelLightPulseColor(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime, CRGB crgbColor)
// Turn (force) Green Pulse on Full Channel. Strip Length Aware. 
// AnTaChannelPulseColor
{
  int intTm;
  int intDurW;
  int intDurG;
  int intCt;
  int intSp;

  int intDelay;

  // Set the fadeout color 
  CRGB crgbColor4;
  crgbColor4.r = crgbColor.r + 64;
  crgbColor4.g = crgbColor.g + 64;
  crgbColor4.b = crgbColor.b + 64;

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
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm + 50, intDurW, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor4, CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  // Overhead Color with White
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm + intDelay + 50, intDurW, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor4, CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, true);
 
  // Door Color Fadeout
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, intDurG, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor, CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  // Overhead Color Fadeout
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm + intDelay, intDurG, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), crgbColor4, CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, true);
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// Normal door open animation script

// Mock Normal Open Door Animation
void vdDoorOpenAnimation(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door Open 
// Door is open, engage safety lights and start door overhead lights.
{
  //Door Animation
  // Clear Events On Door
  vdClearAllTimedEvent(teEvent, lsStrips[intStripID].Cl, lsStrips[intStripID].St, lsStrips[intStripID].Ed);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTaDoorOpen00, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);

  // Clear Events for the Overhead Animation
  vdClearAllTimedEvent(teEvent, lsStrips[intStripID].Cl, lsStrips[intStripID +1 ].St, lsStrips[intStripID +1 ].Ed);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 10, 0, 0, AnEvSchedule, AnTavdPacificaish, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

// -------------------------------------------------------------------------------------

void vdDoorOpenAnimation00(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door Open Stage 0
// Prepare red backgrounds and puddle lights for the caution lights, and start shimmer effect.
{
  printf("vdDoorOpenAnimation00 (S:%d E:%d)\n",lsStrips[intStripID].St, lsStrips[intStripID].Ed);
  int intTm;
  int intDur;
  int intCt;
  int intSp;
  // Door Open Animation
  intTm = 100; intDur = 500; intSp = 10; intCt = lsStrips[intStripID].Ct(); // was 60

  // Clear set background to door open colors.
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(255, 255, 255), CRGB(0, 0, 0), CRGB(255, 64, 64), lsStrips[intStripID].St, lsStrips[intStripID].St + 4, false, false);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(255, 64, 64), CRGB(0, 0, 0), CRGB(25, 0, 0), lsStrips[intStripID].St + 5, lsStrips[intStripID].St + 10, false, false);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFade, false, CRGB(0, 0, 0), CRGB(25, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St + 11, lsStrips[intStripID].Ed - 6, false, false);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm + 500, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(25, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed - 5, lsStrips[intStripID].Ed, false, false);

  // Shimmer
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, 10000, 500, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(15, 20, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, 6000, 280, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(15, 20, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);

  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, 0, 0, AnEvSchedule, AnTaDoorOpen01, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

// -------------------------------------------------------------------------------------

void vdDoorOpenAnimation01(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door Open Stage 1
{
  printf("vdDoorOpenAnimation01 (S:%d E:%d)\n",lsStrips[intStripID].St, lsStrips[intStripID].Ed);
  int intTm = 50;
  int intDur;
  int intCt;
  int intSp;

  // Caution Door Open Flash
  intDur = 100; intSp = 2; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  intDur = 600; intSp = 12; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  intDur = 1500; intSp = 30; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(128, 128, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);

  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, 0, 0, AnEvSchedule, AnTaDoorOpen02, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

// -------------------------------------------------------------------------------------

void vdDoorOpenAnimation02(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door Open Stage 2
{
  printf("vdDoorOpenAnimation02 (S:%d E:%d)\n",lsStrips[intStripID].St, lsStrips[intStripID].Ed);
  int intTm = 0;
  int intDur;
  int intCt;
  int intSp;
  int intMid = lsStrips[intStripID].Ct() / 2;

  // Repeat Pulse
  intDur = 1500; intSp = 125; intCt = lsStrips[intStripID].Ct(); // was 36
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(255, 255, 0), CRGB(255, 255, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].St + intMid, true, true);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(255, 255, 0), CRGB(255, 255, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].Ed - intMid, true, true);
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// Normal close door animation script.

// Mock Normal Close Door Animation
void vdDoorCloseAnimation(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door Close Stage 0
// Door is closed, disengage safety lights and stop door overhead lights.
{
  printf("vdDoorCloseAnimation (S:%d E:%d)\n",lsStrips[intStripID].St, lsStrips[intStripID].Ed);
  int intTm;
  int intDur;
  int intSp;

  //  Clear Currently Running Animations First
  //  Door
  vdClearAllTimedEvent(teEvent, lsStrips[intStripID].Cl, lsStrips[intStripID].St, lsStrips[intStripID].Ed);
  //  Overhead
  vdClearAllTimedEvent(teEvent, lsStrips[intStripID +1 ].Cl, lsStrips[intStripID +1 ].St, lsStrips[intStripID +1 ].Ed);

  // Pulse Clear All Animations
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColor, false, CRGB(125,125,0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  
  //Restore the privouse Blue to fade out
  intTm = 200; intDur = 6000; intSp = 5;
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm , intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 60), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID +1 ].Ed, lsStrips[intStripID +1 ].St, false, true);

  // Door Animation
  //  No Need While Green Whipe Is Clearing

  // Overhead Animation
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 1500, 0, 0, AnEvSchedule, AnTavdPaAnimClose, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID +1 ].St, lsStrips[intStripID +1 ].Ed, false, true);
}

// -------------------------------------------------------------------------------------

void vdDoorCloseAnimation00(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door closed.  Quick animation to show and turn off lights.
{
  // Fade remaining colors out.

  //  // Not Necesary because clearing door with Green Whipe
  //intTm = intAnTmDly(intTm, intDur, intCt, intSp) + 300;
  //intDur = 5000; intSp = 100; intCt = 36;
  //teEvent[intPos].set(tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFade, CRGB(0, 20, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

/*
// Close overhead animation script

void vdPacificaishAnimationClose(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
{
  // Stop the currently running Pacificaish animation.
  // Schedule clear animation events ahead of time in case animations don't get completed.
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, AUXDRLINGERBCK + 2000, 0, 0, AnEvClearRunning, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, AUXDRLINGERBCK + 2100, 3000, 30, AnEvSweep, AnPiFade, false, CRGB(20, 4, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);

  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 50, 0, 0, AnEvSchedule, AnTavdPaAnimClose00, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[lsStrips[intStripID].Cl].St, lsStrips[lsStrips[intStripID].Cl].Ed, false, true);
}

// -------------------------------------------------------------------------------------

// Amber wave animations on strip.

void vdPacificaishAnimationClose00(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
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
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 50 + 2000, 3000, 30, AnEvSweep, AnPiFade, false, CRGB(0, 0, 0), CRGB(20, 4, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, false);

  // Amber waves.
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intRandomHD(2000) + 2000, intRandomHD(3500), intRandomHD(250), AnEvSweep, AnPiPulse, false, CRGB(20, 4, 0), CRGB(20, 4, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intRandomHD(2000) + 2000, intRandomHD(1500), intRandomHD(150), AnEvSweep, AnPiPulse, false, CRGB(16, 20, 0), CRGB(16, 20, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intRandomHD(2000) + 2000, intRandomHD(3600), intRandomHD(270), AnEvSweep, AnPiPulse, false, CRGB(15, 6, 0), CRGB(20, 4, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intRandomHD(2000) + 2000, intRandomHD(3200), intRandomHD(200), AnEvSweep, AnPiPulse, false, CRGB(25, 2, 0), CRGB(20, 4, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// Blue wave animations on strip.

void vdPacificaishAnimation(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
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
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 1000, 500, 30, AnEvSweep, AnPiFade, false, CRGB(0, 0, 0), CRGB(0, 0, 60), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, false);

  // The waves.
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intRandomHD(2000), intRandomHD(3500), intRandomHD(250), AnEvSweep, AnPiPulse, false, CRGB(40, 200, 160), CRGB(40, 200, 160), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intRandomHD(2000), intRandomHD(1500), intRandomHD(150), AnEvSweep, AnPiPulse, false, CRGB(160, 200, 40), CRGB(40, 200, 160), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intRandomHD(2000), intRandomHD(3600), intRandomHD(270), AnEvSweep, AnPiPulse, false, CRGB(20, 200, 180), CRGB(40, 200, 160), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intRandomHD(2000), intRandomHD(3200), intRandomHD(200), AnEvSweep, AnPiPulse, false, CRGB(60, 200, 140), CRGB(40, 200, 160), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
}
*/

/*
// -------------------------------------------------------------------------------------
// Halloween Effects
// -------------------------------------------------------------------------------------


// Dim clouds on strip.

void vdCloudAnimation(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
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
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 1000, 500, 5, AnEvSweep, AnPiFade, CRGB(0, 0, 0), CRGB(4, 6, 10), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, false);

  // The Clouds.
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(500), AnEvSweep, AnPiPulse, CRGB(10, 17, 20), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(1000), AnEvSweep, AnPiPulse, CRGB(10, 20, 20), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(500), AnEvSweep, AnPiPulse, CRGB(10, 27, 33), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, true, true);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(1000), AnEvSweep, AnPiPulse, CRGB(10, 22, 31), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, true, true);
  }

// -------------------------------------------------------------------------------------

// Dingy yellow light on strip end.

void vdCeilingLightAnimation(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
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
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 1000, 500, 20, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), CRGB(64, 64, 30), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, false);
  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), CRGB(255, 255, 255), CRGB(0, 0, 0), CRGB(255, 64, 64), lsStrips[intStripID].St, lsStrips[intStripID].St + 4, false, false);
}

// -------------------------------------------------------------------------------------

// Random lightning strike on strip.

void vdLightning(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
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
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, StartTime + 5000, 0, 0, AnEvSchedule, AnTavdLightning, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  
  // Thunder
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime,  StartTime + BlinkInterval, 1500, 3, AnEvSweep, AnPiFade, CRGB(32, 32, 49), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);

  // Flash 1
  intSp = intRandomHD(2);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime,  StartTime + BlinkInterval, intDur, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  
  // Flash 2
  BlinkTime = intRandomHD(BlinkInterval); intSp = intRandomHD(2);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime,  StartTime + BlinkTime, intDur, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);

  // Flash 3
  // BlinkTime = intRandomHD(BlinkInterval); intSp = intRandomHD(2);
  // teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime,  StartTime + BlinkTime, intDur, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

// -------------------------------------------------------------------------------------

// Random lightning strike on channel.

void vdChannelLightning(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
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
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime,  StartTime + BlinkInterval, 1500, 3, AnEvSweep, AnPiFade, CRGB(32, 32, 49), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  // Overhead 
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime,  StartTime + BlinkInterval + intDelay, 1500, 3, AnEvSweep, AnPiFade, CRGB(32, 32, 49), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, true);
 
  // Flash 1
  intSp = intRandomHD(2);
  // Door
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime,  StartTime + BlinkInterval, 150, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  // Overhead
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime,  StartTime + BlinkInterval + intDelay, 150, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, true);

  // Flash 2
  BlinkTime = intRandomHD(BlinkInterval); intSp = intRandomHD(2);
  // Door
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime,  StartTime + BlinkTime, 150, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  // Overhead
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime,  StartTime + BlinkTime + intDelay, 150, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, true);

  // Flash 3
  BlinkTime = intRandomHD(BlinkInterval); intSp = intRandomHD(2);
  // Door
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime,  StartTime + BlinkTime, 150, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  // Overhead
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime,  StartTime + BlinkTime + intDelay, 150, intSp, AnEvSweep, AnPiPulse, CRGB(128, 128, 196), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), start, end, false, true);
}


//------------------------------------------------------------------------------------
// Thanksgiving Effects
// -------------------------------------------------------------------------------------

// Blue sky with white clouds

void vdBlueSky(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
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
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 1000, 1000, 40, AnEvSweep, AnPiFade, CRGB(0, 0, 0), CRGB(0, 0, 30), CRGB(0, 0, 0), CRGB(0, 0, 30), start, end, false, false);

  // The Clouds.
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(125), AnEvSweep, AnPiPulse, CRGB(30, 30, 30), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intRandomHD(2000), intRandomHD(6000), intRandomHD(250), AnEvSweep, AnPiPulse, CRGB(30, 30, 30), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);
  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(500), AnEvSweep, AnPiPulse, CRGB(10, 27, 33), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, true, true);
  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(1000), AnEvSweep, AnPiPulse, CRGB(10, 22, 31), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, true, true);
  }


// 
void vdNightSkyClose(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
{

  int intTm;
  int intDur;
  int intSp;


  // Stop the currently running Pacificaish animation.
  // Schedule clear animation events ahead of time in case animations don't get completed.
  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, AUXDRLINGERBCK + 2000, 0, 0, AnEvClearRunning, 0, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);

  // Schedule Animations to Fade Out
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, AUXDRLINGERBCK + 1000, 3000, 0, AnEvSetToEnd, 0, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID -1 ].St, lsStrips[intStripID].Ed, false, false);

  //Restore the privouse Color to fade out
  intTm = 200; intDur = 6000; intSp = 5;

  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm , intDur, intSp, AnEvSweep, AnPiPulse, CRGB(0, 0, 30), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].St, false, true);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 50, 0, 0, AnEvSchedule, AnTavdNightSky, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[lsStrips[intStripID].Cl].St, lsStrips[lsStrips[intStripID].Cl].Ed, false, true);
}

// Night Sky

void vdNightSky(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
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
    teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 1000, 8000, 20, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), Set3, CRGB(0, 0, 0), Set2, start, end -25, false, false);
    teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 1000, 8000, 20, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), Set2, CRGB(0, 0, 0), Set1, end -24, end -6, false, false);
    teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 1000, 8000, 20, AnEvSweep, AnPiFade, CRGB(0, 0, 0), Sun, CRGB(0, 0, 0), Sun, end -6, end, false, false);
  }
  else
  {
    // Front Door Light Strip
    start = lsStrips[intStripID].Ed;
    end = lsStrips[intStripID].St;

    teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 1000, 5000, 20, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), Set3, CRGB(0, 0, 0), Set4, start, end + 15, false, false);
    teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 1000, 5000, 20, AnEvSweep, AnPiFadeDith, CRGB(0, 0, 0), Set4, CRGB(0, 0, 0), Set5, end + 14, end, false, false);
  }

}

// -------------------------------------------------------------------------------------
*/


//------------------------------------------------------------------------------------
// Christmas Effects
// -------------------------------------------------------------------------------------

void vdChristmasTree(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Christmas Overhead Open
{
  printf("vdChristmasTree (S:%d E:%d)\n",lsStrips[intStripID].St, lsStrips[intStripID].Ed);
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
    teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 500, 2000, 100, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(0, 45, 20), CRGB(0, 0, 0), CRGB(0, 0, 4), bot, top +15, false, false);

    // Star
    teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 6000, 10000, 0, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(128, 128, 16), top +5, top, false, false);
  }
  else
  {
    // Front Door
    top = lsStrips[intStripID].Ed;
    bot = lsStrips[intStripID].St;

    // Set the background color.
    teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 500, 2000, 100, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(0, 45, 20), CRGB(0, 0, 0), CRGB(0, 0, 4), bot, top -15, false, false);

    // Star 
    teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 10000, 10000, 0, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(128, 128, 16), top -5, top, false, false);
  }
  
  // The Lights.
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 3000, 8000, 0, AnEvSweep, AnPiTwinkle, false, CRGB(200, 0, 0), CRGB(0, 200, 0), CRGB(0, 0, 200), CRGB(2, 75, 3), lsStrips[intStripID].St +6, lsStrips[intStripID].Ed -6, true, false);

  // Variance
  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(500), AnEvSweep, AnPiPulse, true, CRGB(20, 20, 20), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), bot, top, true, true);
}

// -------------------------------------------------------------------------------------

void vdChristmasTreeCo(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn (force) Lights Off ona Strip

// AnTavdChristmasTreeCo

{
  printf("vdChristmasTreeCo (S:%d E:%d)\n",lsStrips[intStripID].St, lsStrips[intStripID].Ed);
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
    teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 500, 10000, 0, AnEvSweep, AnPiFadeDith, false, CRGB(0, 45, 20), CRGB(0, 0, 0), CRGB(0, 0, 4),CRGB(0, 0, 0),  bot, top +15, false, false);
  
    // Star
    teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 500, 0, 0, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(125,124,16), top + lsStrips[intStripID].Ct() /2, top, false, false);
  }
  else
  {
    // Front Door
    top = lsStrips[intStripID].Ed;
    bot = lsStrips[intStripID].St;

    // Background Color Fade out.
    teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 500, 10000, 0, AnEvSweep, AnPiFadeDith, false, CRGB(0, 45, 20), CRGB(0, 0, 0), CRGB(0, 0, 4),CRGB(0, 0, 0),  bot, top - 15, false, false);
  
    // Star 
    teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 500, 0, 0, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(125,124,16), top - lsStrips[intStripID].Ct() /2, top, false, false);
  }

  // Background Color Fade out.

  // Schedule all lights to turn ahead of time at end of cycle
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, AUXDRLINGERBCK - 6000, 9000, 0, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);

  // The Lights.
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 500, 15000, 0, AnEvSweep, AnPiTwinkle, false, CRGB(200, 0, 0), CRGB(0, 200, 0), CRGB(0, 0, 200), CRGB(2, 75, 3), lsStrips[intStripID].St +6, lsStrips[intStripID].Ed -6, false, false);
  // with Sparkle
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 500, 5500, 0, AnEvSweep, AnPiTwinkle, false, CRGB(128, 128, 128), CRGB(64, 0, 64), CRGB(0, 64, 64), CRGB(2, 85, 1), lsStrips[intStripID].St +6, lsStrips[intStripID].Ed -6, true, false);
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
//  Christmas Door Open Animation

void vdDoorOpenAnimation00Christmas(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door Open Stage 0
// Prepare red backgrounds and puddle lights for the caution lights, and start shimmer effect.
{
  printf("vdDoorOpenAnimation00Christmas (S:%d E:%d)\n",lsStrips[intStripID].St, lsStrips[intStripID].Ed);

  int intTm;
  int intDur;
  int intCt;
  int intSp;
  // Door Open Animation
  intTm = 100; intDur = 500; intSp = 10; intCt = lsStrips[intStripID].Ct(); // was 60

  // Clear set background to door open colors.
  
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(255, 255, 255), CRGB(0, 0, 0), CRGB(255, 32, 32), lsStrips[intStripID].St, lsStrips[intStripID].St + 10, false, false);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(255, 32, 32), CRGB(0, 0, 0), CRGB(25, 0, 0), lsStrips[intStripID].St + 5, lsStrips[intStripID].St + 10, false, false);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiFade, false, CRGB(0, 0, 0), CRGB(25, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St + 11, lsStrips[intStripID].Ed - 6, false, false);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm + 500, intDur, intSp, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(25, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed - 5, lsStrips[intStripID].Ed, false, false);
 
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, 0, 0, AnEvSchedule, AnTaDoorOpen01Christmas, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

void vdDoorOpenAnimation01Christmas(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door Open Stage 1
{
  printf("vdDoorOpenAnimation01Christmas (S:%d E:%d)\n",lsStrips[intStripID].St, lsStrips[intStripID].Ed);
  int intTm = 50;
  int intDur;
  int intCt;
  int intSp;

  // Caution Door Open Flash
  intDur = 100; intSp = 2; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  intDur = 600; intSp = 12; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(80, 80, 0), CRGB(80, 80, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  intDur = 1500; intSp = 30; intCt = lsStrips[intStripID].Ct();
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(128, 128, 0), CRGB(128, 128, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);

  intTm = intAnTmDly(intTm, intDur, intCt, intSp);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, 0, 0, AnEvSchedule, AnTaDoorOpen02Christmas, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, true);
}

// -------------------------------------------------------------------------------------

void vdDoorOpenAnimation02Christmas(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Door Open Stage 2
{
  printf("vdDoorOpenAnimation02Christmas (S:%d E:%d)\n",lsStrips[intStripID].St, lsStrips[intStripID].Ed);
  int intTm = 0;
  int intDur;
  int intCt;
  int intSp;
  int intMid = lsStrips[intStripID].Ct() / 2;

  // Repeat Pulse
  intDur = 1500; intSp = 125; intCt = lsStrips[intStripID].Ct(); // was 36
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(255, 255, 0), CRGB(255, 255, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].St + intMid, true, true);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intTm, intDur, intSp, AnEvSweep, AnPiPulse, false, CRGB(255, 255, 0), CRGB(255, 255, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].Ed, lsStrips[intStripID].Ed - intMid, true, true);

  // Sparkle
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 500, 10000, 0, AnEvSweep, AnPiTwinkle, false, CRGB(128, 128, 128), CRGB(64, 0, 64), CRGB(0, 64, 64), CRGB(3, 85, 1), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 500, 5500, 0, AnEvSweep, AnPiTwinkle, false, CRGB(128, 128, 128), CRGB(64, 0, 64), CRGB(0, 64, 64), CRGB(2, 95, 1), lsStrips[intStripID].St +20, lsStrips[intStripID].Ed -20, true, false);
}

void vdAddOpenChristm(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
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
    teEvent[lsStrips[intStripID +1].Cl].set(tmeCurrentTime, 1000, 1000, 80, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(125,124,16), CRGB(0, 0, 0), CRGB(0, 0, 0), top, top + lsStrips[intStripID +1].Ct() /2, false, false);
  }
  else
  {
    // Front Door
    top = lsStrips[intStripID +1].Ed;
    bot = lsStrips[intStripID +1].St;
    
    // Star
    teEvent[lsStrips[intStripID +1].Cl].set(tmeCurrentTime, 1000, 1000, 80, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(125,124,16), CRGB(0, 0, 0), CRGB(0, 0, 0), top, top - lsStrips[intStripID +1].Ct() /2, false, false);
  }
}


void vdAddCloseChristm(led_strip lsStrips[], int intStripID, timed_event teEvent[], unsigned long tmeCurrentTime)
// Turn (force) Lights Off on a Strip

// AnTavdvdAddCloseChristm
{
  // Set the background color.
  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 500, 200, 100, AnEvSweep, AnPiFade, false, CRGB(0, 0, 0), CRGB(0, 45, 20), CRGB(0, 0, 0), CRGB(0, 0, 4), lsStrips[intStripID].St, lsStrips[intStripID].Ed, false, false);

  // The Sparkle.
  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 3000, 15000, 0, AnEvSweep, AnPiTwinkle, false, CRGB(200, 0, 0), CRGB(0, 200, 0), CRGB(0, 0, 200), CRGB(2, 75, 3), lsStrips[intStripID].St , lsStrips[intStripID].Ed, true, false);
  teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, 500, 10000, 0, AnEvSweep, AnPiTwinkle, false, CRGB(128, 128, 128), CRGB(64, 0, 64), CRGB(0, 64, 64), CRGB(3, 85, 1), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, false);
  
  // Variance
  //teEvent[lsStrips[intStripID].Cl].set(tmeCurrentTime, intRandomHD(2000), intRandomHD(10000), intRandomHD(500), AnEvSweep, AnPiPulse, true, CRGB(20, 20, 20), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID].St, lsStrips[intStripID].Ed, true, true);

  // Fade out the bright star.
  teEvent[lsStrips[intStripID +1].Cl].set(tmeCurrentTime, 3000, 1000, 80, AnEvSetToEnd, 0, false, CRGB(125,124,16), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), lsStrips[intStripID +1].St, lsStrips[intStripID +1].Ed, false, true);
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------


// -------------------------------------------------------------------------------------

// System event system for non animations.

void teSystem(led_strip lsStripList[], timed_event teEvent[], unsigned long tmeCurrentTime)
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
    for (int event = 0; event < NUM_TIMED_EVENTS; event++)
    {
      if (tmeCurrentTime >= teEvent[channel].teDATA[event].tmeSTARTTIME && teEvent[channel].teDATA[event].booCOMPLETE == false)
      {
        // Process Timed System Events (keeping the LED type event scheduler format for 
        //  now)
        switch (teEvent[channel].teDATA[event].bytANIMATION)
        {
          case AnEvClear:   // Clear all events, whether running or not, if event is within Start and End Position.
          {
            teEvent[channel].teDATA[event].booCOMPLETE = true;
            teEvent[channel].ClearAll(teEvent[channel].teDATA[event].intSTARTPOS,teEvent[channel].teDATA[event].intENDPOS);
            break;
          }
          
          case AnEvClearRunning:  // Clear all active events if event is within Start and End Position.
          {                       // Possible problem if InTime is set to 0.
            teEvent[channel].teDATA[event].booCOMPLETE = true;

            for (int eventscan = 0; eventscan < NUM_TIMED_EVENTS; eventscan++)
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
                vdPowerOnAnimation(lsStripList, 0, teEvent, tmeCurrentTime);
                break;
              }
              */

              case AnTaChannelPulseColor:
              // Color Specific Channel Pulse
              {
                //vdChannelLightPulseColor(lsStripList, channel *2, teEvent, tmeCurrentTime, CRGB(125,125,0));
                vdChannelLightPulseColor(lsStripList, channel *2, teEvent, tmeCurrentTime, teEvent[channel].teDATA[event].crgbCOLORSTART1);
                break;
              }

              
              // Open Door
              case AnTaDoorOpen:
              {
                vdDoorOpenAnimation(lsStripList, channel *2, teEvent, tmeCurrentTime);
                break;
              }
              case AnTaDoorOpen00:
              {
                vdDoorOpenAnimation00(lsStripList, channel *2, teEvent, tmeCurrentTime);
                break;
              }
              case AnTaDoorOpen01:
              {
                vdDoorOpenAnimation01(lsStripList, channel *2, teEvent, tmeCurrentTime);
                break;
              }
              case AnTaDoorOpen02:
              {
                vdDoorOpenAnimation02(lsStripList, channel *2, teEvent, tmeCurrentTime);
                break;
              }

              // Close Back Door
              case AnTaDoorClose:
              {
                vdDoorCloseAnimation(lsStripList, channel *2, teEvent, tmeCurrentTime);
                break;
              }
              case AnTaDoorClose00:
              {
                vdDoorCloseAnimation00(lsStripList, channel *2, teEvent, tmeCurrentTime);
                break;
              }
              
              case AnTaStripOverOff:
              {
                vdStripOverOff(lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                break;
              }

              /*
              case AnTavdPacificaish:
              {
                vdPacificaishAnimation(lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                break;
              }

              case AnTavdPaAnimClose:
              {
                vdPacificaishAnimationClose(lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                break;
              }

              case AnTavdPaAnimClose00:
              {
                vdPacificaishAnimationClose00(lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                break;
              }
              */

              /*
              // Halloween Animations 

              case AnTavdHallowClose2:
              {
                vdHallowClose2(lsStripList, (channel *2) +1 , teEvent, tmeCurrentTime);
                break;
              }

              case AnTavdCloud:
              {
                vdCloudAnimation(lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                break;
              }

              case AnTavdLightning:
              {
                vdLightning(lsStripList, (channel *2) +1 , teEvent, tmeCurrentTime);
                break;
              }

              case AnTavdCeilingLight:
              {
                vdCeilingLightAnimation(lsStripList, (channel *2) +1 , teEvent, tmeCurrentTime);
                break;
              }

              case AnTavdChannelLightning:
              {
                vdChannelLightning(lsStripList, (channel *2) , teEvent, tmeCurrentTime);
                break;
              }

              // Thanksgiving Animations 

              case AnTavdBlueSky:
              {
                vdBlueSky(lsStripList, (channel *2) +1 , teEvent, tmeCurrentTime);
                break;
              }

              case AnTavdNightSkyClose:
              {
                vdNightSkyClose(lsStripList, (channel *2) +1 , teEvent, tmeCurrentTime);
                break;
              }

              case AnTavdNightSky:
              {
                vdNightSky(lsStripList, (channel *2) +1 , teEvent, tmeCurrentTime);
                break;
              }
              
              case AnTaStripOverOffThanks:
              {
                vdStripOverOffThanks(lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                break;
              }
              */


             // Christmas Animtions
              case AnTavdChristmasTree:
              {
                vdChristmasTree(lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                break; 
              }
              case AnTavdChristmasTreeCo:
              {
                vdChristmasTreeCo(lsStripList, (channel *2) +1, teEvent, tmeCurrentTime);
                break; 
              }
              // Christmas Door Open Animations 
              case AnTaDoorOpen00Christmas:
              {
                vdDoorOpenAnimation00Christmas(lsStripList, channel *2, teEvent, tmeCurrentTime);
                break;
              }
              case AnTaDoorOpen01Christmas:
              {
                vdDoorOpenAnimation01Christmas(lsStripList, channel *2, teEvent, tmeCurrentTime);
                break;
              }
              case AnTaDoorOpen02Christmas:
              {
                vdDoorOpenAnimation02Christmas(lsStripList, channel *2, teEvent, tmeCurrentTime);
                break;
              }
              case AnTavdAddOpenChristm:
              {
                vdAddOpenChristm(lsStripList, channel *2, teEvent, tmeCurrentTime);
                break;
              }
              case AnTavdAddCloseChristm:
              {
                vdAddCloseChristm(lsStripList, channel *2, teEvent, tmeCurrentTime);
                break;
              }


            } // End Case Animation Set
            break;
          } // End Case AnEvSchedule

          case AnEvSetToEnd:  // Schedules an animation to end. Fades out Fades and stops repeat on Pulses.
          {                   // Possible problem if InTime is set to 0.  
            // Clear the Event whether the event ran or not.
            teEvent[channel].teDATA[event].booCOMPLETE = true;   

            // Is the Event we are processing within the event?
            for (int eventscan = 0; eventscan < NUM_TIMED_EVENTS; eventscan++)
            {

              if(teEvent[channel].teDATA[eventscan].tmeSTARTTIME <= tmeCurrentTime)   // May Have Fixed It.  IDK
              {

                if (  ((teEvent[channel].teDATA[eventscan].intSTARTPOS >= teEvent[channel].teDATA[event].intSTARTPOS)  
                      && (teEvent[channel].teDATA[eventscan].intSTARTPOS <= teEvent[channel].teDATA[event].intENDPOS))
                            ||
                      ((teEvent[channel].teDATA[eventscan].intENDPOS >= teEvent[channel].teDATA[event].intSTARTPOS)  
                      && (teEvent[channel].teDATA[eventscan].intENDPOS <= teEvent[channel].teDATA[event].intENDPOS))  )
                {
                  // Check to see if we are only stopping a specificly colored event. 
                  bool cont = false;
                  // Trying not to complicate the code too much.
                  
                  //if (teEvent[channel].teDATA[event].crgbCOLORSTART1.r == 0 &&
                  //    teEvent[channel].teDATA[event].crgbCOLORSTART1.g == 0 &&
                  //    teEvent[channel].teDATA[event].crgbCOLORSTART1.b == 0)
                  
                  if (teEvent[channel].teDATA[event].crgbCOLORSTART1 == CRGB(0,0,0))
                  {
                    cont = true;
                  }
                  else if (teEvent[channel].teDATA[event].crgbCOLORSTART1 == teEvent[channel].teDATA[eventscan].crgbCOLORSTART1)
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

                  if (cont == true)
                  {
                    // Stop the event.
                    teEvent[channel].teDATA[eventscan].booREPEAT = false;
                    teEvent[channel].teDATA[eventscan].booCLEARONEND = true;

                    // Check the event we are stopping to make sure its not the event calling the SetToEnd.
                    if (event != eventscan)
                    {
                      // Manage the Fade Animations to End.
                      if ((teEvent[channel].teDATA[eventscan].bytLEDANIMATION == AnPiFade) ||
                            (teEvent[channel].teDATA[eventscan].bytLEDANIMATION == AnPiFadeDith))
                      {
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
                      if ((teEvent[channel].teDATA[eventscan].bytLEDANIMATION == AnPiPulse) ||
                            (teEvent[channel].teDATA[eventscan].bytLEDANIMATION == AnPiPulseTo))
                      {
                        // Tell the pulse to stop.
                        if (teEvent[channel].teDATA[event].booREPEAT == false)
                        {
                          // For now, we will just kill it and hope another animation clears the artifacts.
                          // It would be nice to have a gracreful end and let the pixel end its animation,
                          // but, thats for another time.
                          teEvent[channel].teDATA[eventscan].booCOMPLETE = true;
                        }

                        // Pulse will end on its on at end of animation.
                        /* if (teEvent[channel].teDATA[event].booREPEAT == true)
                        {
                        } */
                        
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
  } // End FOR strip
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

//  AuxLightControlModule

void DoorMonitorAndAnimationControlModule(led_strip lsStrips[], timed_event teEvent[], hardware_monitor hwmDoor[], bool booSensors[], unsigned long tmeCurrentTime)
// This routine is designed to scan all the doors or switches.  If anthing is open, opened 
//  closed or closed (odd twist of english there) then set the appropriate or maintain
//  animations.  
// Works like this.  If any door is open then make sure the overhead lights are on.  
//  If all the doors are closed, turn all the lights off.  Run door animations like 
//  normal.
{
  int opencount = 0;
  int strip;
  bool changedetected = false;

  // Scan Through Doors and Check for Changes

  // Check for newly opened and run animation on them.
  for (int door=0; door < NUM_SWITCHES; door++)
  {
    if (hwmDoor[door].changed(booSensors[door]) == true)
    {
      changedetected = true; 
      if (hwmDoor[door].booVALUE)  // Door Just Opened
      {
        // Start Open Door Animation on This Door
        if (hwmDoor[door].ISHARDWARE == true)  // Only if its real switch (with lights attached to it)
        {
          strip = door *2;

          lsStrips[strip].AnimationStatus = OpenDoor;

          //Door Animation
          // Clear Events On Door
          vdClearAllTimedEvent(teEvent, door, lsStrips[strip].St, lsStrips[strip].Ed);
          // Clear Events On Overhead
          //vdClearAllTimedEvent(teEvent, door, lsStrips[strip +1 ].St, lsStrips[strip +1 ].Ed);

          printf("  Door %d Open ... ", door);
          vdDoorOpenAnimation00(lsStrips,strip,teEvent,tmeCurrentTime);
        }
      }
      else                        // Door Just Closed
      {
        if (hwmDoor[door].ISHARDWARE == true)  // Only if its real switch (with lights attached to it)
        {
          strip = door *2;

          lsStrips[strip].AnimationStatus = CloseDoor;

          // Start Close Door Animation on This Door
          vdClearAllTimedEvent(teEvent, door, lsStrips[strip].St, lsStrips[strip].Ed);
          // Clear Events On Overhead
          //vdClearAllTimedEvent(teEvent, door, lsStrips[strip +1 ].St, lsStrips[strip +1 ].Ed);
          
          // Pulse Clear All Animations
          printf("Door %d Close ... ", door);          
          vdCloseDoorChristmas(lsStrips,strip,teEvent,tmeCurrentTime);
        }
      }
    }
  }


  // If a door was opened or close we need set the Overhead Lights.
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
    printf("Open Door Count: %d\n", opencount);

    if (opencount > 0)
    {
      // There are open Doors.  Make sure all Overheads are running 
      
      for (int door=0; door < NUM_SWITCHES; door++)
      {
        printf("%d ",door);
        strip = (door *2) +1; // Determine Strip from Door aka Channel
        
        if (hwmDoor[door].ISHARDWARE == true)  // Only if its real switch (with lights attached to it)
        {
          printf("  Door %d Running Overhead: ", door);
          if (lsStrips[strip].AnimationStatus != OpenOver)
          {
            // Clear Events for the Overhead Animation
            vdClearAllTimedEvent(teEvent, door, lsStrips[strip].St, lsStrips[strip].Ed);

            // Start Overhead Animation.
            lsStrips[strip].AnimationStatus = OpenOver;

            // Normal Overhead Animation 
            //vdOpenOverNormal(lsStrips,strip,teEvent,tmeCurrentTime);
            printf("  Overhead S%d ... ", strip);
            vdOpenOverChristmas(lsStrips,strip,teEvent,tmeCurrentTime);
          }

          // Additional animations based on whether or not the door is open.
          if (hwmDoor[door].booVALUE == true) // Door is open 
          {
            printf("  Add On S%d ... ", strip);
            vdAddOpenChristmas(lsStrips,strip - 1,teEvent,tmeCurrentTime);
          }
          else  // Door is closed.
          {
            printf("  Add Off S%d ... ", strip);
            vdAddCloseChristmas(lsStrips,strip - 1,teEvent,tmeCurrentTime);
          }
        }
        printf("EXIT\n");
      }      
    }

    else  // All doors are closed.  Make sure lights are off or turning off and Amber Up the newly closded doors.
      {
      printf("  All Doors Closed \n");
      for (int door=0; door < NUM_SWITCHES; door++)
      {
        strip = (door *2) +1; // Determine Strip from Door aka Channel

        if (hwmDoor[door].ISHARDWARE == true)  // Only if its real switch (with lights attached to it)
        {
          if (lsStrips[strip].AnimationStatus == OpenOver)
          {
            
            // Start Overhead Turn On Convenience Animation.
            // See when the door was closed
            if ((tmeCurrentTime - hwmDoor[door].tmeTOGGLEDTIME) < 15000)
            {
              //  The door was recently closed. Run the Amber Pacifica on it.

              vdClearAllTimedEvent(teEvent, door, lsStrips[strip].St, lsStrips[strip].Ed);

              // This needs to be moved outside of this routine, int an animation event. 
              lsStrips[strip].AnimationStatus = CloseOve2;  

              vdCloseOverCoChristmas(lsStrips,strip,teEvent,tmeCurrentTime);
            }
            else
            {
              // The door was closed for a while, just turn off the lights.
              // Start the Close Door Overhead Animation

              // Clear Events for the Overhead Animation
              vdClearAllTimedEvent(teEvent, door, lsStrips[strip].St, lsStrips[strip].Ed);
              vdClearAllTimedEvent(teEvent, door, lsStrips[strip-1].St, lsStrips[strip-1].Ed);

              // Just turn off the lights.
              lsStrips[strip].AnimationStatus = CloseOver;
              vdCloseOverChristmas(lsStrips,strip,teEvent,tmeCurrentTime);
            }
          }
        }
      }
    }
  }
  

  // *************************************************
  //
  //  This Section of code reserved for a routine 
  //  to check for lights should be off.  After
  //  ten minutes, manualy turn them off. 
  //
  // *************************************************

}

bool kbhit(void)
{
    //https://www.raspberrypi.org/forums/viewtopic.php?t=20070 (genius cred)
	
  struct termios original;
    tcgetattr(STDIN_FILENO, &original);

    struct termios term;
    memcpy(&term, &original, sizeof(term));

    term.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    int characters_buffered = 0;
    ioctl(STDIN_FILENO, FIONREAD, &characters_buffered);

    tcsetattr(STDIN_FILENO, TCSANOW, &original);

    bool pressed = (characters_buffered != 0);

    return pressed;
}


// ***************************************************************************************
// The Following chunk of code is what handles the imported library's ability to put the 
// lights on and off or whatever.  Will not pretend to understand it.  Instead, will 
// squish it down as much as possible so that I can pretend its not there.
// ***************************************************************************************
int led_count = LED_COUNT;
ws2811_t ledstring;
int *matrix;
static uint8_t running = 1;
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
// MAIN
// ***************************************************************************************

// GLOBAL VARIABLES



/*
//  Light Strip Hardware
CRGB hwLEDs0[NUM_LEDSs0];       // LED Strip 1 values.
CRGB hwLEDs1[NUM_LEDSs1];       // LED Strip 2 values.
*/



/*
// Onboard LED to signify data being sent to LED strip.
const int ledPin =  LED_BUILTIN;
*/

//bool booRandom = false;




// ***************************************************************************************
// MAIN PROGRAM
// ***************************************************************************************
void setup()
{
  // Generate RandomSeed based on Temperture, Humidity, Air Quality, Gravametric Indifferences, 
  //  Planatery Alignment, and Current Horoscope Predictions.

  printf("Setting System Hardware ... ");

  /*
  // Define Door Sensors.
  pinMode(SWITCH_PINs0, INPUT_PULLUP);
  pinMode(SWITCH_PINs1, INPUT_PULLUP);
  pinMode(SWITCH_PINs2, INPUT_PULLUP);
  pinMode(SWITCH_PINs3, INPUT_PULLUP);
  */

  /*
  // Arduino Onboard LED
  pinMode(ledPin, OUTPUT);
  */

  /*
    // Define Communications.
    Wire.begin(SLAVEID);              // Connect to I2C bus with defined slave ID as 
                                      //  address
    Wire.onReceive(onDataAvailable);  // Register data avaiable event.
  */


  /*

  // Open serial communications if in debug mode.
  if (BOOTEST == true)
  {
    //Serial.begin(115200);
    //Serial.println("Program Start");
    //vdTESTFLASHAnimation(teEvent, 0, tmeCurrentMillis);
    vdPowerOnAnimation(lsStrips, 0, teEvent, tmeCurrentMillis);
  }
  else
  {
    // Boot Animation
    // Make sure we have the current time before we try any test animations.
    vdPowerOnAnimation(lsStrips, 0, teEvent, tmeCurrentMillis);
  }
  */

  printf("OK\n");
}



// ---------------------------------------------------------------------------------------
// MAIN LOOP
void loop()
//  Main Loop:
//    Events and Light Path animations should only be called when their time is up.
{
  using namespace std::chrono;

  printf("PiFLED Loop ('x' to Exit) ...\n");

  // ---------------------------------------------------------------------------------------
  // LED Library Vars and Init
  printf("Initializing LEDS ... ");
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
      //return ret;
      return;
  }
  printf("OK\n");

  // ---------------------------------------------------------------------------------------

  // Key Watch
  Keys keywatch;
  keywatch.set('x',2);  // Exit
  keywatch.set('t',5);  // Test Doors
  keywatch.set('c',2);  // Test Colors

  keywatch.set('1',2);  // Door Toggles
  keywatch.set('2',2);  // 
  keywatch.set('3',2);  // 
  keywatch.set('4',2);  // 

  // Keyboard
  int key = '\0';

  // FLED
  FledTime tmeFled;
  tmeFled.set();
  
  // Light Strip Event System
  timed_event teEvent[NUM_CHANNELS];

  // Define Led Strips
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
  stupid_random sRND;

  // Initialize the Stupid Random Numbers
  sRND.init();


  // FLED LED Array
  struct CRGB crgbMainArrays0[NUM_LEDSs0];
  struct CRGB crgbMainArrays1[NUM_LEDSs1];
  struct CRGB crgbMainArrays2[NUM_LEDSs0];
  struct CRGB crgbMainArrays3[NUM_LEDSs1];
  //struct CRGB crgbMainArrays1[LED_COUNT];

  teEvent[0].create(NUM_LEDSs0);
  teEvent[1].create(NUM_LEDSs1);
  teEvent[2].create(NUM_LEDSs0);
  teEvent[3].create(NUM_LEDSs1);

  // Door Sensor
  hardware_monitor hwDoors[NUM_SWITCHES];
  bool boAuxLightsIsOn = false;

  
  // Define Door Sensors.
  hwDoors[0].set(true, 50, true);
  hwDoors[1].set(true, 50, true);
  hwDoors[2].set(true, 50, true);
  hwDoors[3].set(true, 50, true);
  



  // Delay less Loop Variables
  //    intRestTime defines the amount of time, in milliseconds, passed before another data
  //    read pass is performed and transmitted from the controller to the main system.


  tmeFled.setframetime();
  //printf("EXT Time Sec: %f\n", tmeFled.tmeFrameMillis);
  double tmeStartTime = tmeFled.tmeFrameMillis;
  unsigned long tmeCurrentMillis = (unsigned long)tmeFled.tmeFrameMillis;
  double tmePrevMillis = 0;
  
  // TEST ANIMATION
  //teEvent[lsStrips[0].Cl].set(tmeCurrentMillis, 200, 3000, 70, AnEvSweep, AnPiFade, false, CRGB(0, 0, 0), CRGB(25, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 60, false, false);
  // normal
  //teEvent[lsStrips[0].Cl].set(tmeCurrentMillis, 400, 200, 20, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(25, 25, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 60, true, false);
  // fast
  //teEvent[lsStrips[0].Cl].set(tmeCurrentMillis, 400, 50, 5, AnEvSweep, AnPiPulse, false, CRGB(0, 0, 0), CRGB(0, 0, 50), CRGB(0, 0, 0), CRGB(0, 0, 0), 120, 160, true, false);
  //teEvent[lsStrips[0].Cl].set(tmeCurrentMillis, 100, 500, 10, AnEvSweep, AnPiFadeDith, false, CRGB(0, 0, 0), CRGB(255, 255, 255), CRGB(0, 0, 0), CRGB(255, 32, 32), 0, 60, false, false);

  // ---------------------------------------------------------------------------------------
  while( keywatch.get('x') == 0 )
  {
    tmeFled.setframetime();
    tmeCurrentMillis = (unsigned long)tmeFled.tmeFrameMillis;
    //printf("Frame Time: %f  ... Current: %d \n", tmeFled.tmeFrameMillis, tmeCurrentMillis);
    //  Only update the hardware when changes have been detected.
    //    This vabiable will be checked at the end of the loop.  If nothing was updated,
    //    the loop will just walk on past any hardware updates that would otherwise be
    //    sent.

    bool booUpdates0 = false;
    bool booUpdates1 = false;
    bool booUpdates2 = false;
    bool booUpdates3 = false;

    //  Get current time.  This will be our timeframe to work in.
    //tmeCurrentMillis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    //printf("time: %d\n" , tmeCurrentMillis);

    // --- Begin of Delayless Loop ---
    //if (tmeFled.tmeFrameMillis - tmePrevMillis >= intRestTime)
    //{

    tmePrevMillis = tmeFled.tmeFrameMillis;

    // --- Grabbing Data From Hardware inputs ---
    
    // Keyboard Input
    if (kbhit())
    {
        key = getchar();
        keywatch.in(key);
    }

    // Sensor Array (QUICK FIX)
    bool booSensors[NUM_SWITCHES];

    /* TEST
    booSensors[0] = digitalRead(SWITCH_PINs0);
    booSensors[1] = digitalRead(SWITCH_PINs1);
    booSensors[2] = digitalRead(SWITCH_PINs2);
    booSensors[3] = digitalRead(SWITCH_PINs3);
    */

    booSensors[0] = keywatch.getTF('1');
    booSensors[1] = keywatch.getTF('2');
    booSensors[2] = keywatch.getTF('3');
    booSensors[3] = keywatch.getTF('4');


    // Check the doors and start or end all animations
    DoorMonitorAndAnimationControlModule(lsStrips, teEvent, hwDoors, booSensors, tmeCurrentMillis);

    
    // --- Check and Execute Timed Events That Are Ready ---

    //  Timed Event ALL GLOBAL
    teSystem(lsStrips, teEvent, tmeCurrentMillis);

    //  Timed Event 0
    booUpdates0 = teEvent[0].execute(sRND, crgbMainArrays0, tmeCurrentMillis);

    //  Timed Event 1
    booUpdates1 = teEvent[1].execute(sRND, crgbMainArrays1, tmeCurrentMillis);

    //  Timed Event 0
    booUpdates2 = teEvent[2].execute(sRND, crgbMainArrays2, tmeCurrentMillis);

    //  Timed Event 1
    booUpdates3 = teEvent[3].execute(sRND, crgbMainArrays3, tmeCurrentMillis);

    
    //  If we made it to this part of the code then we need to
    //    tell the LED hardware that it has a change to commit.

    // --- Execute LED Hardware Changes If Anything Was Updated ---
    if ((booUpdates0 == true) || (booUpdates1 == true) || (booUpdates2 == true) || (booUpdates3 == true))
    {
      // ---------------------------------------------------------------------------------------
      // Render - Copy my array int its array.
      //  Do I need to move the whole thing or can I just move the changed pixels?


      int mcount = 0;

      if(keywatch.pressed('t') == true)
      {
        switch (keywatch.get('t'))
        {
          case 0:
          {
            printf("Full Array\n");
            break;
          }
          case 1:
          {
            printf("Door 1\n");
            break;
          }
          case 2:
          {
            printf("Door 2\n");
            break;
          }
          case 3:
          {
            printf("Door 3\n");
            break;
          }
          case 4:
          {
            printf("Door 4\n");
            break;
          }
        }
      }

      if (keywatch.get('c') !=0)
      {
        for (int lcount = 0; lcount < NUM_LEDSs0;lcount++)
        {
          crgbMainArrays0[lcount] = CRGB(25,25,25);
        }
          for (int lcount = 0; lcount < NUM_LEDSs1;lcount++)
        {
          crgbMainArrays1[lcount] = CRGB(25,25,25);
        }
          for (int lcount = 0; lcount < NUM_LEDSs0;lcount++)
        {
          crgbMainArrays2[lcount] = CRGB(25,25,25);
        }
          for (int lcount = 0; lcount < NUM_LEDSs1;lcount++)
        {
          crgbMainArrays3[lcount] = CRGB(25,25,25);
        }
      }

      if (keywatch.get('t') == 0 || keywatch.get('t') == 1)
      {
        for (int lcount = 0; lcount < NUM_LEDSs0;lcount++)
        {
          matrix[mcount]=crgbMainArrays0[lcount].b + (crgbMainArrays0[lcount].g << 8) + (crgbMainArrays0[lcount].r << 16) + (0 << 24);
          mcount++;
        }
      }

      if (keywatch.get('t') == 0 || keywatch.get('t') == 2)
      {
        for (int lcount = 0; lcount < NUM_LEDSs1;lcount++)
        {
          matrix[mcount]=crgbMainArrays1[lcount].b + (crgbMainArrays1[lcount].g << 8) + (crgbMainArrays1[lcount].r << 16) + (0 << 24);
          mcount++;
        }
      }

      if (keywatch.get('t') == 0 || keywatch.get('t') == 3)
      {
        for (int lcount = 0; lcount < NUM_LEDSs0;lcount++)
        {
          matrix[mcount]=crgbMainArrays2[lcount].b + (crgbMainArrays2[lcount].g << 8) + (crgbMainArrays2[lcount].r << 16) + (0 << 24);
          mcount++;
        }
      }

      if (keywatch.get('t') == 0 || keywatch.get('t') == 4)
      {
        for (int lcount = 0; lcount < NUM_LEDSs1;lcount++)
        {
          matrix[mcount]=crgbMainArrays3[lcount].b + (crgbMainArrays3[lcount].g << 8) + (crgbMainArrays3[lcount].r << 16) + (0 << 24);
          mcount++;
        }
      }


      /*
      for(int l=0; l<LED_COUNT;l=l+1)
      {
        // Copy each mastter LED list into the LED Matrix.
        // Fake LED List
        //char r,g,b;
        //r = 20; g = 0; b = 0;
        //matrix[l]=b + (g << 8) + (r << 16) + (0 << 24);
        // FLED LED List
        matrix[l]=crgbMainArrays0[l].b + (crgbMainArrays0[l].g << 8) + (crgbMainArrays0[l].r << 16) + (0 << 24);
        //printf("r = %d, g = %d, b = %d \n",crgbMainArrays0[l].r,crgbMainArrays0[l].g,crgbMainArrays0[l].b);
      }
      */
      
      /*
      char r,g,b;
      r = 12; g = 20; b = 65;
      for(int l=0; l<LED_COUNT;l=l+1)
      {
        matrix[l]=b + (g << 8) + (r << 16) + (0 << 24);;
        //printf("r = %d, g = %d, b = %d \n",crgbMainArrays0[l].r,crgbMainArrays0[l].g,crgbMainArrays0[l].b);
      }
      */

      // LED Library Renderer -- Recommend: DON'T TOUCH        
      matrix_render();
      if ((ret = ws2811_render(&ledstring)) != WS2811_SUCCESS)
      {
          fprintf(stderr, "ws2811_render failed: %s\n", ws2811_get_return_t_str(ret));
          break;
      }
      // ---------------------------------------------------------------------------------------


      // Debug Routines ---
      // Slow delay if in testing mode.
      //if (BOOTEST == true)
      //{
      //  intRestTime = TESTRESTTIME;
      //}
    }   // End Delayless Loop

    // DIAG
    float ct, et, st;
    ct = tmeFled.tmeFrameElapse();
    st = (1 * (1000 - tmeFled.tmeFrameElapse()) / FRAMES_PER_SECOND  );

    usleep ( 1000 * (1000 - tmeFled.tmeFrameElapse()) / FRAMES_PER_SECOND );
    //usleep ( (1000 - (tmeFled.tmeFrameElapse()) * 1000) / FRAMES_PER_SECOND );
    
 
    et = tmeFled.tmeFrameElapse();

    
    printf(SCRPOS, 1, 1);
    printf("Compute Time: %fms  |  ", ct );
    printf("Sleep Time: %fms  |  ", st);
    printf("Cycle Time: %fms  |  ", et);
    printf("\n");
    
    
  }  // While loop

  // Shutdown the LED strip routine.
  ws2811_fini(&ledstring);

  printf ("\nPiFLED Loop ... Exit\n");
  //return ret;
}





int main(int argc, char *argv[])
{
    printf("PiFLED Start ... \n");
 

    setup();
    loop();


/*
    for(int x=0;x<5;x++)
    {
      printf("time: %d\n", millis());
    }
*/
}


