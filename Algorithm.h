#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stddef.h>
#include "Constant.h"
#include "cstring"
#include "SqList.h"
#include "SimpleLinkList.h"
#include "SimpleCircLinkList.h"
#include "CLargeInt.h"
#include "LinkStack.h"
#include "String.h"
#include "BinTree.h"
#include "BinTreeNode.h"
#include "AdjMatrixDirGraph.h"
#include "AdjMatrixUndirGraph.h"
#include "AdjMatrixDirNetwork.h"
#include "AdjMatrixUndirNetwork.h"
#include "AdjListDirGraph.h"
#include "AdjListUndirGraph.h"
#include "AdjListDirNetwork.h"
#include "AdjListUndirNetwork.h"
#include "KruskalForest.h"
#include "KruskalEdge.h"

/*
    基本算法及功能如下：
    （1）Difference(SqList &la, SqList &lb, SqList &lc):
        计算集合差集lc
    （2）Adjust(SqList &la):
        将顺序表元素分离(奇数放左边，偶数放右边)
    （3）MergeList(const SimpleLinkList<ElemType> &la, const SimpleLinkList<ElemType> &lb, SimpleLinkList<ElemType> &lc):
        将两递增有序链表合并成完整递增有序链表
    （4）Josephus(int n. int m):
        约瑟夫问题
    （5）Decompose(const SimpleLinkList<char> &la, SimpleCircLinkList<char> &letter, SimpleCircLinkList<char> &digit, SimpleCircLinkList<char> &other)
        将线性表la中的元素分为字母、数字和其它字符三类分别放入三个单循环链表
    （6）Factorial(unsigned int iNum):
        计算正大数的阶乘
    （7）Match(char *s):
        栈实现字符串中括号配对
    （8）yanghuiTriangle(int n):
        队列实现杨辉三角
    （9）SimpleIndex(String &T, String &P, int pos):
        简单字符串匹配算法
    （10）FrontRearIndex(String &T, String &P, int pos):
        首尾字符串匹配算法
    （11）KMPIndex(String &T, String &P, int pos):
        KMP字符串匹配算法
    （12）NonRecurPreOrder(BinTree<ElemType> &bt, void (*Visit)(ElemType &)):
        二叉树前序遍历非递归算法
    （13）NonRecurInOrder(BinTree<ElemType> &bt, void (*Visit)(ElemType &)):
        二叉树中序遍历非递归算法
    （14）NonRecurPostOrder(BinTree<ElemType> &bt, void (*Visit)(ElemType &)):
        二叉树后序遍历非递归算法
    （15）DFSTraverse(AdjMatrixUndirGraph<ElemType> &g, void (*Visit)(ElemType &):
        无向图深度优先遍历算法
    （16）BFSTraverse(AdjMatrixUndirGraph<ElemType> &g, void (*Visit)(ElemType &):
        无向图广度优先遍历算法
    （17）MiniSpanTreePrim(const AdjMatrixUndirNetwork<ElemType, WeightType> &net, int u0):
        Prim最小生成树算法
    （18）MiniSpanTreeKruskal(const AdjListUndirNetwork<ElemType, WeightType> &net):
        Kruskal最小生成树算法
    （19）TopSort(const AdjMatrixDirGraph<ElemType> &g):
        拓扑排序算法
    （20）CriticalPath(const AdjMatrixDirNetwork<ElemType, WeightType> &net):
        关键路径算法
    （21）ShortestPathDIJ(const AdjMatrixDirNetwork<ElemType, WeightType> &net, int v0, int *path, WeightType *dist)
        迪杰斯特拉 单源最短路径算法
*/

// 计算集合差集lc
template <class ElemType>
void Difference(const SqList<ElemType> &la, const SqList<ElemType> &lb, SqList<ElemType> &lc);

// 将顺序表元素分离(奇数放左边，偶数放右边)
void Adjust(SqList<int> &la);

// 将两递增有序链表合并成完整递增有序链表
template <class ElemType>
void MergeList(const SimpleLinkList<ElemType> &la, const SimpleLinkList<ElemType> &lb, SimpleLinkList<ElemType> &lc);

// 约瑟夫问题
void Josephus(int n, int m);

// 线性表元素分类
void Decompose(const SimpleLinkList<char> &la, SimpleCircLinkList<char> &letter, SimpleCircLinkList<char> &digit, SimpleCircLinkList<char> &other);

// 计算正大数的阶乘
CLargeInt Factorial(unsigned int iNum);

// 栈实现字符串中括号配对
bool Match(char *s);

// 队列实现杨辉三角
void yanghuiTriangle(int n);

// 简单字符串模式匹配算法
int SimpleIndex(const String &T, const String &P, int pos = 0);

// 首尾字符串模式匹配算法
int FrontRearIndex(const String &T, const String &P, int pos = 0);

// KMP字符串模式匹配算法
int KMPIndexHelp(const String &T, const String &P, int pos, int next[]);
void getNext(const String &P, int next[]);
int KMPIndex(const String &T, const String &P, int pos = 0);

// 二叉树的先序、中序、后序遍历的非递归算法实现
template <class ElemType>
void NonRecurPreOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(ElemType &));
template <class ElemType>
void NonRecurPreOrder(BinTree<ElemType> &bt, void (*Visit)(ElemType &));

template <class ElemType>
BinTreeNode<ElemType> *GoFarLeft(BinTreeNode<ElemType> *r, LinkStack<BinTreeNode<ElemType> *> &s);
template <class ElemType>
void NonRecurInOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(ElemType &));
template <class ElemType>
void NonRecurInOrder(BinTree<ElemType> &bt, void (*Visit)(ElemType &));

//非递归后序遍历，对结点应加一个标志指示右子树是否被访问，被修改后的结点结构如下：
template <class ElemType>
struct ModiNode
{
    BinTreeNode<ElemType> *node; // 指向结点
    bool rightSubTreeVisited;    // 是否右子树已被访问
};

