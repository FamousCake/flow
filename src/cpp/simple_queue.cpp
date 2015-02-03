#include "../inc/simple_queue.h"

SimpleQueue::SimpleQueue(int n)
{
    this->m = new int[n];
    this->l = 0;
    this->r = 0;
}

SimpleQueue::~SimpleQueue()
{
    delete [] this->m;
}

void SimpleQueue::push(int n)
{
    this->m[r++] = n;
}

int SimpleQueue::pop()
{
    return this->m[l++];
}

int SimpleQueue::front()
{
    return this->m[l];
}

int SimpleQueue::size()
{
    return r - l;
}
