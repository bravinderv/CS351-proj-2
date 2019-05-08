#define _CRT_SECURE_NO_DEPRECATE
#include "fileStruct.h"



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
	vector<process> proc;
	process temp;

	while (virtualCheck < memorySize)
	{
		cout << "input Memory size :";
		cin >> memorySize;
		if (memorySize > MAXIMUM_TIME) 
		{
			cout << memorySize << " is too big, pick something less than " << MAXIMUM_TIME << endl;
			break;
		}
		cout << "Page Size (enter either 100,200, or 400) ";
		cin >> pageSize;
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

	int time = 0;
	vector<process> active;
	int activeIndex = 0;
	vector<frame> frames;
	frame *tempFrame = new frame;

	for (int i = 0; i < memorySize; i += pageSize) 
	{
		frames.push_back(initializeFrame(i, i + pageSize - 1));
	}

	

	while (proc.size() != 0 || active.size() != 0) 
	{ 
		cout << " t = " << time << endl;

		for (int j = 0; j < active.size(); j++)
		{
			if (time - active.at(j).timeEntered >= active.at(j).processLifeTime)
			{
				frames = removeFrames(frames, active.at(j));
				active.erase(active.begin() + j);
				activeIndex--;
			}
		}

		for (int i = 0; i < proc.size(); i++) 
		{
			if (proc.at(i).arrivalTime <= time) 
			{
				cout << "process " << proc.at(i).processID << " has arrived" << endl;
				active.push_back(proc.at(i));
				proc.erase(proc.begin() + i);
				frames = assignFramesToProcess(frames, active.at(activeIndex));
				if (wasJustEntered(frames, active.at(activeIndex))) 
				{
					active.at(activeIndex).timeEntered = time;
				}

				activeIndex++;
				i--;
			}		
		}

		
		time += pageSize;
	}


	system("pause");
	return 0;
}