template <class ElemType>
ModiNode<ElemType> *GoFarLeft(BinTreeNode<ElemType> *r, LinkStack<ModiNode<ElemType> *> &s);
template <class ElemType>
void NonRecurPostOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(ElemType &));
template <class ElemType>
void NonRecurPostOrder(BinTree<ElemType> &bt, void (*Visit)(ElemType &));

// 图的遍历：深度+广度遍历
template <class ElemType>
void DFS(AdjMatrixUndirGraph<ElemType> &g, int v, void (*Visit)(ElemType &));
template <class ElemType>
void DFSTraverse(AdjMatrixUndirGraph<ElemType> &g, void (*Visit)(ElemType &));

template <class ElemType>
void BFS(AdjMatrixUndirGraph<ElemType> &g, int v, void (*Visit)(ElemType &));

template <class ElemType>
void BFSTraverse(AdjMatrixUndirGraph<ElemType> &g, void (*Visit)(ElemType &));

// 图的最小代价生成树算法
// Prim算法：每次选取在两个不同分量中的两个顶点构成的权值最小的那一条边加入到MST，并把对应的另一个未访问顶点标志为已访问
/* 
   为实现Prim算法，附设一个辅助数组adjVex[]，用于存储V-U中的顶点到U的最小权值的边对应的另一个顶点，也就是当v ∈ V-U时，adjVex[v] ∈ U，
   且边<v, adjVex[v]>是v到U的所有边中权值最小的边，这样连接U到V-U的权值最小的边便是adjVex[]中具有权值最小的边，
   将U中顶点的标志域置为VISTED，V-U中顶点标志域置UNVISITED
*/
template <class ElemType, class WeightType>
int MinVertex(const AdjMatrixUndirNetwork<ElemType, WeightType> &net, int *adjVex);
template <class ElemType, class WeightType>
void MiniSpanTreePrim(const AdjMatrixUndirNetwork<ElemType, WeightType> &net, int u0);

// Kruskal算法：每次选取在两个不同分量中的两个顶点构成的权值最小的那一条边加入到MST，并把对应的另一个未访问顶点标志为已访问
/* 
   为实现Kruskal算法，
*/
template <class WeightType>
void Sort(KruskalEdge<WeightType> *a, int n);
template <class ElemType, class WeightType>
void MiniSpanTreeKruskal(const AdjListUndirNetwork<ElemType, WeightType> &net);

// 拓扑排序算法
template <class ElemType>
void StatIndegree(const AdjMatrixDirGraph<ElemType> &g, int *indegree);

template <class ElemType>
int TopSort(const AdjMatrixDirGraph<ElemType> &g);

// 关键路径算法
template <class ElemType, class WeightType>
void StatIndegree(const AdjMatrixDirNetwork<ElemType, WeightType> &net, int *indegree);
template <class ElemType, class WeightType>
int CriticalPath(const AdjMatrixDirNetwork<ElemType, WeightType> &net);

// 最短路径算法
/*
    Dijsktra算法
*/
template <class ElemType, class WeightType>
void ShortestPathDIJ(const AdjMatrixDirNetwork<ElemType, WeightType> &net, int v0, int *path, WeightType *dist);

/*
    Froyd算法
*/
template <class ElemType, class WeightType>
void ShortestPathFloyd(const AdjListDirNetwork<ElemType, WeightType> &net, int **path, WeightType **dist);

template <class ElemType>
void Difference(const SqList<ElemType> &la, const SqList<ElemType> &lb, SqList<ElemType> &lc)
{
    // 功能：用lc返回la和lb标识的集合的差集C=A-B
    // 思想：在la中取出元素，在lb中进行查找，如果未在lb中出现，将其插入到lc
    ElemType aItem, bItem;

    lc.Clear();

    for (int aPosition = 1; aPosition <= la.Length(); aPosition++)
    {
        la.GetElem(aPosition, aItem);
        bool isExistInB = false;
        for (int bPosition = 1; bPosition <= lb.Length(); bPosition++)
        {
            lb.GetElem(bPosition, bItem);
            if (aItem == bItem)
            {
                isExistInB = true;
                break; //跳出内层遍历lb的for循环
            }
        }
        if (!isExistInB)
        {
            lc.Insert(lc.Length() + 1, aItem);
        }
    }
}

void Adjust(SqList<int> &la)
{
    // 功能：将la分为左右两部分，左边元素全为奇数，右边元素全为偶数
    // 要求：时间复杂度为O(n)
    // 思想：两个位置标志位分别为aPosition=1, bPosition=la.Length(), 分别指向的是元素aItem和bItem
    // 当aItem为奇数时，Position++；当bItem为偶数时，bPosition--；当aItem为偶数且bItem为奇数时，交换两者位置
    // 当aPosition==bPosition时，完成
    int aItem, bItem;
    int aPosition, bPosition;

    aPosition = 1;
    bPosition = la.Length();

    while (aPosition < bPosition)
    {
        la.GetElem(aPosition, aItem);
        la.GetElem(bPosition, bItem);
        if (aItem % 2 == 1)
        {
            aPosition++;
        }
        else if (bItem % 2 == 0)
        {
            bPosition--;
        }
        else
        {
            la.SetElem(aPosition, bItem);
            la.SetElem(bPosition, aItem);
        }
    }
}

template <class ElemType>
void MergeList(const SimpleLinkList<ElemType> &la, const SimpleLinkList<ElemType> &lb, SimpleLinkList<ElemType> &lc)
{
    // 初始条件：la和lb中数据元素递增有序
    // 操作结果：将la和lb合并为lc，使lc中数据元素仍递增有序
    ElemType aItem, bItem;                            // la和lb中当前数据元素
    int aLength = la.Length(), bLength = lb.Length(); // la和lb的长度
    int aPosition = 1, bPosition = 1;                 // la和lb的当前元素序号

    lc.Clear(); // 清空lc
    while (aPosition <= aLength && bPosition <= bLength)
    {
        // 取出la和lb中数据元素进行归并
        la.GetElem(aPosition, aItem);
        lb.GetElem(bPosition, bItem);
        if (aItem < bItem)
        {
            // 归并aItem
            lc.Insert(lc.Length() + 1, aItem);
            aPosition++; // 指向la下一数据元素
        }
        else
        {
            // 归并bItem
            lc.Insert(lc.Length() + 1, bItem);
            bPosition++; // 指向lb下一元素
        }
    }

    while (aPosition <= aLength)
    {
        // 归并la中剩余数据元素
        la.GetElem(aPosition, aItem);
        lc.Insert(lc.Length() + 1, aItem);
        aPosition++;
    }
    while (bPosition <= bLength)
    {
        // 归并lb中剩余数据元素
        lb.GetElem(bPosition, bItem);
        lc.Insert(lc.Length() + 1, bItem);
        bPosition++;
    }
}

