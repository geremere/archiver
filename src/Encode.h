//
// Created by rmima on 03.04.2020.
//
#include <iostream>
#include <map>

#ifndef KDZ_ENCODE_H
#define KDZ_ENCODE_H


class Encode
{
public:
    void read(std::string path, std::multimap<int, char> &sortedWieght);

    void write(std::string pathToRead, std::string pathToWrite, std::map<unsigned char, std::string> &dict);
    unsigned long long convertFromBinary(std::string code);
};


#endif //KDZ_ENCODE_H
