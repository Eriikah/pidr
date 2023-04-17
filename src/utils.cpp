#include "utils.hpp"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void removeEscapeCharacters(string &s)
{
    s.erase(std::remove_if(s.begin(), s.end(), [](char c)
                           { return std::iscntrl(c); }),
            s.end());
}