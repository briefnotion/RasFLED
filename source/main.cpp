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
// *  PROJECTID: gi6$b*E>*q%;    Revision: 00000000.25A
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
// * V 0.26_210609
// *    - More work has been done for loading files and settings
// *    - Started working on a loadable, from file, hardware configuration.  This is a 
// *        precursor to a more dynamiclly configurable system and is just the first step, 
// *        of many, towards a system that can handle multiple varying numbers of LED 
// *        strips and switch configurations.  All defined by one configuration file, and 
// *        without needing a recompile to change.  This is also the groundwork for 
// *        loadable animation packages. 
// *    - Transfered a large chunk of settings to the System Data variable.
// *
// *
// * V 0.25_210607
// *    - Starting implementing the files system.  At the moment, the system will only 
// *        remember the running colors through a reset.  It's only groundwork.
// *    - Made the flash more visible.
// *    - Added some randomness to the pulse animation.
// *    - changed "pp" command to run pulses on running colors.
// *    - Adjusted the start time of animation end to hopefully correct a problem 
// *        causing the countdown timer pulse not to completely end when a door was
// *        opened.
// *
// * V 0.24_210514
// *    - A few days of testing done. 
// *    - Modified a few of the animations.
// *    - Flash color flash animation can be called with 'f' command.
// *
// * V 0.23_210519
// *    - Spent the day working on Twinkle and got it working as it was originally 
// *        programmed.  Still broken though and needs a rewrite.  Works fine until 
// *        the animation speed is anything more than 0.  All I wanted to do is refresh
// *        the animations.
// *    - Changed the ovehead door open animation to pulse yellow. 
// *    - Changed the default pulses to sweep from front to back top to bottom, 
// *        hopefully.
// *    - Reworked and recrated many animations.  Everthing now as a Glitch theme to 
// *        constantly remind me I need to finish twinkle.
// *    - Flash needs plenty of work.  It looks garbage enough to catch my attention 
// *        when the countdown timer runs out
// *    - Oh, Countdown timer works.  It was an to correct.
// *
// * V 0.22_210517
// *    - Duplicated Pulse Animation to Pulse Animation Running.
// *    - Introduced a Countdown Timer.
// *    - Original plan was to create a helper library and move a few functions needed
// *        for the timer functions.  Thing went nova.
// *    - Countdown timer changes color of 'pp' or 'space space' command starting with
// *        running color, to green, to yellow, and then to red.
// *    - Added a 'fw', to flash white, command.  It is suposed to be triggered at end 
// *        of countdown timer, but it is just a freeloading gonk that doesn't want to
// *        behave.
// *
// * V 0.21_210315
// *    - Increased the size of the side running lights from 6 to 12.
// *    - Running Color allows a default color for Pulse and Overhead Illumination to be
// *        set and retained.  'pp' or '  ' and 'oo' or 'zz' commands will call pulse 
// *        and or overhead with the set color.  Choose with 'rX' where X is the color, 
// *        shuch as R is Red, G is Green ...
// *    - 'zz' can now turn on overhead illumination.  This was added because the z key 
// *      is much easier to find in the dark than the o key.
// *    - Yes, I want to tackle the to do list items such as "code it into header files," 
// *        and have a "configuration file" or "read the animations from a JSON file" 
// *        but, nearly every time I'm out there, testing the system, I find the smallest 
// *        amount of changes and additions, adds more practicallity, utility, and 
// *        convienance to my job.  For instance, a simple 5 minute pulse that starts 
// *        green and ends red when finished, would let people know, at a glance 
// *        how much time is remaining before I start thinking, and have to figure out 
// *        if its a no show or not.
// *
// * V 0.20_210301
// *    - Hardware changed requiring me to change the order of pixel animations.  Some of 
// *        animations work differently because the Door Strip is no longer door*2 and 
// *        the Overhead Strips are no longer door*2+1.  I'm surprised it works at all.
// *    - Window resize stopped working.  A work around is now in place and hotkeyable 
// *        with the '*' key. 
// *    - Created the "profile_strip" and "profile_strip_group" classes, to, completely, 
// *        replace the "led_strip" class, so the door*2+1 problem is no longer an issue.
// *    - Overhead illumination now turns off when a door is opened.  The code was there,
// *        I had just forgotten to activate it.
// *    - Color markings are added to the "c - Test LEDs" so the LEDs can be counted.
// *    - Started removing code and animations no longer needed because the new classes
// *        has made them obsolete.  Keeping animations like Halloween, Christmas, and 
// *        Thanksgiving commented, to be referenced when rebuilding next year.
// *    - Reprogrmmed Running Lights.
// *    - I've been live running the lights for a week now, and, despite one occasional 
// *        bug that doesnt turn off (all) the pusle lights when a door is opened, 
// *        the system is very stable.  Meaning: no crashes, no odd behavior, nothing 
// *        out of the ordinary.  Putting this up on GitHub now before I go through the 
// *        next phase of major changes. 
// *
// * V 0.19 _210205
// *    - Created a routine for copying over the prepared matrix to the display matrix.
// *    - Clean up the Calculated Matrix to the Render Matrix part, somewhat.  Still 
// *        wishing it was handled better.  At least now I have a central part for it. 
// *    - Put the matrix fill into its own routine. 
// *
// * V 0.18 _210203
// *    - Removed these items from ToDo list.  They got done.
// *      - Set up an animation ID tag.
// *      - Create an Better interface.
// *      - Create specialized animations for specific alerts and hazards.
// *    - No longer clearing all animations before starting new animations.  Instead, 
// *        setting animations of animations being replaced to ClearOnEnd. 
// *    - Added Orange to the pulses, for Lyft.
// *    - Added Blue and Orange to the Overhead.
// *
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
// *    - Update everything properly classified with reference .h, supporting, and helper 
// *        libraries.
// *    - Create a way to import all animations from an animations file.
// *    - Clean up 90% of the code.
// *    - Move all the main animations into their own subroutines.
// *    - Create animations for day and night running.
// *    - Generate animations for shutting down animations.
// *    - Trace Flicker that occurs when sleep = 0 and doors are closing.
// *    - Phase out all tmeCurrentTime call towards sdSysData.tmeCURRENT_FRAME_TIME.
// *    - Revisit previous implementation of vectors.  "pop_back"s, "first", "last"s 
// *        and queues exist.  Had no idea.
// *    - Continue refining animations into an event language that can be ported. 
// *
// ***************************************************************************************


