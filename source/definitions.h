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

#define RASFLED

// Debug Counters
#define DEBUG_COUNTER false

// -------------------------------------------------------------------------------------
// DEFINITIONS
// -------------------------------------------------------------------------------------

#define Revision "00000001.75"
#define  QACODE  "A565"

// -------------------------------------------------------------------------------------
// CONSOLE AND INTEFACE SETUP

#define SCREENUPDATEDELAY 60  // in milliseconds
//#define CONSOLESPLITSIZE  6

// Files
#define FILES_DIRECTORY           "/etc/RasFLED/"
//#define FILES_DIRECTORY           "/home/pi/source/RasFLED/configuration/"                   // For Testing:  Configuration Files Directory

#define FILES_CONFIGURATION       "configuration.json"
#define FILES_RUNNING_STATE_SAVE  "runningstate.json"
#define FILES_PLAYLIST            "playlist.json"
#define FILES_ANIMATIONS          "animations.json"

#define FILES_DEAMON_LOG          "/var/log/daemon.log"             // Raspi System Log
#define FILES_AIRCRAFT_JSON       "/run/dump1090-fa/aircraft.json"  // FlightAware Aircraft JSON File
//#define FILES_AIRCRAFT_JSON       "/home/pi/flightaware/aircraft.json"  // For testing:  FlightAware Aircraft JSON File 

// Key Mapping
#define KEYEXIT           'X'
#define KEYRESIZE         '*' // Key Resize

// Debugging and Diagnosis Keys
#define KEYDEBUG          '/' // Enter, Exit debug mode.
#define KEYLEDTEST        'c' // Turn all LEDs on
#define KEYLEDDRCYCL      't' // Cycle through the doors
#define KEYTESTANIM       'a' // Cycle Upper or Lower limits of LEDs

// Testing and Debugging
#define BOOTEST       false       // Not Implemented - Fading Away

// Default Timer
#define DEFAULTTIMER      5   //Minutes

#define LED_FPS           50  // Compile time LED Frames per Second, frams/second.

// -------------------------------------------------------------------------------------
// Door Switches

//#define DOOR_SWITCH_LEEWAY_TIME 60  // Debounce - Leeway time for door switches in ms.
//#define DOOR_SWITCH_LEEWAY_TIME 120 // Debounce - Leeway time for door switches in ms.
//#define DOOR_SWITCH_LEEWAY_TIME 240 // Debounce - Leeway time for door switches in ms.
#define DOOR_SWITCH_LEEWAY_TIME 480   // Debounce - Leeway time for door switches in ms.

// -------------------------------------------------------------------------------------
// LED Strip Declarations

#define TARGET_FREQ             WS2811_TARGET_FREQ
#define GPIO_PIN                18
#define DMA                     10
//#define STRIP_TYPE            WS2811_STRIP_RGB		// WS2812/SK6812RGB integrated chip+leds
#define STRIP_TYPE              WS2812_STRIP		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE            SK6812_STRIP_RGBW		// SK6812RGBW (NOT SK6812RGB)

//#define LED_COUNT            482

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

// Other Effects and Animations
#define AnTavdOverhead_Mask     51
#define AnTavdPowerAnimation    52

//  Normal Effects  
#define AnTavdPacificaish       60
#define AnTavdPaAnimClose       61
#define AnTaChannelFlashColor   63
#define AnTaChannelPulseSimple  64
#define AnTaChannelPulseColor   65
#define AnTaChannelPulseColorCountdown   66
#define AnTaOverheadIllumColor  67
#define AnTaHazard              68
#define AnTaPacificaishColor    69

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