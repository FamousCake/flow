#ifndef PUSH_RELABEL_H
#define PUSH_RELABEL_H

#include <iostream>
#include <limits>
#include <algorithm>

#include "graph.h"
#include "io.h"

namespace PushRelabel
{

void run(Graph &, const int, const int);
void init(Graph &, int);

bool Push(Graph &, const int, const int);
bool Relabel(Graph &, const int, const int);

} // PushRelabel PushRelabel

#endif // PUSH_RELABEL_H
