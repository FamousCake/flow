#ifndef IO_H
#define IO_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>

#include "residual_network.h"
#include "residual_edge.hpp"

namespace IO
{

void printArray(int a[], int count, int w, const char msg[]);

void printResidualNetwork(ResidualNetwork &E, int w, const char message[]);

ResidualNetwork ReadGraph();

void WriteGraph(ResidualNetwork &);

} // IO

#endif // IO_H
