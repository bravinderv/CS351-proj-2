

#pragma once
#include "fileStruct.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
using namespace std;
using std::vector;


class fileStruct 
{
public:
	fileStruct();
	typedef struct process {
		int processID;
		int arrivalTime;
		int processLifeTime;
		int address;
		vector<int> space;
		int timeEntered;
	}process;

	typedef struct frame {
		int startTime;
		int endTime;
		int page;
		int processID;
	}frame;

	frame initializeFrame(int start, int end);

	void setFrame(frame* f, process p, int start, int end, int page);

	void printFrame(frame f);

	int spaceOfProc(vector<int> space);

	void printArrived(std::vector<process> processes, int time, int page);

	vector<process> enteredQueue(vector<process> processes, int time, int page, int memory);

	vector<frame> assignFramesToProcess(vector<frame> f, process p);

	int numOfFreeFrames(vector<frame> f);

	bool wasJustEntered(vector<frame> f, process p);

	vector<frame> removeFrames(vector<frame> f, process p);

	void printQueueProcesses(vector<process> p);

};


