#ifndef GUARD_Engine_h
#define GUARD_Engine_h

#include "PetersenGraph.h"

class Engine {
public:
	Engine();
	int p1size;
	int p2size;
	   
private:
	void printIntro();
	void printStartMenu();
	void startMenuChoices(int);
	void createPetersenGraph(int);
	void rotateBarParse();
	void rotateBarAnalyzeP1();
	void rotateBarAnalyzeP2();
	int barCount1;
	int barCount2;
	void createCompleteGraph(int, int);
	void parseMasterData();
	void dataAnalysis1(int);
	void dataAnalysis2(int);
};

#endif