void Josephus(int n, int m)
{
    // 操作结果：n和人围成一个圆圈，首先第1个人从1开始一个人一个人顺时针报数，
    // 报到第m个人，令其出列。然后再从下一个人开始，从1顺时针报数报到第m个人，
    // 再令其出列，......，如此下午，直到圆圈中只剩一个人为止。此人即为优胜者
    SimpleCircLinkList<int> la; // 定义空循环链表
    int position = 0;           // 报数到的人在链表中序号
    int out, winner;
    for (int k = 1; k <= n; k++)
    {
        la.Insert(k, k); // 建立数据域为1,2,...,n的循环链表
    }
    cout << "出列者:" << endl;
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= m; j++) // 从1报数到m
        {
            position++;
            if (position > la.Length())
            {
                position = 1;
            }
        }
        la.Delete(position--, out); // 报数到m的人出列
        cout << out << " ";
    }
    la.GetElem(1, winner); // 剩下的人序号为1，为优胜者
    cout << endl
         << "优胜者:" << winner << endl;
}

void Decompose(const SimpleLinkList<char> &la, SimpleCircLinkList<char> &letter, SimpleCircLinkList<char> &digit, SimpleCircLinkList<char> &other)
{
    // 初始条件：la是单链表，数据域存放一个字符
    // 操作结果：构造3个带头结点的单循环链表表示的线性表，使每个表中只含有同一类字符
    char ch;
    int laLength = la.Length();
    for (int position = 1; position <= laLength; position++)
    {
        // 取出la中的元素
        la.GetElem(position, ch);
        if (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z'))
        {
            letter.Insert(1, ch); // ch为字母，插入letter中
        }
        else if ('0' <= ch && ch <= '9')
        {
            digit.Insert(1, ch); // ch为数字，插入digit中
        }
        else
        {
            other.Insert(1, ch); // ch为其它字符，插入在other中
        }
    }
}

CLargeInt Factorial(unsigned int iNum)
{
    // 操作结果：计算正大数的阶乘
    CLargeInt tmpLargeInt(1);

    for (unsigned int i = 1; i <= iNum; i++)
    {
        // 连乘求阶乘
        tmpLargeInt = tmpLargeInt * CLargeInt(i);
    }

    return tmpLargeInt;
}

// 简单字符串模式匹配算法
int SimpleIndex(const String &T, const String &P, int pos)
{
    // 操作结果：查找模式串P第一次在目标串T中从第pos个字符开始出现的位置
    int i = pos, j = 0; // i为T的下标，j为P的下标
    while (i < T.Length() && j < P.Length())
    {
        if (T[i] == P[j])
        {
            // 当前对应位置字符匹配成功，继续比较后续字符
            i++;
            j++;
        }
        else
        {
            // 匹配失败，指针回退，重新开始新的匹配
            i = i - j + 1; // 已经匹配成功的位数为j位，退回到本次失败匹配开始的位置，再往后移动一位
            j = 0;
        }
    }

    if (j >= P.Length())
    {
        return i - j; // 匹配成功，返回目标串T中模式串P第一个字符出现的下标位置
    }
    return -1; // 匹配失败
}

bool Match(char *s)
{
    // 操作结果：判别用字符串s表示的表达式中大、中、小括号是否配对出现
    LinkStack<char> tmpS; // 临时栈
    char tmpCh;           // 临时字符

    for (int i = 0; i < strlen(s); i++)
    {
        // 从左至右依次读字符
        if (s[i] == '(' || s[i] == '[' || s[i] == '{')
        {
            tmpS.Push(s[i]);
        }
        else if (s[i] == ')')
        {
            // 读入字符为‘(’
            if (tmpS.Empty())
            {
                return false;
            }
            else if (tmpS.Top(tmpCh), tmpCh == ')')
            {
                tmpS.Pop(tmpCh);
            }
            else
            {
                return false;
            }
        }
        else if (s[i] == ']')
        {
            // 读入字符为‘[’
            if (tmpS.Empty())
            {
                return false;
            }
            else if (tmpS.Top(tmpCh), tmpCh == '[')
            {
                tmpS.Pop(tmpCh);
            }
            else
            {
                return false;
            }
        }
        else if (s[i] == '}')
        {
            // 读入字符为‘{’
            if (tmpS.Empty())
            {
                return false;
            }
            else if (tmpS.Top(tmpCh), tmpCh == '{')
            {
                tmpS.Pop(tmpCh);
            }
            else
            {
                return false;
            }
        }
    }
    return tmpS.Empty();
}

void yanghuiTriangle(int n)
{
    // 操作结果：显示三角形的第1行~第n行
    LinkQueue<int> q;
    int s, t;

    q.InQueue(1);
    q.InQueue(1);           // 存储杨辉三角形的第1行的两个元素
    cout << 1 << "\t" << 1; // 显示杨辉三角性的第1行
    for (int i = 2; i <= n; i++)
    {
        // 依次显示杨辉三角形的第2行~第n行
        cout << endl;
        q.InQueue(1);      // 第i行的第1个元素的值为1
        cout << 1 << "\t"; // 显示第i行第1个元素的值
        q.OutQueue(s);     // 取第i-1行第1个元素的值
        for (int j = 2; j <= i; j++)
        {
            q.OutQueue(t);         // 取第i-1行第j个元素的值
            q.InQueue(s + t);      // s+t为第i行第j个元素的值
            cout << s + t << "\t"; // 显示第i行第j个元素的值
            s = t;
        }
        q.InQueue(1); // 第i行第i+1个元素的值为1
        cout << 1;
    }
    cout << endl;
}

// 首尾字符串模式匹配算法
int FrontRearIndex(const String &T, const String &P, int pos)
{
    // 操作结果：查找模式串P第一次在目标串T中从第pos个字符开始出现的位置
    int startPos = pos;                            // startPos为T开始匹配的位置下标
    while (startPos < T.Length() - P.Length() + 1) // 如果startPos大于两者长度差，则在T中已没有足够的字符数目来与P匹配
    {
        int front = 0, rear = P.Length() - 1; // 当前匹配到的P的下标位置
        while (front <= rear)
        {
            if (T[startPos + front] != P[front] || T[startPos + rear] != P[rear])
            {
                // 首或尾某个位置字符匹配失败
                break;
            }
            else
            {
                // 两端位置字符均匹配成功
                front++;
                rear--;
            }
        }
        if (front > rear)
        {
            // 匹配成功
            return startPos;
        }
        else
        {
            startPos++; // 首部或尾部字符不匹配，重新查找匹配起始点
        }
    }
    return -1;
}

// KMP字符串模式匹配算法
int KMPIndexHelp(const String &T, const String &P, int pos, int next[])
{
    // 操作结果：通过next数组查找模式串P第一次在目标串T中从第pos个字符开始出现的位置j
    int i = pos, j = 0; // i为目标串T的当前字符位置，j为模式串P的当前字符位置
    while (i < T.Length() && j < P.Length())
    {
        if (j == -1)
        {
            // 此时表明P中任何字符都不再与T[i]进行比较，下次P[0]与T[i+1]开始比较
            i++;
            j = 0;
        }
        else if (P[j] == T[i])
        {
            // P[j]与T[i]匹配
            i++;
            j++; // 模式串P与目标串T的当前位置向后移
        }
        else
        {
            // P[j]与T[i]不匹配
            // i不动，j回退到k，
            j = next[j]; // 寻找新的模式串P的匹配字符
        }
    }
    if (j < P.Length())
    {
        return -1; // 匹配失败
    }
    return i - j; // 匹配成功时，返回串P的第一个字符在串T中出现的位置下标
}

void getNext(const String &P, int next[])
{
    // 操作结果：求模式串P的next数组的元素值
    next[0] = -1;      // 由next[0]=-1开始递推
    int j = 0, k = -1; // next[j]=k成立的初始情况
    while (j < P.Length() - 1)
    {
        // 数组next的下标范围为0~P.Length()-1，通过递推方式得到next[j+1]的值
        if (k == -1 || P[k] == P[j])
        {
            // 此时next[j+1]=next[j]+1
            next[j + 1] = k + 1; // 由于P[k]=P[j]，所以next[j+1]=next[j]+1=k+1
            j++;
            k++; // 由于已求得next[j+1]=k+1，所以j更新为++j，k更新为++k
        }
        else
        {
            // P[k]与P[j]不匹配
            k = next[k]; // 寻求新的匹配字符
        }
    }
}

int KMPIndex(const String &T, const String &P, int pos)
{
    // 操作结果：查找模式串P第一次在目标串T从第pos个字符开始出现的位置
    int *next = new int[P.Length()];            // 为数组next分配空间
    getNext(P, next);                           // 求模式串P的next数组的元素值
    int result = KMPIndexHelp(T, P, pos, next); // 返回模式串P第一次在目标串T中从第pos个字符开始出现的位置
    delete[] next;                              // 释放next所占用的存储空间
    return result;
}

// 二叉树的先序、中序、后序遍历的非递归算法实现
template <class ElemType>
void NonRecurPreOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(ElemType &))
{
    // 操作结果：非递归先序遍历以r为根的二叉树
    BinTreeNode<ElemType> *cur = r; // 当前结点
    LinkStack<BinTreeNode<ElemType> *> s;

    while (cur != NULL)
    {
        // 处理当前结点
        (*Visit)(cur->data); // 访问当前结点，本算法唯一的访问结点操作
        s.Push(cur);         //当前结点入栈

        if (cur->leftChild != NULL)
        {
            // cur的先序序列后继为cur->leftChild
            cur = cur->leftChild;
        }
        else if (!s.Empty()) // 当前已有被访问过的结点
        {
            // cur的先序序列后继为栈s的栈顶结点的非空右孩子（注意这里不是cur！cur已经在入栈前就被访问过了！）
            while (!s.Empty())
            {
                // 栈为空时自动跳出While循环
                s.Pop(cur); // 出栈
                cur = cur->rightChild;
                if (cur != NULL)
                {
                    // 若有右孩子则跳出循环
                    break;
                }
            }
        }
        else
        {
            // 栈s为空，无后继，将cur置空，结束最外层循环
            cur = NULL;
        }
    }
}

