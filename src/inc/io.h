#ifndef IO_H
#define IO_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>

#include "residual_network_matrix.h"
#include "residual_network_list.h"

namespace IO
{

/**
 * @brief Print a 1D Array
 *
 * @param a     - array to be printed
 * @param count - arracy lenght
 * @param w     - offset for each element
 * @param msg   - mesage to be outputed before the array
 */
void printArray(int a[], int count, int w, const char msg[]);

/**
 * @brief Print a Residual Network
 *
 * @param E     - residual network to be printed
 * @param w     - offset for each element
 * @param msg   - mesage to be outputed before the output
 */
void printResidualNetwork(ResidualNetwork &E, int w, const char message[]);

/**
 * @brief Read DMACS graph from STDIN
 */
ResidualNetworkMatrix ReadGraph();

ResidualNetworkList ReadGraphList();

void WriteGraph(ResidualNetwork &);

} // IO

#endif // IO_H
