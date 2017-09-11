/****************************************************************
 * Rather generic header file that includes the 'Utilities' code.
 *
 * Author/copyright:  Dylan Desai
 * Used with permission and modified by: Dylan Desai
 * Date: 6 September 2017 
 *
**/
#ifndef MAIN_H
#define MAIN_H

//includes and namespaces
using namespace std;
#include <iostream>
#include <cmath>
#include <algorithm> //allows sort function
#include "../../Utilities/utils.h"
#include "../../Utilities/scanner.h"
#include "../../Utilities/scanline.h"

//functions
#ifdef PARTB
double GetMaxValue(vector<double> input);
double GetMinValue(vector<double> input);
#endif // PARTB

#endif // MAIN_H

