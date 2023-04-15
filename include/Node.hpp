#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <string.h>

using namespace std;

class Node;
class Link
{
public:
    Link();
    Link(string filename);
    string getFilename() const;
    void setFilename(string filename);
    vector<Node> getClasses();
    void addClasses(Node classe);

private:
    string filename;
    vector<Node> classes;
};

class Node
{
public:
    Node();
    Node(string filename);
    string getFilename() const;
    void setFilename(string filename);
    vector<string> getAttribute();
    vector<Link> getLinks() const;
    void addLink(Link link);

private:
    string filename;
    vector<string> attributes;
    vector<Link> links;
};
