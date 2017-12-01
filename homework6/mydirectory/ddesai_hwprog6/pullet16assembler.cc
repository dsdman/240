#include "pullet16assembler.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Assembler' for assembling code.
 *
 * Author: Duncan A. Buell
 * Used with permission and modified by: Dylan Desai
 * Date: 13 Nov 2017
**/

/******************************************************************************
 * Constructor
**/
Assembler::Assembler() {
  globals_ = Globals();

}

/******************************************************************************
 * Destructor
**/
Assembler::~Assembler() {
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'GetCode'
 * This function returns a vector of 'CodeLine' From a file scanner
 *
 * Parameters:
 *  in_scanner - the scanner to read for source code
**/
vector<CodeLine> Assembler::GetCode(Scanner& in_scanner) {
  //temporary variables to create instance of 'CodeLine'
  string line = "dummyline";
  int linecounter = 1;
  CodeLine temp;
  int pc = -1;
  maxpc_ = -1;
  //output variable
  vector<CodeLine> out;

  //get metainfo for instance of 'CodeLine' if line size is not zero
  cout << "RAW FILE CODE: " << endl;
  while (line.size() > 0) {
    //temporary variables for instance of codeline
    string label = "nulllabel"; 
    string mnemonic = "nullmnemonic";
    string addr = " ";
    string symoperand = "nullsymoperand";
    string hexoperand = "     ";
    string comments = "nullcomments";
    string code = "nullcode";

    //get line
    line = in_scanner.NextLine();
    cout << line << endl;
    if (line.size() != 0) {
      //the whole thing is a comment
      if (line.at(0) == '*') {
        temp.SetCommentsOnly(linecounter, line);
        out.push_back(temp);
      } else {
        //increment program counters
        ++pc;
        ++maxpc_;

        //get the label
        label = line.substr(0,3);
        if (label == "   ") {
          label = "nulllabel";
        }
        //get the opcode
        mnemonic = line.substr(4,3);
        if (mnemonic == "   ") {
          mnemonic = "nullmnemonic";
        }
        //rest of data if the mnemonic is not a 'STP' or (english or) 'END'
        if (mnemonic != "STP" && mnemonic != "END") {
          if (line.size() > 7) {
            addr = line.substr(8,1);
            if (addr != "*") {
              addr = " ";
            }
          }
          //get the symbolic operand
          if (line.size() > 9) {
            symoperand = line.substr(10,3);
            if (symoperand == "   ") {
              symoperand = "nullsymoperand";
            }
          }
          //get the hex operand
          if (line.size() > 13) {
            hexoperand = line.substr(14,5);
            if (hexoperand == "    ") {
              hexoperand = "     ";
            }
          }
          //get the commments
		      if (line.size() > 19) {
            comments = line.substr(20);
            if (comments.at(0) != '*') {
            comments = "nullcomments";
            }
		      }
        }

        //put together the codeline
        temp.SetCodeLine(linecounter, pc, label, mnemonic, addr, 
                         symoperand, hexoperand, comments, code);
        out.push_back(temp);
      }
    }
    linecounter += 1;
  }
  return out;
}

/******************************************************************************
 * Function 'Assemble'.
 * This top level function assembles the code.
 *
 * Parameters:
 *   in_scanner - the scanner to read for source code
 *   out_stream - the output stream to write to
**/
void Assembler::Assemble(Scanner& in_scanner, string binary_filename, 
                         ofstream& out_stream) {
#ifdef EBUG
  Utils::log_stream << "enter Assemble\n"; 
#endif
  //grab the codeLines
  codelines_ = this->GetCode(in_scanner);

  ////////////////////////////////////////////////////////////////////////////
  // Pass one
  // Produce the symbol table and detect errors in symbols.
  Utils::log_stream << endl << endl << "PASS ONE" << endl;
  this->PassOne(in_scanner);

  ////////////////////////////////////////////////////////////////////////////
  // Pass two
  // Generate the machine code.
  Utils::log_stream << endl << endl << "PASS TWO" << endl;
  this->PassTwo();

  ////////////////////////////////////////////////////////////////////////////
  // Dump the results.
  cout << "\nAS 'CODELINES:' " << endl;
  this->PrintCodeLines();
  //this->PrintSymbolTable(); I DON'T NEED THIS SINCE I DID THIS IN 'PassOne'

#ifdef EBUG
  Utils::log_stream << "leave Assemble\n"; 
#endif
}

/******************************************************************************
 * Function 'GetInvalidMessage'.
 * This creates a "value is invalid" error message.
 *
 * Parameters:
 *   leadingtext - the text of what it is that is invalid
 *   symbol - the symbol that is invalid
**/
string Assembler::GetInvalidMessage(string leadingtext, string symbol) {
  string returnvalue = "Value " + symbol + " is an invalid " + leadingtext;

  return returnvalue;
}

/******************************************************************************
 * Function 'GetInvalidMessage'.
 * This creates a "value is invalid" error message.
 *
 * Parameters:
 *   leadingtext - the text of what it is that is invalid
 *   hex - the hex operand that is invalid
**/
string Assembler::GetInvalidMessage(string leadingtext, Hex hex) {
  string returnvalue = "Value " + hex.ToString() + " is an invalid " + leadingtext;

  return returnvalue;
}

/******************************************************************************
 * Function 'GetUndefinedMessage'.
 * This creates a "symbol is undefined" error message.
 *
 * Parameters:
 *   badtext - the undefined symbol text
**/
string Assembler::GetUndefinedMessage(string badtext) {
  string returnvalue = "Symbol " + badtext + " is undefined";
  return returnvalue;
}

/******************************************************************************
 * Function 'PassOne'.
 * Produce the symbol table and detect multiply defined symbols.
 *
 * CAVEAT: We have deliberately forced symbols and mnemonics to have
 *         blank spaces at the end and thus to be all the same length.
 *         Symbols are three characters, possibly with one or two blank at end.
 *         Mnemonics are three characters, possibly with one blank at end.
 *
 * Parameters:
 *   in_scanner - the input stream from which to read
 *   out-stream - the output stream to which to write
**/
void Assembler::PassOne(Scanner& in_scanner) {
#ifdef EBUG
  Utils::log_stream << "enter PassOne\n"; 
#endif

  //temporary label variable
  string label = "";

  //for each codeline with a symbol, add it to the symbol table
  //map<string, Symbol> symboltable_;
  for (auto iter = codelines_.begin(); iter != codelines_.end(); ++iter) {
    if ( (*iter).GetLabel() != "nulllabel") {
      label = (*iter).GetLabel();
      Symbol temp(label, (*iter).GetPC() );

      //if it is multiply defined, set the boolean and don't insert it
      if (symboltable_.count(label) > 0) {
        symboltable_[label].SetMultiply();
        has_an_error_ = true;
      } else {
        symboltable_[label] = temp;
      }
    }
  }

  //print symbol table
  cout << "SYMBOL TABLE: " << endl;
  Utils::log_stream << "SYMBOL TABLE:\n";

  for (auto& x: symboltable_) {
    cout << x.first << ": " << x.second.ToString() << endl;
    Utils::log_stream << x.first << ": "  << x.second.ToString() + "\n";
  }
#ifdef EBUG
  Utils::log_stream << "leave PassOne\n"; 
#endif
}

/******************************************************************************
 * Function 'MakeCode'.
 * Helper function for PassTwo that generates code for opcodes of type 1
 *
 * Returns: The machine code for opcode of type 1
 *
 * Parameters:
 *  line: the codeline to generate the machinecode for
 *  opcode: the 3-digit string representation of the opcode
**/
string Assembler::MakeCode(CodeLine line, string opcode) {
  //stop if symbol is not in symbol table
  if (symboltable_.find(line.GetSymOperand() ) == symboltable_.end() ) {
    cout << this->GetUndefinedMessage(line.GetSymOperand() ) << endl;
    has_an_error_ = true;
    return "";
  }

  //ouput variable and temporary variable to hold location of target 
  string code = "";
  int temp = 0;

  //add opcode if its size is 3 and get location of target
  if (opcode.size() == 3) {
    code += opcode;
  } else {
    has_an_error_ = true;
    return "";
  }
  temp = symboltable_[ line.GetSymOperand()].GetLocation();
  //cout << "DEC: " << temp << " SYMBOL: " << line.GetSymOperand() << endl;

  //add addressing bit
  if (line.GetAddr() == "*") {
    code += "1";
  } else {
    code += "0";
  }

  //add location of target and return the code
  code += globals_.DecToBitString(temp, 12);
  return code;
}

/******************************************************************************
 * Function 'PassTwo'.
 * This function does pass two of the assembly process.
**/
void Assembler::PassTwo() {
#ifdef EBUG
  Utils::log_stream << "enter PassTwo\n"; 
#endif
  //temporary variable to hold machinecode
  string code = "";
  //map<int, string> machinecode_;
  
  for (auto iter = codelines_.begin(); iter != codelines_.end(); ++iter) {
    if ( (*iter).GetMnemonic() == "RD " || (*iter).GetMnemonic() == "RD") {
      code += "1110000000000001";
    } else if ( (*iter).GetMnemonic() == "STP") {
      code += "1110000000000010";
    } else if ( (*iter).GetMnemonic() == "WRT") {
      code += "1110000000000011";
    } else if ( (*iter).GetMnemonic() == "BAN") {
      code = this->MakeCode( (*iter), "000");
    } else if ( (*iter).GetMnemonic() == "SUB") {
      code = this->MakeCode( (*iter), "001");
    } else if ( (*iter).GetMnemonic() == "STC") {
      code = this->MakeCode( (*iter), "010");
    } else if ( (*iter).GetMnemonic() == "AND") {
      code = this->MakeCode( (*iter), "011");
    } else if ( (*iter).GetMnemonic() == "ADD") {
      code = this->MakeCode( (*iter), "100");
    } else if ( (*iter).GetMnemonic() == "LD ") {
      code = this->MakeCode( (*iter), "101");
    } else if ( (*iter).GetMnemonic() == "BR ") {
      code = this->MakeCode( (*iter), "110");
    //TODO handle pseudo-op codes 'ORG'  and 'DS'
    } else if ( (*iter).GetMnemonic() == "ORG") {
      //Change the pc value
      this->SetNewPC( (*iter));

    } else if ( (*iter).GetMnemonic() == "HEX") {
      //temporary Hex variable
      Hex temp = (*iter).GetHexObject();
      code += globals_.DecToBitString(temp.GetValue(), 16);
    } else if ( (*iter).GetMnemonic() == "DS ") {
      //define storage of N words starting at current PC location

    } else if ( (*iter).GetMnemonic() == "END") {
      //End of input
    } else {
      //invalid mnemonic
      if ( !( (*iter).IsAllComment()) ) {
        cout << this->GetInvalidMessage("mnemonic", (*iter).GetMnemonic() ) 
             << endl;
        has_an_error_ = true;
      }
    }
    //cout << "M: " << (*iter).GetMnemonic() << " PC: " << (*iter).GetPC() 
    //     << " C: " << code << " L: " << code.size() << endl; DEBUG

    //set the value of code for the codeline
    (*iter).SetMachineCode(code);

    //reset code for next line
    code = "";
  }

#ifdef EBUG
  Utils::log_stream << "leave PassTwo\n"; 
#endif
}

/******************************************************************************
 * Function 'PrintCodeLines'.
 * This function prints the code lines.
**/
void Assembler::PrintCodeLines() {
#ifdef EBUG
  Utils::log_stream << "enter PrintCodeLines\n"; 
#endif
  string s = "";
  int counter = 0;

  for (auto iter = codelines_.begin(); iter != codelines_.end(); ++iter) {
    s += (*iter).ToString() + '\n';
    //s += (*iter).ToString();
  }

  if (!found_end_statement_) {
    s += "\n***** ERROR -- NO 'END' STATEMENT\n";
    has_an_error_ = true;
  }

  cout << s << endl;
  //for (auto iter = codelines_.begin(); iter != codelines_.end(); ++iter) {
  //  //cout << "where: " << counter << endl;
  //  cout << (*iter).ToString() << endl;
  //  counter += 1;
  //}
#ifdef EBUG
  Utils::log_stream << "leave PrintCodeLines\n"; 
#endif
  Utils::log_stream << s << endl;
}

/******************************************************************************
 * Function 'PrintMachineCode'.
 * This function prints the machine code.
**/
void Assembler::PrintMachineCode(string binary_filename, ofstream& out_stream) {
#ifdef EBUG
#endif
  string s = "";
  Utils::log_stream << "enter PrintMachineCode" << " " << binary_filename << endl; 
  cout << "machine code:" << endl;

#ifdef EBUG
  Utils::log_stream << "leave PrintMachineCode" << endl; 
#endif
}

/******************************************************************************
 * Function 'PrintSymbolTable'.
 * This function prints the symbol table.
void Assembler::PrintSymbolTable() {
#ifdef EBUG
  Utils::log_stream << "enter PrintSymbolTable\n"; 
#endif
  string s = "SYMBOL TABLE\n    SYM LOC FLAGS\n";

#ifdef EBUG
  Utils::log_stream << "leave PrintSymbolTable\n"; 
#endif
  Utils::log_stream << s << endl;
}
**/

/******************************************************************************
 * Function 'SetNewPC'.
 * This function gets a new value for the program counter.
 *
 * No return value--this sets the class's PC variable.
 *
 * Parameters:
 *   codeline - the line of code from which to update
**/
void Assembler::SetNewPC(CodeLine codeline) {
#ifdef EBUG
  Utils::log_stream << "enter SetNewPC\n"; 
#endif
  //have to do Hex > int
  Hex hex = codeline.GetHexObject();
  int value = hex.GetValue();

  //set PC to value of Operand if it is not invalid
  if (value < 0) {
    this->GetUndefinedMessage("Value of " + to_string(value) + " is invalid");
    this->has_an_error_ = true;
  }
  codeline.SetPC(value);
  cout << "THING: " << codeline.GetPC() << " VAL: " << value << endl;
#ifdef EBUG
  Utils::log_stream << "leave SetNewPC\n"; 
#endif
}

/******************************************************************************
 * Function 'UpdateSymbolTable'.
 * This function updates the symbol table for a putative symbol.
 * Note that there is a hack here, in that the default value is 0
 * and that would mean we can't store a symbol at location zero.
 * So we add one, and then back that out after the full first pass is done.
**/
void Assembler::UpdateSymbolTable(int pc, string symboltext) {
#ifdef EBUG
  Utils::log_stream << "enter UpdateSymbolTable\n"; 
#endif

#ifdef EBUG
  Utils::log_stream << "leave UpdateSymbolTable\n"; 
#endif
}
