#include "newBayNodeBuilder.hpp"

// renvoie toutes les alternatives
using namespace std;

void newBayNodeBuilder(BayesianNode newBayNode, vector<BayesianNode> S_prev, vector<Attribute> list_att)
{
    vector<Attribute> potNewNode = pot(*(newBayNode.getAttribute()), list_att);
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

            if (A.getAttribute()->name == pot.name)
            {
                int dir = 1;
                Relationship newRel = Relationship(&A, dir);
                newBayNode.addRelationship(&newRel);
            }
        }
    }
}

vector<Attribute> removeEl(vector<Attribute> myvector, Attribute att)
{
    for (unsigned i = 0; i < myvector.size(); ++i)
    {
        if (myvector[i].name == att.name)
        {
            myvector.erase(myvector.begin() + i);
        }
    }
    return myvector;
}
