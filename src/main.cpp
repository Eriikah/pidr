#include "newBayNodeBuilder.hpp"

using namespace std;
#include <cassert>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

template <typename T>
class unique_queue
{
private:
    std::queue<T> m_queue;
    std::set<T> m_set;

public:
    bool push(const T &t)
    {
        if (m_set.insert(t).second)
        {
            m_queue.push(t);
            return true;
        }
        return false;
    }

    void pop()
    {
        assert(!m_queue.empty());
        const T &val = front();

        typename std::set<T>::iterator it = m_set.find(val);
        assert(it != m_set.end());

        m_set.erase(it);
        m_queue.pop();
    }

    const T &front() const
    {
        return m_queue.front();
    }

    long unsigned int size()
    {
        return m_queue.size();
    }
};

int main()
{
    vector<Attribute> list_att = setupNodesAndLinks();
    vector<Attribute> att_restants = setupNodesAndLinks();
    Attribute first = list_att[0];
    list_att = removeEl(list_att, first);
    vector<Attribute> Suivants = pot(first, list_att);

    unique_queue<Attribute> Suiv;
    for (long unsigned int i = 0; i < Suivants.size(); i++)
    {
        Suiv.push(Suivants[i]);
    }
    vector<BayesianNode> S;
    S.push_back(BayesianNode(first));
    vector<BayesianNode> S_prev = S;
    while (att_restants.size() != 0 && Suiv.size() != 0)
    {
        BayesianNode bayNode = BayesianNode(Suiv.front());
        att_restants = removeEl(att_restants, Suiv.front());
        S_prev = S;
        bayNode = newBayNodeBuilder(bayNode, S_prev, list_att);
        S.push_back(bayNode);
        vector<Attribute> nextPots = pot(bayNode.getAttribute(), list_att);
        for (long unsigned int i = 0; i < nextPots.size(); i++)
        {
            for (Attribute att : att_restants)
            {
                if (att.name == nextPots[i].name)
                {
                    Suiv.push(nextPots[i]);
                }
            }
        }

        Suiv.pop();
    }
    for (BayesianNode node : S)
    {
        node.print(0);
        cout << "\n";
    }
    return 0;
}