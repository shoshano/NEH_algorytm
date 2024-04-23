#include "Task.h"

Task::Task(int Id, std::vector<int> MT)
{
	this->Id = Id;
	this->MachineTime = MT;
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
	std::cout << Id << "\n";
	for (auto x : MachineTime)
	{
		std::cout << x << " ";
	}
	std::cout << "\n";
}