#ifndef PUSH_RELABEL_H
#define PUSH_RELABEL_H

#include "iostream"
#include <limits>
#include "graph.h"
#include "io.h"

namespace PushRelabel
{

void run(Graph &, const Graph &, unsigned const int, unsigned const int);
void init(Graph &, int);

bool Push(Graph &, const Graph &, unsigned const int, unsigned const int);
bool Relabel(Graph &, const Graph &, unsigned const int, unsigned const int);

} // PushRelabel PushRelabel

#endif // PUSH_RELABEL_H
