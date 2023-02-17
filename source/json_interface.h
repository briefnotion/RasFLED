// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: json_interface.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef JSON_INTERFACE_H
#define JSON_INTERFACE_H

// Standard Header Files
#include <stdio.h>
//#include <ncurses.h>
#include <string.h>
#include <deque>

#include "stringthings.h"
//#include "system.h"
//#include "helper_ncurses.h"
#include "files.h"
#include "rasapi.h"

using namespace std;

// Ledgend Scale Types:
#define LEDGEND_OFF     0
#define LEDGEND_RANGE   1
#define LEDGEND_SCALER  2

// -------------------------------------------------------------------------------------
//  Class

class JSON_ENTRY
{
  private:
  
  int errcountcap = 1000;

  string parse_label(string Text, int Pos_Colon);

  string parse_value(string Text, int Pos_Colon);

  int find_closing(string Text, int Start_Pos, char Opening, char Closing);

  bool remove_brackets(string &Entry);

  bool remove_curls(string &Entry);

  bool check_entry(string &Entry, int &Size_Of_Entry, int &Size_Of_Label, int &Size_Of_Value, 
                              bool &Is_A_Set, bool &Is_A_List);

  bool parse_item_list(string Entry);

  bool parse_item_set(string Entry, string Set_Name);

  public:

  string LABEL = "";
  string VALUE = "";
  deque<JSON_ENTRY> DATA;

  bool IS_VALUE = false;
  bool IS_SET = false;
  bool IS_LIST = false;

  bool set_list(string Entry);

  bool set_set(string Entry, string Set_Name);
};

class JSON_INTERFACE_PROPERTIES
// Properties (duh)
{
  public: 
  string FILENAME = "";

};

class JSON_INTERFACE
{
  private:

  FILE_TO_STRING FILE_JSON;

  public: 

  JSON_INTERFACE_PROPERTIES PROP;

  JSON_ENTRY ROOT;

  bool load_json();

  string sub();

};


#endif