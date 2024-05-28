#include <iostream>
#include <vector>
#include <string>
#include "Data.h"
#include <chrono>


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

    //int dataSet = 15;
    //Result res = dataTab.at(dataSet).algorithm();
    //Result quick_res = dataTab.at(dataSet).algorithm();
    //res.printResult();
    //cout << "\n";
    //quick_res.printResult();
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point stop;
    int launch = 0;
    int limit = 121;
    //start = chrono::high_resolution_clock::now();
    //for (int x = launch; x < limit; x++)
    //{
    //    //Result res = dataTab.at(x).algorithm();
    //    cout << x;
    //    Result quick_res = dataTab.at(x).NEH_Taillard();
    //    
    ////    //if (res.getCmax() != quick_res.getCmax()) 
    ////    //{
    ////    //    cout << "<>" << to_string(x) << endl;
    ////    //}
    //}
    //stop = chrono::high_resolution_clock::now();
    //
    //chrono::duration<double> time_span1 = chrono::duration_cast<chrono::duration<double>>(stop - start);
    //cout << "Czas NEH_Taillard: " << time_span1.count() << "s\n\n";

    start = chrono::high_resolution_clock::now();
    for (int x = launch; x < limit; x++)
    {
        cout << x<<endl;
        //Result res = dataTab.at(x).algorithm();
        Result quick_res = dataTab.at(x).NEH_Taillard();
        cout << quick_res.getCmax() << endl<<endl;
        
    //    //if (res.getCmax() != quick_res.getCmax()) 
    //    //{
    //    //    cout << "<>" << to_string(x) << endl;
    //    //}
    }
    stop = chrono::high_resolution_clock::now();

    chrono::duration<double> time_span2 = chrono::duration_cast<chrono::duration<double>>(stop - start);
    cout << "Czas NEH_2: " << time_span2.count() << "s\n\n";
    //cout << "koniec";
}
