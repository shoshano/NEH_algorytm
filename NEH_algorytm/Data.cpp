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
		//NumberOfData = stoi(line);
		for (int i = 0; i < NumberOfData; i++) 
		{
			getline(file, line);
			std::stringstream s(line);
			while (getline(s, chunk, ' '))
			{
				tmp.push_back(chunk);
			}
			//Task d = Task(i + 1, stoi(tmp.at(0)), stoi(tmp.at(1)), stoi(tmp.at(2)));

			//list.push_back(d);
			//tmp.erase(tmp.begin(), tmp.end());
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
	for (auto x : ListOfTasks)
	{
		x.printTask();
	}
}