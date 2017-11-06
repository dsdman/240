/****************************************************************
 * Header file for the Pullet16 interpreter.
 *
 * Author/copyright:  Duncan Buell
 * Used with permission and modified by: Dylan Desai
 * Date: 16 October 2017
 *
**/

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

#include "../../Utilities/scanner.h"
#include "../../Utilities/scanline.h"
#include "../../Utilities/utils.h"

#include "globals.h"
#include "hex.h"
#include <sstream>;

class Interpreter {
  public:
    Interpreter();
    virtual ~Interpreter();

    void Interpret(Scanner& data_scanner, ofstream& out_stream);
    void Load(Scanner& exec_scanner, string binary_filename);

  private:
    static const int kMaxInstrCount = 256;
    static const int kPCForStop = 4095;
    static const int kMaxMemory = 4095;
    int counter = 0;

    int pc_; //contins address of next instruction to be executed
    int accum_; //contains temporary data

    string ToString();

    vector<string> memory_;
    Globals globals_;

    void DumpData(const vector<string>& input);
    void DoADD(string addr, string target);
    void DoAND(string addr, string target);
    void DoBAN(string addr, string target);
    void DoBR(string addr, string target);
    void DoLD(string addr, string target);
    void DoRD(Scanner& data_scanner);
    void DoSTC(string addr, string target);
    void DoSTP();
    void DoSUB(string addr, string target);
    void DoWRT(ofstream& out_stream);
    void Execute(string opcode, string addr, string target, Scanner& data_scanner, ofstream& out_stream);
    void FlagAddressOutOfBounds(int address);
    int GetTargetLocation(string label, string address, string target);
    int TwosComplementInteger(int value);
};
#endif
