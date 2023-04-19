#include "importfiles.hpp"
#include "Node.hpp"
#include "utils.hpp"
#include <iostream>
#include <iterator>
#include <map>
#include <variant>
#include <algorithm>
#include <set>
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

class Element
{
public:
    string id;
    Attribute att;
    string value;
    Element();
    Element(string id, Attribute att, string value);
};
Element::Element() : id(""), att(Attribute()), value("")
{
}
Element::Element(string id, Attribute att, string value) : id(id), att(att), value(value)
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

vector<Element> getElements(Attribute X)
{
    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    fstream file(X.filename, ios::in);
    if (file.is_open())
    {

        while (getline(file, line))
        {
            row.clear();

            stringstream str(line);

            while (getline(str, word, ','))
            {
                removeEscapeCharacters(word);
                row.push_back(word);
            }
            content.push_back(row);
        }
    }
    else
    {
        cout << "Could not open the file\n";
    }

    vector<Element> all_Els = vector<Element>();
    long unsigned int k = X.column;
    for (long unsigned int i = 0; i < content.size(); i++)
    {
        Element temp = Element(content[i][0], X, content[i][k]);
        all_Els.push_back(temp);
    }
    return all_Els;
}

Node getClassRec(Attribute att, Node begin_node, vector<Node> already_visited)
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
                    foundClass = getClassRec(att, next_classes[j], already_visited);
                }
            }
        }
    }
    return foundClass;
}

Node getClass(Attribute att)
{
    return getClassRec(att, prof, vector<Node>());
}

vector<variant<Node, Link>> scoutPath(Node startingNode, Node destinationNode, set<Node> visitedClasses)
{
    if (startingNode.getFilename() == destinationNode.getFilename())
    {
        vector<variant<Node, Link>> path;
        path.push_back(startingNode);
        return path;
    }
    else
    {
        vector<variant<Node, Link>> pathStep;
        for (auto link : startingNode.getLinks())
        {
            pathStep.push_back(link);
            for (auto pathClass : link.getClasses())
            {
                for (Node const &node : visitedClasses)
                {
                    cout << "debug: " << node.getFilename() << ' ';
                }
                cout << "\n";

                if (visitedClasses.find(pathClass) == visitedClasses.end())
                {
                    cout << "debug: " << pathClass.getAttribute()[1] << "\n";
                    visitedClasses.insert(pathClass);
                    vector<variant<Node, Link>> updatedPath = scoutPath(pathClass, destinationNode, visitedClasses);
                    pathStep.insert(pathStep.end(), updatedPath.begin(), updatedPath.end());
                    return pathStep;
                }
            }
        }
    }
}

vector<variant<Node, Link>> getPath(Attribute attributeX, Attribute attributeY)
{
    Node ClassX = getClass(attributeX);
    Node ClassY = getClass(attributeY);
    vector<variant<Node, Link>> path;
    path.push_back(ClassX);

    if (ClassX.getFilename() != ClassY.getFilename())
    {
        Node lookedNode = ClassX;
        set<Node> visitedClasses;
        vector<variant<Node, Link>> updatedPath = scoutPath(ClassX, ClassY, visitedClasses);

        // for (int i = 0; i < updatedPath.size(); i++)
        // {
        //     cout << "debug : scoutpath.updatedPath : " << visit(GetFilenameVisitor{}, updatedPath[i]) << "\n";
        // }
        path.insert(path.end(), updatedPath.begin(), updatedPath.end());
    }
    // for (int i = 0; i < path.size(); i++)
    // {
    //     cout << "debug : scoutpath.path : " << visit(GetFilenameVisitor{}, path[i]) << "\n";
    // }
    return path;
}

