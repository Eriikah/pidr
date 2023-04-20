#include "potfunction.hpp"

using namespace std;

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
    follows.getAttribute();
    learns.getAttribute();
    teach.getAttribute();

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

        vector<Node> next_classes = begin_node.getNexts();

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
    return foundClass;
}

Node getClass(Attribute att)
{
    return getClassRec(att, prof, vector<Node>());
}

vector<Node> scoutPath(Node startingNode, Node destinationNode, set<Node> visitedClasses, set<Node> visitedLink)
{
    if (startingNode.getFilename() == destinationNode.getFilename())
    {
        vector<Node> path;
        return path;
    }
    else
    {
        vector<Node> pathStep;
        for (auto link : startingNode.getNexts())
        {
            if (visitedLink.find(link) == visitedLink.end())
            {
                pathStep.push_back(link);
                visitedLink.insert(link);
                for (auto pathClass : link.getNexts())
                {
                    if (visitedClasses.find(pathClass) == visitedClasses.end())
                    {
                        visitedClasses.insert(pathClass);
                        vector<Node> updatedPath = scoutPath(pathClass, destinationNode, visitedClasses, visitedLink);
                        pathStep.push_back(pathClass);
                        pathStep.insert(pathStep.end(), updatedPath.begin(), updatedPath.end());
                        return pathStep;
                    }
                }
            }
        }
        return pathStep;
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
        set<Node> visitedClasses = set<Node>();
        visitedClasses.emplace(ClassX);
        vector<Node> updatedPath = scoutPath(ClassX, ClassY, visitedClasses, set<Node>());

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
            if (first_column && (*it).first == observedElement.id)
            {
                second_column = false;
                Attribute ph_att = Attribute(pathNode.getAttribute()[1], filename, 0);
                Element added_elt;
                if (pathNode.isLink())
                {
                    added_elt = Element((*it).second, ph_att, "");
                }
                else
                {
                    added_elt = Element((*it).second, ph_att, observedElement.value);
                }
                names.push_back(added_elt);
            }
            else if (second_column && (*it).second == observedElement.id)
            {
                first_column = false;
                Attribute ph_att = Attribute(pathNode.getAttribute()[0], filename, 0);
                Element added_elt;
                if (pathNode.isLink())
                {
                    added_elt = Element((*it).first, ph_att, "");
                }
                else
                {
                    added_elt = Element((*it).first, ph_att, observedElement.value);
                }

                names.push_back(added_elt);
            }
        }
        return names;
    }
}
vector<Element> getLinkedElements(Element el, vector<Node> Path)
{
    vector<Element> buffer;
    if (getClass(el.att).getFilename() == Path.back().getFilename())
    {
        buffer.push_back(el);
        return buffer;
    }
    else
    {
        cout << "debug : getLinkedElements : recurssion " << el.id << "\n";
        vector<Element> list_next_el = pathStep(el, Path);
        cout << "debug : getLinkedElements : listnextel " << list_next_el.size() << "\n";

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
        // cout << "debug : getValues.Xelements : " << XElements[i].value << "\n";
        vector<Element> YElements = getLinkedElements(XElements[i], Path);
        cout << "debug : getValues Yelements : " << YElements.size() << "\n";

        for (long unsigned int j = 0; j < YElements.size(); j++)
        {
            vector<string> temp = vector<string>();
            temp.push_back(XElements[i].value);
            temp.push_back(YElements[j].id);
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
