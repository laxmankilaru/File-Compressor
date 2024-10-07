#include "frequencycounter.h"

const unordered_map<char, int> &frequencycounter::getfrequencymap() const
{
    return frequencymap;
}

void frequencycounter::readfile(string filename)
{
    ifstream ifile;
    ifile.open(filename,ios::in);
    char x;
    while(ifile.get(x)){
        frequencymap[x]++;
    }
    ifile.close();
    return;
}
