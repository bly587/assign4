#include <iostream>

using namespace std;

class Student{
  public:

    int waitTime;
    int timeNeeded;

    //constructor
    Student();
    //overload
    Student(int tn);
    //setter for time at window
    void UpdateTimeNeeded();
    void UpdateTimeWaiting();
};

Student::Student()
{
  waitTime = 0;
  timeNeeded = 0;
}

Student::Student(int tn)
{
  waitTime = 0;
  timeNeeded = tn;
}

void Student::UpdateTimeNeeded()
{
  timeNeeded--;
}

void Student::UpdateTimeWaiting()
{
  waitTime++;
}
