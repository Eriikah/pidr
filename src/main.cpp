#include "newBayNodeBuilder.hpp"

using namespace std;

int main()
{
    vector<Attribute> list_att = setupNodesAndLinks();
    Attribute first = list_att[0];
    list_att = removeEl(list_att, first);
    vector<Attribute> Suiv = pot(first, list_att);
    vector<BayesianNode> S;
    S.push_back(BayesianNode(&first));
    vector<BayesianNode> S_prev = S;
    while (list_att.size() != 0 && Suiv.size() != 0)
    {
        BayesianNode bayNode = BayesianNode(&Suiv[0]);
        list_att = removeEl(list_att, Suiv[0]);
        S_prev = S;
        newBayNodeBuilder(bayNode, S_prev, list_att);
        S.push_back(bayNode);

        Suiv = removeEl(Suiv, Suiv[0]);
    }

    S.back().print();
    return 0;
}