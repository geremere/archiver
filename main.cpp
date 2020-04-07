// КДЗ по дисциплине Алгоритмы и структуры данных, 2019-2020 уч.год
// Имамов Радмир Маратович БПИ183
// CLion,
// Состав проекта (файлы *.cpp и *.h)
//main.cpp Shennon_Fano.h/.cpp Encode.h/.cpp Decode.h/.cpp
// Реализовано сжатие файла с помощью алгоритма Шеннона-Фано
//Послностью написан отчет с таблицами и графиками
//
//Не реализован алгоритм LZ77 и соответсвенно графики и таблицы по нему
//Также не выполнен алгорит LZW


#include <iostream>
#include <vector>
#include <map>
#include <bitset>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <cmath>

#include "src/Shenon_Fano.h"
#include "src/Encode.h"
#include "src/Decode.h"

using namespace std;
int BUFFER_SIZE = 10000000;

bool isFilesEqual(const std::string &lFilePath, const std::string &rFilePath)
{
    std::ifstream lFile(lFilePath.c_str(), std::ifstream::in | std::ifstream::binary);
    std::ifstream rFile(rFilePath.c_str(), std::ifstream::in | std::ifstream::binary);

    if (!lFile.is_open() || !rFile.is_open())
    {
        return false;
    }

    char *lBuffer = new char[BUFFER_SIZE]();
    char *rBuffer = new char[BUFFER_SIZE]();

    do
    {
        lFile.read(lBuffer, BUFFER_SIZE);
        rFile.read(rBuffer, BUFFER_SIZE);

        if (std::memcmp(lBuffer, rBuffer, BUFFER_SIZE) != 0)
        {
            delete[] lBuffer;
            delete[] rBuffer;
            return false;
        }
    } while (lFile.good() || rFile.good());

    delete[] lBuffer;
    delete[] rBuffer;
    return true;

}

bool flag = true;

LARGE_INTEGER FR, START, END, DE, DD, D;
unsigned long long size = 0;

void startShenonFanno(string name, string format)
{
//    ofstream ent;
//    ent.open("../entropy.csv", ios_base::app);
    multimap<int, char> sortedWieght;
    Encode e;
    e.read("DATA/" + name + format, sortedWieght);
    Shenon_Fano *shf = new Shenon_Fano();
    double H = 0;

    for (auto it = --sortedWieght.end(); it != sortedWieght.begin(); --it)
    {
        size += it->first;
        shf->addChance(it->first);
    }
    shf->addChance(sortedWieght.begin()->first);
    size += sortedWieght.begin()->first;
//    ent << name + ";";
//    for (auto it:sortedWieght)
//    {
//        double tmp = (double) it.first / size;
//        string line=to_string(tmp);
//        string res="";
//        for (int i = 0; i < line.length(); ++i)
//        {
//            if(line[i]=='.')
//                res+=',';
//            else res+=line[i];
//        }
//        ent << res + ";";
//        if(tmp!=0)
//            H -= tmp * (log(tmp) / log(2));
//    }
//    string line=to_string(H);
//    string qw="";
//    for (int i = 0; i < line.length(); ++i)
//    {
//        if(line[i]=='.')
//            qw+=',';
//        else qw+=line[i];
//    }
//    ent << qw + ";" << endl;
//    ent.flush();
//    ent.close();
    shf->build();
    vector<string> res = shf->res;
    map<unsigned char, string> dict;
    auto it = --sortedWieght.end();
    for (int i = 0; i < res.size(); ++i)
    {
        dict.insert({it->second, res[i]});
        it--;
    }
    Decode d;

    QueryPerformanceCounter(&START);
    e.write("DATA/" + name + format, "SHAN/" + name + ".shan", dict);
    QueryPerformanceCounter(&END);
    D.QuadPart = (END.QuadPart - START.QuadPart);
    D.QuadPart = D.QuadPart;
    DE.QuadPart += D.QuadPart;
    QueryPerformanceCounter(&START);
    d.read("SHAN/" + name + ".shan", "OUT/" + name + ".unshan");
    QueryPerformanceCounter(&END);
    D.QuadPart = (END.QuadPart - START.QuadPart);
    D.QuadPart = D.QuadPart;
    DD.QuadPart += D.QuadPart;
    QueryPerformanceCounter(&END);
}

int main()
{
    string format[] = {".txt", ".docx", ".ppt", ".pdf", ".exe", ".jpg", ".jpg", ".bmp", ".bmp"};
    QueryPerformanceFrequency(&FR);
//    ofstream inp;
//    inp.open("../res.csv");
//    inp << "Name;" << "S1;" << "H;" << "tu;" << "tp;" << endl;
    for (int i = 0; i < 9; ++i)
    {
        string name = to_string(i + 1);

//        for (int j = 0; j < 10; ++j)
//        {
            size = 0;
            startShenonFanno(name, format[i]);
//        }
        if (isFilesEqual("DATA/" + name + format[i], "OUT/" + name + ".unshan"))
            cout << name + format[i] << " - succses" << endl;
        else
            cout << name + format[i] << " - error" << endl;
//        inp << name << ";" << size / 10 << ";" << H << ";" << DE.QuadPart * 100000000 / FR.QuadPart << ";"
//            << DD.QuadPart * 100000000 / FR.QuadPart
//            << ";" << endl;
//        inp.flush();
        DD.QuadPart = 0;
        DE.QuadPart = 0;
        size = 0;
    }
//    inp.close();
    return 0;

}