#pragma once
#include <iostream>
#include <vector>
#include "Task.h"
#include <fstream>
#include <string>
#include <sstream>

class Data
{
private:
	int NumberOfData;
	std::vector<Task> ListOfTasks;
	std::string FilePath;
	std::string caseCount;
	std::string machineCount;

public:
	void getData(); //pobieranie danych z pliku

	Data(std::string fp);

	std::vector<Task> getListOfTasks();
	std::string getFilePath();

	void printListOfTasks();

};

