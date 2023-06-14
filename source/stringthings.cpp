// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: stringthings.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef STRINGTHINGS_CPP
#define STRINGTHINGS_CPP

#include "stringthings.h"

using namespace std;

string char_buf_to_string(char Buf[], int Buf_Len)
{
  string ret_str(Buf, Buf_Len);

  //char response[64];
  //string thing = char_buf_to_string(response, 64);
  //printf ("thing: %c %s \n", response[0], thing.c_str());

  return ret_str;
}

string line_create(int Size, char Character)
{
  string line = "";

  return line.append(Size, Character);
}

string linefill(int size, string text)
// Returns a space filled line of size with text in center.
{
  string line = "";

  line = line.append(size,' ');

  line.replace(((size/2)-(text.length()/2)), text.length(), text);
  line.resize(size);
  return line;
}

string linemerge_left_justify(int size, string line, string text)
// Overlaps and right justifies text onto line.
// Returns value at size of size. 
{
  string return_string = line;

  if (line.size() > text.size())
  {
    return_string.replace(0, text.size(), text);
  }
  else
  {
    return_string = text;
  }

  if((return_string.size() > size) && (size > 0))
  {
    return_string.erase(size, line.size() - size);
  }

  return return_string;
}

string linemerge_left_justify(string line, string text)
// Overlaps and left justifies text onto line.
// No Truncate.
// Returns value at size of line or text size, whichever
//  is larger. 
{
  return linemerge_left_justify(0, line, text);
}

string linemerge_right_justify(int size, string line, string text)
// Overlaps and right justifies text onto line.
// Returns value at size. 
{
  string return_string = line;

  if (line.size() > text.size())
  {
    return_string.replace(line.size() - text.size(), text.size(), text);
  }
  else
  {
    return_string = text;
  }

  if(return_string.size() > size)
  {
    return_string.erase(0, return_string.size() - size);
  }

  return return_string;
}

string right_justify(int size, string text)
// Overlaps and right justifies text onto line.
// Returns value at size. 
{
  string return_string = "";

  if (text.size() > size)
  {
    return_string = text.erase(0, text.size()- size);
  }
  else if (text.size() == size)
  {
    return_string = text;
  }
  else
  {
    return_string = return_string.append(size - text.size() , ' ') + text;
  }

  return return_string;
}

string left_justify(int size, string text)
// Overlaps and left justifies text onto line.
// Returns value at size. 
{
  string return_string = "";

  text.resize(size, ' ');
  return_string = text;

  return return_string;
}

string center_justify(int size, string text)
// Overlaps and left justifies text onto line.
// Returns value at size. 
{
  string return_string = "";

  if (text.size() > size)
  {
    return_string = left_justify(size, text);
  }
  else if (text.size() == size)
  {
    return_string = text;
  }
  else
  {
    return_string.resize(size, ' ');
    return_string.replace(((size/2)-(text.size()/2)), text.size(), text);
  }

  return return_string;
}

 
string left_trim(const string &Text)
{
  //const std::string WHITESPACE = " \n\r\t\f\v";
  size_t start = Text.find_first_not_of(" \n\r\t\f\v");
  return (start == string::npos) ? "" : Text.substr(start);
}
 
string right_trim(const string &Text)
{
  size_t end = Text.find_last_not_of(" \n\r\t\f\v");
  return (end == string::npos) ? "" : Text.substr(0, end + 1);
}
 
string trim(const string &Text) 
{
  return right_trim(left_trim(Text));
}

string quotify(string Text)
{
  return "\"" + Text + "\"";
}

//string to_string_hex(I w, size_t hex_len = sizeof(I)<<1) 
string to_string_hex(char Char_Byte) 
{
  static const char* digits = "0123456789ABCDEF";
  
  string ret_number = "";

  int d1 = (Char_Byte % 256 - Char_Byte % 16) / 16;
  int d2 = Char_Byte % 16;
  
  ret_number = digits[d1];
  ret_number = ret_number + digits[d2];

  return ret_number;
}

