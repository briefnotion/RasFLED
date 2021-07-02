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
// *  PROJECTID: gi6$b*E>*q%;    Revision: 00000000.33A
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
// * V 0.33_210702 
// *    - MAKE NO MISTAKE: 
// *        I have no disillusionment about this software.  At the time of this writing  
// *        RasFLED has always been free to use, as per the GNU GENERAL PUBLIC LICENSE. 
// *         
// *        I can honestly say, literally, I have never been paid, by anybody or anyone,  
// *        in any way, shape or form, for writing this software.  Nor, has anybody or  
// *        anyone contributed in any way for its development. I have, literally, not   
// *        recieved any feedback at all that ever helped contribute to RasFLEDs future  
// *        developement.  The only comments ever recieved by first hand experience from  
// *        passerbys was the generic "thats nice." 
// * 
// *        If you paid or given up anything to send or suggest anything, regarding these 
// *        lights, or anything else, for that matter, then, I am sorry, but you have been 
// *        scammed.  Your message was never delivered.  If you paid anyone for a feature  
// *        to be placed into this software, you have been scammed.  Any and all features  
// *        of RasFLED were by my design, and the only driving force behind my desire to  
// *        change, delete, or add to the program, has always been, "because I wanted to." 
// *        I promise to tell you, in the unlikely event the program gets any type of  
// *        sponser or paid for feature added, I will disclose it with a statement in  
// *        these comments, along with any relevant information.  
// * 
// *        Literally, this app has no followers or comments or support.  Metaphorically,  
// *        well, if you didn't help make the bread, then you are not going to help eat  
// *        the bread. 
// *
// *    - Door module can handle multiple strips.  Groups triggered by switches will run 
// *        preset animations on strips with the grouple with name "Door" and "Overhead". 
// * 
// *                 To Demonstrate, here is an example config file.
// *                 ______________________________________
// *                |
// *                |* ------------------------------
// *                |* Switch Configuration
// *                |*   - Switch ID PIN
// *                |Switch_Count 4
// *                |Switch 0 22
// *                |Switch 1 23
// *                |Switch 2 24
// *                |Switch 3 25
// *                |
// *                |* ------------------------------
// *                |* Strip Configuration
// *                |LED_Main 0 Car
// *                |
// *                |
// *                |
// *                |LED_Group_Count 4
// *                |  LED_Group_ID 0 Back_Driver
// *                |    LED_Strip_Count 0 2
// *                |      LED_Strip_ID 0 0 Door Back 70 Forward Standing
// *                |      LED_Strip_ID 0 1 Overhead Back 52 Forward Standing
// *                |  LED_Group_ID 1 Front_Driver
// *                |    LED_Strip_Count 1 4
// *                |      LED_Strip_ID 1 0 Overhead Front 52 Forward Standing
// *                |      LED_Strip_ID 1 1 Door Front 66 Forward Hanging
// *                |      LED_Strip_ID 1 2 Overhead Front 52 Forward Standing
// *                |      LED_Strip_ID 1 3 Door Front 66 Forward Hanging
// *                |  LED_Group_ID 2 Back_Passenger
// *                |    LED_Strip_Count 2 3
// *                |      LED_Strip_ID 2 0 Overhead Back 52 Forward Standing
// *                |      LED_Strip_ID 2 1 Door Back 70 Forward Standing
// *                |      LED_Strip_ID 2 2 Overhead Back 52 Forward Standing
// *                |  LED_Group_ID 3 Front_Passenger
// *                |   LED_Strip_Count 3 2
// *                |      LED_Strip_ID 3 0 Overhead Front 52 Forward Standing
// *                |      LED_Strip_ID 3 1 Door Front 66 Forward Hanging
// *                |______________________________________
// *
// *        - Made some changes to the pulse repeat timer.  Its still not right, but  
// *           I know whats wrong. 
// *
// * V 0.31_210622
// *    - Current version will be more of a "get it working in any kind of way" update for 
// *        the configurable system.  Plenty of routines need an overhaul.  
// *        - Current Restrictions for current test version:
// *            - Switches are directly tied to groups of strips.
// *            - Animations are directly tied to groups of strips (mostly).
// *            - Only one switch per group.
// *            - There is no direct mapping for switch to strip group.
// *            - Console Display could use plenty of work.  Holding off until I get 
// *                a display because never needed in live environement and not a system 
// *                dependent component. 
// *    - Sucesses:
// *        - No Hardcoded strip sizes or switch sizes should exist anywhere in the 
// *            system.
// *        - Any Array within the system is dynamicly allocated on startup or whenever 
// *            needed.
// *        - Every part of the system that relied on hardcoded sizes has been rewritten 
// *            to handle dynamic sizes or allocations. 
// *        - Portions of the console has been rewitten to handle dynamic sizes.
// *        - Test funcions have been modified to handle dynamic sizes.
// *        - All in all, a bunch of things changed.
// *    - I am not certain everythings is working as was before, so running everything 
// *        through some live test to find out.  
// *    - Cut out a bunch of old animations.  Structure of the animation classes changed 
// *        so much, probably couldnt get them running without a rewrite anyway. 
// *    - Added things to the ToDo list.  Good things.
// *    - I would totally love a Cesna 152 and the ability to continuously affor its 
// *        upkeep and minor trips.  I think I could handle a Cesna 152 as long as  
// *        everything worked.  Do you really need to go to a flight school to get 
// *        a pilots license.  Really need to get rid of people in my life who keep 
// *        tieing me down.
// *    - Large portions of code are out of place, not needed, or just in the wrong 
// *        order.  Doesn't really affect the program compile or running, but, tidying 
// *        up will make the program easier to read. 
// *
// * V 0.30_210619
// *    - Delete the old configuration file before running.  Things have changed.
// *    - Got tired of looking at the same old animations.  
// *        Redid the Door open spotlight animation.
// *        Redid the Pulse animation.  Easier on the eyes.
// *    - Scheduled Events (AnEvSchedule) are now repeatable by setting repeat = true and
// *        duration.
// *    - Pulse animation and Pulse Countdown now call the same single simple pulse
// *        animation repeatedly.  No need to double up on the same animation to do two 
// *        seperate versions of the same thing.
// *    - Started the trek of configurable and numeralable strip types and sizes.  I am 
// *        not going to need to traverse any mountains, but there are a number of not so 
// *        small hills on the way.  I had the foresight during the designing and the 
// *        seemingly novel days of the Arduino Nano, to design the system so Fled could 
// *        handle an array type of LED strips.  Back then, though, I had no idea about 
// *        how it could be implemented. A fair amount of code will need to be rewritten.
// *    - Added a new command (config) to see if files loaded properly.  Probably have 
// *        more function in the futuer.
// *    - The Door Sensor Hardware Interface is now upgraded to the new Configurable 
// *        system.  Sure, much of the system cant take advantage of the varible amount  
// *        of switches, yet, and things like the console is hardcoded for, no less than
// *        4 switches.  However, a first step towards a fully configurable system has 
// *        been made.  The only steps remaining is:  modifying the strip classes to 
// *        be something more generic.  Writing the code to load those generic strips 
// *        with custom classifications.  Mapping the Hardware Map to the strips, and 
// *        hardware reactions through configuration files.  And, rewriting all the 
// *        animations.  I'm making it sound much more difficult than it actually is. 
// *        Like I said before, the groundwork has already been laid out. 
// *    - Taking the system out for a test before making any more changes. 
// *
// * V 0.29_210616
// *    - A simple, editable, configuration file is generated when ran for the first 
// *        time.  It will look like this:
// *          ______________________________________
// *          |Size_Test_Strip 63
// *          |
// *          |Size_Door_Back_Driver 70
// *          |Size_Door_Back_Passenger 70
// *          |Size_Door_Front_Driver 66
// *          |Size_Door_Front_Passenger 66
// *          |
// *          |Size_Overhead_Back_Driver 52
// *          |Size_Overhead_Back_Passenger 52
// *          |Size_Overhead_Front_Driver 52
// *          |Size_Overhead_Front_Passenger 52
// *          |______________________________________
// *
// *        This file can then be edited to match your LED count setup.  
// *        
// *        The string path is still propritary and is one long string
// *          in this order:
// *      
// *          Size_Door_Back_Driver --> Size_Overhead_Back_Driver --> 
// *          Size_Overhead_Front_Driver --> Size_Door_Front_Driver --> 
// *          Size_Door_Back_Passenger --> Size_Overhead_Back_Passenger --> 
// *          Size_Overhead_Front_Passenger --> Size_Door_Front_Passenger
// *      
// *        This much of the configuration file only allows easy change of the LED count 
// *          in each segment.  
// *        Remaining work:  Number of segments, Number of sub segments, Segment names, 
// *          Segment order, Segment orientation...
// *
// * V 0.28_210615
// *    - "AnEvSetToEnd" event now works as expected and properly ends sheduled events 
// *        also.  This squishes the bug causing Pulse Animations to, seemingly, randomly 
// *        not end.  The problem was a scheduled event would get reactivated during 
// *        PostCheck if it the ScheduleEvent was a passing Repeat=true parameter, and 
// *        the event was able to repeat itself before the the SetToEnd event completed.  
// *        There may be a reason to do this.  I don't know, But, never the less, the 
// *        event now stops, cold turkey, when asked to.
// *      Ok, its complecated.  Just went back and looked at it.  It may be realated to 
// *        the code not setting the completion value to true, because it was lumped into
// *        a part of code that actually needed to check for repeats.  
// *      Just checked, "AnEvSchedule" aren't coded to be able to be repeated.  Could 
// *        be with just one line of code.  But, isn't.
// *
// * V 0.27_210614
// *    - Program files are now stored in "/etc/RasFLED/"
// *        Note: The program cannot create the directory.  "/etc/RasFLED/" will need to 
// *        be created manually before RasFLED is ran for the first time.
// *    - LED Count is now calculated and not hard coded.
// *    - Further reduction of static variables to facilitate migration towards loadable 
// *        configuration.  Also, necessary for future implementation of dynamic 
// *        classification of objects, such as doors, and sub objects, such as overhead 
// *        lights, door lights, and switches.
// *    - Still haven't traced the END_ANIMATION bug.  To think, I was only setting out 
// *        to remove one static, rarely used definition (LED_COUNT).
// *        
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
// *          Although I was successful, I stopped progress on this because I was limited 
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
// *        libraries. (in progress)
// *    - Create a way to import all animations from an animations file. (finish 
//*         configuration files first)
// *    - Clean up 90% of the code. (recursive)
// *    - Move all the main animations into their own subroutines.
// *    - Create animations for day and night running.
// *    - Generate animations for shutting down animations.
// *    - Trace Flicker that occurs when sleep = 0 and doors are closing.
// *    - Revisit previous implementation of vectors.  "pop_back"s, "first", "last"s 
// *        and queues exist.  Had no idea.  Correction: vectors are so "3 months ago." 
// *        If ever RasFLED goes throgh a polish, replace vectors with deques.
// *    - Continue refining animations into an event language that can be ported. 
// *    - Configuration files. (in progress)
// *    - Add descriptions in the configuration.cfg file.
// *    - Thow in some code to allow switchs to groups to respond to multiple "Overhead" 
// *        and "Door"s within the group.
// *    - Tie Switches to groups through ID in configuration. 
// *    - Build a seperate config file for the Door control module so any additional 
// *        control modules created can be differentiated. 
// *    - Create an animation profile system to change all animations to another set of 
// *        animations.  For instance, change from normal animations to prebuilt holiday
// *        animations. 
// *    - There were a few more things to list here.  I'll write them down later as 
// *        needed.
// *    - Virtual LED Strips, for lack of a better name.  A way for the single LED strip
// *        to be a composit of two or more other strip, and act as one.  The overhead
// *        lights can be combined together so that animations can flow from one, to the 
// *        other, even if the LEDs are in differant portions of the LED strip, or in a 
// *        differant type of order or orientation.
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
  int return_code = 0;
  Console cons;
  system_data sdSystem;
  int intRet = wiringPiSetup(); 

  // Disposable Variables
  int count  = 0;
  
  // ---------------------------------------------------------------------------------------
  // Initialize the console
  initscr();
  cons.set(CONSOLESPLITSIZE);
  nodelay(stdscr, true);
  
  cons.printi("Initializing Console ...");
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
          = teEvents[channel].execute(cons, sRND, sdSystem.CONFIG.LED_MAIN.at(0).vLED_GROUPS.at(group).vLED_STRIPS.at(strip).crgbARRAY, tmeCurrentMillis);
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
      if ((ret = ws2811_render(&ledstring)) != WS2811_SUCCESS)
      {
          fprintf(stderr, "ws2811_render failed: %s\n", ws2811_get_return_t_str(ret));
          //break;    // boop - i touched
          //cons.printi("ws2811_render failed: " + ws2811_get_return_t_str(ret));
          return_code = (int)ret;
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
      processcommandlineinput(cons, sdSystem, tmeCurrentMillis, teEvents);
      extraanimationdoorcheck(cons, sdSystem, tmeCurrentMillis, teEvents);
      // Refresh console data storeage from main program. This will be a pass through buffer. 
      // so the console will not have to access any real data. 
      sdSystem.store_door_switch_states();
      store_event_counts(sdSystem, teEvents);

      cons.output(sdSystem);
      cons.update_displayed_time(tmeCurrentMillis);
      sdSystem.refresh();

      // Also delayed, File maintenance.
      if (sdSystem.booRunning_State_File_Dirty == true)
      {
        save_running_state(cons, sdSystem, Running_State_Filename);

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

  if(sdSystem.booREBOOT == false)
  {
    // Just print we have ended the program.
    printf ("\nRasFLED Loop ... Exit\n");
  }
  else
  {
    // Just print we have ended the program.
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

  // Exit the program.
  printf("RasFLED ... Exit(%d)\n", ret);
  return ret;

}