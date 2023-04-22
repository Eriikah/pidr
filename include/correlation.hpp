#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

double correlation(vector<pair<double, double>> couple);

pair<double, double> moyenne(vector<pair<double, double>> couple);

double sigmas(vector<pair<double, double>> couple);

double cov(vector<pair<double, double>> couple);