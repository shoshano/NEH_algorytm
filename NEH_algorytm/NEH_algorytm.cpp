#include <iostream>
#include <vector>
#include <string>
#include "Data.h"


using namespace std;

vector<string> getFileName()
{
    vector<string> tmpVec;

    string name = "data.";
    string exension = ".txt";
    string tmp, tmpName;

    for (int i = 0; i < 121; i++)
    {
        if (i < 10)
        {
            tmp = "00" + to_string(i);
            tmpName = name + tmp + exension;
            tmpVec.push_back(tmpName);
        }
        else if (i < 100)
        {
            tmp = "0" + to_string(i);
            tmpName = name + tmp + exension;
            tmpVec.push_back(tmpName);
        }
        else
        {
            tmp = to_string(i);
            tmpName = name + tmp + exension;
            tmpVec.push_back(tmpName);
        }

    }
    return tmpVec;
}

int main()
{
    vector<string> FileNames = getFileName();
    vector<Data> dataTab;

    for (auto x : FileNames)
    {
        Data tmp = Data(x);
        dataTab.push_back(tmp);
    }

    for (int x = 0; x < 121; x++) {
        //cout << "\n\n";
        //cout << x << "\n";
        Result res = dataTab.at(x).algorithm();
        //cout << "\n\n";
        //res.printResult();
        //cout << "\n\n";
    }
    cout << "koniec";
}
