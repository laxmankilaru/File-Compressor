#include <bits/stdc++.h>
using namespace std;

class Node{
    char character;
    int frequency;
    private:
    Node *left,*right;
    public:
    Node(char x,int f=0);
    Node* getleft() const;
    Node* getright() const;
    void setleft(Node *l);
    void setright(Node *r);
    char getchar() const;
    int getfrequency() const;
};