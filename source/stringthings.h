// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: stringthings.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef STRINGTHINGS_H
#define STRINGTHINGS_H

// Standard Header Files
#include <string>
#include <deque>

// Optional Includes
#include <ncurses.h>

using namespace std;

class WORDLINE
{
  private:
  deque<string> words;

  public:
  bool empty();
  int size();
  string pop();
  void storeline(string strLine);
};

string line_create(int Size, char Character);
// Returns an character filled line of Size.

string linefill(int size, string text);
// is broken
// Returns a space filled line of size with text in center.

string linemerge(int size, string line, string text);
// Overlaps and centers text onto line.
// Returns value at size. 

string linemerge_left_justify(int size, string line, string text);
// Overlaps and right justifies text onto line.
// Returns value at size of size. 

string linemerge_left_justify(string line, string text);
// Overlaps and left justifies text onto line.
// No Truncate.
// Returns value at size of line or text size, whichever
//  is larger.

string linemerge_right_justify(int size, string line, string text);
// Overlaps and right justifies text onto line.
// Returns value at size. 

string right_justify(int size, string text);
// Overlaps and right justifies text onto line.
// Returns value at size. 

string left_justify(int size, string text);
// Overlaps and left justifies text onto line.
// Returns value at size. 

string center_justify(int size, string text);
// Overlaps and left justifies text onto line.
// Returns value at size. 

string left_trim(const string &Text);
// Remove leading spaces and special characters from text.

string right_trim(const string &Text);
// Remove trailing spaces and special characters from text.

string trim(const string &Text);
// Remove leading and trailing spaces and special characters from text.

bool string_to_int(string String_Value, int &Int_Value);
// Convert in String_Value number to out Int_Value.
//  Returns true if value sucessful.

int string_to_int(string String_Value);

bool string_to_ulong(string String_Value, unsigned long &Unsigned_Long_Value);
// Convert in String_Value number to out Int_Value.
//  Returns true if value sucessful.

unsigned long string_to_ulong(string String_Value);

bool string_to_ulonglong(string String_Value, unsigned long long &Unsigned_Long_Long_Value);
// Convert in String_Value number to out Int_Value.
//  Returns true if value sucessful.

unsigned long long string_to_ulonglong(string String_Value);

bool string_to_float(string String_Value, float &Float_Value);

float string_to_float(string String_Value);
// Convert in String_Value number to out Float_Value.
//  Returns true if value sucessful.

//string to_string_round_to_nth(float Value, int nth);

int color_range(float Value, int Magenta, int Red, int Yellow, int Green, int Blue);
// Returns color in ranges of 1st to 5th of values
// eg (12, 5, 10, 15, 20, 25) returns color yellow
// Non zero or mid level green.

int color_scale(float Value, int Green, int Yellow, int Red, int Magenta, int Blue);
// Returns color in ranges of 1st to 5th of values
// eg (12, 5, 10, 15, 20, 25) returns color red
// zero level green.

class STRING_STRING
// Variable stores original string number and converted value.
// Sets error if conversion unsucessful.
{
  private:
  string  STR_VALUE = "";
  bool    CONVERSION_SUCCESS = false;

  public:

  void store(string str_value);

  string get_str_value();

  bool conversion_success();

};

class STRING_INT
// Variable stores original string number and converted value.
// Sets error if conversion unsucessful.
{
  private:
  string  STR_VALUE = "";
  int     INT_VALUE = 0;
  bool    CONVERSION_SUCCESS = false;

  public:
  void store(string str_value);

  string get_str_value();

  int get_int_value();

  bool conversion_success();

};

class STRING_FLOAT
// Variable stores original string number and converted value.
// Sets error if conversion unsucessful.
{
  private:
  string  STR_VALUE = "";
  float   FLOAT_VALUE = 0;
  bool    CONVERSION_SUCCESS = false;

  public:
  void store(string str_value);
  
  string get_str_value();

  float get_float_value();

  int get_int_value();

  bool conversion_success();
};


#endif