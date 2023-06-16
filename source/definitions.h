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

#define Revision "00000001.942"
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

// COMMS Settings
#define COMMS_PORT        "/dev/serial/by-id/usb-Arduino_LLC_Arduino_Leonardo-if00"
//#define COMMS_BAUD        38400
#define COMMS_BAUD        115200
#define COMMS_BIT_COUNT   8
#define COMMS_BIT_PARITY  false
#define COMMS_STOP_BITS   1
#define COMMS_HARDWARE_FLOW_CONTROL   false
#define COMMS_DISABLE_CANONICAL_MODE  false
#define COMMS_XONXOFF                 false

#define COMMS_SAVE_LOG_FILENAME       "/home/pi/auto/rascomms.txt"
#define COMMS_RECEIVE_TEST_DATA       false
#define COMMS_TEST_DATA_FILENAME      "/home/pi/auto/rascomms.txt"

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

// StupidRandom Parameters
#define StuRNDsize              100


#endif