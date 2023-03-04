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
#include <string.h>
#include <deque>

#include "stringthings.h"
#include "rasapi.h"

using namespace std;

// Ledgend Scale Types:
#define LEDGEND_OFF     0
#define LEDGEND_RANGE   1
#define LEDGEND_SCALER  2

// -------------------------------------------------------------------------------------
//  Supporting Functions

bool remove_opens_and_closes(string &Entry, char Open, char Close);

string parse_label(string Text, int Pos_Colon);

string parse_value(string Text, int Pos_Colon);

// -------------------------------------------------------------------------------------
//  JSON Class

class JSON_ENTRY
{
  private:
  
  int errcountcap = 1000;

  int find_closing(string Text, int Start_Pos, char Opening, char Closing);

  bool check_entry(string &Entry, int &Size_Of_Entry, int &Size_Of_Label, int &Size_Of_Value, 
                              bool &Is_A_Set, bool &Is_A_List);

  bool parse_item_list(string Entry, bool Is_Set, string Set_Name);

  string LABEL = "";
  string VALUE = "";

  public:

  deque<JSON_ENTRY> DATA;

  bool IS_VALUE = false;
  bool IS_SET = false;
  bool IS_LIST = true;

  void clear_data();

  int find_label_pos(string Label_In_List);

  int size_of_set(string Set_Label);

  bool set_list(string Entry);

  bool set_set(string Entry, string Set_Name);

  string label();

  string value();

  string value_from_list(string Label_In_List);

  void create_label_value(string Label, string Value);

  void put_json_in_list(JSON_ENTRY Entry);

  void put_json_in_set(string Set_Name, JSON_ENTRY Entry);
};

class JSON_INTERFACE
{
  private:
  
  void json_debug_to_string_deque(deque<string> &JSON_Print_Build, JSON_ENTRY Json_entry, int Level, int Count);

  void json_to_string_deque(deque<string> &JSON_Print_Build, JSON_ENTRY Json_entry, int Level, string Trailing_Seperator);

  public: 

  JSON_ENTRY ROOT;

  bool load_json_from_string(string JSON_Text);
  // boolean failure and success decisions not complete

  void json_debug_build_to_string_deque(deque<string> &JSON_Print_Build);

  void json_print_build_to_string_deque(deque<string> &JSON_Print_Build);
};


#endif