template <class ElemType>
void NonRecurPreOrder(BinTree<ElemType> &bt, void (*Visit)(ElemType &))
{
    // 操作结果：先序遍历二叉树
    NonRecurPreOrderHelp(bt.GetRoot(), Visit);
    // 调用辅助函数完成先序遍历二叉树
}

template <class ElemType>
BinTreeNode<ElemType> *GoFarLeft(BinTreeNode<ElemType> *r, LinkStack<BinTreeNode<ElemType> *> &s)
{
    // 操作结果：返回以r为根的二叉树的最左侧的结点，并将搜索过程中的结点加入到栈s中
    if (r == NULL)
    {
        // 空二叉树
        return NULL;
    }
    else
    {
        // 非空二叉树
        BinTreeNode<ElemType> *cur = r;
        while (cur->leftChild != NULL)
        {
            s.Push(cur); // 把有左孩子的结点全部入栈
            cur = cur->leftChild;
        }
        return cur;
    }
}

template <class ElemType>
void NonRecurInOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(ElemType &))
{
    // 操作结果：非递归中序遍历以r为根的二叉树
    BinTreeNode<ElemType> *cur = r;
    LinkStack<BinTreeNode<ElemType> *> s;

    cur = GoFarLeft<ElemType>(cur, s); // cur为以r为根的二叉树的最左侧的结点

    while (cur != NULL)
    {
        (*Visit)(cur->data);
        if (cur->rightChild != NULL)
        {
            // 右孩子不为空，cur的中序序列后继为右子树的最左侧结点
            cur = GoFarLeft<ElemType>(cur->rightChild, s);
        }
        else if (!s.Empty())
        {
            // 右孩子为空，cur的中序序列后继为栈s的栈顶结点
            s.Pop(cur);
        }
        else
        {
            // 栈s为空，无后继，cur置空
            cur = NULL;
        }
    }
}

