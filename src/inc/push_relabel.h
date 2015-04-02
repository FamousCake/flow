#ifndef PUSH_RELABEL_H
#define PUSH_RELABEL_H

#include <iostream>
#include <limits>
#include <algorithm>

#include "graph.h"
#include "io.h"
#include "dual_linked_list.h"

namespace PushRelabel
{

void run(Graph &, const int, const int);
void init(Graph &, int);

int FindOverflowing(Graph &, int, int);

void Discharge(Graph &, int);

bool CanPush(Graph &, int, int);
bool CanRelabel(Graph &, int);

void Push(Graph &, const int, const int);
void Relabel(Graph &, int);

} // PushRelabel PushRelabel

#endif // PUSH_RELABEL_H
