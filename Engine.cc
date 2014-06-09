#include <iostream>
#include "PetersenGraph.h"
#include "CompleteGraph.h"
#include "Engine.h"

#include <string>
#include <cstdio>
#include <ctime>
#include <fstream>	

#include <vector>

Engine::Engine()
{
	int choice = 0;
	barCount = 0;
	printIntro();
	printStartMenu();
	std::cin >> choice;
	//startMenuList(choice);
	startMenuChoices(choice);
}

void Engine::printIntro()
{
	std::cout << std::endl;
	std::cout << "Welcome to the Text-Based Graph Theory Logging Program" << std::endl;
	std::cout << std::endl;
}

void Engine::printStartMenu()
{
	std::cout << "What type of graph would you like to use?" << std::endl;
	std::cout << "1. Petersen Graph with unit weight edges" << std::endl;
	std::cout << "2. Complete Graph with unit weight edges" << std::endl;
	std::cout << "3. Quit program" << std::endl;
	std::cout << "Please enter your choice: ";
}

void Engine::startMenuChoices(int choice)
{
	int numGamesToPlay = 0;
	int numNodes = 0;
	if (choice == 1)
	{
		std::cout << "How many games would you like to play?: ";
		std::cin >> numGamesToPlay;
		createPetersenGraph(numGamesToPlay);
	}
	else if (choice == 2)
	{
		std::cout << "How many nodes would you like in this graph?: ";
		std::cin >> numNodes;
		std::cout << "How many games would you like to play?: ";
		std::cin >> numGamesToPlay;
		createCompleteGraph(numGamesToPlay, numNodes);
	}
}

void Engine::parseMasterData()
{
	longestGame = 0;
	p1size = 0;
	p2size = 0;
	std::ifstream master;
	std::ofstream p1;
	std::ofstream p2;
	std::string master_data_path = "output_data/master_data.txt";
	std::string player1_data_path = "output_data/player1_moves.txt";
	std::string player2_data_path = "output_data/player2_moves.txt";
	master.open(master_data_path);
	p1.open(player1_data_path, std::ios_base::app);
	p2.open(player2_data_path, std::ios_base::app);
	std::string parseLine;
	//std::string::iterator iter = parseLine.end();
	while (std::getline(master, parseLine))
	{
		rotateBarParse();
		std::string::iterator iter = (parseLine.end()-1);
//		std::getline(master, parseLine);
		//std::cout << parseLine << std::endl;
		//std::cout << *(parseLine.end()-1) << "*" << std::endl;
		if (*(iter) == '1')
		{
			p1size++;
			parseLine.pop_back();
			parseLine.pop_back();
			p1 << parseLine << std::endl;
			if (parseLine.size() > longestGame)
				longestGame = parseLine.size();
		}
		else if(*(iter) == '2')
		{
			p2size++;
			parseLine.pop_back();
			parseLine.pop_back();
			p2 << parseLine << std::endl;
			if (parseLine.size() > longestGame)
				longestGame = parseLine.size();
		}
		master.clear();
	}
	std::cout << "\nData sorted by player successfully!" << std::endl;
	p1.close();
	p2.close();
	master.close();	
}	

void Engine::parsePlayerLogicalData()
{
	std::ifstream p1;
	std::ifstream p2;
	std::ofstream p1logical;
	std::ofstream p2logical;
	std::string player1_data_path = "output_data/player1_moves.txt";
	std::string player2_data_path = "output_data/player2_moves.txt";
	std::string player1_logical_data_path = "output_data/player1_logical_moves.txt";
	std::string player2_logical_data_path = "output_data/player2_logical_moves.txt";
	p1.open(player1_data_path);
	p2.open(player2_data_path);
	p1logical.open(player1_logical_data_path, std::ios_base::app);
	p2logical.open(player2_logical_data_path, std::ios_base::app);
	std::string testLine;
	while (std::getline(p1, testLine))
	{
		rotateBarParsePlayer1();
		if (testLine.size() == longestGame)
			p1logical << testLine << std::endl;
	}
	std::cout << "Logical moves extracted from player 1 data successfully!" << std::endl;
	while (std::getline(p2, testLine))
	{
		rotateBarParsePlayer2();
		if (testLine.size() == longestGame)
			p1logical << testLine << std::endl;
	}
	std::cout << "Logical moves extracted from player 2 data successfully!" << std::endl;
	p1.close();
	p2.close();
	p1logical.close();
	p2logical.close();
}