template <class ElemType>
void NonRecurInOrder(BinTree<ElemType> &bt, void (*Visit)(ElemType &))
{
    // 操作结果：中序遍历二叉树
    NonRecurInOrderHelp(bt.GetRoot(), Visit);
    // 调用辅助函数完成中序遍历二叉树
}

template <class ElemType>
ModiNode<ElemType> *GoFarLeft(BinTreeNode<ElemType> *r, LinkStack<ModiNode<ElemType> *> &s)
{
    // 操作结果：返回以r为根的二叉树的最左侧的结点，并将搜索过程中的被修改后的结点加入到栈s中
    if (r == NULL)
    {
        return NULL;
    }
    else
    {
        BinTreeNode<ElemType> *cur = r;
        ModiNode<ElemType> *newPtr;
        while (cur->leftChild != NULL)
        {
            // cur存在左孩子，则cur移向左孩子
            newPtr = new ModiNode<ElemType>;
            newPtr->node = cur;
            newPtr->rightSubTreeVisited = false;
            s.Push(newPtr);
            cur = cur->leftChild;
        }
        // While循环结束后cur就是最左边结点
        newPtr = new ModiNode<ElemType>;
        newPtr->node = cur;
        newPtr->rightSubTreeVisited = false;
        return newPtr;
    }
}

template <class ElemType>
void NonRecurPostOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(ElemType &))
{
    // 操作结果：非递归后序遍历以r为根的二叉树
    ModiNode<ElemType> *cur;
    LinkStack<ModiNode<ElemType> *> s;

    cur = GoFarLeft<ElemType>(r, s); // cur为以r为根的二叉树的最左侧的被搜索结点
    while (cur != NULL)
    {
        // 处理当前结点
        if (cur->node->rightChild == NULL || cur->rightSubTreeVisited)
        {
            // 如当前结点无右子树或右子树已被访问
            (*Visit)(cur->node->data); // 访问当前结点
            delete cur;                // 释放空间
            if (!s.Empty())
            {
                // 栈非空，则栈顶即为下一次要访问的结点
                s.Pop(cur);
            }
            else
            {
                // 栈为空，遍历完毕
                cur = NULL;
            }
        }
        else
        {
            // 有右子树且未被访问
            cur->rightSubTreeVisited = true; // 标识该结点的右子树已被访问
            s.Push(cur);
            cur = GoFarLeft<ElemType>(cur->node->rightChild, s); // 搜索右子树最左侧结点
        }
    }
}

template <class ElemType>
void NonRecurPostOrder(BinTree<ElemType> &bt, void (*Visit)(ElemType &))
{
    // 操作结果：后序遍历二叉树
    NonRecurPostOrderHelp(bt.GetRoot(), Visit);
    // 调用辅助函数完成后序遍历二叉树
}

// 图的遍历：深度+广度遍历
template <class ElemType>
void DFS(AdjMatrixUndirGraph<ElemType> &g, int v, void (*Visit)(ElemType &))
{
    // 初始条件：存在图g
    // 操作结果：从顶点v出发进行深度优先搜索图g，递归实现
    g.SetTag(v, VISITED); // 标志顶点v已访问
    ElemType e;           // 临时变量
    g.GetElem(v, e);      // 返回顶点v的数据元素
    Visit(e);             // 访问（打印）顶点v的数据元素
    int w;
    for (w = g.FirstAdjVex(v); w >= 0; w = g.NextAdjVex(v, w))
    {
        int tag;
        g.GetTag(w, tag);
        if (tag == UNVISITED)
        {
            DFS(g, w, Visit);
        }
    }
}

template <class ElemType>
void DFSTraverse(AdjMatrixUndirGraph<ElemType> &g, void (*Visit)(ElemType &))
{
    // 初始条件：存在图g
    // 操作结果：对图g进行深度优先遍历
    // 需要一个栈存储已访问过的元素用来回溯，或者直接递归即可
    int v;
    for (v = 0; v < g.GetVexNum(); v++)
    {
        // 对每个顶点作访问标志（其实在构造函数中已经初始化为UNVISITED）
        g.SetTag(v, UNVISITED);
    }

    for (v = 0; v < g.GetVexNum(); v++)
    {
        // 对尚未访问的顶点按DFS进行深度优先搜索
        int tag;
        g.GetTag(v, tag);
        if (tag == UNVISITED)
        {
            // 从v=0（可以任意指定-加个函数参数即可）开始进行深度优先搜索
            DFS(g, v, Visit);
        }
    }
}

template <class ElemType>
void BFS(AdjMatrixUndirGraph<ElemType> &g, int v, void (*Visit)(ElemType &))
{
    // 初始条件：存在图g
    // 操作结果：从顶点v出发进行广度优先搜索图g
    g.SetTag(v, VISITED); // 标志顶点v已访问
    ElemType e;           // 临时变量
    g.GetElem(v, e);      // 返回顶点v的数据元素
    Visit(e);             // 访问（打印）顶点v的数据元素
    LinkQueue<int> q;     // 定义队列
    q.InQueue(v);         // 顶点v入队
    while (!q.Empty())
    {
        // 队列非空，开始循环
        int u, w;      //临时顶点
        q.OutQueue(u); //出队
        for (w = g.FirstAdjVex(u); w >= 0; w = g.NextAdjVex(u, w))
        {
            // 对u尚未访问过的邻接顶点w进行访问
            int tag;
            g.GetTag(w, tag);
            if (tag == UNVISITED)
            {
                // 对w进行访问
                g.SetTag(w, VISITED); // 标志顶点w已访问
                g.GetElem(w, e);      // 返回顶点w的数据元素
                Visit(e);             // 访问（打印）顶点w的数据元素
                q.InQueue(w);         // 顶点w入队
            }
        }
    }
}

