#include "Attribute.hpp"

Attribute::Attribute() : name(""), filename(""), column(0)
{
}

Attribute::Attribute(string name, string filename, int column) : name(name), filename(filename), column(column)
{
}