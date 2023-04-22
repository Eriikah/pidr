#include "BayesianNode.hpp"
#include "Relationship.hpp"

void newBayNodeBuilder(BayesianNode newBayNode, vector<BayesianNode> S_prev, vector<Attribute> list_att);

vector<Attribute> removeEl(vector<Attribute> myvector, Attribute att);