template <class ElemType>
void BFSTraverse(AdjMatrixUndirGraph<ElemType> &g, void (*Visit)(ElemType &))
{
    // 初始条件：存在图g
    // 操作结果：对图g进行广度优先遍历
    // 需要一个栈存储已访问过的元素用来回溯
    int v;
    for (v = 0; v < g.GetVexNum(); v++)
    {
        // 对每个顶点作访问标志（其实在构造函数中已经初始化为UNVISITED）
        g.SetTag(v, UNVISITED);
    }

    for (v = 0; v < g.GetVexNum(); v++)
    {
        // 对尚未访问的顶点按BFS进行深度优先搜索
        int tag;
        g.GetTag(v, tag);
        if (tag == UNVISITED)
        {
            // 从v=0（可以任意指定-加个函数参数即可）开始进行深度优先搜索
            BFS(g, v, Visit);
        }
    }
}

// 图的最小代价生成树算法
// Prim算法：每次选取在两个不同分量中的两个顶点构成的权值最小的那一条边加入到MST，并把对应的另一个未访问顶点标志为已访问
/* 
   为实现Prim算法，附设一个辅助数组adjVex[]，用于存储V-U中的顶点到U的最小权值的边对应的另一个顶点，也就是当v ∈ V-U时，adjVex[v] ∈ U，
   且边<v, adjVex[v]>是v到U的所有边中权值最小的边，这样连接U到V-U的权值最小的边便是adjVex[]中具有权值最小的边，
   将U中顶点的标志域置为VISTED，V-U中顶点标志域置UNVISITED
*/
template <class ElemType, class WeightType>
int MinVertex(const AdjMatrixUndirNetwork<ElemType, WeightType> &net, int *adjVex)
{
    // 操作结果：返回w，使得边<w,adjVex[w]>为连接V-U到U的具有最小权值的边（w是未访问的顶点，但是是在未访问的顶点中到已访问的顶点之间边权值最小的顶点）
    int w = -1; // 初始化最小顶点
    int v;      // 临时顶点
    for (v = 0; v < net.GetVexNum(); v++)
    {
        // 查找第一个满足条件的V-U中顶点v
        int tag;
        net.GetTag(v, tag);
        if (tag == UNVISITED && net.IsEdge(v, adjVex[v]))
        {
            // 第一个条件表示v为V-U中的顶点
            // 第二个条件表示存在从v到U的边(v, adjVex[v])
            w = v;
            break;
        }
    }

    for (v++; v < net.GetVexNum(); v++)
    {
        // 查找连接到V-U和U的具有最小权值的边<w,adjVex[w]>
        int tag;
        net.GetTag(v, tag);
        if (tag == UNVISITED && net.IsEdge(v, adjVex[v]) &&
            net.GetWeight(v, adjVex[v]) < net.GetWeight(w, adjVex[w]))
        {
            w = v;
        }
    }
    return w;
}

template <class ElemType, class WeightType>
void MiniSpanTreePrim(const AdjMatrixUndirNetwork<ElemType, WeightType> &net, int u0)
{
    // 初始条件：存在网net，u0为net的一个顶点
    // 操作结果：用Prim算法从u0出发构造网net的最小代价生成树
    if (net.IsVertex(u0))
    {
        int *adjVex;                       // 如果v∈V-U，net.GetWeight(v, adjVex[v])>0，表示（v, adjVex[v]）是v到U具有最小权值的边
        int u, v, w;                       // 表示顶点的临时变量
        adjVex = new int[net.GetVexNum()]; // 分配存储空间，开始构造辅助数组adjVex
        for (v = 0; v < net.GetVexNum(); v++)
        {
            // 初始化辅助数组adjVex，并对顶点作标志，此时U={v0}
            if (v != u0)
            {
                // 对于v!=u0
                adjVex[v] = u0;
                net.SetTag(v, UNVISITED);
            }
            else
            {
                // 对于v∈U
                net.SetTag(v, VISITED);
                adjVex[v] = u0;
            }
        }
        for (u = 1; u < net.GetVexNum(); u++)
        {
            // 选择生成树的其余net.GetVexNum()-1个顶点
            w = MinVertex(net, adjVex); // 选择使得边<w, adjVex[w]>为连接V-U到U的具有最小权值的边
            if (w == -1)
            {
                // 表示U与V-U已无边相连
                return;
            }
            cout << "edge:(" << adjVex[w] << "," << w << "), weight="
                 << net.GetWeight(w, adjVex[w]) << endl; // 输出边及权值
            net.SetTag(w, VISITED);                      // 将w并入U
            for (int k = net.FirstAdjVex(w); k >= 0; k = net.NextAdjVex(w, k))
            {
                // 新顶点并入U后重新选择最小边
                int tag;
                net.GetTag(k, tag);
                if (tag == UNVISITED &&                                   // v∈V-U
                    (net.GetWeight(k, w) < net.GetWeight(k, adjVex[k]) || // 边<v,w>的权值最小
                     !net.IsEdge(k, adjVex[k])))                          // 不存在边<v, adjVex[v]>
                {
                    // <v,w>为新的最小边
                    adjVex[k] = w;
                }
            }
        }
        delete[] adjVex; // 释放辅助数组空间
    }
}

