#include "inc/dual_linked_list.h"

DualNode::DualNode(int a, DualNode *prev, DualNode *next)
{
    this->a = a;
    this->prev = prev;
    this->next = next;

}

void DualLinkedList::Push(int a) {

    if (this->start == nullptr) {
        this->start = new DualNode(a, nullptr, nullptr);
        this->last = start;
    }
    else {

        DualNode *temp = new DualNode(a, nullptr, nullptr);

        temp->next = start;
        temp->prev = nullptr;

        start->prev = temp;

        start = temp;
    }
}

void DualLinkedList::MoveToFront(DualNode *x)
{
    if (x == start || x == nullptr)
        return;

    if (x->prev != nullptr) {
        // This is guaranteed if x is not the start
        x->prev->next = x->next;
    }

    // When x i the last element
    if (x->next != nullptr) {
        x->next->prev = x->prev;
    }

    x->next = start;
    x->prev = nullptr;

    start->prev = x;

    start = x;

}

DualLinkedList::~DualLinkedList()
{
    DualNode *x = this->start;

    while (x) {

        DualNode *y = x;

        x = x->next;

        delete y;
    }

    delete x;
}
