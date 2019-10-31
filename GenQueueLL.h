#include <iostream>
#include "GenDoublyLinkedList.h"
#ifndef GENQUEUELL_H
#define GENQUEUELL_H

using namespace std;

template <class T>
class GenQueueLL{
  public:
    GenQueueLL(); // constructor
    ~GenQueueLL();

    void add(T data);
    T remove();
    T peekFront();
    T peekBack();
    bool isEmpty();
    int getSize();

  private:
    int numElements;
    GenDoublyLinkedList<T> *myQueue;
};
#endif

// constructor
template <class T>
GenQueueLL<T>::GenQueueLL(){
  myQueue = new GenDoublyLinkedList<T>();
  numElements = 0;
}

// destructor
template <class T>
GenQueueLL<T>::~GenQueueLL(){
  delete myQueue;
}

// add method
template <class T>
void GenQueueLL<T>::add(T data){
  // adds the actual element
  myQueue->insertBack(data);
  ++numElements;
}

// remove method
template <class T>
T GenQueueLL<T>::remove(){
  T c = myQueue->removeFront();
  --numElements;
  return c;
}

// peek front method
template <class T>
T GenQueueLL<T>::peekFront(){
  return myQueue->front->data;
}

// peek back method
template <class T>
T GenQueueLL<T>::peekBack(){
  return myQueue->back->data;
}

// isEmpty method
template <class T>
bool GenQueueLL<T>::isEmpty(){
  return (numElements == 0);
}

// getSize method
template <class T>
int GenQueueLL<T>::getSize(){
  return numElements;
}
