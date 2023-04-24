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
        X_buffer += pow((p.first - moyennes.first), 2);
        Y_buffer += pow((p.second - moyennes.second), 2);
    }
    return sqrt(X_buffer * Y_buffer) / couple.size();
}

double correlation(vector<pair<double, double>> couple)
{
    double c = cov(couple);
    double sig = sigmas(couple);
    return cov(couple) / sigmas(couple);
}

pair<double, double> check_impl_direct(vector<pair<double, double>> couple)
{
    multimap<string, int> impl_counter;
    impl_counter.insert(make_pair("high", 0));
    impl_counter.insert(make_pair("mid", 0));
    impl_counter.insert(make_pair("low", 0));
    double c_high = 0;
    double c_mid = 0;
    double c_low = 0;
    for (auto p : couple)
    {
        if (p.first >= 3)
        {
            c_high += 1;
            if (p.second >= 3)
            {
                impl_counter.find("high")->second++;
            }
        }
        else if (p.first >= 2)
        {
            c_mid += 1;
            if (p.second >= 2)
            {
                impl_counter.find("mid")->second++;
            }
        }
        else
        {
            c_low += 1;
            if (p.second < 2)
            {
                impl_counter.find("low")->second++;
            }
        }
    }
    double test = (impl_counter.find("high")->second) / c_high;
    double dir = (((impl_counter.find("high")->second) / c_high) + (impl_counter.find("mid")->second / c_mid) + (impl_counter.find("low")->second / c_low)) / 3;
    impl_counter.find("high")->second = 0;
    impl_counter.find("mid")->second = 0;
    impl_counter.find("low")->second = 0;
    c_high = 0;
    c_mid = 0;
    c_low = 0;
    for (auto p : couple)
    {
        if (p.second >= 3)
        {
            c_high += 1;
            if (p.first >= 3)
            {
                impl_counter.find("high")->second++;
            }
        }
        else if (p.second >= 2)
        {
            c_mid += 1;
            if (p.first >= 2)
            {
                impl_counter.find("mid")->second++;
            }
        }
        else
        {
            c_low += 1;
            if (p.first < 2)
            {
                impl_counter.find("low")->second++;
            }
        }
    }
    return make_pair(dir, ((impl_counter.find("high")->second / c_high) + (impl_counter.find("mid")->second / c_mid) + (impl_counter.find("low")->second / c_low)) / 3);
}

pair<double, double> check_impl_indirect(vector<pair<double, double>> couple)
{
    multimap<string, int> impl_counter;
    impl_counter.insert(make_pair("high", 0));
    impl_counter.insert(make_pair("mid", 0));
    impl_counter.insert(make_pair("low", 0));
    double c_high = 0;
    double c_mid = 0;
    double c_low = 0;
    for (auto p : couple)
    {
        if (p.first >= 3)
        {
            c_high += 1;
            if (p.second <= 1)
            {
                impl_counter.find("high")->second++;
            }
        }
        else if (p.first >= 2)
        {
            c_mid += 1;
            if (p.second <= 2)
            {
                impl_counter.find("mid")->second++;
            }
        }
        else
        {
            c_low += 1;
            if (p.second > 2)
            {
                impl_counter.find("low")->second++;
            }
        }
    }
    double dir = ((impl_counter.find("high")->second / c_high) + (impl_counter.find("mid")->second / c_mid) + (impl_counter.find("low")->second / c_low)) / 3;
    impl_counter.find("high")->second = 0;
    impl_counter.find("mid")->second = 0;
    impl_counter.find("low")->second = 0;
    c_high = 0;
    c_mid = 0;
    c_low = 0;
    for (auto p : couple)
    {
        if (p.second >= 3)
        {
            c_high += 1;
            if (p.first <= 1)
            {
                impl_counter.find("high")->second++;
            }
        }
        else if (p.second >= 2)
        {
            c_mid += 1;
            if (p.first <= 2)
            {
                impl_counter.find("mid")->second++;
            }
        }
        else
        {
            c_low += 1;
            if (p.first > 2)
            {
                impl_counter.find("low")->second++;
            }
        }
    }
    return make_pair(dir, ((impl_counter.find("high")->second / c_high) + (impl_counter.find("mid")->second / c_mid) + (impl_counter.find("low")->second / c_low)) / 3);
}

int order(vector<pair<double, double>> couple)
{
    if (correlation(couple) > 0)
    {
        auto impl = check_impl_direct(couple);
        if (impl.first > impl.second)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        auto impl = check_impl_indirect(couple);
        if (impl.first > impl.second)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
}