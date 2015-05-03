#ifndef IO_H
#define IO_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "globals.h"
#include "residual_network.h"

namespace IO
{

// @TODO Add a write graph to file function

/**
 * @brief Print a 1D Array
 *
 * @param a Array to be printed
 * @param message Mesage to be outputed before the array
 * @param w offset for each element
 * @param count arracy lenght
 */
void printArray(int a[], const char message[], int w, int count);

/**
 * @brief Print a Residual Network
 *
 * @param message Mesage to be outputed before the array
 * @param w offset for each element
 */
void printResidualNetwork(ResidualNetwork &E, const char message[], int w);

/**
 * @brief Read graph from file as a 2D Vector
 *
 * @param filename
 */
std::vector<std::vector<int>> ReadGraph(const char[]);

} // IO

#endif // IO_H
