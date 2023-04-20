#include "potfunction.hpp"

int main()
{
    setupNodesAndLinks();
    Attribute test1 = Attribute("Teaching Ability", "resources/Professeurs.csv", 2);
    Attribute test2 = Attribute("Satisfaction", "resources/Registration.csv", 1);
    // vector<Node> a = getPath(test1, test2);
    // for (Node i : a)
    // {
    //     cout << i.getFilename() << "\n";
    // }

    vector<vector<string>> coupleXY = getValues(test1, test2);

    for (long unsigned i = 0; i < coupleXY.size(); i++)
    {
        for (long unsigned j = 0; j < coupleXY[i].size(); j++)
        {
            cout << coupleXY[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
