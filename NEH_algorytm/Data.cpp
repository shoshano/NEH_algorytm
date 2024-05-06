#include "Data.h"

void Data::getData()
{
	NumberOfData = 0;
	std::string n;
	std::fstream file;
	file.open(FilePath);
	std::string line, chunk;
	std::vector<std::string> tmp;

	if (file.is_open()) 
	{
		getline(file, line);
		std::string delimiter = " ";

		int pos = line.find(delimiter);
		caseCount = line.substr(0, pos);
		machineCount = line.substr(pos, line.length());
		///Do testów
		//std::cout << caseCount << " " << machineCount << std::endl;

		///Wersja dla wiêcej ni¿ 2
		//std::string caseCount, machineCount;
		//while ((pos = line.find(delimiter)) != std::string::npos) {
		//	caseCount = line.substr(0, pos);
		//	machineCount = line.substr(pos, line.length());
		//	std::cout << caseCount << " " << machineCount << std::endl;
		//	line.erase(0, pos + delimiter.length());
		//}
		 
		NumberOfData = stoi(line);
		for (int i = 0; i < NumberOfData; i++) 
		{
			getline(file, line);
			std::stringstream s(line);
			while (getline(s, chunk, ' '))
			{
				tmp.push_back(chunk);
			}


			std::vector<int> machineTimes;
			for (auto x : tmp)
			{
				machineTimes.push_back(stoi(x));
			}

			Task d = Task(i + 1, machineTimes);

			ListOfTasks.push_back(d);
			tmp.erase(tmp.begin(), tmp.end());
			machineTimes.erase(machineTimes.begin(), machineTimes.end());
		}
	}
	else 
	{
		std::cout << "Plik nie otwarty";
	}
}

Data::Data(std::string fp)
{
	this->FilePath = fp;
	getData();
}

std::vector<Task> Data::getListOfTasks()
{
	return this->ListOfTasks;
}

std::string Data::getFilePath()
{
	return this->FilePath;
}

void Data::printListOfTasks()
{
	std::cout << caseCount << " " << machineCount << "\n";
	for (auto x : ListOfTasks)
	{
		x.printTask();
	}
}