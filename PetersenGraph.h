#ifndef GUARD_PetersenGraph_h
#define GUARD_PetersenGraph_h

#include <list>
#include <vector>
#include <string>

class Node;

class PetersenGraph {
public:
	PetersenGraph(int);
	virtual ~PetersenGraph();
	void createInitialEdges();
	void createInitialNodes(int);
	void removeEdge();
	void printVersion();
	void print();
	void game();
	//std::vector<std::string> player1;
	//std::vector<std::string> player2;
	//void analysis(int);
    int getRandomNumber(int);
    int gameNumber;
    
private:
	int nodeNameCount; //Keeps track of what the name of the next Node will be
	std::list<Node*> nodeList;
	
};

#endif