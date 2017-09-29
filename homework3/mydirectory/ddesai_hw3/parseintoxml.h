/****************************************************************
 * Header file for the class to parse a sentence into an XML
 # version.
 *
 * Documentation for this code is in the implementation file. 
 * NOTE: I couldn't find this file, so I'll comment to make sense of it
 *
 * Author/copyright:  Duncan Buell
 * Used with permission and modified by: Dylan Desai
 * Date: 22 September 2017
**/

#ifndef PARSEINTOXML_H
#define PARSEINTOXML_H

//boilerplate includes and namespaces
#include <iostream>
#include <set>
#include <vector>
#include <stack>
using namespace std;

//utils
#include "../../Utilities/scanner.h"
#include "../../Utilities/scanline.h"

//class for storing data in the input
#include "xmlitem.h"


//Functions
class ParseIntoXML {
  public:
    ParseIntoXML(); 
    virtual ~ParseIntoXML();

    void ParseTheFile(Scanner& in_scanner);

  private:
    //returns a vector containing data from an opened scanner
    vector<string> ReadData(Scanner& file_scanner);
    //adds space after paren from an opened line scanner
    string SplitParen(ScanLine& line);
    //checks whether a string contains a substring
    bool Contains(const string& the_string, const string& substring);
    //returns the index of the beginning of the a substring
    int IndexOf(const string& the_string, const string& substring);
    string FilterInput(string& the_string);
    string Replace(string the_string, string old_string, string new_string); 
    string ToStringXML(vector<XMLItem> the_vector) const;
    vector<string> Split(string in_string) const;
    vector<XMLItem> XMLize(string in_string) const;
};
#endif
