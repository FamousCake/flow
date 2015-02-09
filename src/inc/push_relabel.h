#ifndef PUSH_RELABEL_H
#define PUSH_RELABEL_H

#include "iostream"
#include "graph.h"
#include "io.h"

namespace PushRelabel
{

void run(Graph &, const Graph &, int, int);
void init(Graph &, int);

bool canPush(Graph &, const Graph &, int, int);

bool Push(Graph &, const Graph &);
bool Relabel(Graph &, const Graph &, int, int);

} // PushRelabel PushRelabel

#endif // PUSH_RELABEL_H
