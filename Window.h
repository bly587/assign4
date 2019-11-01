#include <iostream>

using namespace std;

class Window{
  public:

    bool isOpen;
    Student *s;
    int idleTime; // cumulative idle time

    Window();
    ~Window();

    // add or remove student from the window
    void setStudent(Student *s1); // used when student exits line and goes to window
    Student* removeStudent(); // when student is done at the window
    void updateWindow();
};

Window::Window()
{
  isOpen = true;
  s = NULL;
  idleTime = 0;
}

Window::~Window(){
  // figure out
}

void Window::setStudent(Student *s1){
  s = s1;
  isOpen = false;
}

Student* Window::removeStudent(){
  isOpen = true;
  Student *student = s;
  s = NULL;
  return student;
}

void Window::updateWindow(){
  if (isOpen){ // no student here
    idleTime++; // increments cumulative idleTime for the window
  }
  else{ // student at window
    s->timeNeeded--; // decrement timeNeeded
    if (s->timeNeeded == 0){ // if student is done at window
      removeStudent();
      cout << "student leaving Window!" << endl;
    }
  }
}
