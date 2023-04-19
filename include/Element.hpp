#include <string>
#include "Attribute.hpp"

using namespace std;

class Element
{
public:
    string id;
    Attribute att;
    string value;
    Element();
    Element(string id, Attribute att, string value);
};
