#include "Huffman.h"
#define INTERNAL_NODE_CHARACTER char(128)
#define PSEUDO_EOF char(129)
#define CHARACTER_CODE_SEPERATOR char(130)
#define HEADER_ENTRY_SEPERATOR char(131)
#define HEADER_TEXT_SEPERATOR char(132)
int Huffman::mycompartor::operator()(Node *node1, Node *node2)
{
    return node1->getfrequency() > node2->getfrequency();
}

void Huffman::encodecharacters(Node *root, string codestring)
{
    if(root==nullptr) return;
    if(root->getchar()!=INTERNAL_NODE_CHARACTER){
        codemap[root->getchar()] = codestring;
    }
    encodecharacters(root->getleft(),codestring+"0");
    encodecharacters(root->getright(),codestring+"1");
}

void Huffman::writeheader(ofstream &outputstream)
{
    for(auto &item:codemap){
        outputstream<<item.first<<CHARACTER_CODE_SEPERATOR<<item.second<<HEADER_ENTRY_SEPERATOR;
    }
    outputstream<<HEADER_TEXT_SEPERATOR;
}

void Huffman::readheader(ifstream &inputStream)
{
    codemap.clear();
    char character;
    inputStream.get(character);
    char key = character;
    while (character != HEADER_TEXT_SEPERATOR) {
        if (character == CHARACTER_CODE_SEPERATOR) {
            inputStream.get(character);
            while (character != HEADER_ENTRY_SEPERATOR) {
                codemap[key] += character;
                inputStream.get(character);
            }
        } else
            key = character;
        inputStream.get(character);
    }
}

Node *Huffman::builddecodingtree(unordered_map<char, string> encodingMap)
{
    Node *rootNode = new Node(INTERNAL_NODE_CHARACTER);
    Node *previousNode;

    for (const auto &item : encodingMap) {
        previousNode = rootNode;
        Node *newNode = new Node(item.first);
        string characterCode = item.second;
        for (int i = 0; i < characterCode.size(); ++i) {
            if (characterCode[i] == '0') {
                if (i == characterCode.size() - 1)
                    previousNode->setleft(newNode);
                else {
                    if (!previousNode->getleft()) {
                        previousNode->setleft(new Node(INTERNAL_NODE_CHARACTER));
                        previousNode = previousNode->getleft();
                    } else previousNode = previousNode->getleft();
                }
            } else {
                if (i == characterCode.size() - 1)
                    previousNode->setright(newNode);
                else {
                    if (!previousNode->getright()) {
                        previousNode->setright(new Node(INTERNAL_NODE_CHARACTER));
                        previousNode = previousNode->getright();
                    } else previousNode = previousNode->getright();
                }
            }
        }

    }
    return rootNode;
}

void Huffman::huffer(unordered_map<char, int> frequencymap)
{
    priority_queue<Node *,vector<Node *>,mycompartor> hufferqueue;
    string tempString;
    Node *leftnode,*rightnode,*newnode;
    for(auto &item : frequencymap){
        hufferqueue.push(new Node(item.first,item.second));
    }
    while(hufferqueue.size()!=1){
        leftnode = hufferqueue.top();
        hufferqueue.pop();
        rightnode = hufferqueue.top();
        hufferqueue.pop();
        newnode = new Node(INTERNAL_NODE_CHARACTER,leftnode->getfrequency()+rightnode->getfrequency());
        hufferqueue.push(newnode);
        newnode->setleft(leftnode);
        newnode->setright(rightnode);
    }
    encodecharacters(hufferqueue.top(),tempString);
}

void Huffman::dehuffer(string filename, string decompressedfilename)
{
    char x;
    string s;
    ifstream ifile;
    ifile.open(filename,ios::in);
    readheader(ifile);
    while(ifile.get(x)){
        bitset<8> bits(x);
        s += bits.to_string();
    }
    Node *root = builddecodingtree(codemap);
    decompresstofile(s,root,decompressedfilename);
}

void Huffman::compresstofile(string inputfilename, string outputfilename)
{
    char x;
    string file;
    ifstream input;
    ofstream output;
    input.open(inputfilename,ios::in);
    output.open(outputfilename,ios::out);
    writeheader(output);
    while(input.get(x)){
        file += codemap[x];
    }
    input.close();
    file += codemap[PSEUDO_EOF];
    unsigned long remainder = (file.size() - 1) % 8;
    for (int i = 0; i < 8 - remainder; ++i)
        file += '0';
    stringstream stringStream(file);

    while (stringStream.good()) {
        bitset<8> bits;
        stringStream >> bits;
        char c = char(bits.to_ulong());
        output << c;
    }
    output.flush();
    output.close();
}

void Huffman::decompresstofile(string codestring, Node *root, string decompressedfilename)
{
    ofstream ofile;
    ofile.open(decompressedfilename,ios::out);
    Node *x = root;
    for(int i=0;i<codestring.size()+1;i++){
        if (codestring[i] == '0')
            x = x->getleft();
        else
            x = x->getright();

        if (x->getchar() != INTERNAL_NODE_CHARACTER) {
            if (x->getchar() == PSEUDO_EOF)
                break;
            ofile << x->getchar();
            x = root;
        }
    }
    ofile.flush();
    ofile.close();
}
