#include "main.h"

/****************************************************************
 * Main program for Homework XML.
 *
 * The purpose of this program is to parse a sentence that has
 * been parsed into parentheses-nested syntactic elements and
 * convert that nested-parentheses form into an equivalent
 * nested form that is proper XML. This would facilitate use of
 * an XML-reading package for traversing the parsed sentence.
 *
 * We read and write from and to files whose names are
 * command-line arguments.
 * This program does nothing but open the files, create an
 * instance of the class that parses into XML, and then invoke
 * that instance for processing the input data.
 *
 * Author/copyright:  Duncan Buell. All rights reserved.
 * Used with permission and modified by: Dylan Desai
 * Date: 22 September 2017
**/

static const string kTag = "Main: ";

int main(int argc, char *argv[]) {
  string in_filename = "";
  string log_filename = "";
  Scanner in_scanner;
  ParseIntoXML parseintoxml;

  //assigns the filenames to the user-provided inputs
  Utils::CheckArgs(2, argc, argv, "infilename logfilename");
  in_filename = static_cast<string>(argv[1]);
  log_filename = static_cast<string>(argv[2]);

  //opens the above file names
  Utils::LogFileOpen(log_filename);
  in_scanner.OpenFile(in_filename);

  //debug/trace information to write
  Utils::log_stream << kTag << "Beginning execution\n";
  Utils::log_stream.flush();
  Utils::log_stream << kTag << "logfile '" << log_filename << "'\n";

  //send the scanner to the above declared class for parsing
  parseintoxml.ParseTheFile(in_scanner);

  //more debug/trace information to write
  Utils::log_stream << kTag << "Ending execution\n";
  Utils::log_stream.flush();

  //end program
  Utils::FileClose(Utils::log_stream);
  return 0;
}

