#include "globals.h"

/****************************************************************
 * Code file for the 'Globals' class for global constants and
 * functions.
 *
 * Documentation for the functions is in the header for those
 * functions.
 *
 * Author/copyright:  Duncan Buell
 * Used with permission and modified by: Dylan Desai
 * Date: 16 October 2017
 *
**/

/******************************************************************************
 * Function 'BitStringToDec'.
 * Convert a bit string to a decimal value.
**/
int Globals::BitStringToDec(const string& thebits) const {
#ifdef EBUG
  Utils::log_stream << "enter BitStringToDec\n"; 
#endif
  // Remember that the second parameter is for positioning the pointer
  // after doing the conversion (so we don't care here) and the third
  // says we are converting from a string of digits in binary.
  // Remember that the second parameter is for positioning the pointer
  // after doing the conversion (so we don't care here) and the third
  // says we are converting from a string of digits in binary.
  
  // return variable, boolean for the twos complement logic, and copy of bits
  int stoivalue = 0;
  bool is_negative = false;
  string newbits = thebits;

  //determine if the "binary" is negative
  if (thebits.at(0) == '1') {
    is_negative = true;
  } else {
    is_negative = false;
  }
  
  //convert the string of ansii binary into decimal
  if (is_negative) {
    //do twos complement arithmetic
    for (int i = 0; i < thebits.size(); ++i) {
      //switch the bits 
      if (newbits.at(i) == '1') {
        newbits.at(i) = '0';
      } else {
        newbits.at(i) = '1';
      }
    }
    //then add 1 from the result and take its complement
    stoivalue = -1 * (this->BinToDec(newbits) + 1);
  } else {
    //do regular binary aritmetic
    stoivalue = this->BinToDec(newbits);
  }
 
#ifdef EBUG
  Utils::log_stream << "leave BitStringToDec\n"; 
#endif

  return stoivalue;
}

/******************************************************************************
 * Function 'BinToDec'.
 * A helper function that will do the actual arithmetic
 *
 * Parameters:
 *  thebits - the bits to work with
 *
**/
int Globals::BinToDec(const string& thebits) const {
  //output variable and exponent
  int out = 0; 
  int exp = thebits.size() - 1;

  //do arithmetic
  for (int i = 0; i < thebits.size(); ++i) {
    if (thebits.at(i) == '1') {
      out += pow(2, exp);
    }
    --exp;
  }
  return out;
}

/******************************************************************************
 * Function 'DecToBitString'.
 * This function converts a decimal 'int' to a string of 0s and 1s.
 *
 * We only allow conversion to a string of length 12 or of length 16
 * because we only allow an address (lessequal 4096 = 2^12) or a hex
 * operand of 16 bits.
 *
 * Parameters:
 *   value - the value to convert
 *   how_many_bits - the length of the result
**/
string Globals::DecToBitString(const int& value, const int& how_many_bits) const {
#ifdef EBUG
  Utils::log_stream << "enter DecToBitString\n";
#endif
  string bitsetvalue = "";
  bitset <16> the_bits(value);
  //use the bitset class to do it for me
  bitsetvalue = the_bits.to_string();
//  if (value < 0) {
//  } else if (value == 0) {
//    for (int i = 0; i < how_many_bits; ++i) {
//      bitsetvalue += "0";
//    }
//  } else {
//    
//  }
#ifdef EBUG
  Utils::log_stream << "leave DecToBitString\n";
#endif

  return bitsetvalue;
}

/******************************************************************************
 * Function 'HexToDec'.
 * This function converts a string of hex characters to a decimal (base 10) val
 *
 * Parameters:
 *  thehex - the hex to convert
 */
int Globals::HexToDec(const string& thehex) const {
  //variables for the hex minus the bit and out
  string nosign_hex = thehex.substr(1);
  int out = 0;
  int exp = nosign_hex.size() - 1;

  if (thehex.at(0) == '+') {
    //do the normal conversion
    for (int i = 0; i < nosign_hex.size(); ++i) {
      if (nosign_hex.at(i) == '1') {
        //do the output
        out += (1 * pow(16, exp));
      } else if (nosign_hex.at(i) == '2') {
        out += (2 * pow(16, exp));
      } else if (nosign_hex.at(i) == '3') {
        out += (3 * pow(16, exp));
      } else if (nosign_hex.at(i) == '4') {
        out += (4 * pow(16, exp));
      } else if (nosign_hex.at(i) == '5') {
        out += (5 * pow(16, exp));
      } else if (nosign_hex.at(i) == '6') {
        out += (6 * pow(16, exp));
      } else if (nosign_hex.at(i) == '7') {
        out += (7 * pow(16, exp));
      } else if (nosign_hex.at(i) == '8') {
        out += (8 * pow(16, exp));
      } else if (nosign_hex.at(i) == '9') {
        out += (9 * pow(16, exp));
      } else if (nosign_hex.at(i) == 'A') {
        out += (10 * pow(16, exp));
      } else if (nosign_hex.at(i) == 'B') {
        out += (11 * pow(16, exp));
      } else if (nosign_hex.at(i) == 'C') {
        out += (12 * pow(16, exp));
      } else if (nosign_hex.at(i) == 'D') {
        out += (13 * pow(16, exp));
      } else if (nosign_hex.at(i) == 'E') {
        out += (14 * pow(16, exp));
      } else if (nosign_hex.at(i) == 'F') {
        out += (15 * pow(16, exp));
      }
      --exp;
    }

  } else {
    for (int i = 0; i < nosign_hex.size(); ++i) {
      if (nosign_hex.at(i) == '1') {
        //do the output
        out += (1 * pow(16, exp));
      } else if (nosign_hex.at(i) == '2') {
        out += (2 * pow(16, exp));
      } else if (nosign_hex.at(i) == '3') {
        out += (3 * pow(16, exp));
      } else if (nosign_hex.at(i) == '4') {
        out += (4 * pow(16, exp));
      } else if (nosign_hex.at(i) == '5') {
        out += (5 * pow(16, exp));
      } else if (nosign_hex.at(i) == '6') {
        out += (6 * pow(16, exp));
      } else if (nosign_hex.at(i) == '7') {
        out += (7 * pow(16, exp));
      } else if (nosign_hex.at(i) == '8') {
        out += (8 * pow(16, exp));
      } else if (nosign_hex.at(i) == '9') {
        out += (9 * pow(16, exp));
      } else if (nosign_hex.at(i) == 'A') {
        out += (10 * pow(16, exp));
      } else if (nosign_hex.at(i) == 'B') {
        out += (11 * pow(16, exp));
      } else if (nosign_hex.at(i) == 'C') {
        out += (12 * pow(16, exp));
      } else if (nosign_hex.at(i) == 'D') {
        out += (13 * pow(16, exp));
      } else if (nosign_hex.at(i) == 'E') {
        out += (14 * pow(16, exp));
      } else if (nosign_hex.at(i) == 'F') {
        out += (15 * pow(16, exp));
      }
      --exp;
    }
    out *= -1;
  }
  return out;
}
















