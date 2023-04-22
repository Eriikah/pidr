#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <string.h>
#include "potfunction.hpp"
#ifndef BayesianNode_HPP
#define BayesianNode_HPP

using namespace std;

class Relationship;

class BayesianNode
{
public:
    BayesianNode();
    BayesianNode(Attribute *att);
    Attribute *getAttribute();
    vector<Relationship *> getRelationship() const;
    void addRelationship(Relationship *link);

private:
    Attribute *attribute;
    vector<Relationship *> relationships;
};

#endif
