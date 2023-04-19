#include "potfunction.hpp"

int main()
{
    setupNodesAndLinks();
    Attribute test1 = Attribute("Rating", "resources/Professeurs.csv", 2);
    Attribute test2 = Attribute("Teaching Ability", "resources/courses.csv", 1);
    // cout << getClass(test, prof, vector<Node>()).getFilename() << "\n";
    // vector<Element> a = getElements(test2);
    vector<vector<string>> coupleXY = getValues(test1, test2);

    // for (long unsigned i = 0; i < a.size(); i++)
    // {
    //     cout << a[i].id.c_str() << " " << a[i].value.c_str() << "\n";
    // }

    // for (long unsigned i = 0; i < coupleXY.size(); i++)
    // {
    //     for (long unsigned j = 0; j < coupleXY[i].size(); j++)
    //     {
    //         cout << coupleXY[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    return 0;
}
