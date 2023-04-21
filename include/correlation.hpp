#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

double esperance(multimap<string, double> map);

double esperance(vector<pair<double, double>> couple);

double moyenne(multimap<string, double> map);

double ecart_type(multimap<string, double> map);

double correlation(multimap<string, double> main_map, multimap<string, double> second_map, vector<vector<double>> couple);