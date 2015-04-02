#include "inc/linked_list.h"

ListNode::ListNode(int v, ListNode *next)
{
    this->v = v;
    this->next = next;
}

ListNode::~ListNode()
{
    delete this->next;
}

void LinkedList::Add(int v)
{
    this->start = new ListNode(v, start);
}

LinkedList::~LinkedList()
{
    ListNode *x = this->start;

    while (x) {

        ListNode *y = x;

        x = x->next;

        delete y;
    }

    delete x;
}