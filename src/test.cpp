#include "potfunction.hpp"

int main()
{

    vector<Attribute> list_att = setupNodesAndLinks();
    Attribute test1 = Attribute("Teaching Ability", "resources/Professeurs.csv", 2);
    Attribute test2 = Attribute("Ranking", "resources/Students.csv", 2);
    // vector<Element> a = getElements(test1);
    // for (Element i : a)
    // {
    //     cout << i.value << "\n";
    // }

    vector<pair<double, double>> coupleXY = getValues(test1, test2);

    // for (long unsigned i = 0; i < coupleXY.size(); i++)
    // {
    //     for (long unsigned j = 0; j < coupleXY[i].size(); j++)
    //     {
    //         cout << coupleXY[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    vector<Attribute> pot1 = pot(test1, list_att);

    for (auto att : pot1)
    {
        cout << att.filename << " : " << att.name << "\n";
    }

    return 0;
}
