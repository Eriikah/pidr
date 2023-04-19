#include "Element.hpp"

Element::Element() : id(""), att(Attribute()), value("")
{
}
Element::Element(string id, Attribute att, string value) : id(id), att(att), value(value)
{
}