// Kruskal算法：每次选取在两个不同分量中的两个顶点构成的权值最小的那一条边加入到MST，并把对应的另一个未访问顶点标志为已访问
/* 
   为实现Kruskal算法，附设一个辅助数组adjVex[]，用于存储V-U中的顶点到U的最小权值的边对应的另一个顶点，也就是当v ∈ V-U时，adjVex[v] ∈ U，
   且边<v, adjVex[v]>是v到U的所有边中权值最小的边，这样连接U到V-U的权值最小的边便是adjVex[]中具有权值最小的边，
   将U中顶点的标志域置为VISTED，V-U中顶点标志域置UNVISITED
*/
template <class WeightType>
void Sort(KruskalEdge<WeightType> *a, int n)
{
    // 操作结果：按权值对边进行升序排序
    for (int i = n - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (a[j].weight > a[j + 1].weight)
            {
                // 出现逆序，则交换a[j]与a[j+1]
                KruskalEdge<WeightType> tmpEdge; // 临时边
                tmpEdge = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmpEdge;
            }
        }
    }
}

template <class ElemType, class WeightType>
void MiniSpanTreeKruskal(const AdjListUndirNetwork<ElemType, WeightType> &net)
{
    // 初始条件：存在网net
    // 用Kruskal算法构造网net的最小代价生成树
    int count;                              // 计数器
    KruskalForest kForest(net.GetVexNum()); // 定义Kruskal森林
    KruskalEdge<WeightType> *kEdge;
    kEdge = new KruskalEdge<WeightType>[net.GetEdgeNum()]; // 定义边数组，只存储v>u的边(v,u)

    count = 0; // 表示当前已存入kEdge的边数
    for (int v = 0; v < net.GetVexNum(); v++)
    {
        for (int u = net.FirstAdjVex(v); u >= 0; u = net.NextAdjVex(v, u))
        {
            // 将边(v,u)存入kEdge中
            if (v > u)
            {
                // 只存储v>u的边(v,u)
                KruskalEdge<WeightType> tmpKEdge(v, u, net.GetWeight(v, u));
                kEdge[count++] = tmpKEdge;
            }
        }
    }

    Sort(kEdge, count); // 对边按权值排序
    for (int i = 0; i < count; i++)
    {
        // 对kEdgePtr中的边进行搜索
        int v1 = kEdge[i].vertex1, v2 = kEdge[i].vertex2;
        if (!kForest.IsSameTree(v1, v2))
        {
            // 边的两端不再同一棵树上，则为最小代价生成树上的边
            cout << "edge: (" << v1 << "," << v2 << "), weight:" << net.GetWeight(v1, v2) << endl; // 输出边及权值
            kForest.Union(v1, v2);                                                                 // 将v2所在树的所有顶点合并到v1所在树上
        }
    }
    delete[] kEdge; // 释放存储空间
}

// 拓扑排序算法
template <class ElemType>
void StatIndegree(const AdjMatrixDirGraph<ElemType> &g, int *indegree)
{
    // 操作结果：统计图g的各顶点的入度
    for (int v = 0; v < g.GetVexNum(); v++)
    {
        // 初始化入度为0
        indegree[v] = 0;
    }

    for (int v1 = 0; v1 < g.GetVexNum(); v1++)
    {
        // 遍历图的顶点
        for (int v2 = g.FirstAdjVex(v1); v2 != -1; v2 = g.NextAdjVex(v1, v2))
        {
            // v2为v1的一个邻接点
            indegree[v2]++;
        }
    }
}

template <class ElemType>
int TopSort(const AdjMatrixDirGraph<ElemType> &g)
{
    // 初始条件：存在有向图g
    // 操作结果：如g无回路，则输出g的顶点的一个拓扑序列，并返回SUCCESS，否则返回FAIL
    int *indegree = new int[g.GetVexNum()]; // 顶点入度数组
    LinkQueue<int> q;                       // 队列
    int count = 0;
    StatIndegree(g, indegree); // 统计顶点的入度

    for (int v = 0; v < g.GetVexNum(); v++)
    {
        // 遍历顶点
        if (indegree[v] == 0)
        {
            // 建立入度为0的顶点队列
            q.InQueue(v);
        }
    }
    cout << "Top Sequence:" << endl;
    while (!q.Empty())
    {
        // 队列非空
        int v1;
        q.OutQueue(v1); // 取出一个入度为0的顶点
        cout << v1 << " ";
        count++; // 对输出顶点计数
        for (int v2 = g.FirstAdjVex(v1); v2 != -1; v2 = g.NextAdjVex(v1, v2))
        {
            // v2为v1的一个邻接点，对v1的每个邻接点入度减1
            if (--indegree[v2] == 0)
            {
                // 删去v1到v2的边后，v2入度为0，将v2入队
                q.InQueue(v2);
            }
        }
    }
    cout << endl;
    delete[] indegree; // 释放indegree所占用的存储空间

    if (count < g.GetVexNum())
    {
        return TOP_FAIL; // 图g有回路
    }
    else
    {
        return TOP_SUCCESS; // 拓扑排序成功
    }
}

// 关键路径算法
template <class ElemType, class WeightType>
void StatIndegree(const AdjMatrixDirNetwork<ElemType, WeightType> &net, int *indegree)
{
    // 操作结果：统计网net各顶点的入度
    for (int v = 0; v < net.GetVexNum(); v++)
    {
        // 初始化入度为0
        indegree[v] = 0;
    }

    for (int v1 = 0; v1 < net.GetVexNum(); v1++)
    {
        // 遍历网的顶点，统计各点的入度
        for (int v2 = net.FirstAdjVex(v1); v2 != -1; v2 = net.NextAdjVex(v1, v2))
        {
            // v2为v1的一个邻接点
            indegree[v2]++;
        }
    }
}

