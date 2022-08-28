// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: player.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef PLAYER_H
#define PLAYER_H

// Standard Header Files
#include <fstream>
#include <iostream>
#include <string>
#include <deque>

#include "stringthings.h"

using namespace std;

class PLAYER_FRAME
// Variable class containing information about the play system movie/picture frame.
//  Set for play knows timing and frame size.
{
  public:

  int TYPE = 0;
  int FPS = 15;  // Frame hang time. Measured in 15ths of a second
  int DELAY = 1;  // Frame hang time. Measured in 15ths of a second
  int HEIGHT = 1; // Amount of lines per frame.
  int WIDTH = 1;  // Amount of characters per line.

  deque<string> LINES;  // Frame buffer.

  void reset();
};

class PLAYER_MOVIE_LIST
// A simple play list for the movie player.
//  probably not great to access these routines from outside the player
//  handler.
{
  public:

  int CURRENTLY_PLAYING = -1;

  deque<string> MOVIE_LIST;

  int size();

  void add_to_list(string path);

  string get_next_movie();

  void remove_current_movie();
};


class PLAYER_FILE_TO_DEQUE
// Variable class for file handling and loading the next frame into 
//  frame buffer.  
//  Stays open and active untill End Of File reached.
{
  private:
  
  public:
  
  bool booSuccess = false;  // Class status. Set to false if anything is wrong.
  bool booActive = false;   // Class status of file.
  bool booEOF = false;      // Class status of EOF reached.

  bool booLoad_Film(fstream &fsPlayer, string strFilename);
  void close_the_file(fstream &fsPlayer);

  string strRead_Line(fstream &fsPlayer);

  bool booRead_Frame(fstream &fsPlayer, PLAYER_FRAME &qFrame);
};


class PLAYER
// Variable class to handle the player and most of its functions.
//  All player functions should be accessed through this class varable 
//  alone PLAYER handles its own playlist, file stream, and frame buffer.
//  No need to assign any of these functions anywhere else.
{
  private:

  public:

  PLAYER_FILE_TO_DEQUE ftqFilm; // The file handler containing the movie.
  PLAYER_MOVIE_LIST Play_List;  // Playlist handler for sequential movies.
  bool booPlay = true;          // Plays movie when set to true. Pause when 
                                //  set to false
  bool booSkip = false;         // Set the track to skip at next read.

  bool booSucess = false;       // Set to false if anything went wrong.

  bool booDisable = false;      // If for any reason, the player should 
                                // not attempt to play, set disable to 
                                // true.
                                // Disable will set itself to true if the 
                                // playlist is empty.
  
  // Frame Info
  PLAYER_FRAME qFrame;  // Contains the frame of the movie

  unsigned long tmeLAST_FRAME_DRAW_TIME = 0;  // The time of the last successful 
                                              //  frame drawn to screen
  unsigned long tmeNEXT_FRAME_DRAW_TIME = 0;  // The futer time of when the next
                                              //  frame will be drawn to the screen.
  unsigned long tmeTIME_LAST_ASKED      = 0;  // If the player was asked if it was time
                                              //  to draw a frame, this time will be 
                                              //  recorded.  This time can be used 
                                              //  shortly after to calculate the time 
                                              //  the next frame can be drawn.
                                                                                            
  //unsigned long tmeFRAME_TIME_MILLIS = 1000/15; // Lenght of time 1 frame will be displayed 
                                                //  without delay (fastest.) Time is stored 
                                                //  in milliseconds.

  bool load_reel(fstream &fsPlayer, string filename);

  bool get_frame(fstream &fsPlayer);

  void pause();

  void play();

  bool is_ready_to_draw_frame(unsigned long tmeCurrent_Time_millis);

  unsigned long get_next_frame_draw_time();
};


#endif