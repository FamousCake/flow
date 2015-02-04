#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>

#include "graph.h"

namespace io
{

void printGraphV(const Graph &, int);

void printGraphE(const Graph &, int);

void printGraph(const Graph &, int);

Graph readGraph(const char *);
}