#include <stdio.h>
#include <math.h>
#include <wiringPi.h>
#include <string>
#include <chrono>
#include <unistd.h>
#include <termio.h>
#include <vector>
#include <iostream>


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


// RASFled related header files
#include "definitions.h"
#include "helper.h"
#include "files.h"
#include "consoleanddata.h"
#include "fledcore.h"
#include "timedeventsystem.h"
#include "animations.h"



// ***************************************************************************************
// STRUCTURES AND CLASSES
// ***************************************************************************************



// ***************************************************************************************
// FUNCTION AND PROCEDURES
// ***************************************************************************************

// -------------------------------------------------------------------------------------
//  AuxLightControlModule

void DoorMonitorAndAnimationControlModule(Console &cons, system_data &sdSysData, profile_strip_group pstrgDoor[], timed_event teEvent[], bool booSensors[], unsigned long tmeCurrentTime)
// This routine is designed to scan all the doors or switches.  If anthing is open, opened 
//  closed or closed (odd twist of english there) then set the appropriate or maintain
//  animations.  
// Works like this.  If any door is open then make sure the overhead lights are on.  
//  If all the doors are closed, turn all the lights off.  Run door animations like 
//  normal.
{
   using namespace std;

  int opencount = 0;
  //int strip;
  bool changedetected = false;

  // Scan Through Doors and Check for Changes

  // DO NOT CLEAR ANIMATIONS HERE!  CLEAR ANIMATIONS IN ANIMATION SCRIPT!
  //              (easier to track and debug that way)

  // Check for newly opened and run animation on them.
  for (int door=0; door < sdSysData.CONFIG.iNUM_SWITCHES; door++)
  {
    if (pstrgDoor[door].hwSWITCH.changed(booSensors[door], tmeCurrentTime) == true)
    {
      changedetected = true; 
      if (pstrgDoor[door].hwSWITCH.booVALUE)
      {
        // Door Just Opened
        // Start Open Door Animation on This Door
        if (pstrgDoor[door].hwSWITCH.ISHARDWARE == true)  // Only if its real switch (with lights attached to it)
        {
          //strip = door *2;
          
          // Door Animation
          cons.printwait("  Door " + std::to_string(door) + " Open ... ");
          pstrgDoor[door].pstrDOOR.Status = "StDoorOpen";
          vdDoorOpenAnimationADV00(cons, pstrgDoor[door].pstrDOOR, teEvent, tmeCurrentTime);

          // Turn on additional lights overhead
          cons.printwait("  Add On Strip:" + std::to_string(-1 + 1));
          vdAdditionalOpenADV01(cons, pstrgDoor[door].pstrOVERHEAD, teEvent, tmeCurrentTime);
        }
      }
      else
      {
        // Door Just Closed
        if (pstrgDoor[door].hwSWITCH.ISHARDWARE == true)  // Only if its real switch (with lights attached to it)
        {
          //strip = door *2;
          
          // Replace Open or Current door animation to closed door animation
          cons.printwait("  Door " + std::to_string(door) + " Close ... ");
          pstrgDoor[door].pstrDOOR.Status = "StDoorCloseA";        
          vdDoorCloseActiveADV00(cons, pstrgDoor[door].pstrDOOR, teEvent, tmeCurrentTime);

          // Turn off additional lights overhead
          cons.printwait("  Add Off Strtip:" + std::to_string(-1));
          vdAdditionalCloseADV00(cons, pstrgDoor[door].pstrOVERHEAD, teEvent, tmeCurrentTime);
        }
      }
    }
  }

  // Check To See If Any Door Opened or Closed.
  if (changedetected == true)
  {
    // Count the amount of open doors
    for (int door=0; door < sdSysData.CONFIG.iNUM_SWITCHES; door++)
    {
      if (pstrgDoor[door].hwSWITCH.booVALUE  == true)
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
      for (int door=0; door < sdSysData.CONFIG.iNUM_SWITCHES; door++)
      {
        //strip = (door *2); // Determine Strip from Door aka Channel
        if (pstrgDoor[door].hwSWITCH.ISHARDWARE == true)  // Only if its real switch (with lights attached to it)
        {

          // If a door is open
          if (pstrgDoor[door].pstrDOOR.Status != "StDoorOpen" && pstrgDoor[door].pstrDOOR.Status != "StDoorCloseA")
          {
            // If this door is not open then make sure the closed door animation is running on it.
            cons.printwait("  Door " + std::to_string(door) + " Running Active Closed: ");

            // Closed Active Doors animation
            pstrgDoor[door].pstrDOOR.Status = "StDoorCloseA";
            vdDoorCloseActiveADV00(cons, pstrgDoor[door].pstrDOOR, teEvent, tmeCurrentTime);
          }

          // If  a door is open
          if (pstrgDoor[door].pstrOVERHEAD.Status != "stOverOpen")
          {
            // Make sure this door has the overhead animation running on it.
            cons.printwait("  Door " + std::to_string(door) + " Running Overhead: ");

            // Normal Overhead Animation 
            pstrgDoor[door].pstrOVERHEAD.Status = "stOverOpen";
            vdPacificaishAnimationADV(cons, pstrgDoor[door].pstrOVERHEAD, teEvent, tmeCurrentTime);
          }
        }
      }      
    }
    else 
      {
      // All doors are closed.
      cons.printwait("  All Doors Closed: ");

      for (int door=0; door < sdSysData.CONFIG.iNUM_SWITCHES; door++)
      {
        //strip = (door *2); // Determine Strip from Door aka Channel
          // Strip will be the door strip
          // Strip +1 is the door overhead strip // Try to avoid passing this also. 
          //  Let the Animations handle it.
        
        // Finalize additionall animations on newley closed doors
        if (pstrgDoor[door].hwSWITCH.ISHARDWARE == true)  // Only if its real switch (with lights attached to it)
        {
          //  Guarantee all animations end in 15 seconds. This is a fall back method to
          //    make sure everythings stops in case a clear animation fails to start.
          //vdEndAllAnimationsADV(cons, lsStrips,strip,teEvent,tmeCurrentTime);

          // Start the Doors Running Mode on each door.
          pstrgDoor[door].pstrDOOR.Status = "StDoorCloseR";
          vdDoorCloseRunningADV(cons, pstrgDoor[door].pstrDOOR, teEvent, tmeCurrentTime);

          //cons.printwait("All Doors Closed HWLVL: D%d AS%d" + std::to_string(door) + std::to_string(lsStrips[strip + 1].AnimationStatus));
          
          // Make sure lights are off or turning off and Amber Up the newly closded doors.
          if (pstrgDoor[door].pstrOVERHEAD.Status == "stOverOpen")
          {
            // Start Overhead Turn On Convenience Animation.
            // See when the door was closed
            // cons.printwait("Door Toggle Time (current time - toggle time): %d - %dms < 1500", tmeCurrentTime, hwmDoor[door].tmeTOGGLEDTIME);
            if ((tmeCurrentTime - pstrgDoor[door].hwSWITCH.tmeTOGGLEDTIME) < 15000)
            {
              // The door was recently closed. Run the Convienance lights on it.
              cons.printwait("  Door " + std::to_string(door) + " Conviencance Lights On: ");
              
              // Turn on Convienance Lights 
              pstrgDoor[door].pstrOVERHEAD.Status = "StOverCloseCon";
              vdCoADV01(cons, pstrgDoor[door].pstrOVERHEAD, teEvent, tmeCurrentTime);
            }
            else
            {
              // The door was closed for a while, just turn off the lights.
              // Start the Close Door Overhead Animation
              cons.printwait("  Door " + std::to_string(door) + " Conviencance Lights Off: ");

              // Just turn off the lights.
              pstrgDoor[door].pstrOVERHEAD.Status = "stOverClose";
              vdCloseOverADV(cons, pstrgDoor[door].pstrOVERHEAD, teEvent, tmeCurrentTime);
            }
          }
        }
      }
    }
  }
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// Matrix Manipulation

// -------------------------------------------------------------------------------------
// Display Materix Prepare.

//  Copy the Prepared Matrix to the Display Matrix.
void MatrixPrepare(Console cons, system_data &sdSysData, CRGB crgbPrepedMatrix[], int intLEDCOUNT, int* DisplayMatrix, int &mcount)
{
  if(cons.keywatch.get(KEYLEDUPLW) == 0)
  {
    for (int lcount = 0; lcount < intLEDCOUNT; lcount++)
    {
      // Normal Display
      DisplayMatrix[mcount]=crgbPrepedMatrix[lcount].b + (crgbPrepedMatrix[lcount].g << 8) + (crgbPrepedMatrix[lcount].r << 16) + (0 << 24);
      mcount++;
    }
  }
  else
  {
    for (int lcount = intLEDCOUNT - sdSysData.CONFIG.iLED_Size_Test_Strip; lcount < intLEDCOUNT; lcount++)
    {
      // Top Only Test Display
      DisplayMatrix[mcount]=crgbPrepedMatrix[lcount].b + (crgbPrepedMatrix[lcount].g << 8) + (crgbPrepedMatrix[lcount].r << 16) + (0 << 24);
      mcount++;
    }
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
// -------------------------------------------------------------------------------------
// Console Commands

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
  cons.printwait(" r - Red    u - Purple  n - Orange");
  cons.printwait(" g - Green  y - Yellow");
  cons.printwait(" b - Blue   c - Cyan    ` - End");
  cons.printwait("");
  cons.printwait("rX  - Set Running Color  (X is the color)");
  cons.printwait("");
  cons.printwait("pX  - Pulse Anim         (X is the color)");
  cons.printwait("oX  - Overhead Anim      (X is the color)");
  cons.printwait("fX  - Flash Anim      (X is the color)");
  cons.printwait("X`  - End Command (X is the Animation)");
  cons.printwait("  Double animations will be with Running Color.");
  cons.printwait("");
  //cons.printwait("  Not all colors implemented for all commands.");
  //cons.printwait("");
  cons.printwait("\\   - Turn on and off diagnosis mode.");
  cons.printwait("t - Cycle Doors  l - Cycle Upper Lower  c - Test LEDs   a - not spec");
  cons.printwait("");
}

// Display all running events.
void consoleprintevents(Console &cons, system_data &sdSysData, timed_event teEvent[])
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
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

// -------------------------------------------------------------------------------------
// Test Animation

void processtestanimation(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor)
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Channel Light Pulse Color", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTavdTestAnimation, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true);  
  }
  sdSysData.booPulsesRunning = true;
}

