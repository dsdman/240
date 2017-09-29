/****************************************************************
 * Header file for the 'XMLItem' class to contain one XML item.
 *
 * Documentation for this code is in the implementation file.
 *
 * Author/copyright:  Duncan Buell
 * Used with permission and modified by: Dylan Desai
 * Date: 22 September 2017
**/

#ifndef XMLITEM_H
#define XMLITEM_H

//includes and namespaces
#include <iostream>
using namespace std;

class XMLItem {
  public:
    //constructor (default and parameterized) and deconstructor
    XMLItem();
    XMLItem(int level, string item, string which);
    virtual ~XMLItem();
    //ToString method
    string ToString() const;

  private:
};

#endif
