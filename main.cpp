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

	system("pause");
	return 0;
}