// -------------------------------------------------------------------------------------
// Pulses

// Set To End All Pulses
void processcommandpulseend(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[])
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Channel Light Pulse Color", tmeCurrentTime, 300, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 255, true, true);
  }
  sdSysData.booPulsesRunning = false;
}

// Flash Color All Channels
void processcommandflash(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBflashcolor)
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Channel Light Pulse Color", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelFlashColor, false, cRGBflashcolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true);  
  }
  //sdSysData.booPulsesRunning = true;
}

// Pulse Color All Channels
void processcommandpulse(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor)
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Channel Light Pulse Color", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColor, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true);  
  }
  sdSysData.booPulsesRunning = true;
}

// Pulse Color All Channels
void processcommandpulsecountdown(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[])
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Channel Light Pulse Color", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaChannelPulseColorCountdown, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true);  
  }
  sdSysData.booPulsesRunning = true;
}

// -------------------------------------------------------------------------------------
// Overhead Illum

// Set To End All Overhead Illumination
void processcommandoverheadillumend(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[])
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Overhead Illumination", tmeCurrentTime, 0, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 255, true, true);
  }
  sdSysData.booOverheadRunning = false;
}

// -------------------------------------------------------------------------------------
// Overhead Illumination Color
void processcommandoverheadillum(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor)
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Overhead Illumination", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaOverheadIllumColor, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true);  
  }
  sdSysData.booOverheadRunning = true;
}

