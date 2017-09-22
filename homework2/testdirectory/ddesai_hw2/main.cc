#include "main.h"

/****************************************************************
 * Main program for Homework 2.
 *
 * Author/copyright:  Dylan Desai. All rights reserved.
 * Used with permission and modified by: Dylan Desai
 * Date: 6 September 2017
 *
**/

int main(int argc, char *argv[]) {
  /*
   *VARIABLES
   */
  vector<double> input_nums;   
  double input = 0.0;
  double max_distance = 0.0;
  double min_distance = 0.0;
  
  //populate vector with double values for input and display values back
  for (int i = 0; i < 20; ++i) { 
    cout << "Inputting value number " << i+1 << endl;
    cin >> input;
    input_nums.push_back(input);
  }
  cout << endl;
  for (int i=0; i < input_nums.size(); ++i) {
    cout << "value at index " << i << ": "<< input_nums.at(i) << endl;
  }

  //get and display the max and min values
  max_distance = GetMaxValue(input_nums);
  min_distance = GetMinValue(input_nums);
  cout << endl;
  cout << "MAX VALUE IS " << max_distance << endl;
  cout << "MIN VALUE IS " << min_distance << endl;
  return 0;
}

double GetMaxValue(vector<double> &input) {
  double out = 0.0;
  
  //sort the vector and calculate the max value as the absolute value of the
  //difference between the smallest (index 0) and largest(last index) value.
  //Note that the code to sort was derived from cplusplus.com
  sort(input.begin(), input.end());
  out = (input.at(0)) - (input.at(input.size() -1));
  out = abs(out);
  
  return out;
}

double GetMinValue(vector<double> &input) { 
  /*
   *VARIABLES
   */
  double out = 0.0;
  double temp_min = 0.0;

  //sort the vector, use three for loops to get a triple, get the minimum(first
  //index) and maximum (last index) values in the triple, then subtract the
  //maximum from the minimum to get the temporary minimum. If that minimum is 
  //less than the current minimum, then it is the new minimum
  for (int i = 0; i < input.size()-3; ++i) {
    for (int j = i + 1; j < input.size()-2; ++j) {
      for (int k = j + 1; k < input.size()-1; ++k) {
        temp_min = abs(input.at(k) - input.at(i));
        //cout << "New temp min is: " << temp_min << endl;
        if (out == 0.0) {
          out = temp_min;
        }
        else if (temp_min < out) {
          out = temp_min;
        }
        //cout << "Current min is: " << out << endl;
      }
    }
  }
  return out;
}
