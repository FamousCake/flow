#ifndef SIMPLE_QUEUE_H
#define SIMPLE_QUEUE_H

class SimpleQueue
{
  public:
    SimpleQueue(const int n)
    {
        this->m = new int[n];
        this->l = 0;
        this->r = 0;
    }

    ~SimpleQueue()
    {
        delete []m;
    }

    void push(const int n)
    {
        this->m[r++] = n;
    }

    int pop()
    {
        return this->m[l++];
    }

    int front()
    {
        return this->m[l];
    }

    int size()
    {
        return r - l;
    }

  private:
    int *m;
    int l, r;
};

#endif // SIMPLE_QUEUE_H
