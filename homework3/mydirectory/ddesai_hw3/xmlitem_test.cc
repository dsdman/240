/*tests whether I've done the ToString function right and also learning
*how to use pointers at the same time
*Author/copyright: Dylan Desai
*/
#include <iostream>
#include "xmlitem.h"
using namespace std;

int main(int argc, char* argv[]) {
  //declare test variables (standard way)
  XMLItem test(2, "test", "open");
  XMLItem test1(2, "test", "close");
  XMLItem test2(2, "test", "BS");

  //alternate method to declare objects: "*" declares a pointer to an object
  //using this method, declaring objects is similar to C#/Java 
  //XMLItem* test = new XMLItem(2, "test", "open");
  //XMLItem* test1 = new XMLItem(2, "test", "close");
  //XMLItem* test2 = new XMLItem(2, "test", "BS"); 

  //test the objects
  cout << test.ToString() << endl; //should return <test level="2">
  cout << test1.ToString() << endl; //should return </test>
  cout << test2.ToString() << endl; //should return test

  //alternate method of testing objects: "->" is how you access the functions
  //of a pointer
  //cout << test->ToString() << endl;
  //cout << test1->ToString() << endl;
  //cout << test2->ToString() << endl;

  //de-referencing the objects for garbage collection
  //"&" is the reference (pointer) to an object and "delete" removes that
  //reference from memory by calling the deconstructor
  //delete &test;
  //delete &test1;
  //delete &test2;

  //alternate de-referencing of the objects
  //since they were declared as pointers, you can simply call delete since
  //the objects were only references(pointers) to begin with
  //delete test;
  //delete test1;
  //delete test2;

  return 0;
}
