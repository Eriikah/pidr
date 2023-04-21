#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include <math.h>
#include "utils.hpp"
using namespace std;

double esperance(multimap<string, double> map)
{
    multimap<double, int> probability_map;
    for (auto v : map)
    {
        if (probability_map.find(v.second) == probability_map.end())
        {
            probability_map.insert(make_pair(v.second, 1));
        }
        else
        {
            probability_map.find(v.second)->second++;
        }
    }
    int n = map.size();
    double esperance = 0;
    for (multimap<double, int>::iterator it = probability_map.begin(); it != probability_map.end(); ++it)
    {
        esperance += it->first * (it->second) / n;
    }
    return esperance;
}

double esperance(vector<vector<double>> couple)
{
    multimap<double, int> probability_map;
    for (auto v : couple)
    {
        if (probability_map.find(produitTaT(v)) == probability_map.end())
        {
            probability_map.insert(make_pair(produitTaT(v), 1));
        }
        else
        {
            probability_map.find(produitTaT(v))->second++;
        }
    }
    int n = couple.size();
    double esperance = 0;
    for (multimap<double, int>::iterator it = probability_map.begin(); it != probability_map.end(); ++it)
    {
        esperance += it->first * (it->second) / n;
    }
    return esperance;
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

double correlation(multimap<string, double> main_map, multimap<string, double> second_map, vector<vector<double>> couple)
{
    return (esperance(couple) - esperance(main_map) * esperance(second_map)) / (ecart_type(main_map) * ecart_type(second_map));
}
