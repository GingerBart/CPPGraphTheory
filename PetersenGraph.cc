#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>	
//#include <boolean>					

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "Token.h"
#include "Node.h"
#include "PetersenGraph.h"
#include "RandomEngine.h"

/*
 This is the .cpp file for the PetersenGraph object.
 */

//Desc: Constructor for the PetersenGraph object. Constructs a PetersenGraph of Nodes,
//		and creates edges between them.
//Input: int i for the number of Nodes
PetersenGraph::PetersenGraph(int i, bool b)
{
	gameNumber = i;
	watch = b;
	nodeNameCount = 0;
	for (int k = 1; k <= 10; k++)
	{
		createInitialNodes(k);
		nodeNameCount++;
	}
	createInitialEdges();
	std::ofstream myfile;
	game();
}
//analysis(numGames);


//Desc: Destructor for the PetersenGraph object. Deletes the nodeList
//		and frees up memory.
PetersenGraph::~PetersenGraph()
{
	while(!nodeList.empty()) {
		delete nodeList.front();
		nodeList.pop_front();
	}
	nodeList.clear();
	//player1.clear();
	//player2.clear();
}

//Desc: Creates the initial edges
void PetersenGraph::createInitialEdges()
{
	std::list<Node*>::iterator iter1 = nodeList.begin();
	std::list<Node*>::iterator iter2 = nodeList.begin();
	std::advance(iter2, 1);
	(*iter1)->setEdge(*iter2);
	std::advance(iter2, 3);
	(*iter1)->setEdge(*iter2);
	std::advance(iter2, 1);
	(*iter1)->setEdge(*iter2);
	iter2 = nodeList.begin();
	std::advance(iter1, 1);
	(*iter1)->setEdge(*iter2);
	std::advance(iter2, 2);
	(*iter1)->setEdge(*iter2);
	std::advance(iter2, 4);
	(*iter1)->setEdge(*iter2);
	std::advance(iter1, 1);
	iter2 = nodeList.begin();
	std::advance(iter2, 1);
	(*iter1)->setEdge(*iter2);
	std::advance(iter2, 2);
	(*iter1)->setEdge(*iter2);
	std::advance(iter2, 4);
	(*iter1)->setEdge(*iter2);
	std::advance(iter1, 1);
	iter2 = nodeList.begin();
	std::advance(iter2, 2);
	(*iter1)->setEdge(*iter2);
	std::advance(iter2, 2);
	(*iter1)->setEdge(*iter2);
	std::advance(iter2, 4);
	(*iter1)->setEdge(*iter2);
	std::advance(iter1, 1);
	iter2 = nodeList.begin();
	(*iter1)->setEdge(*iter2);
	std::advance(iter2, 3);
	(*iter1)->setEdge(*iter2);
	std::advance(iter2, 6);
	(*iter1)->setEdge(*iter2);
	std::advance(iter1, 1);
	iter2 = nodeList.begin();
	(*iter1)->setEdge(*iter2);
	std::advance(iter2, 7);
	(*iter1)->setEdge(*iter2);
	std::advance(iter2, 1);
	(*iter1)->setEdge(*iter2);
	std::advance(iter1, 1);
	iter2 = nodeList.begin();
	std::advance(iter2, 1);
	(*iter1)->setEdge(*iter2);
	std::advance(iter2, 7);
	(*iter1)->setEdge(*iter2);
	std::advance(iter2, 1);
	(*iter1)->setEdge(*iter2);
	std::advance(iter1, 1);
	iter2 = nodeList.begin();
	std::advance(iter2, 2);
	(*iter1)->setEdge(*iter2);
	std::advance(iter2, 3);
	(*iter1)->setEdge(*iter2);
	std::advance(iter2, 4);
	(*iter1)->setEdge(*iter2);
	std::advance(iter1, 1);
	iter2 = nodeList.begin();
	std::advance(iter2, 3);
	(*iter1)->setEdge(*iter2);
	std::advance(iter2, 2);
	(*iter1)->setEdge(*iter2);
	std::advance(iter2, 1);
	(*iter1)->setEdge(*iter2);
	std::advance(iter1, 1);
	iter2 = nodeList.begin();
	std::advance(iter2, 4);
	(*iter1)->setEdge(*iter2);
	std::advance(iter2, 2);
	(*iter1)->setEdge(*iter2);
	std::advance(iter2, 1);
	(*iter1)->setEdge(*iter2);
	
}

//Desc: Creates the initial Nodes
//Input: int i, which is the name of the Node
void PetersenGraph::createInitialNodes(int i)
{
	Node *n = new Node(i);
	nodeList.push_back(n);
}

void PetersenGraph::removeEdge()
{
	int n1 = 0;
	int n2 = 0;
	std::cout << "Please enter the nodes you would like to remove the edge between (x y): ";
	std::cin >> n1;
	std::cin >> n2;
	std::list<Node*>::iterator iter1;
	std::list<Node*>::iterator iter2;
	for (iter1 = nodeList.begin(); iter1 != nodeList.end(); iter1++)
	{
		if ((*iter1)->getName() == n1)
		{
			for (iter2 = nodeList.begin(); iter2 != nodeList.end(); iter2++)
			{
				if ((*iter2)->getName() == n2)
				{
					(*iter1)->destroyEdge(*iter2);
					(*iter2)->destroyEdge(*iter1);
				}
			}
		}
	}
}

