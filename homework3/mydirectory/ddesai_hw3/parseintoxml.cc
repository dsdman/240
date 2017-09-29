#include "parseintoxml.h"
/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'ParseIntoXML' for parsing a parsed sentence into XML format. 
 *
 * Author: Duncan A. Buell
 * Used with permission and modified by: Dylan Desai
 * Date: 22 September 2017
**/

/*
 *constructor
 */
ParseIntoXML::ParseIntoXML() {
}

/*
 *deconstructor
 */
ParseIntoXML::~ParseIntoXML() {
}

/*Function 'FilterInput'.
**This function cleans up the input so it can be parsed more easily.
*/
string ParseIntoXML::FilterInput(const string& the_string) {
  //debugging/tracing 
  #ifdef EBUG
  Utils::log_stream << "enter FilterInput\n"; 
  #endif

  #ifdef EBUG
  Utils::log_stream << "leave FilterInput\n"; 
  #endif
  //output variable
  string out = ""; 

  //Remove parse tags and add spaces after open/closing paren
  out = this->Replace(the_string, "<parse>", "");
  out = this->Replace(out, "</parse>", "");
  out = this->Replace(out, "(", "( ");
  out = this->Replace(out, ")", " ) ");
  
  //now the input can be parsed more easily
  return out;
}

/*Function 'ParseTheFile'.
**This is the function does does the bulk of the work
**Processing and parsing the file into the correct output.
*/
void ParseIntoXML::ParseTheFile(Scanner& in_scanner) {
  //variables to hold data and any temporary input
  string temp_input = "DEFAULT";
  vector<string> input_strings;

  //debugging/tracing 
  #ifdef EBUG
  Utils::log_stream << "enter ParseTheFile\n"; 
  #endif

  //get the input data into a basic string vector and dump it
  input_strings = this->ReadData(in_scanner);
  cout << "original data: " << endl;
  for (int i = 0; i < input_strings.size(); ++i) {
    cout << input_strings.at(i) << endl;
  }
  cout << endl;

  //filter the input 
  for (int i = 0; i < input_strings.size(); ++i) {
    temp_input = this->FilterInput(input_strings.at(i));
    input_strings.at(i) = temp_input;
  }
  cout << "filtired data: " << endl;
  for (int i = 0; i < input_strings.size(); ++i) {
    cout << input_strings.at(i) << endl;
  }

  #ifdef EBUG
  Utils::log_stream << "leave ParseTheFile\n"; 
  #endif
}

/*Function ReadData
 *this is the function that returns a vector of strings from a file
 */
vector<string> ParseIntoXML::ReadData(Scanner& file_scanner) {
  //ouput variable and temporary variable to hold line value
  string temp = "";
  vector<string> out;

  while (file_scanner.HasNext()) {
    temp = file_scanner.NextLine();
    out.push_back(temp);
  }
  out.push_back(temp);
  return out;
}

 /*  Function 'Replace'
 *   Parameters:
 *   the_string - the string to have things replaced in
 *   old_string - the string to replace
 *   new_string - the string to replace with
 *
 *   Returns:
 *   the original string with the replacement made
**/
string ParseIntoXML::Replace(string the_string, string old_string, string 
                             new_string) {
  string return_string = the_string;

  //debugging/tracing 
  #ifdef EBUG
  Utils::log_stream << "enter Replace\n"; 
  #endif

  size_t found = return_string.find(old_string);
  while (found != string::npos) {
    return_string.replace(found, old_string.length(), new_string);
    found = return_string.find(old_string, (found + 1) + new_string.length());
  }

  //debugging/tracing 
  #ifdef EBUG
  Utils::log_stream << "leave Replace\n"; 
  #endif

  return return_string;
}

/* Function Split
 * tolkenizes a string by whitespace.
 */
vector<string> ParseIntoXML::Split(string in_string) const {
  //TODO make this tolkenize a string by whitespace (spaces)
}

/* Function 'ToStringXML'.
 * This function formats an XML 'vector<string>' for prettyprinting. 
 */
string ParseIntoXML::ToStringXML(vector<XMLItem> the_vector) const {
  //return variable
  string out = "";
  #ifdef EBUG
  Utils::log_stream << "enter ToStringXML\n"; 
  #endif
  string s = "";
  #ifdef EBUG
  Utils::log_stream << "leave ToStringXML\n"; 
  #endif
  return out;
}

/* Function 'XMLize'.
** This function takes a string as input and produces a 'vector' of the XML
** that is that string.
*/
vector<XMLItem> ParseIntoXML::XMLize(string in_string) const {

}
