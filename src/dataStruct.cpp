#include "importfiles.hpp"
#include "Node.hpp"
#include "utils.hpp"
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
    Attribute();
    Attribute(string name, string filename, int column);
};
Attribute::Attribute() : name(""), filename(""), column(0)
{
}

Attribute::Attribute(string name, string filename, int column) : name(name), filename(filename), column(column)
{
}
vector<Attribute> list_att;
Attribute node;

Link follows;
Link teach;
Link learns;

Node prof;
Node course;
Node students;
Node registration;
void setupNodesAndLinks()
{
    follows = Link("resources/Follows.csv");
    teach = Link("resources/teach.csv");
    learns = Link("resources/Learns.csv");

    prof = Node("resources/Professeurs.csv");
    course = Node("resources/courses.csv");
    students = Node("resources/Students.csv");
    registration = Node("resources/Registration.csv");

    teach.addClasses(prof);
    course.addLink(teach);
    follows.addClasses(students);
    registration.addLink(follows);

    learns.addClasses(course);
    learns.addClasses(registration);
    course.addLink(learns);
    teach.addClasses(course);

    registration.addLink(learns);
    follows.addClasses(registration);

    students.addLink(follows);
    prof.addLink(teach);
}

Node getClass(Attribute att, Node begin_node, vector<Node> already_visited)
{
    Node foundClass;
    bool next = true;
    vector<string> atts = begin_node.getAttribute();
    for (long unsigned int k = 0; k < atts.size(); k++)
    {
        if (atts[k] == att.name)
        {
            next = false;
            foundClass = begin_node;
        }
    }
    if (next)
    {
        already_visited.push_back(begin_node);
        vector<Link> links = begin_node.getLinks();
        for (long unsigned int i = 0; i < links.size(); i++)
        {
            vector<Node> next_classes = links[i].getClasses();

            for (long unsigned int j = 0; j < next_classes.size(); j++)
            {
                bool ok = true;
                for (long unsigned k = 0; k < already_visited.size(); k++)
                {
                    if (next_classes[j].getFilename() == already_visited[k].getFilename())
                    {
                        ok = false;
                        break;
                    }
                }
                if (ok)
                {
                    foundClass = getClass(att, next_classes[j], already_visited);
                }
            }
        }
    }
    return foundClass;
}

// void getValues(AttributeX, AttributeY) {}
vector<string> pot(Attribute node)
{
    vector<string> list_pot = vector<string>();
    vector<double> nodeValues = getValue(node.filename, node.column);
    Node ClassX = getClass(node, prof, vector<Node>());
    for (long unsigned int i = 0; i < list_att.size(); i++)
    {
        Attribute A = list_att[i];
        Node ClassY = getClass(A, prof, vector<Node>());

        vector<double> value = getValue(A.filename, A.column);
    }
    // TODO:la metrique
    return list_pot;
}
int main()
{
    setupNodesAndLinks();
    Attribute test = Attribute("Rating", "resources/Professeurs.csv", 1);
    // cout << getClass(test, prof, vector<Node>()).getFilename() << "\n";

    return 0;
}
