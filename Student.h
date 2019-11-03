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
    //Updating student's time needed
    void UpdateTimeNeeded();
    //updating student's time waited
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
//after each clock tick we subtract the time needed IF they are at a window
void Student::UpdateTimeNeeded()
{
  timeNeeded--;
}
//after each clock tick we add time to the time they have waited IF they are in line
void Student::UpdateTimeWaiting()
{
  waitTime++;
}
