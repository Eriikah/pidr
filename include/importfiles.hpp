#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

/**
 * Imports data from csv file
 *
 * @param filename name of the csv with the data
 * @return vector of vector of strings
 */
vector<vector<string>> importFile(string filename);
