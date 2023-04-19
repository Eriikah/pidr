#include "Node.hpp"
#include "utils.hpp"

Node::Node() : filename(""), attributes(vector<string>()), links(vector<Node>()), isLink(false)
{
}

Node::Node(string filename, bool islink) : filename(filename), attributes(vector<string>()), links(vector<Node>()), isLink(islink)
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
                removeEscapeCharacters(word);
                this->attributes.push_back(word);
            }
        }

        else
        {
            cout << "Could not open the file" << filename.c_str() << "\n";
        }
    }
    return this->attributes;
}

vector<Node> Node::getNexts() const
{
    return this->links;
}

void Node::addNext(Node link)
{
    this->links.push_back(link);
}
