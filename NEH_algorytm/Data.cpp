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

int Data::getMachineCount()
{
	return stoi(machineCount);
}

Result Data::NEH_Taillard() {
	std::vector<Task>& tasks = ListOfTasks;
		int numMachines = getMachineCount();

	sort(tasks.begin(), tasks.end(), [](const Task left, const Task right) {
		return left.Weight > right.Weight;
		});

	std::vector<Task> partialSequence;
	partialSequence.push_back(tasks[0]);

	for (size_t i = 1; i < tasks.size(); ++i) {
		std::vector<Task> bestSequence;
		int bestMakespan = std::numeric_limits<int>::max();
		std::vector<int> bestC(numMachines, 0);

		for (size_t j = 0; j <= partialSequence.size(); ++j) {
			std::vector<Task> tempSequence = partialSequence;
			tempSequence.insert(tempSequence.begin() + j, tasks[i]);
			std::vector<int> tempC(numMachines, 0);

			for (size_t k = 0; k < tempSequence.size(); ++k) {
				for (int m = 0; m < numMachines; ++m) {
					if (k == 0) {
						tempC[m] = (m == 0) ? tempSequence[k].getMachineTime()[m] : tempC[m - 1] + tempSequence[k].getMachineTime()[m];
					}
					else {
						tempC[m] = std::max(tempC[m], tempC[m == 0 ? 0 : m - 1]) + tempSequence[k].getMachineTime()[m];
					}
				}
			}

			int currentMakespan = tempC[numMachines - 1];

			if (currentMakespan < bestMakespan) {
				bestMakespan = currentMakespan;
				bestSequence = tempSequence;
				bestC = tempC;
			}
		}
		partialSequence = bestSequence;
	}
	int Cmax = calculate_Cmax(partialSequence);
	Result res = Result(partialSequence, Cmax);
	return res;
}

int Data::calculatePartialMakespan(const std::vector<Task>& schedule, int numMachines, std::vector<int>& endTimes, int position, Task task) {
	std::vector<int> tempEndTimes(endTimes);
	for (int m = 0; m < numMachines; ++m) {
		if (position == 0) {
			tempEndTimes[m] = (m == 0) ? task.getMachineTime()[m] : tempEndTimes[m - 1] + task.getMachineTime()[m];
		}
		else {
			tempEndTimes[m] = std::max(endTimes[m], tempEndTimes[m == 0 ? 0 : m - 1]) + task.getMachineTime()[m];
		}
	}
	return tempEndTimes[numMachines - 1];
}

Result Data::NEH_Taillard2() {
	std::vector<Task>& tasks = ListOfTasks;
	int numMachines = getMachineCount();

	std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
		return a.Weight > b.Weight;
		});

	std::vector<Task> partialSequence;
	partialSequence.push_back(tasks[0]);

	std::vector<int> endTimes(numMachines, 0);

	for (size_t i = 1; i < tasks.size(); ++i) {
		std::vector<Task> bestSequence;
		int bestMakespan = std::numeric_limits<int>::max();

		for (size_t j = 0; j <= partialSequence.size(); ++j) {
			std::vector<Task> tempSequence = partialSequence;
			tempSequence.insert(tempSequence.begin() + j, tasks[i]);
			int currentMakespan = calculatePartialMakespan(tempSequence, numMachines, endTimes, j, tasks[i]);

			if (currentMakespan < bestMakespan) {
				bestMakespan = currentMakespan;
				bestSequence = tempSequence;
			}
		}
		partialSequence = bestSequence;

		for (int m = 0; m < numMachines; ++m) {
			endTimes[m] = std::max(endTimes[m], endTimes[m == 0 ? 0 : m - 1]) + partialSequence.back().getMachineTime()[m];
		}
	}

	int Cmax = calculate_Cmax(partialSequence);
	Result res = Result(partialSequence, Cmax);
	return res;
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