#include "BayesianNode.hpp"
#include "Relationship.hpp"
#include <queue>
BayesianNode newBayNodeBuilder(BayesianNode newBayNode, vector<BayesianNode> S_prev, vector<Attribute> list_att);

vector<Attribute> removeEl(vector<Attribute> myvector, Attribute att);
