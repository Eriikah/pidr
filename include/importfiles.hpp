#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <string.h>
#include "Element.hpp"
#include "utils.hpp"

using namespace std;

/**
 * Imports data from csv file
 *
 * @param filename name of the csv with the data
 * @return vector of vector of strings
 */
vector<vector<string>> importFile(string filename);

/**
 * Imports attribute from csv file
 *
 * @param filename name of the csv with the data
 * @param column index of the attribute
 * @return vector of double
 */
vector<double> getValue(string filename, int column);

vector<pair<string, string>> getLinkValues(string filename);

vector<Element> getElements(Attribute X);
