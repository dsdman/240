#include "parseintoxml.h"
/******************************************************************************
 *
 * Class 'ParseIntoXML' for parsing a parsed sentence into XML format. 
 *
 * Author: Dylan Desai
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

  //output variable
  string out = ""; 

  //Remove parse tags and add spaces after open/closing paren
  out = this->Replace(the_string, "<parse>", "");
  out = this->Replace(out, "</parse>", "");
  out = this->Replace(out, "(", "( ");
  out = this->Replace(out, ")", " ) ");
  
  #ifdef EBUG
  Utils::log_stream << "leave FilterInput\n"; 
  #endif

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
  vector<XMLItem> xml_strings;
  vector< vector<XMLItem> > xml_string_holder;
  string xml_data = "";

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
  cout << endl;

  //xmlize each of the strings
  for (int i = 0; i < input_strings.size(); ++i) {
    xml_strings = this->XMLize(input_strings.at(i));
    xml_string_holder.push_back(xml_strings);
  }
  for (int i = 0; i < xml_string_holder.size(); ++i) {
    xml_data += this->ToStringXML(xml_string_holder.at(i));
  }

  //the program is done
  cout << xml_data << endl;

  #ifdef EBUG
  Utils::log_stream << "leave ParseTheFile\n"; 
  #endif
}

/*Function ReadData
 *this is the function that returns a vector of strings from a file
 */
vector<string> ParseIntoXML::ReadData(Scanner& file_scanner) {
  //output variable and temporary variable to hold line value
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

  #ifdef EBUG
  Utils::log_stream << "leave Replace\n"; 
  #endif

  return return_string;
}

/* Function 'ToStringXML'.
 * This function formats an XML 'vector<string>' for prettyprinting. 
 */
string ParseIntoXML::ToStringXML(vector<XMLItem> the_vector) const {
  #ifdef EBUG
  Utils::log_stream << "enter ToStringXML\n"; 
  #endif

  //return variable
  string out = "";

  //add spaces depending on the level, then print the xml
  for (int i = 0; i < the_vector.size(); ++i) {
    for (int j = 0; j < the_vector.at(i).GetLevel(); ++j) {
      out += "  ";
    }
    out += the_vector.at(i).ToString();
    out += "\n";
  }

  #ifdef EBUG
  Utils::log_stream << "leave ToStringXML\n"; 
  #endif
  //the string should now be indented properly
  return out;
}

/* Function 'XMLize'.
** This function takes a string as input and produces a 'vector' of the XML
** that is that string.
*/
vector<XMLItem> ParseIntoXML::XMLize(string in_string) const {
  //temporary variables for the XMLItem building
  string tolken = "";
  int level = 0;
  string item = "";
  string which = "";
  XMLItem the_item;
  //scanner for reading through the string
  ScanLine scanner; 
  scanner.OpenString(in_string);
  //containers: stack to hold end tags and vector for the return variable
  stack<XMLItem> end_tags;
  vector<XMLItem> out;

  //walk through the line by token
  while (scanner.HasNext()) {
    //grab the next tolken and decide what to do based on what it is
    tolken = scanner.Next();
    if (tolken == "(") {
      //grab the level, item, and which 
      ++level;
      item = scanner.Next();
      which = "open";
      //create and push the xmlItem as well as push end tag for 
      //the corresponding item
      the_item = XMLItem(level, item, which);
      //cout << the_item.ToString() << endl;
      out.push_back(the_item);
      the_item = XMLItem(level, item, "close");
      //cout << the_item.ToString() << endl;
      end_tags.push(the_item);
    }
    else if (tolken == ")") {
      //Return the end tag by popping the top of the stack and decrement 
      //the level 
      the_item = end_tags.top();
      out.push_back(the_item);
      end_tags.pop();
      --level;
    }
    else {
      item = tolken;
      which = "";
      the_item = XMLItem(level, item, which);
      //cout << the_item.ToString() << endl;
      out.push_back(the_item);
    }
  }

  //the vector now contains XML of the string
  return out;
}