void Engine::dataAnalysis(int choice)
{
//	longestGame = 1;
	std::ifstream p1;
	std::ifstream p2;
	std::ofstream results;
	std::string player1_data_path = "output_data/player1_moves.txt";
	std::string player2_data_path = "output_data/player2_moves.txt";
	std::string results_data_path = "output_data/results.txt";
	std::string player1_logical_data_path = "output_data/player1_logical_moves.txt";
	std::string player2_logical_data_path = "output_data/player2_logical_moves.txt";
	p1.open(player1_data_path);
	p2.open(player2_data_path);
//	p1_logical.open(player1_logical_data_path);
//	p2_logical.open(player2_logical_data_path);
	results.open(results_data_path);
	std::string testLine;
	std::vector<std::string> player1moves;
	std::vector<std::string> player2moves;
	std::vector<std::string> player1logicalmoves;
	std::vector<std::string> player2logicalmoves;
	while (std::getline(p1, testLine))
	{
		rotateBarAnalyzeP1();
		std::vector<std::string>::iterator it = find(player1moves.begin(), player1moves.end(), testLine);
		if (it == player1moves.end())
			player1moves.push_back(testLine);
		testLine.clear();
	}
	std::cout << "\nPlayer 1 data analyzed!" << std::endl;
	while (std::getline(p2, testLine))
	{
		rotateBarAnalyzeP2();
		std::vector<std::string>::iterator it = find(player2moves.begin(), player2moves.end(), testLine);
		if (it == player2moves.end())
			player2moves.push_back(testLine);
		testLine.clear();
	}
	std::cout << "\nPlayer 2 data analyzed!" << std::endl;
	std::cout << std::endl;
	results << std::endl;
	p1.close();
	p2.close();
	std::sort(player1moves.begin(), player1moves.end());
	std::sort(player2moves.begin(), player2moves.end());
	int numberOfGamesPlayed = choice;
	std::cout << "-----------------------------------------------" << std::endl;
	results << "-----------------------------------------------" << std::endl;
	std::cout << "\nGame Analysis" << std::endl;
	results << "\nGame Analysis" << std::endl;
	std::cout << std::endl;
	results << std::endl;
	std::cout << "Of the " << numberOfGamesPlayed << " games played:" << std::endl;
	results << "Of the " << numberOfGamesPlayed << " games played:" << std::endl;
	std::cout << std::endl;
	results << std::endl;
	std::cout << "Player 1 won " << p1size << "." << std::endl;
	results << "Player 1 won " << p1size << "." << std::endl;
	std::cout << "Player 2 won " << p2size << "." << std::endl;
	results << "Player 2 won " << p2size << "." << std::endl;
	std::cout << std::endl;
	results << std::endl;
	std::cout << "There are " << player1moves.size() << " unique moves for Player 1." << std::endl;
	results << "There are " << player1moves.size() << " unique moves for Player 1." << std::endl;
	std::cout << "There are " << player2moves.size() << " unique moves for Player 2." << std::endl;
	results << "There are " << player2moves.size() << " unique moves for Player 2." << std::endl;
	std::cout << std::endl;
	results << std::endl;
	std::cout << "The following moves led to Player 1's victory:" << std::endl;
	results << "The following moves led to Player 1's victory:" << std::endl;
	for (std::vector<std::string>::iterator i = player1moves.begin(); i != player1moves.end(); i++)
	{
		std::cout << *i << std::endl;
		results << *i << std::endl;
//		if (i->size() > longestGame)
//			longestGame = i->size();
	}
	std::cout << std::endl;
	results << std::endl;
	std::cout << "The following moves led to Player 2's victory:" << std::endl;
	results << "The following moves led to Player 2's victory:" << std::endl;
	for (std::vector<std::string>::iterator i = player2moves.begin(); i != player2moves.end(); i++)
	{
		std::cout << *i << std::endl;
		results << *i << std::endl;
//		if (i->size() > longestGame)
//			longestGame = i->size();
	}
	std::cout << std::endl;
	results << std::endl;
	std::cout << "The longest game was " << (longestGame + 1) / 2 << " moves.\n" << std::endl;
	results << "The longest game was " << (longestGame + 1) / 2 << " moves.\n" << std::endl;
	results.close();
}

void Engine::rotateBarParse()
{
	barCount++;
	char barspin[4] = {'\\', '|', '/', '-'};
	int whichOne;
	whichOne = barCount % 4;
	if (whichOne == 3)
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while the data is sorted...";
	}
	else
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while the data is sorted...";
	}
	std::cout.flush();
	return;
}