string to_string_binary(char Char_Byte)
{
  string ret_number = "";

  ret_number =  to_string(get_bit_value(Char_Byte, 128)) + 
                to_string(get_bit_value(Char_Byte, 64)) + 
                to_string(get_bit_value(Char_Byte, 32)) + 
                to_string(get_bit_value(Char_Byte, 16)) + 
                to_string(get_bit_value(Char_Byte, 8)) + 
                to_string(get_bit_value(Char_Byte, 4)) + 
                to_string(get_bit_value(Char_Byte, 2)) + 
                to_string(get_bit_value(Char_Byte, 1));

  return ret_number;
}

bool left_of_char(string Text, char Break_Char, string &Left)
{
  bool ret_success = true;

  int pos = Text.find(Break_Char);

  if (pos == string::npos)
  {
    ret_success = false;
  }
  else
  {
    Left = Text.substr(0, pos);
  }

  return ret_success;
}

bool right_of_char(string Text, char Break_Char, string &Right)
{
  bool ret_success = true;

  int pos = Text.find(Break_Char);

  if (pos == string::npos)
  {
    ret_success = false;
  }
  else
  {
    Right = Text.substr(pos +1, Text.size() - pos -1);
  }

  return ret_success;
}

string remove_first_and_last_characters(char Character, string Text)
{
  Text = trim(Text);
  if (Text.size() > 1)
  {
    if (Text[0] == Character)
    {
      if (Text[Text.size() -1] == Character)
      {
        Text = Text.substr(1, Text.size() -2);
      }
    }
  }
  return Text;
}

bool string_to_int(string String_Value, int &Int_Value)
{
  try
  {
    Int_Value = stoi(String_Value);
    return true;
  }
  catch(const std::exception& e)
  {
    Int_Value = 0;
    return false;
  }
}

int string_to_int(string String_Value)
{
  int tmp_int = 0;
  string_to_int(String_Value, tmp_int);
  return tmp_int;
}

bool string_hex_to_int(string Hex_String_Value, int &Int_Value)
{
  try
  {
    Int_Value = stoi(Hex_String_Value, 0, 16);
    return true;
  }
  catch(const std::exception& e)
  {
    Int_Value = 0;
    return false;
  }
}

int string_hex_to_int(string Hex_String_Value)
{
  int tmp_int = 0;
  string_hex_to_int(Hex_String_Value, tmp_int);
  return tmp_int;
}

bool string_to_ulong(string String_Value, unsigned long &Unsigned_Long_Value)
{
  try
  {
    //Long_Value = strtol(String_Value, NULL, 10);
    Unsigned_Long_Value = stoul(String_Value);
    return true;
  }
  catch(const std::exception& e)
  {
    Unsigned_Long_Value = 0;
    return false;
  }
}

unsigned long string_to_ulong(string String_Value)
{
  unsigned long tmp_ulong = 0;
  string_to_ulong(String_Value, tmp_ulong);
  return tmp_ulong;
}

bool string_to_ulonglong(string String_Value, unsigned long long &Unsigned_Long_Long_Value)
{
  try
  {
    Unsigned_Long_Long_Value = stoull(String_Value);
    return true;
  }
  catch(const std::exception& e)
  {
    Unsigned_Long_Long_Value = 0;
    return false;
  }
}

unsigned long long string_to_ulonglong(string String_Value)
{
  unsigned long long tmp_ulonglong = 0;
  string_to_ulonglong(String_Value, tmp_ulonglong);
  return tmp_ulonglong;
}

bool string_to_float(string String_Value, float &Float_Value)
{
  try
  {
    Float_Value = stof(String_Value);
    return true;
  }
  catch(const std::exception& e)
  {
    Float_Value = 0;
    return false;
  }
}

float string_to_float(string String_Value)
{
  float tmp_float = 0;
  string_to_float(String_Value, tmp_float);
  return tmp_float;
}

string to_string_round_to_nth(float Value, int nth)
{
  string ret_string = to_string(Value);

  int pos = ret_string.find('.');

  if (pos != string::npos)
  {
    if (pos + nth +1 <= ret_string.size())
    {
      ret_string.erase(pos + nth +1, ret_string.size() - (pos + nth));
    }
  }
  
  return ret_string;
}

