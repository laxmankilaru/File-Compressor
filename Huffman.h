#include <bits/stdc++.h>
#include "Node.h"
using namespace std;

class Huffman{
    unordered_map<char,string> codemap;
    void encodecharacters(Node *root,string codestring);
    void writeheader(ofstream&outputstream);
    void readheader(ifstream&inputstream);
    Node* builddecodingtree(unordered_map<char,string>encodingmap);
    class mycompartor{
        public:
        int operator()(Node *node1,Node* node2);
    };
    public:
    void huffer(unordered_map<char,int>frequencymap);
    void dehuffer(string filename,string decompressedfilename);
    void compresstofile(string inputfilename,string outputfilename);
    void decompresstofile(string codestring,Node *root,string decompressedfilename);
};