//Desc: Prints out the current version of the program the user is running
void PetersenGraph::printVersion()
{
	std::cout << std::endl;
	std::cout << "Version: 0.2 Beta" << std::endl;
	std::cout << "Author: Kyle Rodgers" << std::endl;
	std::cout << "Date of Last Revision: 5/4/14 23:30" << std::endl;
}

void PetersenGraph::print()
{
	std::cout << "This surface contains the following nodes and edges: " << std::endl;
	std::list<Node*>::iterator iter;
	for (iter = nodeList.begin(); iter != nodeList.end(); iter++)
	{
		(*iter)->printEdges();
	}
}

int PetersenGraph::getRandomNumber(int size)
{
	
	RandomEngine *rand = RandomEngine::instance();
	double r = rand->getRandom();
	int randNum = (int)(r * size);
	return randNum;
}

//This is the method that plays the game
//The master data is sent to the file /output_data/mater_data.txt

void PetersenGraph::rotateBar()
{
	barCount++;
	char barspin[4] = {'\\', '|', '/', '-'};
	int whichOne;
	whichOne = barCount % 4;
	if (whichOne == 3)
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while the games are played. Game: " << gameNumber;
	}
	else
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while the games are played. Game: " << gameNumber;
	}
	std::cout.flush();
	return;
}

void PetersenGraph::game()
{
	std::ofstream myfile;
	//myfile.open("logs/log.txt");
	
	
	//std::string moves;
//	std::string gameName = std::to_string(i) + ".txt";
	std::string master_data_path = "output_data/master_data.txt";
	
//	myfile.open(path+gameName);
	myfile.open(master_data_path, std::ios_base::app);
	std::list<Node*>::iterator iter1 = nodeList.begin();
	Node* nextMoveNode;
	Token* t = new Token(*iter1);
	int nextMove = 0;
	if (watch == true)
	{
		std::cout << "Game " << gameNumber << std::endl;
		std::cout << std::endl;
		myfile << (t->getTokenLocation())->getName() << "-";
		while (true)
		{
    	    nextMove = getRandomNumber(t->getTokenLocation()->getEdgeListSize());
        	nextMoveNode = t->getTokenLocation()->getNodeAtElement(nextMove);
			(t->getTokenLocation())->destroyEdge(nextMoveNode);
	        (nextMoveNode)->destroyEdge(t->getTokenLocation());
	        std::cout << "Player " << t->getCurrentPlayerTurn() << " removed edge " << (t->getTokenLocation())->getName() << " - " << (nextMoveNode)->getName() << std::endl;
	        //myfile << "Player " << t->getCurrentPlayerTurn() << " removed edge " << (t->getTokenLocation())->getName() << " - " << (nextMoveNode)->getName() << std::endl;
	        t->setPlayerTurn();
	        t->setTokenLocation(nextMoveNode);
	        if (t->getTokenLocation()->getEdgeListSize() == 0)
			{
				//moves += std::to_string((t->getTokenLocation())->getName());
				t->setPlayerTurn();
				std::cout << std::endl;
				//myfile << "Player " << t->getCurrentPlayerTurn() << " wins!\n";
				myfile << t->getCurrentPlayerTurn() << std::endl;		
				std::cout << "Player " << t->getCurrentPlayerTurn() << " wins!" << std::endl;
				std::cout << std::endl;
				break;
			}
			myfile << (t->getTokenLocation())->getName() << "-";
			//moves += std::to_string((t->getTokenLocation())->getName()) + "-";
		
		}
	}
	else
	{
		myfile << (t->getTokenLocation())->getName() << "-";
		while (true)
		{
    	    rotateBar();
    	    nextMove = getRandomNumber(t->getTokenLocation()->getEdgeListSize());
        	nextMoveNode = t->getTokenLocation()->getNodeAtElement(nextMove);
			(t->getTokenLocation())->destroyEdge(nextMoveNode);
	        (nextMoveNode)->destroyEdge(t->getTokenLocation());
	        //myfile << "Player " << t->getCurrentPlayerTurn() << " removed edge " << (t->getTokenLocation())->getName() << " - " << (nextMoveNode)->getName() << std::endl;
	        t->setPlayerTurn();
	        t->setTokenLocation(nextMoveNode);
	        if (t->getTokenLocation()->getEdgeListSize() == 0)
			{
				//moves += std::to_string((t->getTokenLocation())->getName());
				t->setPlayerTurn();
				//myfile << "Player " << t->getCurrentPlayerTurn() << " wins!\n";
				myfile << t->getCurrentPlayerTurn() << std::endl;		
				break;
			}
			myfile << (t->getTokenLocation())->getName() << "-";
		}
	}
		
	delete t;
	myfile.close();
	
}