int color_range(float Value, int Magenta, int Red, int Yellow, int Green, int Blue)
// Returns color in ranges of 1st to 5th of values
// eg (12, 5, 10, 15, 20, 25) returns color yellow
// Non zero or mid level green.
{ 
  // 1 - Range Level
  // Magenta  Red  Yellow  Green  Blue  Cyan

  if (Value <= Magenta)
  {
    return COLOR_MAGENTA;
  }
  else if(Value <= Red)
  {
    return COLOR_RED;
  }
  else if(Value <= Yellow)
  {
    return COLOR_YELLOW;
  }
  else if(Value <= Green)
  {
    return COLOR_GREEN;
  }
  else if(Value <= Blue)
  {
    return COLOR_BLUE;
  }
  else
  {
    return COLOR_CYAN;
  }
}

int color_range_reverse(float Value, int Blue, int Green, int Yellow, int Red, int Magenta)
// Returns color in ranges of 1st to 5th of values
// eg (12, 5, 10, 15, 20, 25) returns color yellow
// Non zero or mid level green.
{ 
  // 1 - Range Level
  // Magenta  Red  Yellow  Green  Blue  Cyan

  if (Value <= Blue)
  {
    return COLOR_BLUE;
  }
  else if(Value <= Green)
  {
    return COLOR_GREEN;
  }
  else if(Value <= Yellow)
  {
    return COLOR_YELLOW;
  }
  else if(Value <= Red)
  {
    return COLOR_RED;
  }
  else if(Value <= Magenta)
  {
    return COLOR_MAGENTA;
  }
  else
  {
    return COLOR_CYAN;
  }
}

int color_scale(float Value, int Green, int Yellow, int Red, int Magenta, int Blue)
// Returns color in ranges of 1st to 5th of values
// eg (12, 5, 10, 15, 20, 25) returns color red
// zero level green.
{ 
  // 2 - Scale Level
  // Green  Yellow  Red  Magenta  Blue  Cyan
  
  if (Value <= Green)
  {
    return COLOR_GREEN;
  }
  else if(Value <= Yellow)
  {
    return COLOR_YELLOW;
  }
  else if(Value <= Red)
  {
    return COLOR_RED;
  }
  else if(Value <= Magenta)
  {
    return COLOR_MAGENTA;
  }
  else if(Value <= Blue)
  {
    return COLOR_BLUE;
  }
  else
  {
    return COLOR_CYAN;
  }
}

void STRING_STRING::store(string str_value)
{
  STR_VALUE = str_value;
  if(str_value == "")
  {
    CONVERSION_SUCCESS = false;
  }
  else
  {
    CONVERSION_SUCCESS = true;
  }
}

string STRING_STRING::get_str_value()
// Return original number string value.
{
  return STR_VALUE;
}

bool STRING_STRING::conversion_success()
// Returns true if conversion was unsucessful.
{
  return CONVERSION_SUCCESS;
}

void STRING_INT::store(string str_value)
{
  STR_VALUE = str_value;
  CONVERSION_SUCCESS = string_to_int(str_value, INT_VALUE);
}

string STRING_INT::get_str_value()
// Return original number string value.
{
  return STR_VALUE;
}

int STRING_INT::get_int_value()
// Return converted number string value.
{
  return INT_VALUE;
}

bool STRING_INT::conversion_success()
// Returns true if conversion was unsucessful.
{
  return CONVERSION_SUCCESS;
}

void STRING_FLOAT::store(string str_value)
{
  STR_VALUE = str_value;
  CONVERSION_SUCCESS = string_to_float(str_value, FLOAT_VALUE);
}

string STRING_FLOAT::get_str_value()
// Return original number string value.
{
  return STR_VALUE;
}

float STRING_FLOAT::get_float_value()
// Return converted number string value.
{
  return FLOAT_VALUE;
}

int STRING_FLOAT::get_int_value()
// Return converted number string value.
{
  return FLOAT_VALUE;
}

bool STRING_FLOAT::conversion_success()
// Returns true if conversion was unsucessful.
{
  return CONVERSION_SUCCESS;
}




#endif