#ifndef PUSH_RELABEL_H
#define PUSH_RELABEL_H

#include <iostream>
#include <limits>
#include <algorithm>

#include "graph.h"
#include "io.h"
#include "simple_queue.h"

namespace PushRelabel
{

void run(Graph &, const int, const int);
void init(Graph &, SimpleQueue &, int);

bool CanPush(Graph &, const int, const int);

bool IsActive(Graph &, const int, const int, const int );

void Push(Graph &, const int, const int);
void Relabel(Graph &, const int, const int);

} // PushRelabel PushRelabel

#endif // PUSH_RELABEL_H
