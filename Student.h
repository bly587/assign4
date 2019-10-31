#include <iostream>

using namespace std;

class Student{
  public:

    int waitTime;
    int timeAtWindow;

    //constructor
    Student();
    //overload
    Student(int wt, int tw);
};

Student::Student()
{
  waitTime = 0;
  timeAtWindow = 0;
}

Student::Student(int wt, int tw)
{
  waitTime = wt;
  timeAtWindow = tw;
}
