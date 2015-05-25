#ifndef IO_H
#define IO_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>

#include "residual_network_matrix.h"
#include "residual_network_list.h"
#include "residual_edge.h"

namespace IO
{

void printArray(int a[], int count, int w, const char msg[]);

void printResidualNetwork(ResidualNetwork &E, int w, const char message[]);

ResidualNetworkMatrix ReadGraph();

ResidualNetworkList ReadGraphList();

void WriteGraph(ResidualNetwork &);

} // IO

#endif // IO_H
