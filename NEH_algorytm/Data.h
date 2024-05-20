#pragma once
#include <iostream>
#include <vector>
#include "Task.h"
#include "Result.h"
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

class Data
{
private:
	int NumberOfData;
	int Cmax;
	std::vector<Task> ListOfTasks;
	std::string FilePath;
	std::string caseCount;
	std::string machineCount;

public:
	void getData(); //pobieranie danych z pliku

	Data(std::string fp);

	std::vector<Task> getListOfTasks();
	std::string getFilePath();
	int calculate_Cmax(std::vector<Task> vec);
	void printListOfTasks();
	Result algorithm();
	

};

