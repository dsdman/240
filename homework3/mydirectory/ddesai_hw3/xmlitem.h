/****************************************************************
 * Header file for the 'XMLItem' class to contain one XML item.
 *
 * Documentation for this code is in the implementation file.
 *
 * Author/copyright:  Dylan Desai
 * Used with permission and modified by: Dylan Desai
 * Date: 22 September 2017
**/

#ifndef XMLITEM_H
#define XMLITEM_H

//includes and namespaces
#include <iostream>
#include <sstream> //allows for formatting strings in 'ToString' properly
using namespace std;

//define class
class XMLItem {
  public:
    //constructor (default and parameterized) and deconstructor
    XMLItem();
    XMLItem(int level, string item, string which);
    virtual ~XMLItem();

    //accessors should be const since they don't modify the class variables
    int GetLevel() const;
    string GetItem() const;
    string GetWhich() const;
    //setters should have const parameters becuase they change the class's 
    //variables only
    void SetLevel(const int& level);
    void SetItem(const string& item);
    void SetWhich(const string& which);

    string ToString() const;

  private:
    //instance variables
    int level_; 
    string item_; 
    string which_;
};

#endif
