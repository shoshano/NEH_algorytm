#pragma once
#include <iostream>
#include <vector>

class Task
{
private:
	int Id;
	std::vector<int> MachineTime;
public:
	Task(int Id, std::vector<int> MT);
	int getId();
	std::vector<int> getMachineTime();
	void printTask();
};
