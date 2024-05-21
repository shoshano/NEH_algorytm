#include "Task.h"

Task::Task(int Id, std::vector<int> MT)
{
	this->Id = Id;
	this->MachineTime = MT;
	this->Weight = 0;

	for (auto x : MachineTime)
	{
		Weight += x;
	}
}

int Task::getId()
{
	return this->Id;
}

std::vector<int> Task::getMachineTime()
{
	return this->MachineTime;
}

void Task::printTask()
{
	std::cout << Id << "  ";
}

int Task::getWeight()
{
	return this->Weight;
}
