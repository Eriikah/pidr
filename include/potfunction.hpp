#include "importfiles.hpp"
#include "correlation.hpp"
#include "Node.hpp"
#include "utils.hpp"
#include <iostream>
#include <iterator>
#include <map>
#include <variant>
#include <algorithm>
#include <set>
using namespace std;

vector<Attribute> setupNodesAndLinks();

Node getClass(Attribute att);

vector<Node> scoutPath(Node startingNode, Node destinationNode, set<Node> visitedClasses, set<Node> vsistedLinks);

vector<Node> getPath(Attribute attributeX, Attribute attributeY);

vector<Element> pathStep(Element observedElement, vector<Node> path);

vector<Element> getLinkedElements(Element el, vector<Node> Path);

vector<pair<double, double>> getValues(Attribute X, Attribute Y);

vector<Attribute> pot(Attribute X, vector<Attribute> list_att);