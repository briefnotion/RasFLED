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


// Standard Header Files
#include <fstream>
#include <iostream>
#include <string.h>
#include <deque>


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

  void reset()
  {
    TYPE = 0;
    FPS = 15;
    DELAY = 1;
    HEIGHT = 1;
    WIDTH = 1;
    LINES.clear();
  }
};

class PLAYER_MOVIE_LIST
// A simple play list for the movie player.
//  probably not great to access these routines from outside the player
//  handler.
{
  public:

  int CURRENTLY_PLAYING = -1;

  deque<string> MOVIE_LIST;

  int size()
  // Returns size of current playlist.
  {
    return MOVIE_LIST.size();
  }

  void add_to_list(string path)
  // Add a file to the playlist. Must contain full path name.
  {
    MOVIE_LIST.push_back(path);
  }

  string get_next_movie()
  // Returns the full path name of the next item in the play list. 
  //  Then, increases its position in the play list, and starts over 
  //  from the beginning when the end is reached.
  {
    CURRENTLY_PLAYING++;
    if (CURRENTLY_PLAYING <0 || CURRENTLY_PLAYING >= MOVIE_LIST.size())
    {
      CURRENTLY_PLAYING = 0;
    }

    return MOVIE_LIST[CURRENTLY_PLAYING];
  }

  void remove_current_movie()
  // Removes the current item in the playlist and preps net next item 
  //  to play as the next item to play. 
  {
    MOVIE_LIST.erase(MOVIE_LIST.begin() + CURRENTLY_PLAYING);
    CURRENTLY_PLAYING--;
    if (CURRENTLY_PLAYING <0)
    {
      CURRENTLY_PLAYING = MOVIE_LIST.size() - 1;
    }
  }
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

  bool booLoad_Film(fstream &fsPlayer, string strFilename)
  // Opens the file stream of the player with filename.
  //  Returns false if could not open for any reason.
  {
    fsPlayer.open(strFilename, ios::in);

    if (!fsPlayer)
    {
      booActive = false;
      booSuccess = false;
      booEOF = true;
    }
    else 
    {
      booActive = true;
      booSuccess = true;
      booEOF = false;
    }
    return booSuccess;
  }

  void close_the_file(fstream &fsPlayer)
  // close the film file and set everything off.
  {
    booActive = false;
    booSuccess = false;
    booEOF = true;
    fsPlayer.close();
  }

  string strRead_Line(fstream &fsPlayer)
  // Returns the next line of the file stream.
  //  Returns false if could not read for any reason.
  {
    string strRead = "";
    if(booActive == true)
    {
      getline(fsPlayer,strRead);
      
      if(fsPlayer.eof())
      {
        close_the_file(fsPlayer);
      }
    }
    return strRead;
  }

  bool booRead_Frame(fstream &fsPlayer, PLAYER_FRAME &qFrame)
  // Reads next fram into frame buffer passed. File stream needs to be 
  //  previously opened. Size is determined by Frame parameters.
    //  Returns false if could not read full frame for any reason.
  {
    if (booActive == true)
    {
      for(int line=0; (line < qFrame.HEIGHT) && (booActive == true); line++)
      {  
        qFrame.LINES.push_back(strRead_Line(fsPlayer));
      }
    }
    return booSuccess;
  }
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

  bool load_reel(fstream &fsPlayer, string filename)
  // Opens the file containing te movie.
  //  Returns false if anything goes wrong.
  {
    qFrame.reset();

    booSucess = ftqFilm.booLoad_Film(fsPlayer, filename);
    
    return booSucess;
  }

  bool get_frame(fstream &fsPlayer)
  // Puts next frame into frame buffer.
  //  Returns false if anything goes wrong.
  // Also, in case of a bad or errored movie file, instead of crashing the 
  //  program, the get_frame routine will attempt to search for the next 
  //  key frame and attempt to load it instead.
  // Returns false if anything goes wrong. 
  //  Except in the case that it was a badly formatted movie, instead 
  //  it will return what it found as the frame and return success as true. 
  {
    int hold_time = 0;
    string strFrameInfo = "";
    int Frame_Type = 0;
    int Frame_Width = 0;
    int Frame_Height = 0; 
    int Frame_FPS = 60;
    
    int pos1 = 0;
    int pos2 = 0;

    bool booFrame_info_loaded = false;

    // Prep for first run
    if (tmeNEXT_FRAME_DRAW_TIME == 0)
    {
      tmeNEXT_FRAME_DRAW_TIME = tmeTIME_LAST_ASKED;
    }

    // Get Frame Info
    while (booFrame_info_loaded == false && ftqFilm.booSuccess == true)
    {
      try
      {
        // Read next line
        strFrameInfo = ftqFilm.strRead_Line(fsPlayer);

        // Check for basic frame time hold
        pos1 = strFrameInfo.find(" ");

        // Check to see if Frame type is unset or type 1.
        if (pos1 == strFrameInfo.npos && (qFrame.TYPE == 0 || qFrame.TYPE == 1))
        {
          qFrame.TYPE = 1;
          hold_time = stoi(strFrameInfo);
          
          qFrame.DELAY = hold_time;
          qFrame.FPS = 15;

          qFrame.WIDTH = 67;
          qFrame.HEIGHT = 13;

          booFrame_info_loaded = true;
        }
        else
        // Check to see if Frame type is 1000 or 1001
        {
          int Frame_Type = atoi(strFrameInfo.substr(0, pos1).c_str());

          if ((Frame_Type == 1000 || qFrame.TYPE == 1000) ||
              (Frame_Type == 1001 || qFrame.TYPE == 1001)    )
          {
            // Get Width
            pos2 = strFrameInfo.find(" ", pos1 +1);
            Frame_Width = atoi(strFrameInfo.substr(pos1 +1, pos2).c_str());

            // Get Height
            pos1 = pos2;
            pos2 = strFrameInfo.find(" ", pos1 +1);
            Frame_Height = atoi(strFrameInfo.substr(pos1 +1, pos2).c_str());

            // Get FPS
            pos1 = pos2;
            //pos2 = strFrameInfo.find(" ", pos1 +1);
            Frame_FPS = atoi(strFrameInfo.substr(pos1 +1).c_str());

            // No exceptions yet, not likely to get any.
            // Store the settings.
            qFrame.TYPE = Frame_Type;
            qFrame.WIDTH = Frame_Width;
            qFrame.HEIGHT = Frame_Height;
            qFrame.DELAY = 1;

            // With possibility of read error, FPS may be 0.
            // Set FPS to something else if it is 0 because 
            //  0 FPS will trigger an exception elswhere in the program.
            if (Frame_FPS <= 0)
            {
              qFrame.FPS = 30;
            }
            else
            {
              qFrame.FPS = Frame_FPS;
            }

            // Info line sucessfully loaded, exit the trap loop.
            booFrame_info_loaded = true;
          }
        }
        booSucess = ftqFilm.booSuccess;
      }
      catch(const std::exception& e)
      {
        //std::cerr << e.what() << '\n';
        booSucess = false;
      }
    }

    //tmeLAST_FRAME_DRAW_TIME = tmeNEXT_FRAME_DRAW_TIME;
    tmeLAST_FRAME_DRAW_TIME = tmeTIME_LAST_ASKED;
    
    if (qFrame.TYPE == 1)
    { // if frame type is 1 use delay method.
      tmeNEXT_FRAME_DRAW_TIME = tmeLAST_FRAME_DRAW_TIME + (1000 /15 * qFrame.DELAY);
    }
    else
    { // if frame type is 1000 use FPS method
      tmeNEXT_FRAME_DRAW_TIME = tmeLAST_FRAME_DRAW_TIME + (1000 / qFrame.FPS);
    }

    if (ftqFilm.booSuccess == true)
    {
      booSucess = ftqFilm.booRead_Frame(fsPlayer, qFrame);
    }

    return booSucess;
  }

  void pause()
  // Pause the player by setting play to false.
  {
    booPlay = false;
    tmeNEXT_FRAME_DRAW_TIME = 0;
  }

  void play()
  // Start the player by setting play to true.
  {
    booPlay = true;
  }

  bool is_ready_to_draw_frame(unsigned long tmeCurrent_Time_millis)
  // Returns true all conditions are met to draw the next frame.
  // Conditions: not disabled, playing, time_ready.
  {
    bool ready = false;
    tmeTIME_LAST_ASKED = tmeCurrent_Time_millis;

    if((booPlay == true) && (booDisable == false))
    {
      if (tmeCurrent_Time_millis >= tmeNEXT_FRAME_DRAW_TIME)
      {
        ready = true;
      }
    }
    return ready;
  }
};


#endif