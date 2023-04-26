#include "BayesianNode.hpp"
#include "Relationship.hpp"

Relationship::Relationship() : direction(1)
{
}

Relationship::Relationship(BayesianNode node, int direction) : node(node), direction(direction)
{
}

BayesianNode Relationship::getNode()
{
    return this->node;
}

int Relationship::getDirection() const
{
    return this->direction;
}
