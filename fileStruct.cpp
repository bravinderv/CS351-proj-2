#include "fileStruct.h"

frame initializeFrame(int start, int end) 
{
	frame* f = new frame();
	f->startTime = start;
	f->endTime = end;
	f->processID = -1;
	f->page = -1;
	return *f;
}

void setFrame(frame* f, process p, int start, int end, int page) 
{
	f->startTime = start;
	f->endTime = end;
	f->processID = p.processID;
	f->page = page;
}

int numOfFreeFrames(vector<frame> f) 
{
	int num = 0;

	for (int i = 0; i < f.size(); i++) 
	{
		if (f.at(i).processID == -1) 
		{
			num += (f.at(i).endTime - f.at(i).startTime + 1);
		}
	}

	return num;
}

vector<frame> assignFramesToProcess(vector<frame> f, process p) 
{
	int space = spaceOfProc(p.space);
	int pageNum = 1;
	for (int i = 0; i< f.size(); i++)
	{
		if (f.at(i).processID == -1 && space > 0) 
		{
			f.at(i).processID = p.processID;
			f.at(i).page = pageNum;
			pageNum++;
			space -= (f.at(i).endTime - f.at(i).startTime + 1);

		}
		printFrame(f.at(i));

	}
	return f;

}

void printFrame(frame f) 
{
	cout << "\t" << f.startTime << "-" << f.endTime;
	if (f.endTime < 1000) 
	{
		cout << "\t";
	}
		
	if (f.processID == -1) 
	{
		cout << ": free frames" << endl;
	}
	else 
	{
		cout << ": process " << f.processID << " page " << f.page << endl;
	}
}

int spaceOfProc(vector<int> space)
{
	int spaceOfProcess = 0;
	for (int i = 0; i < space.size(); i++)
	{
		spaceOfProcess += space.at(i);
	}
	return spaceOfProcess;
}

void printArrived(vector<process> processes, int time, int page)
{
	cout << "processes { ";
	for (int j = 0; j < processes.size(); j++)
	{
		cout << processes.at(j).processID << " ";
	}
	cout << "} has arrived at " << time << " - " << time + (page - 1) << endl;
}

vector<process> enteredQueue(vector<process> processes, int time, int page, int memory)
{
	vector<process> toReturn;
	cout << "T - " << time << endl;
	for (int i = 0; i < processes.size(); i++)
	{
		if (processes.at(i).arrivalTime >= time && processes.at(i).arrivalTime <= (time + page - 1))
		{
			toReturn.push_back(processes.at(i));
			printArrived(toReturn, time, page);

		}
	}

	return toReturn;
}

bool wasJustEntered(vector<frame> f, process p) 
{
	if (p.timeEntered != -1) 
	{
		return false;
	}

	for (int i = 0; i < f.size(); i++) 
	{
		if (f.at(i).processID == p.processID) 
		{
			return true;
		}
	}

	return false;
}

vector<frame> removeFrames(vector<frame> f, process p) 
{
	cout << "process : " << p.processID << " has completed" << endl;
	for (int i = 0; i < f.size(); i++) 
	{
		if (f.at(i).processID == p.processID) 
		{
			f.at(i) = initializeFrame(f.at(i).startTime, f.at(i).endTime);
		}
		printFrame(f.at(i));
	}
	return f;
}

void printQueueProcesses(vector<process> p) 
{
	cout << "Queue [";
	for (int i = 0; i < p.size(); i++) 
	{
		if (p.at(i).timeEntered == -1) 
		{
			cout << p.at(i).processID << " ";
		}
	}
	cout << "]" << endl;
}