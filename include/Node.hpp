#include <string>
#include <vector>

using namespace std;

class Node
{
public:
    string filename;
    vector<string> attributes;
    vector<Link> links;
};

class Link
{
public:
    string filename;
    vector<Node> classes;
};