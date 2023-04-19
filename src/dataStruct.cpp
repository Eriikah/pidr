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

Node follows;
Node teach;
Node learns;

Node prof;
Node course;
Node students;
Node registration;
void setupNodesAndLinks()
{
    follows = Node("resources/Follows.csv", true);
    teach = Node("resources/teach.csv", true);
    learns = Node("resources/Learns.csv", true);

    prof = Node("resources/Professeurs.csv", false);
    course = Node("resources/courses.csv", false);
    students = Node("resources/Students.csv", false);
    registration = Node("resources/Registration.csv", false);

    teach.addNext(prof);
    course.addNext(teach);
    follows.addNext(students);
    registration.addNext(follows);

    learns.addNext(course);
    learns.addNext(registration);
    course.addNext(learns);
    teach.addNext(course);

    registration.addNext(learns);
    follows.addNext(registration);

    students.addNext(follows);
    prof.addNext(teach);
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
        vector<Node> links = begin_node.getNexts();
        for (long unsigned int i = 0; i < links.size(); i++)
        {
            vector<Node> next_classes = links[i].getNexts();

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

vector<Node> scoutPath(Node startingNode, Node destinationNode, set<Node> visitedClasses)
{
    if (startingNode.getFilename() == destinationNode.getFilename())
    {
        vector<Node> path;
        path.push_back(startingNode);
        return path;
    }
    else
    {
        vector<Node> pathStep;
        for (auto link : startingNode.getNexts())
        {
            pathStep.push_back(link);
            for (auto pathClass : link.getNexts())
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
                    vector<Node> updatedPath = scoutPath(pathClass, destinationNode, visitedClasses);
                    pathStep.insert(pathStep.end(), updatedPath.begin(), updatedPath.end());
                    return pathStep;
                }
            }
        }
    }
}

vector<Node> getPath(Attribute attributeX, Attribute attributeY)
{
    Node ClassX = getClass(attributeX);
    Node ClassY = getClass(attributeY);
    vector<Node> path;
    path.push_back(ClassX);

    if (ClassX.getFilename() != ClassY.getFilename())
    {
        Node lookedNode = ClassX;
        set<Node> visitedClasses;
        vector<Node> updatedPath = scoutPath(ClassX, ClassY, visitedClasses);

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

vector<Element> pathStep(Element observedElement, vector<Node> path)
{
    Attribute observedAttribute = observedElement.att;
    Node observedClass = getClass(observedAttribute);
    if (observedClass.getFilename() == path.back().getFilename())
    {
        vector<Element> placeholder;
        return placeholder;
    }
    else
    {
        Node pathNode;
        for (vector<Node>::iterator it = path.begin(); it != path.end(); ++it)
        {
            if ((*it).getFilename() == observedClass.getFilename())
            {
                ++it;
                pathNode = *it;
            }
        }
        vector<pair<string, string>> linkValues = getLinkValues(pathNode.getFilename());
        vector<Element> names;
        for (vector<pair<string, string>>::iterator it = linkValues.begin(); it != linkValues.end(); ++it)
        {
            bool first_column = true;
            bool second_column = true;
            string filename = pathNode.getFilename();
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
vector<Element> getLinkedElements(Element el, vector<Node> Path)
{
    cout << "debug : bonjour";
    vector<Element> buffer;
    if (getClass(el.att).getFilename() == Path.back().getFilename())
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
    vector<Node> Path = getPath(X, Y);
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
