#ifndef LINKED_LIST_H
#define LINKED_LIST_H

class ListNode
{
  public:
    ListNode(int, int, ListNode *);
    ~ListNode();

    int v, w;
    ListNode *next;
};

class LinkedList
{
  public:
    LinkedList(){};
    ~LinkedList();

    ListNode *start = nullptr;

    void Add(int, int);
};

#endif // LINKED_LIST_H
