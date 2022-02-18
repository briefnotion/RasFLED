// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: screen2.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef SCREEN2_H
#define SCREEN2_H

// Standard Header Files
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <deque>

#include "system.h"
#include "consoleanddata.h"

using namespace std;


class Screen2
{
  private:
  // Keyboard input variable
  int key = -1;

  // NCurses Variables
  int YMax = 0;
  int XMax = 0;
  int Xmid = 0;

  string strBotLine;
  
  WINDOW * winTop;
  WINDOW * winBot;

  // Display Variables
  int YSeperator = 0;   // Console y start pos
  int YConOut = 0;      // Console Printout cursor line pos

  public:

  void init()
  {
    cbreak();   // do not buffer input until cr.
    noecho();   // do not echo back pressed characters

    keypad(stdscr, true);      // Keypad mode for reported mouse events as KEY_MOUSE.

    // Don't mask any mouse events
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    printf("\033[?1003h\n");  // Makes the terminal report mouse movement events.
  }

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

    //wborder(winTop,' ',' ',' ','_',' ',' ',' ',' ') ;
    //wborder(winBot,' ',' ',' ','_',' ',' ',' ',' ') ;

    wborder(winTop,'|','|',' ','_','|','|','|','|') ;
    wborder(winBot,'|','|',' ','_',' ',' ','|','|') ;

    wrefresh(winBot);
    wrefresh(winTop);
    
    strBotLine = "";
    strBotLine = strBotLine.append(XMax-1, '_');

