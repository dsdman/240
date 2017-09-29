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
    //constructor and deconstructor
    ParseIntoXML(); 
    virtual ~ParseIntoXML();

    //functions that read data and do the parsing
    void ParseTheFile(Scanner& in_scanner);

  private:
    //cleans up the string
    string FilterInput(const string& the_string);
    //intuitive replace function
    string Replace(string the_string, string old_string, string new_string); 
    //returns the "pretty" string of xml given a vector of data
    string ToStringXML(vector<XMLItem> the_vector) const;
    //splits a string into tolkens
    vector<string> Split(string in_string) const;
    //reads the data from a file opened from a scanner
    vector<string> ReadData(Scanner& file_scanner);
    //returns vector of data from a string
    vector<XMLItem> XMLize(string in_string) const;
};
#endif
