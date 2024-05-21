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
	this->Cmax = 0;
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

int Data::calculate_Cmax(std::vector<Task> vec)
{
	std::vector<std::vector<int>> times;
	int result_Cmax = 0;
	int caseCount = vec.size();

	times.resize(caseCount);
	for (int i = 0; i < caseCount; i++)
	{
		times.at(i).resize(stoi(machineCount));

		for (int j = 0; j < stoi(machineCount); j++)
		{
			int p = vec.at(i).getMachineTime().at(j);

			if (j > 0 && i > 0)
			{
				times[i][j] = std::max(times[i - 1][j], times[i][j - 1]) + p;
			}
			else if (j == 0 && i == 0)
			{
				times[i][j] = std::max(0, 0) + p;
			}
			else if (j == 0 && i > 0)
			{
				times[i][j] = std::max(times[i - 1][j], 0) + p;
			}
			else if (j > 0 && i == 0)
			{
				times[i][j] = std::max(times[i][j - 1], 0) + p;
			}
		}
	}

	result_Cmax = times[caseCount - 1][stoi(machineCount) - 1];

	return result_Cmax;
}

Result Data::algorithm() {
	std::vector<Task> listCopy = ListOfTasks;
	sort(listCopy.begin(), listCopy.end(), [](const Task left, const Task right) {
		return left.Weight > right.Weight;
		});
	/*for (auto x : listCopy) {
		x.printTask();
	}*/
	std::cout << "\n";
	std::vector<Task> res;
	std::vector<Task> bestOrder;
	int old_Cmax = 10000000;
	int size = listCopy.size();

	for (int i = 0; i < size; ++i)
	{
		Task tmp = listCopy.at(0);
		listCopy.erase(listCopy.begin());

		res.push_back(tmp);

		if (res.size() > 1)
		{
			old_Cmax = calculate_Cmax(res);
			bestOrder = res;

			for (int j = res.size()-1; j > 0; j--)
			{				
				std::swap(res.at(j), res.at(j - 1));

				int new_Cmax = calculate_Cmax(res);

				if (old_Cmax >= new_Cmax) 
				{
					old_Cmax = new_Cmax;
					bestOrder = res;
				}

			}
			res = bestOrder;
			/*for (auto x : bestOrder) {
				x.printTask();
			}
			std::cout << "\n";*/
		}
		
	}
	Result result = Result(bestOrder, old_Cmax);
	return result;	
}

void Data::printListOfTasks()
{
	std::cout << caseCount << " " << machineCount << "\n";
	for (auto x : ListOfTasks)
	{
		x.printTask();
	}

	Cmax = calculate_Cmax(ListOfTasks);
	std::cout << "\nCmax = " << Cmax;
}