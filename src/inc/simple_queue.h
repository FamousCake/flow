#ifndef SIMPLE_QUEUE_H
#define SIMPLE_QUEUE_H

class SimpleQueue
{
  public:
    SimpleQueue(int);
    ~SimpleQueue();

    void push(int);

    int front();

    int pop();

    int size();

  private:
    int *m;
    int l, r;
};

#endif // SIMPLE_QUEUE_H
