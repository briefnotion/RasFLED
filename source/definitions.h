// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: definitions.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// -------------------------------------------------------------------------------------
// DEFINITIONS
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
// CONSOLE AND INTEFACE SETUP

#define SCREENUPDATEDELAY 100
#define CONSOLESPLITSIZE  6

// Key Mapping
#define KEYEXIT           'X'
#define KEYRESIZE         '*' // Key Resize

// Debugging and Diagnosis Keys
#define KEYDEBUG          '/' // Enter, Exit debug mode.
#define KEYLEDTEST        'c' // Turn all LEDs on
#define KEYLEDDRCYCL      't' // Cycle through the doors
#define KEYLEDUPLW        'l' // Cycle Upper or Lower limits of LEDs
#define KEYTESTANIM       'a' // Cycle Upper or Lower limits of LEDs

// Testing and Debugging
#define BOOTEST       false       // Not Implemented - Fading Away

// Default Timer
#define DEFAULTTIMER      .2   //Minutes

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

// remove
#define NUM_LEDSs0    122     
#define NUM_LEDSs1    118 

#define LED_Size_Test_Strip               63

#define LED_Size_Door_Back_Driver         70
#define LED_Size_Door_Back_Passenger      70
#define LED_Size_Door_Front_Driver        66
#define LED_Size_Door_Front_Passenger     66

#define LED_Size_Overhead_Back_Driver     52
#define LED_Size_Overhead_Back_Passenger  52
#define LED_Size_Overhead_Front_Driver    52
#define LED_Size_Overhead_Front_Passenger 52


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

//  Test Animation  
#define AnTavdTestAnimation     50

//  Normal Effects  
#define AnTavdPacificaish       60
#define AnTavdPaAnimClose       61
#define AnTaChannelFlashColor   63
#define AnTaChannelPulseColor   64
#define AnTaChannelPulseColorCountdown   65
#define AnTaOverheadIllumColor  66
#define AnTaHazard              67
#define AnTaPacificaishColor    68

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


#endif