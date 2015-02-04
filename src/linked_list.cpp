#include "inc/linked_list.h"

ListNode::ListNode(int v, int w, ListNode *next)
{
    this->v = v;
    this->w = w;
    this->next = next;
}

ListNode::~ListNode()
{
    delete this->next;
}

void LinkedList::Add(int v, int w)
{
    this->start = new ListNode(v, w, start);
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