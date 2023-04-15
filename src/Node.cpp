#include "Node.hpp"

Node::Node() : filename(""), attributes(vector<string>()), links(vector<Link>())
{
}

Node::Node(string filename) : filename(filename), attributes(vector<string>()), links(vector<Link>())
{
}

string Node::getFilename() const
{
    return this->filename;
}

void Node::setFilename(string filename)
{
    this->filename = filename;
}

vector<string> Node::getAttribute()
{
    if (this->attributes == vector<string>())
    {
        fstream file(filename, ios::in);
        string line, word;
        if (file.is_open())
        {
            getline(file, line);
            stringstream str(line);

            while (getline(str, word, ','))
            {
                this->attributes.push_back(word);
            }
        }

        else
        {
            cout << "Could not open the file\n";
        }
    }
    return this->attributes;
}

void Node::addLink(Link link)
{
    this->links.push_back(link);
}

Link::Link() : filename(""), classes(vector<Node>())
{
}
Link::Link(string filename) : filename(filename), classes(vector<Node>())
{
}

string Link::getFilename() const
{
    return this->filename;
}

void Link::setFilename(string filename)
{
    this->filename = filename;
}

vector<Node> Link::getClasses()
{
    return this->classes;
}

void Link::addClasses(Node classe)
{
    this->classes.push_back(classe);
}