void Engine::rotateBarParsePlayer1()
{
	barCount++;
	char barspin[4] = {'\\', '|', '/', '-'};
	int whichOne;
	whichOne = barCount % 4;
	if (whichOne == 3)
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while player 1 logical moves are extracted...";
	}
	else
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while player 1 logical moves are extracted";
	}
	std::cout.flush();
	return;
}

void Engine::rotateBarParsePlayer2()
{
	barCount++;
	char barspin[4] = {'\\', '|', '/', '-'};
	int whichOne;
	whichOne = barCount % 4;
	if (whichOne == 3)
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while player 2 logical moves are extracted";
	}
	else
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while player 2 logical moves are extracted";
	}
	std::cout.flush();
	return;
}

void Engine::rotateBarAnalyzeP1()
{
	barCount++;
	char barspin[4] = {'\\', '|', '/', '-'};
	int whichOne;
	whichOne = barCount % 4;
	if (whichOne == 3)
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while Player 1's data is analyzed...";
	}
	else
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while Player 1's data is analyzed...";
	}
	std::cout.flush();
	return;
}

void Engine::rotateBarAnalyzeP2()
{
	barCount++;
	char barspin[4] = {'\\', '|', '/', '-'};
	int whichOne;
	whichOne = barCount % 4;
	if (whichOne == 3)
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while Player 2's data is analyzed...";
	}
	else
	{
		std::cout << '\r' << barspin[whichOne] << "  Please wait while Player 2's data is analyzed...";
	}
	std::cout.flush();
	return;
}


void Engine::createPetersenGraph(int choice)
{
	std::clock_t startTime = clock();
	for (int i = 1; i <= choice; i++)
	{
		PetersenGraph *a = new PetersenGraph(i);
		delete a;
	}
	parseMasterData();
	dataAnalysis(choice);
	//Surface *a = new Surface(choice);
	std::clock_t endTime = clock();
	std::clock_t timeDelta = endTime - startTime;
	double timeInSeconds = timeDelta / (double)CLOCKS_PER_SEC;
	int timeInDays = timeInSeconds / (60*60*24);
	int timeInHours = (timeInSeconds / (60*60)) - (timeInDays * 24);
	int timeInMinutes = (timeInSeconds / 60) - (timeInHours * 60);
	int secondsRemaining = (int)(timeInSeconds - (timeInMinutes * 60));
	std::cout << "Benchmark:" << std::endl;
	if (secondsRemaining == 0 && timeInMinutes == 0)
	{
		std::cout << "This calculation was quite quick!" << std::endl;
		std::cout << std::endl;
	}
	else if (secondsRemaining >= 10)
	{
		std::cout << "Time to completion: " << timeInMinutes << ":" << secondsRemaining << std::endl;
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Time to completion: " << timeInMinutes << ":0" << secondsRemaining << std::endl;
		std::cout << std::endl;
	}
	std::cout << "This calculation took exactly " << timeInSeconds << " seconds." << std::endl;		
	std::cout << std::endl;
}

void Engine::createCompleteGraph(int numGames, int numNodes)
{
	//int numberOfNodes = numNodes;
	std::clock_t startTime = clock();
	for (int i = 1; i <= numGames; i++)
	{
		CompleteGraph *a = new CompleteGraph(i, numNodes);
		delete a;
	}
	std::cout << "-----------------------------------------------\n" << std::endl;
	parseMasterData();
	parsePlayerLogicalData();
	dataAnalysis(numGames);
	//Surface *a = new Surface(choice);
	std::clock_t endTime = clock();
	std::clock_t timeDelta = endTime - startTime;
	double timeInSeconds = timeDelta / (double)CLOCKS_PER_SEC;
	int timeInDays = timeInSeconds / (60*60*24);
	int timeInHours = (timeInSeconds / (60*60)) - (timeInDays * 24);
	int timeInMinutes = (timeInSeconds / 60) - (timeInHours * 60);
	int secondsRemaining = (int)(timeInSeconds - (timeInMinutes * 60));
	std::cout << "Benchmark:" << std::endl;
	if (secondsRemaining == 0 && timeInMinutes == 0)
	{
		std::cout << "This calculation was quite quick!" << std::endl;
		std::cout << std::endl;
	}
	else if (secondsRemaining >= 10)
	{
		std::cout << "Time to completion: " << timeInMinutes << ":" << secondsRemaining << std::endl;
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Time to completion: " << timeInMinutes << ":0" << secondsRemaining << std::endl;
		std::cout << std::endl;
	}
	std::cout << "This calculation took exactly " << timeInSeconds << " seconds." << std::endl;		
	std::cout << std::endl;
}