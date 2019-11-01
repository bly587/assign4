#include <iostream>
#include <fstream>
#include "Student.h"
#include "Window.h"
#include "GenQueueLL.h"
#include "SLinkedList.h"

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

  // declare variables
  ifstream text_file;
  string line;
  int line_count = 0;
  GenQueueLL<Student*> *registrar_line = new GenQueueLL<Student*>();
  SLinkedList *student_wait_times = new SLinkedList();

  text_file.open(filename);

  while (!text_file.is_open()){
    cout << "File could not be read, please input filename again: " << endl;
    string user_input;
    cin >> user_input;
    text_file.open(user_input);
  }
  // made it here, then the text file opened succesfully
  cout << "Text file opened successfully." << endl;

  getline(text_file, line);
  int num_windows = stoi(line); // gets number of windows

  // Creates the windows
  Window* window_array[num_windows];
  for (int i = 0; i < num_windows; ++i){
    Window *w  = new Window();
    window_array[i] = w;
  }

  while(true){
    /*
    // Increment variables
    for (int i = 0; i < registrar_line->getSize(); ++i){

    }
    */

    // Stores the clock tick
    getline(text_file, line);
    int clock_tick = stoi(line);

    // Creates new students and adds them to the queue
    getline(text_file, line);
    int num_students = stoi(line);
    for (int i = 0; i < num_students; ++i){
      getline(text_file, line);
      int timeNeeded = stoi(line); // gets Student's time needed at window
      Student *s = new Student(timeNeeded); // creates new instance of student with timeNeeded variable
      registrar_line->add(s); // adds student to the queue
    }

    // removes students from line and into a window if there is space
    for (int i = 0; i < num_windows; ++i){
      if (window_array[i]->isOpen && !registrar_line->isEmpty()){ // there is an open window AND a student is in line
        Student *s = registrar_line->remove(); // removes student from line
        student_wait_times->insertFront(s->waitTime); // sends student's wait time to stat collector
        window_array[i]->setStudent(s); // sends student to window
      }
    }

    cout << "agfajkflnjgalefnzfg" << endl;
    student_wait_times->printList();

    break;
  }


  // ---------------------------------
  testTheFunctions();
  return 0;
}


bool testTheFunctions(){

  cout << "------------ PRINTING THE TEST FUNCTIONS ---------- " << endl;

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
