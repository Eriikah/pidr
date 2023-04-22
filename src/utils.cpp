#include "utils.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

void removeEscapeCharacters(string &s)
{
    s.erase(std::remove_if(s.begin(), s.end(), [](char c)
                           { return std::iscntrl(c); }),
            s.end());
}

double produitTaT(pair<double, double> vect)
{
    return vect.first * vect.second;
}

double convert(string str)
{
    if (str == "LOW" || str == "BAD" || str == "F" || str == "E")
    {
        return 1;
    }
    else if (str == "AVERAGE" || str == "MEDIUM" || str == "D" || str == "C")
    {
        return 2;
    }
    else if (str == "HIGH" || str == "GOOD" || str == "A" || str == "B")
    {
        return 3;
    }
    else
    {
        return stod(str);
    }
}