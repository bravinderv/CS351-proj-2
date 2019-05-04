#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
using namespace std;

typedef struct process {
	int processID;
	int arrivalTime;
	int processLifeTime;
	int address;
	vector<int> space;
}process;
