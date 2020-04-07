//
// Created by rmima on 03.04.2020.
//

#include "Decode.h"
#include <iostream>
#include <fstream>
#include <map>
#include <bitset>


void Decode::read(std::string path, std::string secondpath)
{
    std::ifstream rd;
    std::ofstream wr;
    rd.open(path, std::ios::in | std::ios::binary);
    wr.open(secondpath, std::ios::binary);
    std::map<std::string, unsigned char> dict;
    unsigned long n;
    rd.read(reinterpret_cast<char*>(&n), sizeof(n));
    std::string str;
    unsigned char ch;
    unsigned char l;
    for (int i = 0; i < n; ++i)
    {
        int k;
        rd.read((char *) &ch, sizeof(ch));
        rd.read((char *) &l, sizeof(ch));
        k=(int)l;
        std::string line="";
        for (int j = 0; j < k; ++j)
        {
            rd.read((char *) &l, sizeof(ch));
            line+=l;
        }
        dict.insert({line, ch});
    }

    str = "";
    std::string tmp = "";
    rd.read(reinterpret_cast<char*>(&n), sizeof(n));
    for (int m = 0; m < n; ++m)
    {
        rd.read((char*)&ch,1);
        str+=ch;
    }
    auto start = rd.tellg();
    rd.seekg(0, std::ios::end);
    int end = (int) rd.tellg();
    rd.seekg(start);
    for (int i = (int) start; i < end; i++)
    {
        rd.read((char *) &ch, 1);
        int pos = (int) rd.tellg();
        if (pos > 0)
            tmp += std::bitset<8>(ch).to_string();
        if (tmp.length() > 40)
        {
            for (int i = 1; i <= tmp.length(); ++i)
            {
                if (dict.find(tmp.substr(0, i)) != dict.end())
                {
                    wr.write((char *) &dict[tmp.substr(0, i)], 1);
                    tmp.erase(0, i);
                    i = 0;
                }
            }
        }
    }
    tmp += str;
    if (tmp.length() != 0)
        for (int i = 1; i <= tmp.length(); ++i)
        {
            if (dict.find(tmp.substr(0, i)) != dict.end())
            {
                wr.write((char *) &dict[tmp.substr(0, i)], 1);
                tmp.erase(0, i);
                i = 0;
            }
        }
    rd.close();
    wr.close();
}