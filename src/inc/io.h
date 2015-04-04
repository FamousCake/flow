#ifndef IO_H
#define IO_H

#include <iostream>
#include <iomanip>
#include <fstream>

#include "globals.h"

namespace IO
{

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
 * @brief Print a 2D Array
 *
 * @param a Array to be printed
 * @param message Mesage to be outputed before the array
 * @param w offset for each element
 * @param count [description]
 */
void printArrayDouble(int a[][MAX_GRAPH_SIZE], const char message[], int w, int count);

int ReadGraph(int[][MAX_GRAPH_SIZE], const char[]);

} // IO

#endif // IO_H
