#ifndef LINKED_LIST_H
#define LINKED_LIST_H

class ListNode
{
  public:
    ListNode(int, ListNode *);
    ListNode(){}
    ~ListNode();

    int v;
    ListNode *next;
};

class LinkedList
{
  public:
    LinkedList(){};
    ~LinkedList();

    ListNode *start = nullptr;

    void Add(int);
};

#endif // LINKED_LIST_H
