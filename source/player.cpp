// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: player.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "player.h"

using namespace std;

void PLAYER_FRAME::reset()
{
  TYPE = 0;
  FPS = 15;
  DELAY = 1;
  HEIGHT = 1;
  WIDTH = 1;
  LINES.clear();
}

int PLAYER_MOVIE_LIST::size()
// Returns size of current playlist.
{
  return MOVIE_LIST.size();
}

void PLAYER_MOVIE_LIST::add_to_list(string path)
// Add a file to the playlist. Must contain full path name.
{
  MOVIE_LIST.push_back(path);
}

string PLAYER_MOVIE_LIST::get_next_movie()
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

void PLAYER_MOVIE_LIST::remove_current_movie()
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


bool PLAYER_FILE_TO_DEQUE::booLoad_Film(fstream &fsPlayer, string strFilename)
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

void PLAYER_FILE_TO_DEQUE::close_the_file(fstream &fsPlayer)
// close the film file and set everything off.
{
  booActive = false;
  booSuccess = false;
  booEOF = true;
  fsPlayer.close();
}

string PLAYER_FILE_TO_DEQUE::strRead_Line(fstream &fsPlayer)
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

bool PLAYER_FILE_TO_DEQUE::booRead_Frame(fstream &fsPlayer, PLAYER_FRAME &qFrame)
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



bool PLAYER::load_reel(fstream &fsPlayer, string filename)
// Opens the file containing te movie.
//  Returns false if anything goes wrong.
{
  qFrame.reset();

  booSucess = ftqFilm.booLoad_Film(fsPlayer, filename);
  
  return booSucess;
}

bool PLAYER::get_frame(fstream &fsPlayer)
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
        int Frame_Type = string_to_int(strFrameInfo.substr(0, pos1));

        if ((Frame_Type == 1000 || qFrame.TYPE == 1000) ||
            (Frame_Type == 1001 || qFrame.TYPE == 1001)    )
        {
          // Get Width
          pos2 = strFrameInfo.find(" ", pos1 +1);
          Frame_Width = string_to_int(strFrameInfo.substr(pos1 +1, pos2));

          // Get Height
          pos1 = pos2;
          pos2 = strFrameInfo.find(" ", pos1 +1);
          Frame_Height = string_to_int(strFrameInfo.substr(pos1 +1, pos2));

          // Get FPS
          pos1 = pos2;
          Frame_FPS = string_to_int(strFrameInfo.substr(pos1 +1));

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

void PLAYER::pause()
// Pause the player by setting play to false.
{
  booPlay = false;
  tmeNEXT_FRAME_DRAW_TIME = 0;
}

void PLAYER::play()
// Start the player by setting play to true.
{
  booPlay = true;
}

bool PLAYER::is_ready_to_draw_frame(unsigned long tmeCurrent_Time_millis)
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

unsigned long PLAYER::get_next_frame_draw_time()
// Returns the time the next frame is to be drawn.
// Returns 0 if the not playing or player is disabled.
{
  if((booPlay == true) && (booDisable == false))
  {
    return tmeNEXT_FRAME_DRAW_TIME;
  }
  else
  {
    return 0;
  }
}




#endif