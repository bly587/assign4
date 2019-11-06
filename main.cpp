#include <iostream>
#include <fstream>
#include "Student.h"
#include "Window.h"
#include "GenQueueLL.h"
#include "SLinkedList.h"

using namespace std;

// test functions
bool testTheFunctions();
void calcAndPrintStats(SLinkedList *student_wait_times, Window* window_array, int num_windows);

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
  int num_windows;
  try{
    throw stoi(line);
  }
  catch (invalid_argument e){
    cout << "Line: " << line << endl;
    cout << "Invalid character in text file. Please try again." << endl;
    exit(1);
  }
  catch (int e){
    num_windows = stoi(line); // gets number of windows
  }

  // Creates window array and all the window objects
  Window *window_array[num_windows];
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
    //cout << "time: " << time << endl;

    if (!isFirstIter){
      // Increment variables
      // Updates students in line/queue
      for (int i = 0; i < registrar_line->getSize(); ++i){
        //pull out to update
        Student *s = registrar_line->remove();
        //update their waittime
        s->waitTime++;
        //cout << "incrementing wait time for student in line!" << endl;
        //add them back into the queue. This works because if everyone is removed and then added back to the queue the order will be the same
        registrar_line->add(s);
      }
      // Updates Windows
      //cout << "updating the windows!" << endl;
      for (int i = 0; i < num_windows; ++i){
        //decrements the time needed to the students at windows
        //also has students removed from windows if their time needed is 0
        //increments time idle if window is open
        window_array[i]->updateWindow();
        //cout << "Window idle time is: " << window_array[i]->idleTime << endl;
      }
    }

    if (!haltFileRead){
      // Stores the clock tick
      getline(text_file, line);
      //cout << "this is the line: " << line << endl;
      if (text_file.eof()){ // checks to see if we are done reading the file
        fileIsDone = true;
      }
      else{ // if we are still reading the file like usual
        try{
          throw stoi(line);
        }
        catch (invalid_argument e){
          cout << "Line: " << line << endl;
          cout << "Invalid character in text file. Please try again." << endl;
          exit(1);
        }
        catch (int e){
          clock_tick = stoi(line);
        }
        //cout << "Clock tick: " << clock_tick << endl;
      }
      haltFileRead = true;
    }

    // Only adds students to the queue if the clock_tick listed in the file is same as our time in the loop
    if (clock_tick == time){
      // Creates new students and adds them to the queue
      getline(text_file, line);
      int num_students;

      try{
        throw stoi(line);
      }
      catch (invalid_argument e){
        cout << "Line: " << line << endl;
        cout << "Invalid character in text file. Please try again." << endl;
        exit(1);
      }
      catch (int e){
        num_students = stoi(line);
      }
      for (int i = 0; i < num_students; ++i){
        getline(text_file, line);
        int timeNeeded;
        try{
          throw stoi(line);
        }
        catch (invalid_argument e){
          cout << "Line: " << line << endl;
          cout << "Invalid character in text file. Please try again." << endl;
          exit(1);
        }
        catch (int e){
          timeNeeded = stoi(line); // gets Student's time needed at window
        }

        //cout << "student with timeNeeded - " << timeNeeded << " - added to queue" << endl;
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
        //cout << "Moving student at front of line to window. Their wait time was: " << s->waitTime << endl;
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

  /* ------------------------------ Calculate Statistics ---------------------*/

  // -------------- Student Wait Times --------------------
  float mean_wait_time = 0;
  float median = 0;
  int longest_wait_time = 0;
  int students_over_ten = 0;
  //int counter = 0;
  //since we only get one chance to remove the value we have to use it wisley
  int tmp_wait_time = 0;
  bool isEven = false;
  int size_of_list = student_wait_times->getSize();
  //if length is even
  //cout << size_of_list << endl;
  //cout << student_wait_times->getSize() << endl;
  if(size_of_list % 2 == 0)
  {
    isEven = true;
  }
  for(int i = 0; i < student_wait_times->getSize(); ++i)
  {
    tmp_wait_time = student_wait_times->removeFront();
    //put the longest wait time value into the respective variable
    //check with each iteration if the wait time is greater than the one we have stored
    if(tmp_wait_time > longest_wait_time)
    {
      longest_wait_time = tmp_wait_time;
    }
    //increment number of students waiting over 10 min
    if(tmp_wait_time > 10)
    {
      students_over_ten++;
    }
    //cout << tmp_wait_time << endl;
    //add to mean
    mean_wait_time += tmp_wait_time;
    //calculate for median
    //store first median value
    if(isEven == true && i == (size_of_list / 2) - 1)
    {
      median += tmp_wait_time;
    }
    //store second median value
    if(isEven == true && i == size_of_list / 2)
    {
      median += tmp_wait_time;
      //divide by 2 since this will be the last time we alter the median variable
      median = median / 2;
    }
    else
    {
      if(i == ((size_of_list - 1) / 2) + 1)
      {
        median = tmp_wait_time;
      }
    }
  }
  //cout << mean_wait_time << endl;
  mean_wait_time = mean_wait_time / size_of_list;
  //cout << student_wait_times->getSize() << endl;
  // ------------------------- Window Stats -----------------------
  //cout << "Window stats starting" << endl;
  float mean_idle = 0;
  int longest_idle = 0;
  int window_idle_over_five = 0;
  //cout << "Number of windows: " << num_windows << endl;
  for(int i = 0; i < num_windows; ++i)
  {
    //cout << window_array[i]->idleTime << endl;
    mean_idle += window_array[i]->idleTime;
    // compare longest idle times
    if(window_array[i]->idleTime > longest_idle)
    {
      longest_idle = window_array[i]->idleTime;
    }
    //if anyone windows were idle for more than 10 min increment
    if(window_array[i]->idleTime > 5)
    {
      window_idle_over_five++;
    }
  }
  //calculate mean
  mean_idle = mean_idle / num_windows;

  cout << "1. The mean wait time per student is: " << mean_wait_time << endl;
  cout << "2. The median wait time per student is: " << median << endl;
  cout << "3. The longest wait time was: " << longest_wait_time << endl;
  cout << "4. Number of students waiting longer than 10 min: " << students_over_ten << endl;
  cout << "5. The mean window idle time: " << mean_idle << endl;
  cout << "6. The longest window idle time: " << longest_idle << endl;
  cout << "7. Number of windows idle for over 5 min: " << window_idle_over_five << endl;

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
