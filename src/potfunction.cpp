#include "potfunction.hpp"

using namespace std;

Attribute node;

Node follows;
Node teach;
Node learns;

Node prof;
Node course;
Node students;
Node registration;
vector<Attribute> setupNodesAndLinks()
{
    vector<Attribute> list_att;
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
    int i = 0;
    for (auto att : prof.getAttribute())
    {
        if (i != 0)
        {
            list_att.push_back(Attribute(att, prof.getFilename(), i));
        }
        i++;
    }
    i = 0;
    for (auto att : course.getAttribute())
    {
        if (i != 0)
        {
            list_att.push_back(Attribute(att, course.getFilename(), i));
        }
        i++;
    }
    i = 0;
    for (auto att : students.getAttribute())
    {
        if (i != 0)
        {
            list_att.push_back(Attribute(att, students.getFilename(), i));
        }
        i++;
    }
    i = 0;
    for (auto att : registration.getAttribute())
    {
        if (i != 0)
        {
            list_att.push_back(Attribute(att, registration.getFilename(), i));
        }
        i++;
    }

    teach.addNext(&prof);
    course.addNext(&teach);
    follows.addNext(&students);
    registration.addNext(&follows);

    learns.addNext(&course);
    learns.addNext(&registration);
    course.addNext(&learns);
    teach.addNext(&course);

    registration.addNext(&learns);
    follows.addNext(&registration);

    students.addNext(&follows);
    prof.addNext(&teach);

    return list_att;
}

Node getClassRec(Attribute att, Node begin_node, vector<Node> already_visited)
{
    Node foundClass;
    bool next = true;
    if (begin_node.getFilename() == att.filename)
    {
        next = false;
        foundClass = begin_node;
    }

    if (next)
    {
        already_visited.push_back(begin_node);

        vector<Node *> next_classes = begin_node.getNexts();

        for (long unsigned int j = 0; j < next_classes.size(); j++)
        {
            bool ok = true;
            for (long unsigned k = 0; k < already_visited.size(); k++)
            {
                if ((*next_classes[j]).getFilename() == already_visited[k].getFilename())
                {
                    ok = false;
                    break;
                }
            }
            if (ok)
            {
                foundClass = getClassRec(att, *next_classes[j], already_visited);
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
        visitedClasses.insert(startingNode);
        vector<Node> pathStep;
        for (auto link : startingNode.getNexts())
        {
            if (visitedLink.find(*link) == visitedLink.end())
            {
                pathStep.push_back(*link);
                visitedLink.insert(*link);
                for (auto pathClass : (*link).getNexts())
                {
                    if (visitedClasses.find(*pathClass) == visitedClasses.end())
                    {
                        visitedClasses.insert(*pathClass);
                        vector<Node> updatedPath = scoutPath(*pathClass, destinationNode, visitedClasses, visitedLink);
                        pathStep.push_back(*pathClass);
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

        path.insert(path.end(), updatedPath.begin(), updatedPath.end());
    }
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
        string filename = pathNode.getFilename();
        if (!pathNode.isLink())
        {
            names.push_back(Element(observedElement.id, Attribute(pathNode.getAttribute()[0], filename, 0), observedElement.value));
        }
        else
        {
            for (auto val : linkValues)
            {
                bool first_column = true;
                bool second_column = true;
                if (first_column && val.first == observedElement.id)
                {
                    second_column = false;
                    Attribute ph_att = Attribute(pathNode.getAttribute()[1], filename, 0);
                    names.push_back(Element(val.second, ph_att, observedElement.value));
                }
                else if (second_column && val.second == observedElement.id)
                {
                    first_column = false;
                    Attribute ph_att = Attribute(pathNode.getAttribute()[0], filename, 0);
                    names.push_back(Element(val.first, ph_att, observedElement.value));
                }
            }
        }
        return names;
    }
}

vector<Element> getLinkedElements(Element el, vector<Node> Path, int endColumn)
{
    vector<Element> buffer;
    if (getClass(el.att).getFilename() == Path.back().getFilename())
    {
        el.att.column = endColumn;
        vector<Element> all = getElements(el.att);
        for (Element fileElement : all)
        {
            if (fileElement.id == el.id)
            {
                buffer.push_back(fileElement);
            }
        }
        return buffer;
    }
    else
    {
        vector<Element> list_next_el = pathStep(el, Path);
        if (list_next_el.size() > 0)
        {
            for (auto elt : list_next_el)
            {
                vector<Element> newlist = getLinkedElements(elt, Path, endColumn);
                buffer.insert(buffer.end(), newlist.begin(), newlist.end());
            }
        }

        return buffer;
    }
}

vector<pair<double, double>> getValues(Attribute X, Attribute Y)
{
    vector<Node> Path = getPath(X, Y);
    vector<pair<double, double>> CouplesXY;
    vector<Element> XElements = getElements(X);
    for (long unsigned int i = 0; i < XElements.size(); i++)
    {
        vector<Element> YElements = getLinkedElements(XElements[i], Path, Y.column);
        for (long unsigned int j = 0; j < YElements.size(); j++)
        {
            CouplesXY.push_back(
                make_pair(convert(XElements[i].value), convert(YElements[j].value)));
        }
    }

    return CouplesXY;
}

vector<Attribute> pot(Attribute X, vector<Attribute> list_att)
{
    vector<Attribute> list_pot = vector<Attribute>();
    multimap<string, double> X_val = buildValueMap(X.filename, X.column);
    Node ClassX = getClass(X);
    for (auto Y : list_att)
    {
        if (!(Y.name == X.name && Y.filename == X.filename) && Y.column != 0)
        {
            Node ClassY = getClass(Y);
            multimap<string, double> Y_val = buildValueMap(Y.filename, Y.column);
            vector<pair<double, double>> XY_couple = getValues(X, Y);
            double corr = correlation(XY_couple);
            cout << corr << "\n";
            if (abs(corr) > 0.15)
            {
                list_pot.push_back(Y);
            }
        }
    }
    return list_pot;
}
