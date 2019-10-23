#include <iostream>
#include "ListNode.h"

using namespace std;
//template <class T>
ListNode::ListNode()
{
  data = NULL;
  next = NULL;
  prev = NULL;
}
//template <class T>
ListNode::ListNode(T elem)
{
  data = elem;
  next = NULL; //nullptr
  prev = NULL;
}
//template <class T>
ListNode::~ListNode(){
  next = NULL;
  prev = NULL;
}
