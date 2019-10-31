#include <iostream>

using namespace std;

class Window{
  public:

    bool isOpen;
    Student s;
    int idleTime;

    Window();
    Window(bool occ, Student s1, int iT);
};

Window::Window()
{
  isOpen = true;
  s = NULL;
  idleTime = 0;
}

Window::Window(bool occ, Student s1, int iT)
{
  isOpen = occ;
  s = s1;
  idleTime = iT;
}
