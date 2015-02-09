#ifndef IO_H
#define IO_H

#include <iostream>
#include <fstream>
#include <iomanip>

#include "graph.h"

namespace io
{

void printGraphV(const Graph &, const int);

void printGraphE(const Graph &, const int);

void printGraph(const Graph &, const int);

Graph readGraph(const char *);
}

#endif // IO_H