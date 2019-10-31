#include <iostream>
//#include "GenDoublyLinkedList.h"
#include "GenQueueLL.h"

using namespace std;

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

  //create new DoublyLinkedList
  GenDoublyLinkedList<int> g;
  g.insertFront(5);
  g.printList();

  GenQueueLL<int> gee;
  gee.add(3);

  GenQueueLL<string> theBestQueue;
  theBestQueue.add("dicks");
  theBestQueue.add("dick2");
  theBestQueue.add("dick3");
  theBestQueue.add("dick4");
  theBestQueue.add("dick5");
  theBestQueue.add("dick6");
  theBestQueue.remove();
  cout << "dick5??? " << theBestQueue.peek() << endl;
  cout << "size should be 5: " << theBestQueue.getSize() << endl;


}
