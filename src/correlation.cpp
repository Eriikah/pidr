#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

double correlation(multimap<string, double> main_map, multimap<string, double> second_map, vector<double, double>)
{
    return (esperance(main_map, second_map) - esperance(main_map) * esperance(second_map)) / (ecart_type(main_map) * ecart_type(second_map));
}

double esperance(multimap<string, double> map)
{
}

double esperance(multimap<string, double> map1, multimap<string, double> map2)
{
}

double ecart_type(multimap<string, double> map)
{
    double X_bar = moyenne(map);
    double buffer = 0;
    for (multimap<string, double>::iterator it = map.begin(); it != map.end(); ++it)
    {
        buffer += pow((it->second - X_bar), 2);
    }
    return sqrt(buffer / map.size());
}

double moyenne(multimap<string, double> map)
{
    double buffer = 0;
    for (multimap<string, double>::iterator it = map.begin(); it != map.end(); ++it)
    {
        buffer += it->second;
    }
    return buffer / map.size();
}