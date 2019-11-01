#include <iostream>
#ifndef SLISTNODE_H
#define SLISTNODE_H

using namespace std;

// List node for single linked list
class SListNode{
  public:
    int data;
    SListNode *next; // pointer to the next node

    SListNode(); //constructor
    SListNode(int d); // overload constructor
    ~SListNode(); // destructor
};
#endif

SListNode::SListNode(){}

SListNode::SListNode(int d){
  data = d;
  next = NULL; // null pointer
}

SListNode::~SListNode(){
  if (next == NULL){
    delete next;
  }
}
