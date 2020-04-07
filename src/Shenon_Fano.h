//
// Created by rmima on 31.03.2020.
//
#include "iostream"
#include <vector>
#ifndef KDZ_SHENON_FANO_H
#define KDZ_SHENON_FANO_H


class Shenon_Fano
{
public:
    Shenon_Fano();

    void build();
    void addChance(int chance);
    void buildTree(int l, int r);

    std::vector<std::string> res;
    std::vector<int> q;

};


#endif //KDZ_SHENON_FANO_H
