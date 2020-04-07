//
// Created by rmima on 31.03.2020.
//
#include "Shenon_Fano.h"


Shenon_Fano::Shenon_Fano() {}

void Shenon_Fano::buildTree(int l, int r)
{
    if (l >= r)
        return;

    if (l == r - 1)
    {
        res[l] += "0";
        res[r] += "1";
        return;
    }
    int hight = l, low = r;
    int hsum = q[l];
    int lsum = q[r];
    while (hight != low - 1)
    {
        if (hsum >= lsum)
        {
            low--;
            lsum += q[low];
        }
        else
        {
            hight++;
            hsum += q[hight];
        }
    }
    for (int i = l; i <= r; ++i)
    {
        if (i <= hight)
            res[i] += "0";
        else
            res[i] += "1";
    }
    buildTree(l, hight);
    buildTree(low, r);
}

void Shenon_Fano::build()
{
    res.resize(q.size());
    buildTree(0, q.size() - 1);
}

void Shenon_Fano::addChance(int chance)
{
    q.push_back(chance);
}


