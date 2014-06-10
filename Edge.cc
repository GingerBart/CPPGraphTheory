//Edge.cc

#include <list>

#include "Edge.h"

Edge::Edge(Node* n1, Node* n2, int w)
{
	connectedNodes.push_back(n1);
	connectedNodes.push_back(n2);
	weight = w;
}	

Edge::~Edge()
{
	while(!connectedNodes.empty()) 
	{
		delete connectedNodes.front();
		connectedNodes.pop_front();
	}
	connectedNodes.clear();
}

int Edge::getWeight()
{
	return weight;
}
	
void Edge::setWeight(int w)
{
	weight = w;
}

Node* Edge::returnNode1()
{
	return connectedNodes.front();
}

Node* Edge::returnNode2()
{
	return connectedNodes.back();
}