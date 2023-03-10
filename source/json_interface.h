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
#include <string>
#include <deque>

#include "stringthings.h"
#include "rasapi.h"
#include "LEDstuff.h"

using namespace std;

// Ledgend Scale Types:
#define LEDGEND_OFF     0
#define LEDGEND_RANGE   1
#define LEDGEND_SCALER  2

// -------------------------------------------------------------------------------------
//  Supporting Functions

bool remove_opens_and_closes(string &Entry, char Open, char Close);

string parse_label(string Text, int Pos_Colon);
// Sub out the Label

string parse_value(string Text, int Pos_Colon);
// Sub out the Value

int pos_of_first_non_space(int Start, string Text);
// Find first non space character starting from the start position.

// -------------------------------------------------------------------------------------
//  JSON Class

class JSON_ENTRY
{
  private:
  
  int errcountcap = 10000;

  int find_closing(string Text, int Start_Pos, char Opening, char Closing);
  // Find matching position of closing character matching opening character.
  //  starting from start position.  e.g. "{{{}}}" "{" "}" returns 5th pos.

  bool check_entry(string &Entry, int &Size_Of_Entry, int &Size_Of_Label, 
                              bool &Is_A_Set, bool &Is_A_List, bool &Is_A_Value);
  // Get characteristics of entry.  

  bool parse_item_list(string Entry, bool Is_Set, string Set_Name);
  // Parse list or set.

  string LABEL = "";
  string VALUE = "";

  public:

  deque<JSON_ENTRY> DATA;

  bool IS_VALUE = false;
  bool IS_SET = false;
  bool IS_LIST = false;

  void clear_data();
  // Clear all entries JSON 

  int find_label_pos(string Label_In_List);
  // return pos in JSON entry data list.

  int size_of_set(string Set_Label);
  // returns the size set list with with Label, within a set.

  bool set_list(string Entry);
  // Creates a list within a JSON Entry

  bool set_set(string Entry, string Set_Name);
  // Creates a set within a JSON Entry

  string label();
  // Returns label of JSON Entry.

  string value();
  // Returns value of JSON Entry.

  string value_from_list(string Label_In_List);
  // Returns the value of label within a JSON list.

  bool get_if_is(string Label, int &Value);
  // Returns false if label within a json does not match.
  // Returns true  if label within a json does match and changes.
  //  Value to JSON value.

  bool get_if_is(string Label, char &Value);
  // Returns false if label within a json does not match.
  // Returns true  if label within a json does match and changes.
  //  Value to JSON value.

  bool get_if_is(string Label, bool &Value);
  // Returns false if label within a json does not match.
  // Returns true  if label within a json does match and changes.
  //  Value to JSON value.

  bool get_if_is(string Label, CRGB &Value);
  // Returns false if label within a json does not match.
  // Returns true  if label within a json does match and changes.
  //  Value to JSON value.

  bool get_if_is(string Label, string &Value);
  // Returns false if label within a json does not match.
  // Returns true  if label within a json does match and changes.
  //  Value to JSON value.

  bool get_if_is(string Label, STRING_STRING &Value);
  // Returns false if label within a json does not match.
  // Returns true  if label within a json does match and changes.
  //  Value to JSON value.

  bool get_if_is(string Label, STRING_INT &Value);
  // Returns false if label within a json does not match.
  // Returns true  if label within a json does match and changes.
  //  Value to JSON value.

  bool get_if_is(string Label, STRING_FLOAT &Value);
  // Returns false if label within a json does not match.
  // Returns true  if label within a json does match and changes.
  //  Value to JSON value.

  void create_label_value(string Label, string Value);
  // Creates a simple Label Value JSON Entry.

  void put_json_in_list(JSON_ENTRY Entry);
  // Moves a JSON Entry into JSON Entry list.

  void put_json_in_set(string Set_Name, JSON_ENTRY Entry);
  // Moves a JSON Entry into JSON Entry set with Set Name.
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
  // Creates an easy to read JSON representation into a string deque.

  void json_print_build_to_string_deque(deque<string> &JSON_Print_Build);
    // Creates a propery formated to read JSON into a string deque.
};


#endif