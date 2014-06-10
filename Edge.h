#ifndef GUARD_Edge_h
#define GUARD_Edge_h

#include <list>

#include "Node.h"

class Edge {
public:
	Edge(Node*, Node*, int);
	virtual ~Edge();
	int getWeight();
	void setWeight(int);
	Node* returnNode1();
	Node* returnNode2();

private:
	int weight;
	std::list<Node*> connectedNodes;
};

#endif