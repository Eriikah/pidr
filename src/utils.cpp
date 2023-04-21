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

double produitTaT(vector<double> vect)
{
    double buffer = 1;
    for (auto val : vect)
    {
        buffer = buffer * val;
    }
    return buffer;
}

double convert(string str)
{
    if (str == "LOW" || str == "BAD" || str == "F")
    {
        return 0;
    }
    else if (str == "AVERAGE" || str == "MEDIUM" || str == "E")
    {
        return 1;
    }
    else if (str == "HIGH" || str == "GOOD" || str == "D")
    {
        return 2;
    }
    else if (str == "A")
    {
        return 5;
    }
    else if (str == "B")
    {
        return 4;
    }
    else if (str == "C")
    {
        return 3;
    }
    else
    {
        return stod(str);
    }
}