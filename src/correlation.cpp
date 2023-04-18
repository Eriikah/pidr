#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

double esperance(multimap<string, double> map)
{
    multimap<double, int> probability_map;
    for (multimap<string, double>::iterator it = map.begin(); it != map.end(); ++it)
    {
        probability_map.find(it->second)++;
    }
    int n = map.size();
    double esperance = 0;
    for (multimap<double, int>::iterator it = probability_map.begin(); it != probability_map.end(); ++it)
    {
        esperance += it->first * (it->second) / n;
    }
    return esperance;
}

double esperance(vector<pair<double, double>> couple)
{
    multimap<double, int> probability_map;
    for (vector<pair<double, double>>::iterator it = couple.begin(); it != couple.end(); ++it)
    {
        probability_map.find(it.base()->first * it.base()->second)++;
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

double correlation(multimap<string, double> main_map, multimap<string, double> second_map, vector<pair<double, double>> couple)
{
    return (esperance(couple) - esperance(main_map) * esperance(second_map)) / (ecart_type(main_map) * ecart_type(second_map));
}