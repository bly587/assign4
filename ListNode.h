template <class T>
class ListNode
{
  public:
    T data;
    ListNode *next;
    ListNode *prev;

  //constructor
  ListNode();
  ListNode(T elem);
  ~ListNode();
};
