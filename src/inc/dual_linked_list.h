#ifndef DUAL_LINKED_LIST_H
#define DUAL_LINKED_LIST_H

class DualNode {

public:
    int a;
    DualNode *next, *prev;

    DualNode(int a, DualNode *, DualNode *);
};

class DualLinkedList{
public:
    DualNode *start = nullptr;
    DualNode *last = nullptr;


    DualLinkedList(){ this->start = nullptr;}
    ~DualLinkedList();

    void Push(int);
    void MoveToFront(DualNode *);
};

#endif // DUAL_LINKED_LIST_H
