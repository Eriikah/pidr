#include "BayesianNode.hpp"
#include "Relationship.hpp"

BayesianNode::BayesianNode()
{
}

BayesianNode::BayesianNode(Attribute *att) : attribute(att)
{
}

Attribute *BayesianNode::getAttribute()
{
    return this->attribute;
}

vector<Relationship *> BayesianNode::getRelationship() const
{
    return this->relationships;
}

void BayesianNode::addRelationship(Relationship *link)
{
    this->relationships.push_back(link);
}
