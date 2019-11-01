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
  // opens text file
  text_file.open(filename);
  // ensures user inputs valid text_file name
  while (!text_file.is_open()){
    cout << "File could not be read, please input filename again: " << endl;
    string user_input;
    cin >> user_input;
    text_file.open(user_input);
  }
  // made it here, then the text file opened succesfully

  // Gets first line in file --> number of windows
  getline(text_file, line);
  int num_windows = stoi(line); // gets number of windows

  // Creates window array and all the window objects
  Window* window_array[num_windows];
  for (int i = 0; i < num_windows; ++i){
    Window *w  = new Window();
    window_array[i] = w;
  }

  // Declare more variables
  int clock_tick;
  bool fileIsDone = false;
  // boolean to make sure stat variable incrementation doesn't occur until second iteration of time loop
  bool isFirstIter = true;
  // boolean which stops reading the file until time has catched up with clock_tick
  bool haltFileRead = false;
  // int interator to keep track of time in loop
  int time = 0;

  // --------------------- Time loop ----------------------------
  while(true){

    time++;
    cout << "time: " << time << endl;

    if (!isFirstIter){
      // Increment variables
      // Updates students in line/queue
      for (int i = 0; i < registrar_line->getSize(); ++i){
        Student *s = registrar_line->remove();
        s->waitTime++;
        cout << "incrementing wait time for student in line!" << endl;
        registrar_line->add(s);
      }
      // Updates Windows
      cout << "updating the windows!" << endl;
      for (int i = 0; i < num_windows; ++i){
        window_array[i]->updateWindow();
      }
    }

    if (!haltFileRead){
      // Stores the clock tick
      getline(text_file, line);
      cout << "this is the line: " << line << endl;
      if (text_file.eof()){ // checks to see if we are done reading the file
        fileIsDone = true;
      }
      else{ // if we are still reading the file like usual
        clock_tick = stoi(line);
        cout << "Clock tick: " << clock_tick << endl;
      }
      haltFileRead = true;
    }

    // Only adds students to the queue if the clock_tick listed in the file is same as our time in the loop
    if (clock_tick == time){
      // Creates new students and adds them to the queue
      getline(text_file, line);
      int num_students = stoi(line);
      for (int i = 0; i < num_students; ++i){
        getline(text_file, line);
        int timeNeeded = stoi(line); // gets Student's time needed at window
        cout << "student with timeNeeded - " << timeNeeded << " - added to queue" << endl;
        Student *s = new Student(timeNeeded); // creates new instance of student with timeNeeded variable
        registrar_line->add(s); // adds student to the queue
      }

      haltFileRead = false;
    }

    // removes students from line and into a window if there is space
    for (int i = 0; i < num_windows; ++i){
      if (window_array[i]->isOpen && !registrar_line->isEmpty()){ // there is an open window AND a student is in line
        Student *s = registrar_line->remove(); // removes student from line
        student_wait_times->insertFront(s->waitTime); // sends student's wait time to stat collector
        cout << "Moving student at front of line to window. Their wait time was: " << s->waitTime << endl;
        window_array[i]->setStudent(s); // sends student to window
      }
    }

    // Runs every time, but only has effect after first iteration
    isFirstIter = false;

    // Exits the loop if the sim is over
    if (fileIsDone && registrar_line->isEmpty()){
      break;
    }

    if (time == 100)
      break;

  }


  // ---------------------------------
  //testTheFunctions();
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
