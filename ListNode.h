template <class T>
class ListNode
{
  public:
    T data;
    ListNode* next;
    ListNode* prev;

  //constructor
  ListNode();
  ListNode(T elem);
  ~ListNode();
};

template <class T>
ListNode<T>::ListNode()
{
  data = NULL;
  next = NULL;
  prev = NULL;
}
template <class T>
ListNode<T>::ListNode(T elem)
{
  data = elem;
  next = NULL; //nullptr
  prev = NULL;
}
template <class T>
ListNode<T>::~ListNode(){
  next = NULL;
  prev = NULL;
}
