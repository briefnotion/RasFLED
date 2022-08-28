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

#include "stringthings.h"

using namespace std;


bool WORDLINE::empty()
{
  return words.empty();
}

int WORDLINE::size()
{
  return words.size();
}

string WORDLINE::pop()
{
  string word = "";
  if(words.empty() == false)
  {
    word = words.front();
    words.pop_front();
  }
  return word;
}

void WORDLINE::storeline(string strLine)
{
  int c1 = 0;
  string word = "";
  bool juststop = false;

  while((strLine.length() > 0) && (juststop == false))
  {
    c1 = strLine.find(" ");

    if(c1==std::string::npos)
    {
      c1 = strLine.length();
      juststop = true;
    }

    if (c1 > 0)
    {
      word = strLine.substr(0,c1).c_str();
      
      if(word.length()>0)
      {
        words.push_back(word);
      }
    }

    if(juststop == false)
    {
      strLine = strLine.substr(c1+1,strLine.length()-(c1+1));
    }
  }
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

string linemerge(int size, string line, string text)
// Overlaps and centers text onto line.
// Returns value at size. 
{
  int text_size = text.length();
  
  if (text_size > size)
  {
    text.resize(size);
    text_size = text.length();
  }

  line.replace(((size/2)-(text_size/2)), text_size, text);
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
    return_string = return_string.append(size - text.size() ,' ') + text;
  }

  return return_string;
}

string left_justify(int size, string text)
// Overlaps and left justifies text onto line.
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
    return_string = text + return_string.append(size - text.size() ,' ');
  }

  return return_string;
}

bool string_to_int(string String_Value, int &Int_Value)
// Convert in String_Value number to out Int_Value.
//  Returns true if value sucessful.
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

bool string_to_ulong(string String_Value, unsigned long &Unsigned_Long_Value)
// Convert in String_Value number to out Int_Value.
//  Returns true if value sucessful.
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
// Convert in String_Value number to out Int_Value.
//  Returns true if value sucessful.
{
  try
  {
    //Long_Value = strtol(String_Value, NULL, 10);
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
// Convert in String_Value number to out Float_Value.
//  Returns true if value sucessful.
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

bool STRING_FLOAT::conversion_success()
// Returns true if conversion was unsucessful.
{
  return CONVERSION_SUCCESS;
}