#include "hex.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Hex' as a container for one hex operand.
 *
 * Author: Duncan Buell
 * Used with permission and modified by: Dylan Desai
 * Date: 16 October 2017
**/

/******************************************************************************
 * Constructor
**/
Hex::Hex() {
}

/******************************************************************************
 * Constructor
**/
Hex::Hex(string text, Globals globals) {
  this->Init(text, globals);
}

/******************************************************************************
 * Destructor
**/
Hex::~Hex() {
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * Accessor for 'error_messages_'.
**/
string Hex::GetErrorMessages() const {
  return this->error_messages_;
}

/******************************************************************************
 * Accessor for 'text_'.
**/
string Hex::GetText() const {
}

/******************************************************************************
 * Accessor for 'value_'.
**/
int Hex::GetValue() const {
}

/******************************************************************************
 * Accessor for error flags.
 * The answer to 'has an error' is 'true' iff 'is_invalid_' is true.
**/
bool Hex::HasAnError() const {
}

/******************************************************************************
 * Accessor for 'is_negative_'.
**/
bool Hex::IsNegative() const {
}

/******************************************************************************
 * Accessor for 'is_null_' in the negative.
**/
bool Hex::IsNotNull() const {
}

/******************************************************************************
 * Accessor for 'is_null_' in the positive.
**/
bool Hex::IsNull() const {
}

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Initialization function.
**/
void Hex::Init(string text, Globals globals) {
}

/******************************************************************************
 * Function 'ParseHexOperand'.
 * Parses the text into a decimal value and sets the error flags.
 *
 * The text to be parsed must be exactly five characters long
 * with a plus or minus sign present followed by exactly four
 * legitimate hex digit ASCII characters, with the letters uppercase.
 *
**/
void Hex::ParseHexOperand() {
#ifdef EBUG
  Utils::log_stream << "enter ParseHexOperand" << endl;
#endif

  string hexdigits = "0123456789ABCDEF";

  is_invalid_ = false;

  // All blanks is legal, but if any non-blank, the text must be
  // 5 characters long, and legal characters. We check for legal by
  // a lookup in a string and then test later for invalid.

    // If any of the characters weren't in the lookup we have an error.
    // Otherwise, we can build the decimal equiv of the hex. 

    // Deal with the signum to convert neg values to 2s complement
    // and check that the lead char is either '+' or '-'.

#ifdef EBUG
  Utils::log_stream << "leave ParseHexOperand" << endl;
#endif
}

/******************************************************************************
 * Function 'ToString'.
 * This function formats a 'Hex' for prettyprinting.
 *
 * Returns:
 *   the prettyprint string for printing
**/
string Hex::ToString() const {
#ifdef EBUG
  Utils::log_stream << "enter ToString" << endl; 
#endif
  string s = "";

  if (text_ == "nullhexoperand") {
    s += Utils::Format(".....", 5);
  } else {
    s += Utils::Format(text_, 5);
  }

#ifdef EBUG
  Utils::log_stream << "leave ToString" << endl; 
#endif
  return s;
}
