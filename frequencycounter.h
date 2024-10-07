#include <bits/stdc++.h>
using namespace std;

class frequencycounter{
    unordered_map<char,int> frequencymap;
    public:
    const unordered_map<char,int> &getfrequencymap() const;
    void readfile(string filename);
};