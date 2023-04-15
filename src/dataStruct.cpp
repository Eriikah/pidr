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

    prof.addLink(teach);
    registration.addLink(follows);
    registration.addLink(learns);
    course.addLink(teach);
    course.addLink(learns);
    students.addLink(follows);

    teach.addClasses(prof);
    teach.addClasses(course);
    learns.addClasses(course);
    learns.addClasses(registration);
    follows.addClasses(students);
    follows.addClasses(registration);
}

vector<string>
pot(Attribute node)
{
    vector<string> list_pot = vector<string>();
    vector<double> nodeValues = getValue(node.filename, node.column);
    for (long unsigned int i = 0; i < list_att.size(); i++)
    {
        Attribute A = list_att[i];
        vector<double> value = getValue(A.filename, A.column);
    }

    // TODO:la metrique
    return list_pot;
}
