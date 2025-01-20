#pragma once
#include <iostream>
using namespace std;
struct Node
{
    int data[9];    //九宫格
    int height;     //结点深度
    int hn;         //启发式值
    int move;       //移动方向
    Node* left;
    Node* right;
    Node* up;
    Node* down;
    Node* parent;
};
enum move{
    Left=1,
    Right,
    Up,
    Down
};
void initlink(Node* p)
{
    p->left = NULL;
    p->right = NULL;
    p->up = NULL;
    p->down = NULL;
    p->parent = NULL;
}
class Tree
{   
public:
    Node* root;
    Tree()
    {
        root = new Node;
        root->height = 0;
        root->hn = 0;
        root->move = 0;
        initlink(root);
    }
    void readNode(int data[9],Node* p)
    {
        for (int i = 0; i < 9; ++i)
        {
            p->data[i] = data[i];
        }
    }
    void printNodeDate(Node* p)
    {
        cout<<"------Node:"<<p->height<<"------"<<endl;
        for(int i = 0;i < 9;i++)
        {
            cout << p->data[i] << " ";
            if(i%3 == 2)cout << endl;
        }
    }
    void printNode(Node* p)
    {
        if(p->left != NULL)printNodeDate(p->left);
        if(p->right != NULL)printNodeDate(p->right);
        if(p->up != NULL)printNodeDate(p->up);
        if(p->down != NULL)printNodeDate(p->down);
    }
    Node* getNode(Node* p)
    {
        return p;
    }
    void getPath(Node* p)
    {
        Node* temp[100];
        int length = 0;
        while(p->parent!=NULL)
        {
            temp[length++] = p;
            p = p->parent;
        }
        temp[length++] = p;//root
        for(int i = length-1;i >= 0;i--)
            printNodeDate(temp[i]);
    }
};