//  Overhead Illumination Pacificaish Color
void processcommandpacificaishcolor(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor)
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Overhead Illumination", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaPacificaishColor, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true);  
  }
  sdSysData.booOverheadRunning = true;
}

// -------------------------------------------------------------------------------------
// Hazard

// Set To End All Hazard
void processcommandhazardend(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[])
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Hazard", tmeCurrentTime, 0, 1000, 80, AnEvSetToEnd, 0, false, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 255, true, true);
  }
  sdSysData.booHazardRunning = false;
}

// Hazard
void processcommandhazard(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[], CRGB cRGBpulsecolor)
{
  for (int channel = 0; channel < sdSysData.CONFIG.iNUM_CHANNELS; channel++)
  {
    teEvent[channel].set("Hazard", tmeCurrentTime, 100, 0, 0, AnEvSchedule, AnTaHazard, false, cRGBpulsecolor, CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), 0, 0, false, true);  
  }
  sdSysData.booHazardRunning = true;
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// Process and call routines as entered on the command line.
void processcommandlineinput(Console &cons, system_data &sdSysData, unsigned long tmeCurrentTime, timed_event teEvent[])
{
  if(cons.keywatch.cmdPressed() == true)
  {
    // Color Palettes
    CRGB crgbWhite  = CRGB(32,32,32); // W
    CRGB crgbRed    = CRGB(64,0,0);   // R
    CRGB crgbGreen  = CRGB(0,64,0);   // G
    CRGB crgbBlue   = CRGB(0,0,64);   // B

    CRGB crgbPurple = CRGB(32,0,64);  // U
    CRGB crgbYellow = CRGB(48,48,0);  // Y
    CRGB crgbCyan   = CRGB(0,48,48);  // C

    CRGB crgbOrange = CRGB(64,16,0);  // N

    
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
      consoleprintevents(cons, sdSysData, teEvent);
      cons.keywatch.cmdClear();
    }

    // End All Extra Repeating Lights and Countdown Timer
    if(cons.keywatch.Command.COMMANDLINE == "``")
    {
      // end Countdown Timer
      sdSysData.cdTIMER.end();

      // end all pulses on all strips
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpulseend(cons, sdSysData, tmeCurrentTime, teEvent);
      processcommandoverheadillumend(cons, sdSysData, tmeCurrentTime, teEvent);
      processcommandhazardend(cons, sdSysData, tmeCurrentTime, teEvent);
      cons.keywatch.cmdClear();
    }

    // -------------------------------------------------------------------------------------
    // FLASH

    // flash Running
    if(cons.keywatch.Command.COMMANDLINE == "ff")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandflash(cons, sdSysData, tmeCurrentTime, teEvent, sdSysData.get_running_color());
      cons.keywatch.cmdClear();
    }

    // flash White
    if(cons.keywatch.Command.COMMANDLINE == "fw")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandflash(cons, sdSysData, tmeCurrentTime, teEvent, crgbWhite);
      cons.keywatch.cmdClear();
    }

    // flash Red
    if(cons.keywatch.Command.COMMANDLINE == "fr")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandflash(cons, sdSysData, tmeCurrentTime, teEvent, crgbRed);
      cons.keywatch.cmdClear();
    }

    // flash Green
    if(cons.keywatch.Command.COMMANDLINE == "fg")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandflash(cons, sdSysData, tmeCurrentTime, teEvent, crgbGreen);
      cons.keywatch.cmdClear();
    }

    // flash Blue
    if(cons.keywatch.Command.COMMANDLINE == "fb")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandflash(cons, sdSysData, tmeCurrentTime, teEvent, crgbBlue);
      cons.keywatch.cmdClear();
    }

    // flash Purple
    if(cons.keywatch.Command.COMMANDLINE == "fu")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandflash(cons, sdSysData, tmeCurrentTime, teEvent, crgbPurple);
      cons.keywatch.cmdClear();
    }
  
    // flash Yellow
    if(cons.keywatch.Command.COMMANDLINE == "fy")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandflash(cons, sdSysData, tmeCurrentTime, teEvent, crgbYellow);
      cons.keywatch.cmdClear();
    }
    
    // flash Cyan
    if(cons.keywatch.Command.COMMANDLINE == "fc")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandflash(cons, sdSysData, tmeCurrentTime, teEvent, crgbCyan);
      cons.keywatch.cmdClear();
    }

    // flash Orange
    if(cons.keywatch.Command.COMMANDLINE == "fn")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandflash(cons, sdSysData, tmeCurrentTime, teEvent, crgbOrange);
      cons.keywatch.cmdClear();
    }

    // -------------------------------------------------------------------------------------
    // PULSES

    // pulse end
    if(cons.keywatch.Command.COMMANDLINE == "p`")
    {
      // end all pulses on all strips
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpulseend(cons, sdSysData, tmeCurrentTime, teEvent);
      cons.keywatch.cmdClear();
    }

    // pulse Running
    if(cons.keywatch.Command.COMMANDLINE == "  ")
    {
      // Keep values below 128
      sdSysData.start_timer(DEFAULTTIMER * 60);
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpulsecountdown(cons, sdSysData, tmeCurrentTime, teEvent);
      cons.keywatch.cmdClear();
    }

    // pulse Running Color
    if(cons.keywatch.Command.COMMANDLINE == "pp")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpulse(cons, sdSysData, tmeCurrentTime, teEvent, sdSysData.get_running_color());
      cons.keywatch.cmdClear();
    }

    // pulse White
    if(cons.keywatch.Command.COMMANDLINE == "pw")
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

    // pulse Orange
    if(cons.keywatch.Command.COMMANDLINE == "pn")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpulse(cons, sdSysData, tmeCurrentTime, teEvent, crgbOrange);
      cons.keywatch.cmdClear();
    }

    // -------------------------------------------------------------------------------------
    // Overhead Illumination
    
    // pulse end overhead illum
    if(cons.keywatch.Command.COMMANDLINE == "o`")
    {
      // end all pulses on all strips
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandoverheadillumend(cons, sdSysData, tmeCurrentTime, teEvent);
      cons.keywatch.cmdClear();
    }

    // Overhead Running
    if((cons.keywatch.Command.COMMANDLINE == "oo") || (cons.keywatch.Command.COMMANDLINE == "zz"))
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, sdSysData.get_running_color());
      cons.keywatch.cmdClear();
    }

    // Overhead White
    if(cons.keywatch.Command.COMMANDLINE == "ow")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbWhite);
      cons.keywatch.cmdClear();
    }

    // Overhead Red
    if(cons.keywatch.Command.COMMANDLINE == "or")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbRed);
      cons.keywatch.cmdClear();
    }

    // Overhead Green
    if(cons.keywatch.Command.COMMANDLINE == "og")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbGreen);
      cons.keywatch.cmdClear();
    }

    // Overhead Blue
    if(cons.keywatch.Command.COMMANDLINE == "ob")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbBlue);
      cons.keywatch.cmdClear();
    }

    // Overhead Purple
    if(cons.keywatch.Command.COMMANDLINE == "ou")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbPurple);
      cons.keywatch.cmdClear();
    }

    // Overhead Yellow
    if(cons.keywatch.Command.COMMANDLINE == "oy")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbYellow);
      cons.keywatch.cmdClear();
    }

    // Overhead Cyan
    if(cons.keywatch.Command.COMMANDLINE == "oc")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbCyan);
      cons.keywatch.cmdClear();
    }

    // Overhead Orange
    if(cons.keywatch.Command.COMMANDLINE == "on")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbOrange);
      cons.keywatch.cmdClear();
    }

    // Set Running Color
    if(cons.keywatch.Command.COMMANDLINE == "rw")
    {
      sdSysData.set_running_color(crgbWhite, "White");
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      cons.keywatch.cmdClear();
    }

    if(cons.keywatch.Command.COMMANDLINE == "rr")
    {
      sdSysData.set_running_color(crgbRed, "Red");
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      cons.keywatch.cmdClear();
    }
    
    if(cons.keywatch.Command.COMMANDLINE == "rg")
    {
      sdSysData.set_running_color(crgbGreen, "Green");
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      cons.keywatch.cmdClear();
    }
    
    if(cons.keywatch.Command.COMMANDLINE == "rb")
    {
      sdSysData.set_running_color(crgbBlue, "Blue");
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      cons.keywatch.cmdClear();
    }
    
    if(cons.keywatch.Command.COMMANDLINE == "ru")
    {
      sdSysData.set_running_color(crgbPurple, "Purple");
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      cons.keywatch.cmdClear();
    }
    
    if(cons.keywatch.Command.COMMANDLINE == "ry")
    {
      sdSysData.set_running_color(crgbYellow, "Yellow");
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      cons.keywatch.cmdClear();
    }
    
    if(cons.keywatch.Command.COMMANDLINE == "rc")
    {
      sdSysData.set_running_color(crgbCyan, "Cyan");
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      cons.keywatch.cmdClear();
    }
    
    if(cons.keywatch.Command.COMMANDLINE == "rn")
    {
      sdSysData.set_running_color(crgbOrange, "Orange");
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      cons.keywatch.cmdClear();
    }

    /*
    // -------------------------------------------------------------------------------------
    // Overhead Pacificaish White
    if(cons.keywatch.Command.COMMANDLINE == "ott")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbWhite);
      cons.keywatch.cmdClear();
    }

    // Overhead Pacificaish Blue
    if(cons.keywatch.Command.COMMANDLINE == "otb")
    {
      // Keep values below 128
      cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
      processcommandpacificaishcolor(cons, sdSysData, tmeCurrentTime, teEvent, crgbBlue);
      cons.keywatch.cmdClear();
    }
    */

    // -------------------------------------------------------------------------------------
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
    
    // -------------------------------------------------------------------------------------
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
      // Run Test Animation
      if(cons.keywatch.Command.COMMANDLINE[0] == KEYTESTANIM)
      {
        cons.printwait("CMD: " + cons.keywatch.Command.COMMANDLINE);
        processtestanimation(cons, sdSysData, tmeCurrentTime, teEvent, crgbWhite);
        cons.keywatch.cmdClear();
      }

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

    // -------------------------------------------------------------------------------------
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
  if ( (sdSysData.intDoorsOpen > 0)  && ((sdSysData.booPulsesRunning == true) || (sdSysData.booOverheadRunning == true)) )
  {
    // End pulses when door is opened and end countdown timer.
    sdSysData.cdTIMER.end();
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
  // Define System Data and Console
  Console cons;
  system_data sdSystem;
  
  // ---------------------------------------------------------------------------------------
  // Initialize the console
  initscr();
  cons.set(CONSOLESPLITSIZE);
  nodelay(stdscr, true);
  
  cons.printi("Initializing Console");
  cons.printi("RasFLED Loop ('X' to Exit) ...");
  
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
  cons.keywatch.set(KEYRESIZE,2);

  // ---------------------------------------------------------------------------------------
  // Load system configuration and set data
  
  // Set Running Color to white.
  sdSystem.init_running_color_list();
  sdSystem.set_running_color(CRGB(32,32,32),"White");


  // Loading Running State
  string strRunning_State_Filename = "./runningstate.cfg";
  cons.printi("Loading running state ...");
  bool booload = false;
  // yes, it resaves the file.  as is for now.
  booload = load_saved_running_state(cons, sdSystem, strRunning_State_Filename);

  // ---------------------------------------------------------------------------------------
  // LED Library Vars and Init
  cons.printi("Initializing LEDS ...");

  ledstring.freq = TARGET_FREQ;
  ledstring.dmanum = DMA;
  ledstring.channel[0].gpionum = GPIO_PIN;
  ledstring.channel[0].count = LED_COUNT;
  ledstring.channel[0].brightness = 255;
  ledstring.channel[0].invert = 0;
  ledstring.channel[0].strip_type = STRIP_TYPE;

  ws2811_return_t ret;
  ledprep(&ledstring);
  matrix = (int*)malloc(sizeof(ws2811_led_t) * LED_COUNT);
  setup_handlers();
  if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS)
  {
      fprintf(stderr, "ws2811_init failed: %s\n", ws2811_get_return_t_str(ret));
      return ret;
  }
  cons.printi("     OK");

  // ---------------------------------------------------------------------------------------

  // Define Door Sensors.
  cons.printi("Initializing Switches");
  int intRet = wiringPiSetup();    // Initialize wiringPI.
  pinMode(sdSystem.CONFIG.iSWITCH_PINs0, INPUT);
  pinMode(sdSystem.CONFIG.iSWITCH_PINs1, INPUT);
  pinMode(sdSystem.CONFIG.iSWITCH_PINs2, INPUT);
  pinMode(sdSystem.CONFIG.iSWITCH_PINs3, INPUT);
  // Set resistors in pins to Pull Up to the 3.3v rail.
  pullUpDnControl(sdSystem.CONFIG.iSWITCH_PINs0, PUD_UP);
  pullUpDnControl(sdSystem.CONFIG.iSWITCH_PINs1, PUD_UP);
  pullUpDnControl(sdSystem.CONFIG.iSWITCH_PINs2, PUD_UP);
  pullUpDnControl(sdSystem.CONFIG.iSWITCH_PINs3, PUD_UP);


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
  // FLED
  cons.printi("Initializing Timer");
  FledTime tmeFled;
  tmeFled.set();
  
  // ---------------------------------------------------------------------------------------
  // Light Strip Event System
  cons.printi("Initializing System Event Channels");
  timed_event teEvent[sdSystem.CONFIG.iNUM_CHANNELS];


  // ---------------------------------------------------------------------------------------
  // Define the Supid Random Numbers
  cons.printi("Initializing Random Number Generator");
  stupid_random sRND;
  // Initialize the Stupid Random Numbers
  sRND.set();

  // -------------------------------------------------------------------------------------
  // FLED LED Array
  cons.printi("Initializing LED Arrays");
  CRGB crgbMainArrays0[sdSystem.CONFIG.iNUM_LEDSs0];
  CRGB crgbMainArrays1[sdSystem.CONFIG.iNUM_LEDSs1];
  CRGB crgbMainArrays2[sdSystem.CONFIG.iNUM_LEDSs0];
  CRGB crgbMainArrays3[sdSystem.CONFIG.iNUM_LEDSs1];
  
  cons.printi("Initializing Event System");
  teEvent[0].create(sdSystem.CONFIG.iNUM_LEDSs0);
  teEvent[1].create(sdSystem.CONFIG.iNUM_LEDSs1);
  teEvent[2].create(sdSystem.CONFIG.iNUM_LEDSs0);
  teEvent[3].create(sdSystem.CONFIG.iNUM_LEDSs1);

  // Door Sensor
  cons.printi("Initializing Sensors");
  hardware_monitor hwDoors[sdSystem.CONFIG.iNUM_SWITCHES];
  bool boAuxLightsIsOn = false;

  // -------------------------------------------------------------------------------------
  // FLED LED Array
  
  // Define Led Strips
  cons.printi("Initializing LED Strips");

  profile_strip_group pstrgDoor[4];

  hardware_monitor hwTempDoor;
  profile_strip pstrTempDoor;
  profile_strip pstrTempOverhead;

  hwTempDoor.set(true, (unsigned long)tmeFled.now(), 50, true);

  // Back Driver Door
  pstrTempDoor.set(0, 0, sdSystem.CONFIG.iLED_Size_Door_Back_Driver, true, true, "Back");
  pstrTempOverhead.set(0, sdSystem.CONFIG.iLED_Size_Door_Back_Driver, sdSystem.CONFIG.iLED_Size_Overhead_Back_Driver, true, true, "Back");
  pstrgDoor[0].set(pstrTempDoor, pstrTempOverhead, hwTempDoor);

  // Front Driver Door
  pstrTempDoor.set(1, sdSystem.CONFIG.iLED_Size_Overhead_Front_Driver, sdSystem.CONFIG.iLED_Size_Door_Front_Driver, true, true, "Front");
  pstrTempOverhead.set(1, 0, sdSystem.CONFIG.iLED_Size_Overhead_Front_Driver, true, false, "Front");
  pstrgDoor[1].set(pstrTempDoor, pstrTempOverhead, hwTempDoor);

  // Back Passenger Door
  pstrTempDoor.set(2, 0, sdSystem.CONFIG.iLED_Size_Door_Back_Passenger, true, true, "Back");
  pstrTempOverhead.set(2, sdSystem.CONFIG.iLED_Size_Door_Back_Passenger, sdSystem.CONFIG.iLED_Size_Overhead_Back_Passenger, true, true, "Back");
  pstrgDoor[2].set(pstrTempDoor, pstrTempOverhead, hwTempDoor);

  // Front Passenger Door
  pstrTempDoor.set(3, sdSystem.CONFIG.iLED_Size_Overhead_Front_Passenger, sdSystem.CONFIG.iLED_Size_Door_Front_Passenger, true, true, "Front");
  pstrTempOverhead.set(3, 0, sdSystem.CONFIG.iLED_Size_Overhead_Front_Passenger, true, false, "Front");
  pstrgDoor[3].set(pstrTempDoor, pstrTempOverhead, hwTempDoor);


  // -------------------------------------------------------------------------------------
  
  cons.printi("Starting System");
  // Sleeping Loop Variables
  tmeFled.setframetime();
  
  double tmeStartTime = tmeFled.tmeFrameMillis;
  unsigned long tmeCurrentMillis = (unsigned long)tmeFled.tmeFrameMillis;
   sdSystem.store_Current_Frame_Time(tmeCurrentMillis);

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

    bool booUpdates0 = false;
    bool booUpdates1 = false;
    bool booUpdates2 = false;
    bool booUpdates3 = false;

    // Sensor Array (QUICK FIX)
    bool booSensors[sdSystem.CONFIG.iNUM_SWITCHES];

    booSensors[0] = digitalRead(sdSystem.CONFIG.iSWITCH_PINs0);
    booSensors[1] = digitalRead(sdSystem.CONFIG.iSWITCH_PINs1);
    booSensors[2] = digitalRead(sdSystem.CONFIG.iSWITCH_PINs2);
    booSensors[3] = digitalRead(sdSystem.CONFIG.iSWITCH_PINs3);
    
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
    DoorMonitorAndAnimationControlModule(cons, sdSystem, pstrgDoor, teEvent, booSensors, tmeCurrentMillis);

    // ---------------------------------------------------------------------------------------
    // --- Check and Execute Timed Events That Are Ready ---

    //  Run ALL GLOBAL Timed Events
    teSystem(cons, sdSystem, pstrgDoor, teEvent, tmeCurrentMillis);

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

    // --- Execute LED Hardware Changes If Anything Was Updated ---
    //  For now we are working with just one big LED strip.  So, just check to see if anything
    //    changed.  Then, Redraw the entire strip. 
    if ((booUpdates0 == true) || (booUpdates1 == true) || (booUpdates2 == true) || (booUpdates3 == true))
    {
      //  Do I need to move the whole thing or can I just move the changed pixels?

      int mcount = 0;

      // If debug mode Display all lights static color are selectted, replace all generated led colors
      // with a static color
      if (cons.keywatch.get(KEYLEDTEST) !=0)
      {
        MatxixFill(crgbMainArrays0, sdSystem.CONFIG.iNUM_LEDSs0, CRGB(25,25,25));
        MatxixFill(crgbMainArrays1, sdSystem.CONFIG.iNUM_LEDSs1, CRGB(25,25,25));
        MatxixFill(crgbMainArrays2, sdSystem.CONFIG.iNUM_LEDSs0, CRGB(25,25,25));
        MatxixFill(crgbMainArrays3, sdSystem.CONFIG.iNUM_LEDSs1, CRGB(25,25,25));
      }

      // Copy the Prepared, or Calculated to the Display Matrix, before rendering.
      //  Checking to see if the matix is to be displayed like normal or with DIAGs.
      if (cons.keywatch.get(KEYLEDDRCYCL) == 0 || cons.keywatch.get(KEYLEDDRCYCL) == 1)
      {
        MatrixPrepare(cons, sdSystem, crgbMainArrays0, sdSystem.CONFIG.iNUM_LEDSs0, matrix, mcount);
      }
      if (cons.keywatch.get(KEYLEDDRCYCL) == 0 || cons.keywatch.get(KEYLEDDRCYCL) == 2)
      {
        MatrixPrepare(cons, sdSystem, crgbMainArrays1, sdSystem.CONFIG.iNUM_LEDSs1, matrix, mcount);
      }
      if (cons.keywatch.get(KEYLEDDRCYCL) == 0 || cons.keywatch.get(KEYLEDDRCYCL) == 3)
      {
        MatrixPrepare(cons, sdSystem, crgbMainArrays2, sdSystem.CONFIG.iNUM_LEDSs0, matrix, mcount);
      }
      if (cons.keywatch.get(KEYLEDDRCYCL) == 0 || cons.keywatch.get(KEYLEDDRCYCL) == 4)
      {
        MatrixPrepare(cons, sdSystem, crgbMainArrays3, sdSystem.CONFIG.iNUM_LEDSs1, matrix, mcount);
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

      // Also delayed, File maintenance.
      if (sdSystem.booRunning_State_File_Dirty == true)
      {
        save_running_state(cons, sdSystem, strRunning_State_Filename);

        // set false even if there was a save error to avoid repeats.
        sdSystem.booRunning_State_File_Dirty = false;
      }
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

  // Just print we have ended the program.
  printf ("\nRasFLED Loop ... Exit\n");

  return ret;
}

// ---------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  int ret = 0;

  printf("RasFLED Start ... \n");

  // Setup the Program
  setup();

  // Start the main loop.
  ret = loop();

  // Exit the program.
  printf("RasFLED ... Exit(%d)\n", ret);
  return ret;

}