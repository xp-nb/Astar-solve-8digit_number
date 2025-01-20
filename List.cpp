#pragma once
#include <iostream>
#include "tree.cpp"
using namespace std;
struct ListNode
{
    Node* address;
    int fn;
};
struct List
{
    ListNode dat[100];
    Node* bestNode;
    int length;
};
void initlist(List &L)
{
    L.length = 0;
    L.bestNode = NULL;
    cout << "List is initialized" << endl;
}
void addList(List &L, Node* n)
{
    if (L.length < 100)
    {
        L.dat[L.length].address = n;
        L.dat[L.length].fn = n->height+n->hn;
        L.length++;
    }
    else
    {
        cout << "List is full" << endl;
    }
}
void deleteList(List &L,int index)
{
    if(L.length > 0)
    {
        for(int i = index;i<L.length-1;i++)
            L.dat[i] = L.dat[i + 1];
        L.length--;
    }
    else
    {
        cout << "List is empty" << endl;
    }
}
//寻找最小fn，返回最小fn对应的节点地址
int findbest(List &L)
{
    int min = L.dat[0].fn;
    int index = 0;
    Node* Node = L.dat[0].address;
    for(int i = 1;i<L.length;i++)
    {
        if(L.dat[i].fn < min)
        {
            min = L.dat[i].fn;
            Node = L.dat[i].address;
            index = i;
        }
    }
    L.bestNode = Node;
    return index;
}