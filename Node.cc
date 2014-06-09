#include "Node.h"

#include <list>
#include <iostream>
#include <algorithm>


Node::Node(int n)
{
	name = n;
}

Node::~Node()
{
}

int Node::getName()
{
	return name;
}

void Node::printEdges()
{
	std::cout << "Node " << name << " is connected to the following nodes: " << std::endl;
	std::list<Node*>::iterator iter;
	if (edgeList.size() == 0)
	{
		std::cout << "This node is not connected to any other node" << std::endl;
	}
	else
	{
		for (iter = edgeList.begin(); iter != edgeList.end(); iter++)
		{
			std::cout << "N" << name << " - N" << (*iter)->getName() << std::endl;
		}
	}
	std::cout << std::endl;
}

int Node::getEdgeListSize()
{
	return edgeList.size();
}

Node* Node::getNodeAtElement(int i)
{
    std::list<Node*>::iterator iter = edgeList.begin();
    std::advance(iter, i);
    return *iter;
}

void Node::setEdge(Node* n1)
{
	edgeList.push_back(n1);
	edgeList.sort();
}

bool Node::edgeExists(int n1)
{
	bool answer = false;
	std::list<Node*>::iterator iter;
	for (iter = edgeList.begin(); iter != edgeList.end(); iter++)
	{
		if ((*iter)->getName() == n1)
		{
			answer = true;
		}
		else
		{
			answer = false;
		}
	}
	return answer;
}

void Node::destroyEdge(Node* n1)
{
	edgeList.remove(n1);
}