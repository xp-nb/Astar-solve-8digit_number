#include<iostream>
#include "tree.cpp"
#include "list.cpp"
using namespace std;
class Grid3x3
{
public:
    int grid[9];
    int p;
    Grid3x3(){p = -1;}
    void readGrid(int num[9])
    {
        for(int i = 0;i < 9;i++){
            grid[i] = num[i];
        }
    }
    //返回空白格位置
    int getBlank()
    {
        for(p = 0;p < 9;p++){
            if(grid[p] == 0)return p;
        }
        return -1;
    }
    //空白格向左移
    int moveLeft(int num[9])
    {
        if(p%3 == 0)return -1;
        swapNum(num[p-1],num[p]);
        return p-1;
    }
    //空白格向右移
    int moveRight(int num[9])
    {
        if(p%3 == 2)return -1;
        swapNum(num[p+1],num[p]);
        return p+1;
    }
    //空白格向上移
    int moveUp(int num[9])
    {
        if(p < 3)return -1;
        swapNum(num[p-3],num[p]);
        return p-3;
    }
    //空白格向下移
    int moveDown(int num[9])
    {
        if(p > 5)return -1;
        swapNum(num[p+3],num[p]);
        return p+3;
    }
    //判断九宫格状态是否为最终状态
    bool ifFinal()
    {
        for(int i = 0;i < 9;i++){
            switch (i){
                case 0:if(grid[i] != 1)return false;break;
                case 1:if(grid[i] != 2)return false;break;
                case 2:if(grid[i] != 3)return false;break;
                case 3:if(grid[i] != 8)return false;break;
                case 4:if(grid[i] != 0)return false;break;
                case 5:if(grid[i] != 4)return false;break;
                case 6:if(grid[i] != 7)return false;break;
                case 7:if(grid[i] != 6)return false;break;
                case 8:if(grid[i] != 5)return false;break;
                default:break;
            }
        }
        return true;
    }
    void printGrid(int num[9])
    {
        cout<<"----------"<<endl;
        for(int i = 0;i < 9;i++)
        {
            cout << num[i] << " ";
            if(i%3 == 2)cout << endl;
        }
    }
    //启发函数
    int hn(int num[9])
    {
        int sum = 0;
        for(int i = 0;i < 9;i++)
        {
            if(!isRight(i,num[i]) && num[i] != 0)//位置不对
                sum += ManhattanDistance(i,findRightP(num[i]));
        }
        return sum;
    }
    //操作算子，对最佳结点进行拓展
    void operate(List &L)
    {
        Node *p = L.bestNode;
        int temp1[9];int temp2[9];int temp3[9];int temp4[9];
        //复制4个数组
        for(int i = 0;i < 9;i++)
        {
            temp1[i] = grid[i];
            temp2[i] = grid[i];
            temp3[i] = grid[i];
            temp4[i] = grid[i];
        }
        if(p->move != Right && moveLeft(temp1) != -1)
        {
            Node *q = new Node;
            for(int i = 0;i < 9;i++)
                q->data[i] = temp1[i];
            initlink(q);
            q->move = Left;
            q->height = p->height+1;
            q->hn = hn(temp1);
            p->left = q;
            q->parent = p;
            addList(L,q);
        }
        if(p->move != Left && moveRight(temp2) != -1)
        {
            Node *q = new Node;
            for(int i = 0;i < 9;i++)
                q->data[i] = temp2[i];
            initlink(q);
            q->move = Right;
            q->height = p->height+1;
            q->hn = hn(temp2);
            p->right = q;
            q->parent = p;
            addList(L,q);
        }
        if(p->move != Down && moveUp(temp3) != -1)
        {
            Node *q = new Node;
            for(int i = 0;i < 9;i++)
                q->data[i] = temp3[i];
            initlink(q);
            q->move = Up;
            q->height = p->height+1;
            q->hn = hn(temp3);
            p->up = q;
            q->parent = p;
            addList(L,q);
        }
        if(p->move != Up && moveDown(temp4) != -1)
        {            
            Node *q = new Node;
            for(int i = 0;i < 9;i++)
                q->data[i] = temp4[i];
            initlink(q);
            q->move = Down;
            q->height = p->height+1;
            q->hn = hn(temp4);
            p->down = q;
            q->parent = p;
            addList(L,q);
        }
    }


private:
    void swapNum(int &a,int &b)
    {
        int temp = a;
        a = b;
        b = temp;
    }
    //判断此格中的数字是否是否在正确的位置
    bool isRight(int p,int num)
    {
        switch (p)
        {
        case 0:if(num == 1)return true;break;
        case 1:if(num == 2)return true;break;
        case 2:if(num == 3)return true;break;
        case 3:if(num == 8)return true;break;
        case 4:if(num == 0)return true;break;
        case 5:if(num == 4)return true;break;
        case 6:if(num == 7)return true;break;
        case 7:if(num == 6)return true;break;
        case 8:if(num == 5)return true;break;
        default:break;
        }
        return false;
    }
    //为该数字找到正确的位置
    int findRightP(int num)
    {
        switch (num)
        {
            case 0:return 4;break;
            case 1:return 0;break;
            case 2:return 1;break;
            case 3:return 2;break;
            case 4:return 5;break;
            case 5:return 8;break;
            case 6:return 7;break;
            case 7:return 6;break;
            case 8:return 3;break;
            default:break;
        }
        return -1;
    }
    //求曼哈顿距离
    int ManhattanDistance(int p,int target)
    {
        int x1 = p%3;
        int x2 = target%3;
        int y1 = p/3;
        int y2 = target/3;
        return abs(x1-x2)+abs(y1-y2);
    }
};
int main()
{
    Grid3x3 g;
    Tree T;
    List L ;
    int num[9] = {2,8,3,1,0,4,7,6,5};
    //初始化
    initlist(L);
    g.readGrid(num);//九宫格空间读取数据
    T.readNode(g.grid,T.root);//树节点读取数据
    L.bestNode = T.root;//最佳拓展结点更新
    while(!g.ifFinal())
    {
        //确定空白格位置
        g.getBlank();
        //拓展
        g.operate(L);
        //求fn，找最佳拓展结点
        int bset_index = findbest(L);
        //T.printNodeDate(L.bestNode);
        deleteList(L,bset_index);
        //更新九宫格空间
        g.readGrid(L.bestNode->data);
    }
    cout<<"find the solution:"<<endl;
    T.getPath(L.bestNode); 
}