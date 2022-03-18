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
{
  public:

  int DELAY = 1;
  int HEIGHT = 1;
  int WIDTH = 1;

  deque<string> LINES;
};

class PLAYER_MOVIE_LIST
{
  public:

  int CURRENTLY_PLAYING = -1;

  deque<string> MOVIE_LIST;

  int size()
  {
    return MOVIE_LIST.size();
  }

  void add_to_list(string path)
  {
    MOVIE_LIST.push_back(path);
  }

  string get_next_movie()
  {
    CURRENTLY_PLAYING++;
    if (CURRENTLY_PLAYING <0 || CURRENTLY_PLAYING >= MOVIE_LIST.size())
    {
      CURRENTLY_PLAYING = 0;
    }

    return MOVIE_LIST[CURRENTLY_PLAYING];
  }

  void remove_current_movie()
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
{
  private:
  
  public:
  
  bool booSuccess = false;
  bool booActive = false;
  bool booEOF = false;

  bool booLoad_Film(fstream &fsPlayer, string strFilename)
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

  string strRead_Line(fstream &fsPlayer)
  {
    string strRead = "";
    if(booActive == true)
    {
      getline(fsPlayer,strRead);
      
      if(fsPlayer.eof())
      {
        booActive = false;
        booSuccess = false;
        booEOF = true;
        fsPlayer.close();
      }
    }
    return strRead;
  }

  bool booRead_Frame(fstream &fsPlayer, PLAYER_FRAME &qFrame)
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
{
  private:

  public:

  PLAYER_FILE_TO_DEQUE ftqFilm;
  PLAYER_MOVIE_LIST Play_List;
  bool booPlay = true;
  bool booSucess = false;

  bool booDisable = false;
  
  // Frame Info
  PLAYER_FRAME qFrame;

  unsigned long tmeLAST_FRAME_DRAW_TIME = 0;
  unsigned long tmeNEXT_FRAME_DRAW_TIME = 0;
  unsigned long tmeFRAME_TIME_MILLIS = 1000/15;

  bool load_reel(fstream &fsPlayer, string filename)
  {
    qFrame.HEIGHT = 13;
    qFrame.WIDTH = 67;

    booSucess = ftqFilm.booLoad_Film(fsPlayer, filename);
    
    return booSucess;
  }

  bool get_frame(fstream &fsPlayer, unsigned long tmeCurrent_Time_millis)
  {
    int hold_time = 0;

    // Prep for first run
    if (tmeNEXT_FRAME_DRAW_TIME == 0)
    {
      tmeNEXT_FRAME_DRAW_TIME = tmeCurrent_Time_millis;
    }

    // Get Frame Hold Time
    while (hold_time == 0 && ftqFilm.booSuccess == true)
    {
      try
      {
        hold_time = stoi(ftqFilm.strRead_Line(fsPlayer));
        booSucess = ftqFilm.booSuccess;
      }
      catch(const std::exception& e)
      {
        //std::cerr << e.what() << '\n';
        booSucess = false;
      }
    }

    tmeLAST_FRAME_DRAW_TIME = tmeNEXT_FRAME_DRAW_TIME;
    tmeNEXT_FRAME_DRAW_TIME = tmeNEXT_FRAME_DRAW_TIME + (tmeFRAME_TIME_MILLIS * hold_time);

    if (ftqFilm.booSuccess == true)
    {
      booSucess = ftqFilm.booRead_Frame(fsPlayer, qFrame);
    }

    return booSucess;
  }

  void pause()
  {
    booPlay = false;
    tmeNEXT_FRAME_DRAW_TIME = 0;
  }

  void play()
  {
    booPlay = true;
  }
};


#endif