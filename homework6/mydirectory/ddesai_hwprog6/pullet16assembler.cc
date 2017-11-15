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
 *
**/
vector<CodeLine> Assembler::GetCode(Scanner& in_scanner) {
  //temporary variables to create instance of 'CodeLine'
  string line = "dummyline";
  int linecounter = 0;
  CodeLine temp;
  //output variable
  vector<CodeLine> out;

  //get metainfo for instance of 'CodeLine' if line size is not zero
  cout << "RAW FILE CODE: " << endl;
  while (line.size() > 0) {
    //temporary variables for instance of codeline
    int pc = 0;
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
        //cout << "(lc) " << linecounter << " (pc) " << pc << " (label) " 
        //     << label << " (mnemonic) " << mnemonic << " (addr) " << addr
        //     << " (symoperand) " << symoperand << " (hex) " << hexoperand
        //     << " (comments) " << comments << " (code) " << code << endl;

        //put together the codeline
        temp.SetCodeLine(linecounter, pc, label, mnemonic, addr, symoperand, hexoperand, comments, code);
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
void Assembler::Assemble(Scanner& in_scanner, string binary_filename, ofstream& out_stream) {
#ifdef EBUG
  Utils::log_stream << "enter Assemble\n"; 
#endif
  //grab the codeLines
  codelines_ = this->GetCode(in_scanner);

  ////////////////////////////////////////////////////////////////////////////
  // Pass one
  // Produce the symbol table and detect errors in symbols.
  Utils::log_stream << endl << endl << "PASS ONE" << endl;

  ////////////////////////////////////////////////////////////////////////////
  // Pass two
  // Generate the machine code.
  Utils::log_stream << endl << endl << "PASS TWO" << endl;

  ////////////////////////////////////////////////////////////////////////////
  // Dump the results.
  cout << "AS 'CODELINES:' " << endl;
  this->PrintCodeLines();
  this->PrintSymbolTable();

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

  string returnvalue = "";

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

  string returnvalue = "";

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
  string returnvalue = "";

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

#ifdef EBUG
  Utils::log_stream << "leave PassOne\n"; 
#endif
}

/******************************************************************************
 * Function 'PassTwo'.
 * This function does pass two of the assembly process.
**/
void Assembler::PassTwo() {
#ifdef EBUG
  Utils::log_stream << "enter PassTwo\n"; 
#endif

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
  std::ifstream input (binary_filename, std::ifstream::binary);
  short byte1 = 0;
  short byte2 = 0;
  int size_binary = 0;
  char* buffer2; 

  if (input) {
    input.seekg (0, input.end);
    size_binary = input.tellg() / 2; //half since we are going to read a byte
    input.seekg (0, input.beg);
  }
  if (input) {
    buffer2 = new char [1];
    for (int i = 0; i < size_binary; ++i) {
      input.read(buffer2, 1); // read character
      byte1 = *buffer2;      // dereference
      input.read(buffer2, 1);
      byte2 = *buffer2;
      //printf("SHORT %2d %2d    %4d\n", buffer2[0], byte1, byte2);
      printf("SHORT %2d %2d    %4d\n", byte1, byte2);
    }
  }
  input.close();

#ifdef EBUG
  Utils::log_stream << "leave PrintMachineCode" << endl; 
#endif
}

/******************************************************************************
 * Function 'PrintSymbolTable'.
 * This function prints the symbol table.
**/
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
 *
 * Returns:
 *   the prettyprint string for printing
**/
void Assembler::UpdateSymbolTable(int pc, string symboltext) {
#ifdef EBUG
  Utils::log_stream << "enter UpdateSymbolTable\n"; 
#endif

#ifdef EBUG
  Utils::log_stream << "leave UpdateSymbolTable\n"; 
#endif
}
