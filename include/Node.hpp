#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <string.h>

using namespace std;

class Node
{
public:
    Node();
    Node(string filename, bool islink);
    string getFilename() const;
    void setFilename(string filename);
    vector<string> getAttribute();
    vector<Node> getNexts() const;
    void addNext(Node link);
    bool isLink();

    bool operator==(const Node &other) const
    {
        return filename == other.filename;
    }
    bool operator<(const Node &other) const
    {
        return filename < other.filename;
    }

private:
    string filename;
    vector<string> attributes;
    vector<Node> links;
    bool link;
};
