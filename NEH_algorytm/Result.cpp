#include "Result.h"

Result::Result(std::vector<Task> o, int Cmax)
{
	this->Order = o;
	this->Cmax = Cmax;
}

int Result::getCmax()
{
	return this->Cmax;
}

void Result::printResult()
{
	for (auto x : Order)
	{
		std::cout << x.getId() << " ";
	}
	std::cout << "\nCmax = " << Cmax;
}
