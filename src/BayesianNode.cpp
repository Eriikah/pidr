#include "BayesianNode.hpp"
#include "Relationship.hpp"

BayesianNode::BayesianNode()
{
}

BayesianNode::BayesianNode(Attribute att) : attribute(att)
{
}

Attribute BayesianNode::getAttribute()
{
    return this->attribute;
}

vector<Relationship> BayesianNode::getRelationship() const
{
    return this->relationships;
}

void BayesianNode::addRelationship(Relationship link)
{
    this->relationships.push_back(link);
}

void BayesianNode::print(int i)
{
    cout << this->attribute.name << "\n";
    for (Relationship rel : this->relationships)
    {
        if (rel.getDirection() == -1)
        {

            cout << " <= ";
            rel.getNode().print(i + 1);
        }
        else if (rel.getDirection() == 1)
        {
            for (int j = 0; j < i; j++)
            {
                cout << "\t";
            }
            cout << " => ";
            rel.getNode().print(i + 1);
        }
    }
}
