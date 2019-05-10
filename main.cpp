/*
Vincent Bravinder
Ethan Narciso
Daniel Rangel
CPSC 351 Yun Tian
Project 2

*/



#define _CRT_SECURE_NO_DEPRECATE
#include "fileStruct.h"
#include <vector>



const int MAXIMUM_TIME = 100000;

bool isMultiple(int memory, int page) 
{
	if ((memory % page) != 0) 
	{
		return false;
	}
	else 
	{
		return true;
	}
}

int main() 
{	
	int memorySize = MAXIMUM_TIME;
	int pageSize;
	int numOfProcesses;
	int tempInt;
	long virtualCheck = 0;
	char fileName[255] = "";
	fileStruct fs;
	vector<fileStruct::process> proc;
	fileStruct::process temp;

	while (virtualCheck < memorySize)
	{
		cout << "input Memory size :";
		cin >> memorySize;
		if (memorySize > MAXIMUM_TIME) 
		{
			cout << memorySize << " is too big, pick something less than " << MAXIMUM_TIME << endl;
			break;
		}
		cout << "Page Size (1: 100, 2: 200, 3: 400)> ";
		cin >> pageSize;

		if (pageSize == 1) 
		{
			pageSize = 100;
		}
		else if (pageSize == 2) 
		{
			pageSize = 200;
		}
		else if(pageSize == 3) 
		{
			pageSize = 400;
		}
		else 
		{
			cout << "not a valid number" << endl;
			break;
		}

		if (!isMultiple(memorySize, pageSize))
		{
			cout << memorySize << " is not a multiple of " << pageSize << endl;
			break;
		}

		cout << "input file name (end with .txt):";
		cin >> fileName;

		ifstream file;
		file.open(fileName, ifstream::in);

		if (!file)
		{
			cout << "file did not open" << endl;
			break;
		}
		else
		{
			cout << "file did open" << endl;
			file >> numOfProcesses;
			for (int i = 0; i < numOfProcesses; i++) 
			{		
				
				file >> tempInt;
				
				if (tempInt > numOfProcesses) 
				{
					proc.at(i - 1).space.push_back(tempInt);
					file >> temp.processID;
				}
				else
				{
					temp.processID = tempInt;
				}

				file >> temp.arrivalTime >> temp.processLifeTime
					>> temp.address >> tempInt;
				temp.space.push_back(tempInt);
				temp.timeEntered = -1;
				proc.push_back(temp);
				temp.space.clear();
			}


		}

		for (int i = 0; i < numOfProcesses; i++)
		{
			cout << "process ID : " << proc.at(i).processID << endl;
			cout << "arrival time : " << proc.at(i).arrivalTime << endl;
			cout << "life time : " << proc.at(i).processLifeTime << endl;
			cout << "address : " << proc.at(i).address << endl;
			cout << "space : ";
			for (int j = 0; j < proc.at(i).space.size(); j++) 
			{
				cout << proc.at(i).space.at(j) << " ";
			}
			cout << endl << endl;
		}
		break;
	}

	float turnAroundTime = 0;
	int time = 0;
	vector<fileStruct::process> active;
	int activeIndex = 0;
	vector<fileStruct::frame> frames;
	fileStruct::frame *tempFrame = new fileStruct::frame;

	for (int i = 0; i < memorySize; i += pageSize) 
	{
		frames.push_back(fs.initializeFrame(i, i + pageSize - 1));
	}

	

	while (proc.size() != 0 || active.size() != 0) 
	{ 
		cout << " t = " << time << endl;

		for (int k = 0; k < proc.size(); k++) 
		{
			if (proc.at(k).arrivalTime <= time) 
			{
				cout << "process " << proc.at(k).processID << " has arrived" << endl;
				active.push_back(proc.at(k));
				fs.printQueueProcesses(active);
				proc.erase(proc.begin() + k);
				k--;
			}
		}

		for (int j = 0; j < active.size(); j++)
		{
			if (time - active.at(j).timeEntered >= active.at(j).processLifeTime && 
				active.at(j).timeEntered != -1)
			{
				frames = fs.removeFrames(frames, active.at(j));
				turnAroundTime += (time - active.at(j).arrivalTime);
				active.erase(active.begin() + j);
				j--;
			}
		}

		for (int i = 0; i < active.size(); i++) 
		{
			if (active.at(i).timeEntered == -1 && 
				fs.spaceOfProc(active.at(i).space) <= fs.numOfFreeFrames(frames))
			{
				frames = fs.assignFramesToProcess(frames, active.at(i));
				active.at(i).timeEntered = time;
				fs.printQueueProcesses(active);
			}
			
		}
		
		time += 100;
	}

	turnAroundTime /= numOfProcesses;
	cout << "Average Turnaround Time: " << turnAroundTime << endl;


	system("pause");
	return 0;
}