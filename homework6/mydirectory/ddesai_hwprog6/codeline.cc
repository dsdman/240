#include "codeline.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'CodeLine' as a container for one line of code.
 *
 * Author: Duncan A. Buell
 * Used with permission and modified by: Dylan Desai
 * Date: 04 Dec 2017
**/

/******************************************************************************
 * Constructor
**/
CodeLine::CodeLine() {
}

CodeLine::CodeLine(Globals globals) {
  globals_ = globals;
}

/******************************************************************************
 * Destructor
**/
CodeLine::~CodeLine() {
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * Accessor for the 'addr_'.
**/
string CodeLine::GetAddr() const {
  return addr_;
}

/******************************************************************************
 * Accessor for the 'code_'.
**/
string CodeLine::GetCode() const {
  return code_;
}

/******************************************************************************
 * Accessor for the 'comments_'.
**/
string CodeLine::GetComments() const {
  return comments_;
}

/******************************************************************************
 * Accessor for the 'error_messages_'.
**/
string CodeLine::GetErrorMessages() const {
  return error_messages_;
}

/******************************************************************************
 * Accessor for the 'error_messages_'.
**/
int CodeLine::GetPC() const {
  return pc_;
}

/******************************************************************************
 * Accessor for the 'hex_'.
**/
Hex CodeLine::GetHexObject() const {
  return hex_;
}

/******************************************************************************
 * Accessor for the 'label_'.
**/
string CodeLine::GetLabel() const {
  return label_;
}

/******************************************************************************
 * Accessor for the 'mnemonic_'.
**/
string CodeLine::GetMnemonic() const {
  return mnemonic_;
}

/******************************************************************************
 * Accessor for the 'symoperand_'.
**/
string CodeLine::GetSymOperand() const {
  return symoperand_;
}

/******************************************************************************
 * Boolean indicator of the presence of a label.
**/
bool CodeLine::HasLabel() const {
  if (label_ != "nulllabel") {
    return true;
  } else {
    return false;
  }
}

/******************************************************************************
 * Boolean indicator of the presence of a symbolic operand.
**/
bool CodeLine::HasSymOperand() const {
  if (symoperand_ != "nullsymoperand") {
    return true;
  } else {
    return false;
  }
}

/******************************************************************************
 * Accessor for 'is_all_comment_'.
**/
bool CodeLine::IsAllComment() const {
  return is_all_comment_;
}

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'SetCodeLine'.
 * Sets the values for a line of code that isn't all comments.
 *
 * Parameters:
 *   linecounter - the line counter for this line in source
 *   pc - the program counter if it is there
 *   label - the label if it is there
 *   mnemonic - the mnemonic of the opcode
 *   addr - the direct/indirect addresssing asterisk
 *   symoperand - the symbolic operand if it is there
 *   hexoperand - the hexoperand if it is there
 *   comments - comments if any
**/
void CodeLine::SetCodeLine(int linecounter, int pc, string label,
                           string mnemonic, string addr, string symoperand,
                           string hexoperand, string comments, string code) {
  
  is_all_comment_ = false;
  linecounter_ = linecounter;
  pc_ = pc;
  label_ = label;
  mnemonic_ = mnemonic;
  addr_ = addr;
  if (symoperand.size() < 3) {
    if (symoperand.size() == 1) {
      symoperand += "  ";
    } else {
      symoperand += " ";
    }
  }
  symoperand_ = symoperand;
  Hex temp(hexoperand, globals_);
  hex_ = temp;
  comments_ = comments;
  code_ = code;
}

/******************************************************************************
 * Function 'SetCommentsOnly'.
 * Sets a line of code that is all comments.
 *
 * Parameters:
 *   line - the code line that is taken to be all comments
**/
void CodeLine::SetCommentsOnly(int linecounter, string line) {
  //the comment is the whole line
  is_all_comment_ = true;
  linecounter_ = linecounter;
  comments_ = line;

  //everything else at defaults
  pc_ = 0;
  label_ = "nulllabel"; 
  mnemonic_ = "nullmnemonic";
  addr_ = " ";
  symoperand_ = "nullsymoperand";
  string hexoperand = "     ";
  Hex temp(hexoperand, globals_);
  hex_ = temp;
  code_ = "nullcode";
}

/******************************************************************************
 * Function 'SetErrorMessages'.
 * Sets the 'error_messages_' variable for later printing.
 *
 * Parameters:
 *   messages - the string of messages
**/
void CodeLine::SetErrorMessages(string messages) {
}

/******************************************************************************
 * Function 'SetMachineCode'.
 * Set the 'code_' for this line of code.
 *
 * Parameters:
 *   code - the code to set
**/
void CodeLine::SetMachineCode(string code) {
  if (code.size() == 16) {
    code_ = code;
  }
}

/******************************************************************************
 * Function 'SetPC'.
 * Set the PC for this line of code.
 *
 * Parameters:
 *   what - the value to set as the PC
**/
void CodeLine::SetPC(int what) {
  pc_ = what;
}

/******************************************************************************
 * Function 'ToString'.
 * This function formats a 'CodeLine' for prettyprinting.
 *
 * Returns:
 *   the prettyprint string for printing
**/
string CodeLine::ToString() const
{
#ifdef EBUG
  Utils::log_stream << "enter ToString\n"; 
#endif
  string s = "";

  s += Utils::Format(linecounter_, 5) + " ";

  s += Utils::Format(pc_, 4) + "  ";
  s += globals_.DecToBitString(pc_, 12) + " ";

  if (code_ == "nullcode") {
  //if (code_ != "nullcode") {
    s += Utils::Format("xxxx xxxx xxxx xxxx", 19);
  } else {
    s = s       + Utils::Format((code_).substr( 0, 4), 4)
          + " " + Utils::Format((code_).substr( 4, 4), 4)
          + " " + Utils::Format((code_).substr( 8, 4), 4)
          + " " + Utils::Format((code_).substr(12, 4), 4);
  }

  if (label_ == "nulllabel") {
    s += " " + Utils::Format("...", 3);
  } else {
    s += " " + Utils::Format(label_, 3);
  }

  if (mnemonic_ == "nullmnemonic") {
    s += " " + Utils::Format("...", 3);
  } else {
    s += " " + Utils::Format(mnemonic_, 6);
  }

  if (addr_ == "*") {
    s += " " + Utils::Format("*", 1);
  } else {
    s += " " + Utils::Format(" ", 1);
  }

  if (symoperand_ == "nullsymoperand") {
    s += " " + Utils::Format("...", 3);
  } else {
    s += " " + Utils::Format(symoperand_, 3);
  }

  if (!(hex_.IsNotNull())) {
    s += " " + Utils::Format(".....", 5);
  } else {
    s += " " + hex_.ToString();
  }

  if (comments_ != "nullcomments") {
    if (is_all_comment_) {
      s = Utils::Format(linecounter_, 5) + " ";
      //s += Utils::Format(" ", 41);
      s += Utils::Format(" ", 42);
      s += " " + comments_;
    } else {
      s += " " + comments_;
    }
  }

  if ((error_messages_.length() > 0) && (error_messages_ != "nullerrormessages")) {
    s += error_messages_;
  }

#ifdef EBUG
  Utils::log_stream << "leave ToString\n"; 
#endif
  return s;
}