    nodelay(stdscr, true);
  }


  void printout(ConsoleLineList &clou)
  // Print out to console.  (Classic Style)
  //  If console is on another tty through tty over ethernet or serial then a low 
  //    bandwith version will need to created.  Or, I put the console into its own 
  //    thread.  Whichever is necessary to develop or learn first.
  {
    // Figurout the size of the console.
    int Ysize = YMax - YSeperator - 2;
    ConsoleLine line;

    int Ywincurpos = 0;
    int Linecurpos = 0;

    if(clou.avail() == true)
    {
      for( int y=0; y<Ysize; y++)
      {
        Ywincurpos = Ysize - y;
        Linecurpos =  Ysize - Ywincurpos;

        //  get next line to print.
        line = clou.get_line_to_print(Linecurpos);

        // Print console Line
        wmove(winBot, Ywincurpos,0);  //move cursor to next line to print or clear.
        wclrtoeol(winBot);            // clear line befor printing to it.
        mvwprintw(winBot, Ywincurpos, 0, "%s", line.strLine.c_str());  //print line.       
      }
        
      // Print bottom line to prevent spill over.
      //wmove(winBot, Ysize +1,0);  // move cursor to last line +1 to print
      //wclrtoeol(winBot);
      mvwprintw(winBot, Ysize +1 , 0, "%s", strBotLine.c_str()); // fill line with chars.
      
      // Refresh the window.
      wrefresh(winBot);
    }
  }

  
  void output_debug(system_data sdSysData, Keys keywatch, ConsoleLineList &clou, ScreenStatus ScrStat, TheMouse mouse)
  // printout debug info for top win
  {
    if (ScrStat.Debug == true)
    {
      mvwprintw(winTop, 2, 26, "Compute: %fms", sdSysData.fltCOMPUTETIME.data);
      mvwprintw(winTop, 3, 26, "  Sleep: %fms", sdSysData.fltPREVSLEEPTIME.data);
      mvwprintw(winTop, 4, 26, "  Cycle: %fms", sdSysData.fltCYCLETIME.data);

      mvwprintw(winTop, 4, 47, "(m:%fms)", sdSysData.fltCYCLETIME.max);
      if (sdSysData.booprintbuffer == true)
      {
        mvwprintw(winTop, 4, 1, ":%s", sdSysData.strprintbuffer.c_str());
      }
    }
    else
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
    if(ScrStat.Debug == true)
    {
      // Display LED range selected to display.
      string strRange;
      string strLevel;

      // Displaying LEDs selected to be displayed CYCLE selected.
      if (keywatch.get(KEYLEDTEST) == 1)
      {
        strRange = "Fi";
        strLevel = "ll";
      }
      else if (keywatch.get(KEYLEDDRCYCL) == 0)
      {
        strRange = "EA";
        strLevel = "  ";
      }
      else
      {
        strRange = "E" + to_string(keywatch.get(KEYLEDDRCYCL)-1);
        strLevel = to_string(sdSysData.t_group) + to_string(sdSysData.t_strip);
      }

      // Draw RANGE and UPPER OR LOWER VALUES selected.
      mvwprintw(winTop, 2, 19, "RNG:%s", strRange.c_str());
      mvwprintw(winTop, 3, 19, "LVL:%s", strLevel.c_str());
    }    
    else
    // If exiting debug mode, clean out what was printed in when in debug mode.
    {
      mvwprintw(winTop, 2, 19, "      ");
      mvwprintw(winTop, 3, 19, "      ");
    }

    // Debug stuff: Display the amount of events, assoicated to each door, runnng .
    if (ScrStat.Debug == true)
    {
      mvwprintw(winTop, 3, 1, "%03d:E", sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(0));
      mvwprintw(winTop, 2, 1, "%03d:E", sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(1));
      mvwprintw(winTop, 3, 13, "E:%03d", sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(2));
      mvwprintw(winTop, 2, 13, "E:%03d", sdSysData.intCHANNEL_GROUP_EVENTS_COUNTS.at(3));
    }
    else
    // If exiting debug mode, clean out what was printed in when in debug mode.
    {
      mvwprintw(winTop, 3, 1, "     ");
      mvwprintw(winTop, 2, 1, "     ");
      mvwprintw(winTop, 3, 13, "     ");
      mvwprintw(winTop, 2, 13, "     ");
    }

    // Display Diag Indicator
    if (ScrStat.Debug == true)
    {
      wattron(winTop, A_REVERSE);
      mvwprintw(winTop, 0, XMax - 5, "DIAG");
      wattroff(winTop, A_REVERSE);
    }
    else
    {
      mvwprintw(winTop, 0, XMax - 5, "    ");
    } 

    // Display Mouse Info
    if (ScrStat.Debug == true)
    {
      mvwprintw(winTop, 2, XMax - 15, "Mouse: %03d %03d",mouse.x(),mouse.y());
      if (mouse.Clicked() == true)
      {
        mvwprintw(winTop, 3, XMax - 15, "Click: %03d %03d",mouse.x_clicked(),mouse.y_clicked());
      }
    }
    else
    {
      mvwprintw(winTop, 2, XMax - 15, "              ");
      mvwprintw(winTop, 3, XMax - 15, "              ");
    }
  }
  

  // Draw the console, starting with status window, then update console with pending
  // console prints.
  void output(system_data sdSysData, Keys keywatch, ConsoleLineList &clou, ScreenStatus ScrStat, TheMouse mouse)
  {
    //Display Door Statuses, highlighting values that are on (doors open)
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(0).value == true) {wattron(winTop, A_REVERSE);}
    mvwprintw(winTop, 3, 7, "D1");
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(0).value == true) {wattroff(winTop, A_REVERSE);}
    
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(1).value == true) {wattron(winTop, A_REVERSE);}
    mvwprintw(winTop, 2, 7, "D2");
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(1).value == true) {wattroff(winTop, A_REVERSE);}
    
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(2).value == true) {wattron(winTop, A_REVERSE);}
    mvwprintw(winTop, 3, 10, "D3");
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(2).value == true) {wattroff(winTop, A_REVERSE);}

    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(3).value == true) {wattron(winTop, A_REVERSE);}
    mvwprintw(winTop, 2, 10, "D4");
    if (sdSysData.CONFIG.vSWITCH_PIN_MAP.at(3).value == true) {wattroff(winTop, A_REVERSE);}

    mvwprintw(winTop, 0, 18, "REPEAT");
    mvwprintw(winTop, 0, 26, "DOORAWARE");
    
    if(sdSysData.booDay_On == true)
    {
      wattron(winTop, A_REVERSE);
      mvwprintw(winTop, 0, 37, " DAY ");
      wattroff(winTop, A_REVERSE);
    }
    else
    {
      mvwprintw(winTop, 0, 37, "NIGHT");      
    }

    // Debug Stuff: Display Compute Times
    if (ScrStat.Debug == true || ScrStat.Debug_Refresh == true)
    {
      output_debug(sdSysData, keywatch, clou, ScrStat, mouse);
    }

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

    // Clear any Screen Status info
    ScrStat.clear();

    // Commit all our changes to the status portion of the screen (winTop)
    wrefresh(winTop);

    // Now that we are finished drawing the Console Status part of the screen, 
    // we needd to go to the console portion of the screen and update it.
    printout(clou);
  }

};



#endif