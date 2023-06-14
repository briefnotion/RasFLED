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

// Rasfled Includes
#include "helper.h"

using namespace std;

string char_buf_to_string(char* Buf, int Buf_Len);

string line_create(int Size, char Character);
// Returns an character filled line of Size.

string linefill(int size, string text);
// is broken
// Returns a space filled line of size with text in center.

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

string quotify(string Text);
// Put quotes around string;

string to_string_hex(char Char_Byte);
// Returns string two byte hex value from byte.

string to_string_binary(char Char_Byte);
// Returns 8 bit binary value from byte.

bool left_of_char(string Text, char Break_Char, string &Left);
// Returns left of Break_Char as Left;
// Returns true if Break_Char exist.

bool right_of_char(string Text, char Break_Char, string &Right);
// Returns right of Break_Char as Right;
// Returns true if Break_Char exist.

string remove_first_and_last_characters(char Character, string Text);
// For removing things like start and ending quotes.
// Value will be trimmed.

bool string_to_int(string String_Value, int &Int_Value);
// Convert in String_Value number to out Int_Value.
//  Returns true if value sucessful.

int string_to_int(string String_Value);
// Convert in String_Value number to out int.
//  Returns Integer Value

bool string_hex_to_int(string String_Value, int &Int_Value);
// Convert in String_Value number to out Int_Value.
//  Returns true if value sucessful.

int string_hex_to_int(string String_Value);
// Convert in String_Value number to out int.
//  Returns Integer Value

bool string_to_ulong(string String_Value, unsigned long &Unsigned_Long_Value);
// Convert in String_Value number to out Int_Value.
//  Returns true if value sucessful.

unsigned long string_to_ulong(string String_Value);
// Convert in String_Value number to out ulong.
//  Returns Unsigned Long Value

bool string_to_ulonglong(string String_Value, unsigned long long &Unsigned_Long_Long_Value);
// Convert in String_Value number to out Unsigned_Long_Long_Value.
//  Returns true if value sucessful.

unsigned long long string_to_ulonglong(string String_Value);
// Convert in String_Value number to out Unsigned_Long_Long_Value.
//  Returns true if value sucessful.
// ! No Error Checking

bool string_to_float(string String_Value, float &Float_Value);
// Convert in String_Value number to out Float_Value.
//  Returns true if value sucessful.

float string_to_float(string String_Value);
// Convert in String_Value number to out Float_Value.
//  Returns true if value sucessful.
// ! No Error Checking

string to_string_round_to_nth(float Value, int nth);
// Returns string of float rounded to nth decimal.

int color_range(float Value, int Magenta, int Red, int Yellow, int Green, int Blue);
// Returns color in ranges of 1st to 5th of values
// eg (12, 5, 10, 15, 20, 25) returns color yellow
// Non zero or mid level green.

int color_range_reverse(float Value, int Blue, int Green, int Yellow, int Red, int Magenta);
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