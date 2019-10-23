#include <iostream>
#include "GenDoublyLinkedList.h"

using namespace std;

template <class T>
class GenQueueLL{
  public:
    GenQueueLL(); // constructor
    ~GenQueueLL();

    void insert(T data);
    T remove();
    T peek();
    bool isFull();
    bool isEmpty();
    int getSize();

  private:
    int head;
    int tail;
    int numElements;
    T* myQueue;
};

// constructor
template <class T>
GenQueueLL<T>::GenQueueLL(){
  GenDoublyLinkedList<T>* myQueue = new GenDoublyLinkedList<T>();
  numElements = 0;
  head = 0;
  tail = -1;
}

// destructor
template <class T>
GenQueueLL<T>::~GenQueueLL(){
  delete myQueue;
}

// insert method
template <class T>
void GenQueueLL<T>::insert(T data){
  // adds the actual element
  myQueue->insertBack(data);
  ++tail;
  ++numElements;
}

// remove method
template <class T>
T GenQueueLL<T>::remove(){
  T c = myQueue->removeFront();
  ++head;
  --numElements;
  return c;
}

// peek method
template <class T>
T GenQueueLL<T>::peek(){
  return myQueue[head];
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
