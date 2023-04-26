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
    bool operator<(const Attribute &other) const
    {
        return name < other.name;
    }
};