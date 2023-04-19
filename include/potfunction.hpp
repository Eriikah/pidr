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

void setupNodesAndLinks();

Node getClass(Attribute att);

vector<Node> scoutPath(Node startingNode, Node destinationNode, set<Node> visitedClasses);

vector<Node> getPath(Attribute attributeX, Attribute attributeY);

vector<Element> pathStep(Element observedElement, vector<Node> path);

vector<Element> getLinkedElements(Element el, vector<Node> Path);

vector<vector<string>> getValues(Attribute X, Attribute Y);

vector<string> pot(Attribute node);