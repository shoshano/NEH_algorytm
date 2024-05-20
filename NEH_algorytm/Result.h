#pragma once

#include <vector>
#include "Task.h"

class Result
{
private:
	std::vector<Task> Order;
	int Cmax;

public:
	Result(std::vector<Task> o, int Cmax);

	void printResult();

};

