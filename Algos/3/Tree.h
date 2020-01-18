#ifndef INC_4_TREE_H
#define INC_4_TREE_H
#endif //INC_4_TREE_H
#include <iostream>
#include <time.h>
#include <cstring>

using namespace std;



class Node {
    char d;
    Node *left;
    Node *right;
    Node *middle;
public:
    Node(): d('\0'), left(nullptr), right(nullptr), middle(nullptr){}
    ~Node(){
        delete right;
        delete left;
        delete middle;
    }
    friend class Tree;
};

class Tree{
    Node *root;
    char num, maxnum;
    int maxrow, offset;
    char **SCREEN;
    void clrscr();
    Node *MakeNode(int depth);
    void OutNodes(Node *v, int r, int c);
    int restask = 0;
public:
    Tree(char num, char maxnum, int maxrow);
    ~Tree();
    void MakeTree(){
        root = MakeNode(0);
    }
    bool exist(){return root != nullptr;}
    void OutTree();
    void task(Node *ob);
    int bypass(){
        task(root);
        return restask;
    }
};

Tree::Tree(char nm, char mnm, int mxr):
    num(nm), maxnum(mnm), maxrow(mxr), offset(60), root(nullptr), SCREEN(new char *[maxrow])
    {
    for(int i = 0; i < maxrow; ++i) SCREEN[i] = new char[120];
    }

Tree :: ~Tree(){for(int i = 0; i < maxrow; ++i) delete []SCREEN[i];
                delete []SCREEN; delete root;}

Node *Tree::MakeNode(int depth)
{
    Node *v = nullptr;
    int Y = (depth < rand()%maxrow + 1) && (num <= 'z');
    if(Y){
        v = new Node;
        v->left = MakeNode(depth + 1);
        v->middle = MakeNode(depth + 1);
        v->right = MakeNode(depth + 1);
        v->d = num++;
    }
    return v;
}

void Tree::OutTree(){
    clrscr();
    OutNodes(root, 1, offset);
    for(int i = 0; i < maxrow; ++i){
        SCREEN[i][119] = 0;
        std::cout << '\n' << SCREEN[i];
    }
    std::cout << '\n';
}

void Tree::clrscr() {
    for(int i = 0; i < maxrow; ++i) memset(SCREEN[i],'.',120);
}

void Tree::OutNodes(Node *v, int r, int c)
{
    if(r && c && (c < 120)) SCREEN[r - 1][c - 1] = v->d;
    if (r < maxrow){
        if(v->left) OutNodes(v->left,r + 1,c - (offset >> r) + 2);
        if(v->middle) OutNodes(v->middle,r + 1, c);
        if(v->right) OutNodes(v->right, r + 1, c  + (offset >> r) - 2);
    }
}

void Tree::task(Node *ob){
    if(ob != nullptr){
        task(ob->left);
        std::cout << ob->d << "_";
        task(ob->middle);
        task(ob->right);
        if (ob->left || ob->middle || ob->right) restask++;
    }
}