vector<Element> pathStep(Element observedElement, vector<variant<Node, Link>> path)
{
    Attribute observedAttribute = observedElement.att;
    Node observedClass = getClass(observedAttribute);
    if (observedClass.getFilename() == visit(GetFilenameVisitor{}, *path.end()))
    {
        vector<Element> placeholder;
        return placeholder;
    }
    else
    {
        variant<Node, Link> pathNode;
        for (vector<variant<Node, Link>>::iterator it = path.begin(); it != path.end(); ++it)
        {
            if (visit(GetFilenameVisitor{}, *it) == observedClass.getFilename())
            {
                ++it;
                pathNode = *it;
            }
        }
        vector<pair<string, string>> linkValues = getLinkValues(visit(GetFilenameVisitor{}, pathNode));
        vector<Element> names;
        for (vector<pair<string, string>>::iterator it = linkValues.begin(); it != linkValues.end(); ++it)
        {
            bool first_column = true;
            bool second_column = true;
            string filename = visit(GetFilenameVisitor{}, pathNode);
            if (first_column && (*it).first == observedAttribute.name)
            {
                second_column = false;
                Attribute ph_att = Attribute((*it).second, filename, 0);
                Element added_elt = Element((*it).second, ph_att, "");
                names.push_back(added_elt);
            }
            else if (second_column && (*it).second == observedAttribute.name)
            {
                first_column = false;
                Attribute ph_att = Attribute((*it).first, filename, 0);
                Element added_elt = Element((*it).first, ph_att, "");
                names.push_back(added_elt);
            }
        }
        return names;
    }
}
vector<Element> getLinkedElements(Element el, vector<variant<Node, Link>> Path)
{
    cout << "debug : bonjour";
    vector<Element> buffer;
    if (getClass(el.att).getFilename() == visit(GetFilenameVisitor{}, Path.back()))
    {
        cout << "debug : getLinkedElements : condition d'arret";
        buffer.push_back(el);
        return buffer;
    }
    else
    {
        cout << "debug : getLinkedElements : recurssion";
        vector<Element> list_next_el = pathStep(el, Path);
        for (long unsigned int i = 0; i < list_next_el.size(); i++)
        {
            vector<Element> newlist = getLinkedElements(list_next_el[i], Path);
            buffer.insert(buffer.end(), newlist.begin(), newlist.end());
        }
        return buffer;
    }
}

vector<vector<string>> getValues(Attribute X, Attribute Y)
{
    vector<variant<Node, Link>> Path = getPath(X, Y);
    vector<vector<string>> CouplesXY;
    vector<Element> XElements = getElements(X);
    for (long unsigned int i = 0; i < XElements.size(); i++)
    {
        cout << "debug : getValues.Xelements : " << XElements[i].id << "\n";
        vector<Element> YElements = getLinkedElements(XElements[i], Path);
        cout << "debug : getValues Yelements : " << YElements.size() << "\n";

        for (long unsigned int j = 0; j < YElements.size(); j++)
        {
            vector<string> temp = vector<string>();
            temp.push_back(XElements[i].value);
            temp.push_back(YElements[j].value);
            CouplesXY.push_back(temp);
        }
    }

    return CouplesXY;
}

vector<string> pot(Attribute node)
{
    vector<string> list_pot = vector<string>();
    vector<double> nodeValues = getValue(node.filename, node.column);
    Node ClassX = getClass(node);
    for (long unsigned int i = 0; i < list_att.size(); i++)
    {
        Attribute A = list_att[i];
        Node ClassY = getClass(A);

        vector<double> value = getValue(A.filename, A.column);
    }
    // TODO:la metrique
    return list_pot;
}

int main()
{
    setupNodesAndLinks();
    Attribute test1 = Attribute("Rating", "resources/Professeurs.csv", 2);
    Attribute test2 = Attribute("Teaching Ability", "resources/courses.csv", 1);
    // cout << getClass(test, prof, vector<Node>()).getFilename() << "\n";
    // vector<Element> a = getElements(test2);
    vector<vector<string>> coupleXY = getValues(test1, test2);

    // for (long unsigned i = 0; i < a.size(); i++)
    // {
    //     cout << a[i].id.c_str() << " " << a[i].value.c_str() << "\n";
    // }

    // for (long unsigned i = 0; i < coupleXY.size(); i++)
    // {
    //     for (long unsigned j = 0; j < coupleXY[i].size(); j++)
    //     {
    //         cout << coupleXY[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    return 0;
}
