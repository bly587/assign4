#include <iostream>
//#include "GenDoublyLinkedList.h"
#include "Student.h"
//#include "Window.h"
#include "GenQueueLL.h"

using namespace std;

// test functions
bool testTheFunctions();

int main(int argc, char *argv[])
{
  //get user input
  //create variable to hold filename
  string filename = "";
  //if they forgot to add a file at the end in the command line
  if(argc < 2)
  {
    cout << "Please enter a file!" << endl;
    cin >> filename;
  }
  //if the user put too many arguements
  else if(argc > 2)
  {
    cout << "Too many arguements! Try again!" << endl;
  }
  //take the file they entered and make it the variable filename
  else
  {
    filename = argv[1];
  }

  testTheFunctions();

  return 0;
}

bool testTheFunctions(){
  //create new DoublyLinkedList
  GenDoublyLinkedList<int> *g = new GenDoublyLinkedList<int>();
  g->insertFront(5);
  g->printList();

  GenQueueLL<double> *gee = new GenQueueLL<double>();
  gee->add(3.4);
  gee->add(5.4);
  gee->add(6.9);
  cout << "peeking back...: " << gee->peekBack() << endl;

  GenQueueLL<string> *theBestQueue = new GenQueueLL<string>();
  theBestQueue->add("test1");
  theBestQueue->add("test2");
  theBestQueue->add("test3");
  theBestQueue->add("test4");
  theBestQueue->add("test5");
  theBestQueue->add("test6");
  cout << "size: " << theBestQueue->getSize() << endl;
  cout << "removing: " << theBestQueue->remove() << endl;
  cout << "size: " << theBestQueue->getSize() << endl;
  cout << "Front:  " << theBestQueue->peekFront() << endl;
  cout << "Back:  " << theBestQueue->peekBack() << endl;
  cout << "size should be 5: " << theBestQueue->getSize() << endl;
  cout << "isEmpty?: " << theBestQueue->isEmpty() << endl;
}
