#include "importfiles.hpp"
#include "Node.hpp"
#include <iostream>
#include <iterator>
#include <map>
using namespace std;

class Attribute
{
public:
    string name;
    string filename;
    int column;
};

vector<Attribute> list_att;
Attribute node;

Node prof = Node();

vector<string> pot(Attribute node)
{
    vector<double> nodeValues = getValue(node.filename, node.column);
    for (int i = 0; i < list_att.size(); i++)
    {
        Attribute A = list_att[i];
        vector<double> value = getValue(A.filename, A.column);
    }

    // TODO:la metrique
}
