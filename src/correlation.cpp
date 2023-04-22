#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include <math.h>
#include "utils.hpp"
using namespace std;

double cov(vector<pair<double, double>> couple)
{
    multimap<double, int> p_map_XY;
    multimap<double, int> p_map_Y;
    multimap<double, int> p_map_X;
    for (auto v : couple)
    {
        if (p_map_XY.find(produitTaT(v)) == p_map_XY.end())
        {
            p_map_XY.insert(make_pair(produitTaT(v), 1));
        }
        else
        {
            p_map_XY.find(produitTaT(v))->second++;
        }
        if (p_map_X.find(v.first) == p_map_X.end())
        {
            p_map_X.insert(make_pair(v.first, 1));
        }
        else
        {
            p_map_X.find(v.first)->second++;
        }
        if (p_map_Y.find(v.second) == p_map_Y.end())
        {
            p_map_Y.insert(make_pair(v.second, 1));
        }
        else
        {
            p_map_Y.find(v.second)->second++;
        }
    }
    int n = couple.size();
    double esp_XY = 0;
    double esp_X = 0;
    double esp_Y = 0;
    for (multimap<double, int>::iterator it = p_map_XY.begin(); it != p_map_XY.end(); ++it)
    {
        esp_XY += it->first * (it->second) / n;
    }
    for (multimap<double, int>::iterator it = p_map_X.begin(); it != p_map_X.end(); ++it)
    {
        esp_X += it->first * (it->second) / n;
    }
    for (multimap<double, int>::iterator it = p_map_Y.begin(); it != p_map_Y.end(); ++it)
    {
        esp_Y += it->first * (it->second) / n;
    }
    return esp_XY - (esp_X * esp_Y);
}

pair<double, double> moyenne(vector<pair<double, double>> couple)
{
    double X_buffer = 0;
    double Y_buffer = 0;
    for (auto p : couple)
    {
        X_buffer += p.first;
        Y_buffer += p.second;
    }
    return make_pair(X_buffer / couple.size(), Y_buffer / couple.size());
}

double sigmas(vector<pair<double, double>> couple)
{
    pair<double, double> moyennes = moyenne(couple);
    double X_buffer = 0;
    double Y_buffer = 0;
    for (auto p : couple)
    {
        X_buffer += pow(p.first - moyennes.first, 2);
        Y_buffer += pow(p.second - moyennes.second, 2);
    }
    return sqrt(X_buffer * Y_buffer) / couple.size();
}

double correlation(vector<pair<double, double>> couple)
{
    return cov(couple) / sigmas(couple);
}