template <class ElemType, class WeightType>
int CriticalPath(const AdjMatrixDirNetwork<ElemType, WeightType> &net)
{
    // 初始条件：存在有向网net
    // 操作结果：如net无回路，则输出net的关键活动，并返回1，否则返回0
    int *indegree = new int[net.GetVexNum()]; // 顶点入度数组
    int *ve = new int[net.GetVexNum()];       // 事件最早发生时刻数组
    LinkQueue<WeightType> q;                  // 用于存储入度为0的顶点
    LinkStack<WeightType> s;                  // 用于实现逆拓扑排序的栈
    int ee, el, u, v, count = 0;
    for (v = 0; v < net.GetVexNum(); v++)
    {
        // 初始化事件最早发生时刻
        ve[v] = 0;
    }

    StatIndegree(net, indegree); // 统计顶点的入度

    for (v = 0; v < net.GetVexNum(); v++)
    {
        // 遍历顶点
        if (indegree[v] == 0)
        {
            // 建立入度为0的顶点队列
            q.InQueue(v);
        }
    }

    while (!q.Empty())
    {
        // 队列非空
        q.OutQueue(u); // 取出一个入度为0的顶点
        s.Push(u);     // 顶点u入栈，以便得逆拓扑排序序列
        count++;       // 对顶点计数
        for (v = net.FirstAdjVex(u); v != -1; v = net.NextAdjVex(u, v))
        {
            // v2为v1的一个邻接点，对v1的每个邻接点入度减1
            if (--indegree[v] == 0)
            {
                // v入度为0，将v入队
                q.InQueue(v);
            }
            if (ve[u] + net.GetWeight(u, v) > ve[v])
            {
                // 修改ve[v]
                ve[v] = ve[u] + net.GetWeight(u, v);
            }
        }
    }
    delete[] indegree; // 释放indegree所占用的存储空间
    if (count < net.GetVexNum())
    {
        delete[] ve; // 释放ve所占用的存储空间
        return 0;    // 网net有回路
    }
    int *vl = new int[net.GetVexNum()]; // 事件最迟发生时刻数组
    s.Top(u);                           // 取出栈顶，栈顶为顶点
    for (v = 0; v < net.GetVexNum(); v++)
    {
        // 初始化事件最迟发生时刻
        vl[v] = ve[u];
    }

    while (!s.Empty())
    {
        // s非空
        s.Pop(u);
        for (v = net.FirstAdjVex(u); v != -1; v = net.NextAdjVex(u, v))
        {
            // v为u的一个邻接点
            if (vl[v] - net.GetWeight(u, v) < vl[u])
            {
                // 修改vl[u]
                vl[u] = vl[v] - net.GetWeight(u, v);
            }
        }
    }
    cout << "Critical Path:" << endl;
    for (u = 0; u < net.GetVexNum(); u++)
    {
        // 求ee，el和关键路径
        for (v = net.FirstAdjVex(u); v != -1; v = net.NextAdjVex(u, v))
        {
            // v为u的邻接点
            ee = ve[u];
            el = vl[v] - net.GetWeight(u, v);
            if (ee == el)
            {
                // <u, v>为关键活动
                cout << "<" << u << "," << v << "> ";
            }
        }
    }
    cout << endl;
    delete[] ve; // 释放ve所占用的存储空间
    delete[] vl; // 释放vl所占用的存储空间
    return 1;    // 操作成功
}

template <class ElemType, class WeightType>
void ShortestPathDIJ(AdjMatrixDirNetwork<ElemType, WeightType> &net, int v0, int *path, WeightType *dist)
{
    // 操作结果：用Dijkstra算法求有向网net从顶点v0出发到其余顶点v的最短路径path和路径长度
    // dist[v]，path[v]存储在最短路径上至此顶点的前一顶点的顶点号
    for (int v = 0; v < net.GetVexNum(); v++)
    {
        // 初始化path和dist及顶点标志
        if (v == v0)
        {
            dist[v] = 0;
            path[v] = v0;
        }
        else if (net.GetWeight(v0, v) < net.GetInfinity())
        {
            // 边存在
            dist[v] = net.GetWeight(v0, v);
            path[v] = v0;
        }
        else
        {
            // 边不存在
            dist[v] = net.GetInfinity();
            path[v] = -1;
            net.SetTag(v, UNVISITED);
        }
    }
    net.SetTag(v0, VISITED); // U = {v0}

    for (int u = 1; u < net.GetVexNum(); u++)
    {
        // 除v0外的其余net.GetVexNum()-1个顶点
        WeightType minVal = net.GetInfinity();
        int v1 = v0;
        for (int w = 0; w < net.GetVexNum(); w++)
        {
            // dist[v] = min{dist[w] | w∈V-U}
            int tag;
            net.GetTag(w, tag);
            if (tag == UNVISITED && dist[w] < minVal)
            {
                v1 = w;
                minVal = dist[w];
            }
        }
        net.SetTag(v1, VISITED); // 将v1并入U

        for (int v2 = net.FirstAdjVex(v1); v2 != -1; v2 = net.NextAdjVex(v1, v2))
        {
            // 更新当前最短路径及距离
            int tag;
            net.GetTag(v2, tag);
            if (tag == UNVISITED && minVal + net.GetWeight(v1, v2) < dist[v2])
            {
                // 如v2∈V-U且minVal+net.GetWeight(v1, v2)<dist[v2]，则修改dist[v2]及path[v2]
                dist[v2] = minVal + net.GetWeight(v1, v2);
                path[v2] = v1;
            }
        }
    }
}

template <class ElemType, class WeightType>
void ShortestPathFloyd(const AdjListDirNetwork<ElemType, WeightType> &net, int **path, WeightType **dist)
{
    // 操作结果：用Floyd算法求有向网net中各对顶点u和v之间的最短路径path[u][v]和路径长度
    // dist[u][v]，path[u][v]存储从u到v对的最短路径上至此顶点的前一顶点的顶点号，dist[u][v]
    // 存储从u到v的最短路径长度
    for (int u = 0; u < net.GetVexNum(); u++)
    {
        for (int v = 0; v < net.GetVexNum(); v++)
        {
            // 初始化path和dist
            if (v == u)
            {
                dist[u][v] = 0; // 自己到自己的距离为0
                path[u][v] = u;
            }
            else if (net.GetWeight(u, v) < net.GetInfinity())
            {
                dist[u][v] = net.GetWeight(u, v);
                path[u][v] = u;
            }
            else
            {
                dist[u][v] = net.GetInfinity();
                path[u][v] = -1;
            }
        }
    }

    for (int k = 0; k < net.GetVexNum(); k++)
    {
        for (int i = 0; i < net.GetVexNum(); i++)
        {
            for (int j = 0; j < net.GetVexNum(); j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    // 从i到k再到j的路径长度更短
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
}

#endif // ALGORITHM_H
