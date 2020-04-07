//
// Created by rmima on 03.04.2020.
//

#include "Encode.h"
#include <fstream>
#include <map>
#include <bitset>

void Encode::read(std::string path, std::multimap<int, char> &sortedWieght)
{
    int weight[0x100];
    for (auto &i:weight)
        i = 0;
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);
    while (!f.eof())
    {
        unsigned char ch;
        f.read((char *) &ch, sizeof(ch));
        weight[ch]++;
    }
    for (int j = 0; j < 0x100; ++j)
    {
        //if (weight[j] > 0)
            sortedWieght.insert({weight[j], (char) j});
    }
    f.close();
}

void Encode::write(std::string pathToRead, std::string pathToWrite, std::map<unsigned char, std::string> &dict)
{
    std::ofstream wr;
    wr.open(pathToWrite, std::ios::out | std::ios::binary);
    std::string data;
    for (auto it: dict)
    {
        data += it.first;
        data += it.second.length();
        data += it.second;
    }
    unsigned long leng = dict.size();
    wr.write(reinterpret_cast<const char *>(&leng), sizeof(leng));
//    wr.write(reinterpret_cast<const char *>(dict.size()), sizeof(dict.size()));

    wr.write(data.c_str(), data.length());

    std::ifstream rd;
    rd.open(pathToRead, std::ios::in | std::ios::binary);
    rd.seekg(0, std::ios::end);
    int n = (int) rd.tellg();
    rd.seekg(0, std::ios::beg);
    std::string code = "";
    for (int i = 0; i < n; ++i)
    {
        unsigned char ch;
        rd.read((char *) &ch, sizeof(ch));
        std::string tmp = code + dict[ch];
        while (tmp.length() >= 8)
        {
            code = tmp.erase(0, 8);
        }
        code = tmp;
    }

    rd.seekg(0, std::ios::beg);
    if (code.length() > 8)
        throw std::logic_error("1");

    leng = code.length();
    wr.write(reinterpret_cast<const char *>(&leng), sizeof(leng));
    wr.write(code.c_str(), code.length());
    code.clear();
    for (int j = 0; j < n; ++j)
    {
        unsigned char ch;
        rd.read((char *) &ch, sizeof(ch));
        std::string tmp = code + dict[ch];
        while (tmp.length() >= 8)
        {
            unsigned char chr = std::bitset<8>(tmp.substr(0, 8)).to_ulong();
            wr.write((char *) &chr, 1);
            code = tmp.erase(0, 8);
        }
        code = tmp;
    }
    rd.close();
    wr.close();
}