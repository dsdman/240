#include "parseintoxml.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'XMLItem' as a container for one XML item.
 *
 * Author: Dylan Desai
 * Used with permission and modified by: Dylan Desai
 * Date: 22 September 2017
**/

/******************************************************************************
 * Constructor
**/
XMLItem::XMLItem() {
}

/******************************************************************************
 * Parameterized constructor
**/
XMLItem::XMLItem(int level, string item, string which) {
  this->SetItem(item);
  this->SetWhich(which);
  this->SetLevel(level);
}

/******************************************************************************
 * Destructor
**/
XMLItem::~XMLItem() {
}

/******************************************************************************
 * Accessors and Mutators
**/
int XMLItem::GetLevel() const {
  return this->level_;
}
string XMLItem::GetItem() const {
  return this->item_;
}
string XMLItem::GetWhich() const {
  return this->which_;
}
void XMLItem::SetItem(const string& item) {
  this->item_ = item; 
}
void XMLItem::SetLevel(const int& level) {
  this->level_ = level;
}
void XMLItem::SetWhich(const string& which) {
  this->which_ = which;
}

/******************************************************************************
 * Function 'ToString'.
 * This function formats an 'XMLItem' for prettyprinting.
 *
 * Returns:
 *   the prettyprint string for printing
**/
string XMLItem::ToString() const {
  #ifdef EBUG
  Utils::log_stream << "enter ToString\n"; 
  #endif

  //stream for building string and output string
  stringstream temp;
  string out = "";

  //depends on what "which" is (assuming "which" is either "open", "close", 
  //or anything else for returning just the item)
  if (which_ == "open") {
    temp << "<" << this->item_ << " level=\"" << this->level_ << "\">";
  }
  else if(which_ == "close") {
    temp << "</" << this->item_ << ">";
  }
  else {
    //hardcoding the spaces here because I can't get them to work by
    //simply increasing the level
    temp << "  " << this->item_;
  }
  out = temp.str();

  #ifdef EBUG
  Utils::log_stream << "leave ToString\n"; 
  #endif
  return out;
}
