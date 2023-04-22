#ifndef RelationShip_HPP
#define RelationShip_HPP

using namespace std;

class BayesianNode;

class Relationship
{
public:
    Relationship();
    Relationship(BayesianNode *node, int direction);
    BayesianNode *getNode();
    int getDirection() const;

private:
    BayesianNode *node;
    int direction;
};
#endif