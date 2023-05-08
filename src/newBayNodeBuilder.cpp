#include "newBayNodeBuilder.hpp"

// renvoie toutes les alternatives
using namespace std;

BayesianNode newBayNodeBuilder(BayesianNode newBayNode, vector<BayesianNode> S_prev, vector<Attribute> list_att)
{
    vector<Attribute> potNewNode = (pot(newBayNode.getAttribute(), list_att));
    for (BayesianNode A : S_prev)
    {
        /**On verifie si  l'attribut de A et
         * l'attribut de newNode sont reliés par un lien
         * grace a la corrélation :
         * Si oui on ajoute avec le sens défini par une fonction
         * a faire
         * Sinon -> suivant
         */
        for (Attribute pot : potNewNode)
        {
            if (pot.name == A.getAttribute().name)
            {
                vector<pair<double, double>> XY_couple = getValues(newBayNode.getAttribute(), pot);
                int dir = order(XY_couple);
                Relationship newRel = Relationship(A, dir);
                newBayNode.addRelationship(newRel);
            }
        }
    }
    return newBayNode;
}

vector<Attribute> removeEl(vector<Attribute> myvector, Attribute att)
{
    set<Attribute> newset;
    for (long unsigned int j = 0; j < myvector.size(); j++)
    {
        if (myvector[j].name != att.name)
        {
            newset.insert(myvector[j]);
        }
    }
    vector<Attribute> v(newset.begin(), newset.end());
    return v;
}
