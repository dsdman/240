#include "pullet16interpreter.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Interpreter' for interpreting the Pullet16 code.
 *
 * Author: Duncan Buell
 * Used with permission and modified by: Dylan Desai
 * Date: 16 October 2017
**/

/******************************************************************************
 * Constructor
**/
Interpreter::Interpreter() {
}

/******************************************************************************
 * Destructor
**/
Interpreter::~Interpreter() {
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'doADD'.
 * This top level function interprets the 'ADD' opcode.
**/
void Interpreter::DoADD(string addr, string target) {
#ifdef EBUG
  Utils::log_stream << "enter doADD\n"; 
#endif

#ifdef EBUG
  Utils::log_stream << "leave doADD\n"; 
#endif
}

/******************************************************************************
 * Function 'doAND'.
 * This top level function interprets the 'AND' opcode.
**/
void Interpreter::DoAND(string addr, string target) {
#ifdef EBUG
  Utils::log_stream << "enter doAND\n"; 
#endif

#ifdef EBUG
  Utils::log_stream << "leave doAND\n"; 
#endif
}

/******************************************************************************
 * Function 'doBAN'.
 * This top level function interprets the 'BAN' opcode.
**/
void Interpreter::DoBAN(string addr, string target) {
#ifdef EBUG
  Utils::log_stream << "enter doBAN\n"; 
#endif

#ifdef EBUG
  Utils::log_stream << "leave doBAN\n"; 
#endif
}

/******************************************************************************
 * Function 'doBR'.
 * This top level function interprets the 'BR' opcode.
**/
void Interpreter::DoBR(string addr, string target) {
#ifdef EBUG
  Utils::log_stream << "enter doBR\n"; 
#endif

#ifdef EBUG
  Utils::log_stream << "leave doBR\n"; 
#endif
}

/******************************************************************************
 * Function 'doLD'.
 * This top level function interprets the 'LD' opcode.
**/
void Interpreter::DoLD(string addr, string target) {
#ifdef EBUG
  Utils::log_stream << "enter doLD\n"; 
#endif

#ifdef EBUG
  Utils::log_stream << "leave doLD\n"; 
#endif
}

/******************************************************************************
 * Function 'doRD'.
 * This top level function interprets the 'RD' opcode.
**/
void Interpreter::DoRD(Scanner& data_scanner) {
#ifdef EBUG
  Utils::log_stream << "enter doRD\n"; 
#endif

#ifdef EBUG
  Utils::log_stream << "leave doRD\n"; 
#endif
}

/******************************************************************************
 * Function 'doSTC'.
 * This top level function interprets the 'STC' opcode.
**/
void Interpreter::DoSTC(string addr, string target) {
#ifdef EBUG
  Utils::log_stream << "enter doSTC\n"; 
#endif

#ifdef EBUG
  Utils::log_stream << "leave doSTC\n"; 
#endif
}

/******************************************************************************
 * Function 'doSTP'.
 * This top level function interprets the 'STP' opcode.
**/
void Interpreter::DoSTP() {
#ifdef EBUG
  Utils::log_stream << "enter doSTP\n"; 
#endif

#ifdef EBUG
  Utils::log_stream << "leave doSTP\n"; 
#endif
}

/******************************************************************************
 * Function 'doSUB'.
 * This top level function interprets the 'SUB' opcode.
**/
void Interpreter::DoSUB(string addr, string target) {
#ifdef EBUG
  Utils::log_stream << "enter doSUB\n"; 
#endif

#ifdef EBUG
  Utils::log_stream << "leave doSUB\n"; 
#endif
}

/******************************************************************************
 * Function 'doWRT'.
 * This top level function interprets the 'WRT' opcode.
**/
void Interpreter::DoWRT(ofstream& out_stream) {
#ifdef EBUG
  Utils::log_stream << "enter doWRT\n"; 
#endif

#ifdef EBUG
  Utils::log_stream << "leave doWRT\n"; 
#endif
}

/******************************************************************************
 * Function 'Interpret'.
 * This top level function interprets the code.
**/
void Interpreter::Interpret(Scanner& data_scanner, ofstream& out_stream) {
#ifdef EBUG
  Utils::log_stream << "enter Interpret\n"; 
#endif

  ////////////////////////////////////////////////////////////////////////////
  // Loop through the memory.
  // Unpack the instruction.
  // Execute the instruction.
  //
  // The only gotcha in this program is that we ALWAYS bump the PC by 1 at
  // the bottom of this loop, so the execute function takes this into account
  // and bumps by one too few.

    // If we have hit the stop we will have returned a flag value that says
    // we should stop execution.

    // If we have executed but the PC is now incremented past the end of
    // memory, we have an execution error.

    // This is an interpreter thing. We prevent infinite loops from being
    // interpreted by having a timeout feature on instruction count.

#ifdef EBUG
  Utils::log_stream << "leave Interpret\n"; 
#endif
}

/******************************************************************************
 * Function 'Execute'.
 * This top level function executes the code.
**/
void Interpreter::Execute(string opcode, string addr, string target,
                       Scanner& data_scanner, ofstream& out_stream) {
#ifdef EBUG
  Utils::log_stream << "enter Execute\n"; 
#endif

#ifdef EBUG
  Utils::log_stream << "leave Execute\n"; 
#endif
}

/******************************************************************************
 * Function 'FlagAddressOutOfBounds'.
 * Check to see if an address is between 0 and 'kMaxMemory' inclusive and
 * die if this isn't the case.
 *
 * Parameter:
 *   address - the address to check for out of bounds
**/
void Interpreter::FlagAddressOutOfBounds(int address) {
#ifdef EBUG
  Utils::log_stream << "enter FlagAddressOutOfBounds\n"; 
#endif

#ifdef EBUG
  Utils::log_stream << "leave FlagAddressOutOfBounds\n"; 
#endif
}

/******************************************************************************
 * Function 'GetTargetLocation'.
 * Get the target location, perhaps through indirect addressing.
 *
 * Parameter:
 *   label - the label for our tracing output
 *   address - is this indirect or not?
 *   target - the target to look up
**/
int Interpreter::GetTargetLocation(string label, string address, string target) {
#ifdef EBUG
  Utils::log_stream << "enter GetTargetLocation\n"; 
#endif
  int location = 0;

#ifdef EBUG
  Utils::log_stream << "leave GetTargetLocation\n"; 
#endif

  return location;
}

/******************************************************************************
 * Function 'DumpData'.
 * This function dumps the data of a vector into standard output
 *
 * Returns nothing
 *
 * Parameters:
 *  input - the vector to dump
**/
void Interpreter::DumpData(const vector<string>& input) {
 for (auto iter = input.begin(); iter != input.end(); ++iter) {
   cout << *iter << endl;
 }
}

/******************************************************************************
 * Function 'Load'.
 * This top level function loads the machine code into memory.
 *
 * We also open and read the binary executable file, and we verify that the
 * binary that we read matches the ASCII 0 and 1 file that we read as the
 * "machine code" into the memory.
 *
 * Parameters:
 *   in_scanner - the scanner to read for source code
 *   binary_filename - the name of the file of the binary executable
**/
void Interpreter::Load(Scanner& in_scanner, string binary_filename) {
#ifdef EBUG
  Utils::log_stream << "enter Load\n"; 
#endif

  globals_ = Globals();
  vector<string> ascii;
  vector<string> bin;

  //load the ascii into vector and dump it
  while (in_scanner.HasNext()) {
    ascii.push_back(in_scanner.NextLine());
  }
  DumpData(ascii);

  //load the binary into vector and dump it
  in_scanner.Close();
  in_scanner.OpenFile(binary_filename);
  while (in_scanner.HasNext()) {
    bin.push_back(in_scanner.NextLine());
  }
  DumpData(bin);
  
  // Open the binary file and get the size in bytes of the file.

  // Open the binary file and read the characters, pushing them into a
  // 'vector' of 'char' data.

  // Decode the binary, two bytes at a time, and compare to the ASCII that
  // we read in earlier. Die if there's a discrepancy.
  // CAVEAT: We take extra care here because a 'char' is actually an 'int'
  // and thus we need to just pick off the 8 low bits and the next 8 bits
  // and avoid issues of sign propagation. 

#ifdef EBUG
  Utils::log_stream << "leave Load\n"; 
#endif
}

/******************************************************************************
 * Function 'ToString'.
 *
 * Returns:
 *   the prettyprint string for printing
**/
string Interpreter::ToString() {
#ifdef EBUG
  Utils::log_stream << "enter ToString\n"; 
#endif
  string s = "";
#ifdef EBUG
  Utils::log_stream << "leave ToString\n"; 
#endif

  return s;
}
/******************************************************************************
 * Function 'TwosComplementInteger'.
 *
 * This converts a 16 bit integer into the plus or minus 15 bit integer
 * that is the integer of the 2s complement bit pattern.
 *
 * Parameter:
 *   what - the integer value to convert to the integer that is the 2s compl
 *
 * Returns:
 *   the converted value
**/
int Interpreter::TwosComplementInteger(int what) {
#ifdef EBUG
  Utils::log_stream << "enter TwosComplementInteger\n"; 
#endif

  int twoscomplement = 0;
#ifdef EBUG
  Utils::log_stream << "leave TwosComplementInteger\n"; 
#endif

  return twoscomplement;
}
