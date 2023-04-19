#include <string>

using namespace std;

class Attribute
{
public:
    string name;
    string filename;
    int column;
    Attribute();
    Attribute(string name, string filename, int column);
};