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

void BayesianNode::print()
{
    if (this->getRelationship().size() == 0)
    {
        cout << this->attribute->name << "\n";
    }
    else
    {
        for (Relationship *rel : this->relationships)
        {
            if ((*rel).getDirection() == -1)
            {
                cout << " <= ";
                (*(*rel).getNode()).print();
            }
            else if ((*rel).getDirection() == 1)
            {
                cout << " => ";
                (*(*rel).getNode()).print();
            }
        }
    }
}
