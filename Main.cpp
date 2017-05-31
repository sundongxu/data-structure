/*
    debug之前一定要按shift+cmd+B，才能在断点处停下...
    这一步会生成a.out.dSYM文件帮助debug
*/

#include <iostream>
// #include <assert.h>
#include "SqList.h"
#include "SimpleLinkList.h"
#include "LinkList.h"
#include "LinkStack.h"
#include "LinkQueue.h"
#include "CircularQueue.h"
#include "BinTree.h"
#include "String.h"
#include "AdjMatrixDirGraph.h"
#include "AdjMatrixUndirGraph.h"
#include "AdjMatrixDirNetwork.h"
#include "AdjMatrixUndirNetwork.h"
#include "AdjListDirGraph.h"
#include "AdjListUndirGraph.h"
#include "AdjListDirNetwork.h"
#include "AdjListUndirNetwork.h"
#include "HuffmanTree.h"
#include "Algorithm.h"

using namespace std;

// 输出函数
template <class ElemType>
void Print(ElemType e)
{
    cout << e << "\t";
}

// 主函数，包含多个测试用例
int main()
{
    // // For Debugging->launch.json + tasks.json
    // for (int i = 0; i < 5; i++)
    // {
    //     cout << i << endl;
    // }

    // // Test assert
    // assert(0);
    // cout << "Test assert!" << endl;

    // // Test SimpleLinkList
    // SimpleLinkList<int> simpleLinkList;
    // simpleLinkList.Insert(1, 11);
    // simpleLinkList.Insert(2, 22);
    // simpleLinkList.Insert(3, 33);
    // cout << "当前简单线性表元素为:" << endl;
    // simpleLinkList.Traverse(Print);
    // cout << endl << "请输入想删除的元素位置:" << endl;
    // int posToDelete, tmp;
    // cin >> posToDelete;
    // simpleLinkList.Delete(posToDelete, tmp);
    // cout << "删除元素后，简单线性表元素为:" << endl;
    // simpleLinkList.Traverse(Print);
    // cout << endl << "请输入想插入的元素位置和元素值:" << endl;
    // int posToInsert, tmp1;
    // cin >> posToInsert >> tmp1;
    // simpleLinkList.Insert(posToInsert, tmp1);
    // cout << "插入元素后，简单线性表元素为:" << endl;
    // simpleLinkList.Traverse(Print);
    // cout << endl << "由原简单线性表复制构造得到的新简单线性表元素为:" << endl;
    // SimpleLinkList<int> copyLinkList(simpleLinkList);  // 复制构造
    // copyLinkList.Traverse(Print);
    // SimpleLinkList<int> linkList1;
    // linkList1.Insert(1,111);
    // linkList1.Insert(2,222);
    // linkList1.Insert(3,333);
    // cout<<endl<<"新简单线性表元素为:"<<endl;
    // linkList1.Traverse(Print);
    // linkList1 = simpleLinkList;  // 赋值运算
    // cout<<endl<<"赋值操作后该新简单线性表元素为:"<<endl;
    // linkList1.Traverse(Print);
    // cout << endl;

    // // Test LinkList
    // LinkList<int> linkList;
    // linkList.Insert(1, 11);
    // linkList.Insert(2, 22);
    // linkList.Insert(3, 33);
    // cout << "当前线性表元素为:" << endl;
    // linkList.Traverse(Print);
    // cout << endl
    //      << "请输入想删除的元素位置:" << endl;
    // int posToDelete, tmp;
    // cin >> posToDelete;
    // linkList.Delete(posToDelete, tmp);
    // cout << "删除元素后，线性表元素为:" << endl;
    // linkList.Traverse(Print);
    // cout << endl
    //      << "请输入想插入的元素位置和元素值:" << endl;
    // int posToInsert, tmp1;
    // cin >> posToInsert >> tmp1;
    // linkList.Insert(posToInsert, tmp1);
    // cout << "插入元素后，线性表元素为:" << endl;
    // linkList.Traverse(Print);
    // cout << endl
    //      << "由原线性表复制构造得到的新线性表元素为:" << endl;
    // LinkList<int> copyLinkList(linkList); // 复制构造
    // copyLinkList.Traverse(Print);
    // LinkList<int> linkList1;
    // linkList1.Insert(1, 111);
    // linkList1.Insert(2, 222);
    // linkList1.Insert(3, 333);
    // cout << endl
    //      << "新线性表元素为:" << endl;
    // linkList1.Traverse(Print);
    // linkList1 = linkList; // 赋值运算
    // cout << endl
    //      << "赋值操作后该新线性表元素为:" << endl;
    // linkList1.Traverse(Print);
    // cout << endl;

    // // Test LinkStack
    // LinkStack<int> stack;
    // stack.Push(1);
    // stack.Push(2);
    // stack.Push(3);
    // stack.Push(4);
    // stack.Push(5);
    // cout<<"当前栈元素为:"<<endl;
    // stack.Traverse(Print);
    // cout<<endl;
    // int c = 0;
    // stack.Pop(c);
    // cout<<"元素出栈后:"<<endl;
    // stack.Traverse(Print);
    // cout<<endl;
    // stack.Pop(c);
    // cout<<"元素再次出栈后:"<<endl;
    // stack.Traverse(Print);
    // cout<<endl;

    // // Test LinkQueue
    // LinkQueue<int> queue;
    // queue.InQueue(1);
    // queue.InQueue(2);
    // queue.InQueue(3);
    // queue.InQueue(4);
    // queue.InQueue(5);
    // cout << "当前队列元素为:" << endl;
    // queue.Traverse(Print);
    // cout << endl;
    // int c = 0;
    // queue.OutQueue(c);
    // cout << "元素出队后:" << endl;
    // queue.Traverse(Print);
    // cout << endl;
    // queue.OutQueue(c);
    // cout << "元素再次出队后:" << endl;
    // queue.Traverse(Print);
    // cout << endl;

    // Test CircularQueue
    CircularQueue<int> queue(5);
    queue.InQueue(1);
    queue.InQueue(2);
    queue.InQueue(3);
    queue.InQueue(4);
    queue.InQueue(5);
    cout << "当前队列元素为:" << endl;
    queue.Traverse(Print);
    cout << endl;
    cout << "队列长度为:" << queue.Length() << endl;
    int c = 0;
    queue.OutQueue(c);
    cout << "元素出队后:" << endl;
    queue.Traverse(Print);
    cout << endl;
    queue.OutQueue(c);
    cout << "元素再次出队后:" << endl;
    queue.Traverse(Print);
    cout << endl;

    // // Test Alg.h/Match
    // // char *s = "{a*[c+d*(e+f)]";  // 不推荐
    // char s[8] = "{[]a}ss"; // C++推荐字符串表示方法：字符数组，用字符串赋初值时，数组大小要比字符串大1
    // char ss[16] = "{a*[b+c*(e-f])}";
    // char sss[12] = "[(a+b)*c]+d";
    // if(Match(s))
    // {
    //     cout<<"s匹配成功!"<<endl;
    // }
    // else
    // {
    //     cout<<"s匹配失败!"<<endl;
    // }
    // if(Match(ss))
    // {
    //     cout<<"ss匹配成功!"<<endl;
    // }
    // else
    // {
    //     cout<<"ss匹配失败!"<<endl;
    // }if(Match(sss))
    // {
    //     cout<<"sss匹配成功!"<<endl;
    // }
    // else
    // {
    //     cout<<"sss匹配失败!"<<endl;
    // }

    // // Test BinTree
    // BinTree<char> tree('A'); // 构造根结点数据域为A的二叉树
    // tree.InsertLeftChild(tree.GetRoot(), 'B');
    // tree.InsertRightChild(tree.GetRoot(), 'C');
    // tree.InsertLeftChild(tree.GetRoot()->leftChild, 'D');
    // tree.InsertLeftChild(tree.GetRoot()->rightChild, 'E');
    // tree.InsertRightChild(tree.GetRoot()->rightChild, 'F');
    // tree.InsertRightChild(tree.GetRoot()->leftChild->leftChild, 'G');
    // cout << "结点B的父结点为:";
    // cout << tree.Parent(tree.LeftChild(tree.GetRoot()))->data << endl;
    // cout << "二叉树的高度为:";
    // cout << tree.Height() << endl;
    // cout << "二叉树的结点数为:";
    // cout << tree.NodeCount() << endl;
    // cout << "二叉树递归前序遍历序列为:" << endl;
    // tree.PreOrder(Print);
    // cout << endl
    //      << "二叉树递归中序遍历序列为:" << endl;
    // tree.InOrder(Print);
    // cout << endl
    //      << "二叉树递归后序遍历序列为:" << endl;
    // tree.PostOrder(Print);
    // cout << endl
    //      << "二叉树层次遍历序列为:" << endl;
    // tree.LevelOrder(Print);

    // cout << endl
    //      << "二叉树非递归前序遍历序列为:" << endl;
    // NonRecurPreOrder(tree, Print);
    // cout << endl
    //      << "二叉树非递归中序遍历序列为:" << endl;
    // NonRecurInOrder(tree, Print);
    // cout << endl
    //      << "二叉树非递归后序遍历序列为:" << endl;
    // NonRecurPostOrder(tree, Print);
    // cout << endl;

    // char *a = "aaa";
    // cout<<"a的长度为"<<strlen(a)<<endl;
    // cout<<"a的大小为"<<sizeof(a)<<endl;
    // char b[3] = "bb";
    // cout<<"b的长度为"<<strlen(b)<<endl;
    // cout<<"b的大小为"<<sizeof(b)<<endl;

    // // Test String
    // String T("acabaabaabcacx");
    // String P("cac");
    // cout << SubString(T, 3, 3).CStr() << endl;
    // cout << "KMP字符串匹配算法结果:" << endl;
    // int result;
    // if ((result = KMPIndex(T, P, 0)) > 0)
    // {
    //     cout << "匹配成功！此时目标串T中第一次出现模式串P的位置下标为" << result << endl;
    // }

    // // Test 2-Dimension Pointer
    // int arr1[3];
    // int arr2[3];
    // int arr3[3];
    // int *ptr;  // ptr是指向整形变量的指针

    // // ptr1是一个指向 int [3] 的指针，即ptr的类型和&arr1的类型是一样的，注意：arr1指向的内存区域定长
    // int ptr1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};  // roy:数组的数组，数组元素为包含3个int变量的数组，数组名ptr1指向第一个数组元素，即指向一个int[3]={1，2，3}

    // // 指向一维数组的指针，数组元素为一维数组（行）的一维数组，数组元素为含三个整形变量的数组

    // // ptr2是一个指向 int * 的指针，即ptr2的类型和&ptr是一样的，注意：ptr指向的内存区域不定长
    // int *ptr2[3] = {arr1, arr2, arr3}; // roy:指针数组，数组元素为指向int变量的指针，数组名ptr2指向第一个数组元素，即指向一个指向int变量的指针arr1，即指向指针的指针
    //                                    // 定义不带括号->指针数组

    // // ptr3是一个指向 int [3] 的指针，即ptr3的类型和&arr1的类型是一样的，注意：arr1指向的内存区域定长
    // int(*ptr3)[3] = &arr1;  // roy:数组的指针，指向一个int[3]=arr1表示的数组
    //                         // 定义带括号，指向一维数组的指针

    // int **ptr4;  // roy:指针的指针，指向一个指向整形变量的指针
    //              //ptr4=&arr1; //error 无法从“int (*)[3]”转换为“int **

    // ptr3 = ptr1; // 没错，他们的类型相同
    //              // ptr3=ptr2;//error 无法从“int *[3]”转换为“int (*)[3]
    //              // ptr4是一个指向 int * 的指针，即ptr4的类型和&ptr是一样的，注意：ptr指向的内存区域不定长

    // ptr4 = ptr2; // 没错，他们的类型相同
    //              //ptr4=ptr3; // error 无法从“int (*)[3]”转换为“int **

    // Test AdjMatrixDirGraph
    // char elems[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};  // 作为参数不行哦？？？
    // char *elems = new char[9];
    // for (int i = 0; i < 9; ++i)
    // {
    //     elems[i] = (char)('A' + i);
    // }
    // AdjMatrixUndirGraph<char> graph(elems, 9);
    // graph.InsertEdge(0, 1);
    // graph.InsertEdge(0, 3);
    // graph.InsertEdge(0, 4);
    // graph.InsertEdge(1, 2);
    // graph.InsertEdge(1, 4);
    // graph.InsertEdge(2, 5);
    // graph.InsertEdge(4, 6);
    // graph.InsertEdge(6, 3);
    // graph.InsertEdge(6, 7);
    // graph.InsertEdge(7, 8);
    // cout << "广度优先搜索(遍历):" << endl;
    // BFSTraverse(graph, Print); // 广度搜索
    // cout << endl
    //      << "深度优先搜索(遍历):" << endl;
    // DFSTraverse(graph, Print); // 深度搜索

    // // Test Prim
    // // char elems[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
    // char *elems = new char[6];
    // for (int i = 0; i < 6; ++i)
    // {
    //     elems[i] = (char)('A' + i);
    // }
    // AdjMatrixUndirNetwork<char, int> net(elems, 6, 100);
    // net.InsertEdge(0, 1, 8);
    // net.InsertEdge(0, 2, 1);
    // net.InsertEdge(0, 3, 6);
    // net.InsertEdge(1, 2, 6);
    // net.InsertEdge(1, 4, 3);
    // net.InsertEdge(2, 3, 6);
    // net.InsertEdge(2, 4, 8);
    // net.InsertEdge(2, 5, 5);
    // net.InsertEdge(3, 5, 2);
    // net.InsertEdge(4, 5, 8);
    // cout<<"Prim算法得到最小代价生成树如下:"<<endl;
    // MiniSpanTreePrim<char, int>(net, 0);

    // cout<<endl;

    // // Test AdjListDirGraph
    // AdjListDirGraph<char> graph(elems, 6);
    // graph.InsertEdge(0, 1);
    // graph.InsertEdge(1, 2);
    // graph.InsertEdge(4, 5);

    // // Test AdjListUndirGraph
    // AdjListUndirGraph<char> graph(elems, 6);
    // graph.InsertEdge(0, 1);
    // graph.InsertEdge(1, 2);
    // graph.InsertEdge(4, 5);

    // // Test AdjListDirNetwork
    // AdjListDirNetwork<char, int> net(elems, 6, 100);
    // net.InsertEdge(0, 1, 8);
    // net.InsertEdge(1, 2, 10);
    // net.InsertEdge(4, 5, 11);

    // // Test AdjListUndirNetwork
    // AdjListUndirNetwork<char, int> net(elems, 6, 100);
    // net.InsertEdge(0, 1, 8);
    // net.InsertEdge(1, 2, 10);
    // net.InsertEdge(4, 5, 11);

    // // Test Kruskal
    // AdjListUndirNetwork<char, int> net(elems, 6, 100);
    // net.InsertEdge(0, 1, 8);
    // net.InsertEdge(0, 2, 1);
    // net.InsertEdge(0, 3, 6);
    // net.InsertEdge(1, 2, 6);
    // net.InsertEdge(1, 4, 3);
    // net.InsertEdge(2, 3, 6);
    // net.InsertEdge(2, 4, 8);
    // net.InsertEdge(2, 5, 5);
    // net.InsertEdge(3, 5, 2);
    // net.InsertEdge(4, 5, 8);
    // cout << "Kruskal算法得到最小代价生成树如下:" << endl;
    // MiniSpanTreeKruskal<char, int>(net);

    // cout<<endl;

    // // Test TopSort
    // char *elems = new char[5];
    // for (int i = 0; i < 5; ++i)
    // {
    //     elems[i] = (char)('A' + i);
    // }
    // AdjMatrixDirGraph<char> graph(elems, 5);
    // graph.InsertEdge(0, 1);
    // graph.InsertEdge(0, 4);
    // graph.InsertEdge(1, 2);
    // graph.InsertEdge(1, 4);
    // graph.InsertEdge(3, 2);
    // graph.InsertEdge(4, 2);
    // graph.InsertEdge(4, 3);
    // TopSort(graph);

    // // Test CriticalPath
    // char elems[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
    // char *elems = new char[9];
    // for (int i = 0; i < 9; ++i)
    // {
    //     elems[i] = (char)('A' + i);
    // }
    // AdjMatrixDirNetwork<char, int> net(elems, 9, 100);
    // net.InsertEdge(0, 1, 6);
    // net.InsertEdge(0, 2, 4);
    // net.InsertEdge(0, 3, 5);
    // net.InsertEdge(1, 4, 1);
    // net.InsertEdge(2, 4, 1);
    // net.InsertEdge(3, 5, 2);
    // net.InsertEdge(4, 6, 9);
    // net.InsertEdge(4, 7, 7);
    // net.InsertEdge(5, 7, 4);
    // net.InsertEdge(6, 8, 2);
    // net.InsertEdge(7, 8, 3);
    // CriticalPath(net);

    // // Test HuffmanTree
    // char *ch = new char[4];
    // int i;
    // for (i = 0; i < 4; i++)
    // {
    //     ch[i] = (char)('A' + i);
    // }
    // int w[4] = {5, 4, 1, 2};
    // HuffmanTree<char, int> hTree(ch, w, 4);
    // // Encode
    // cout << "字符编码结果:" << endl;
    // for (i = 0; i < 4; i++)
    // {
    //     String EnCode(hTree.EnCode(ch[i]));
    //     cout << ch[i] << ": " << EnCode.CStr() << endl;
    // }
    // // Decode
    // String strCode("0111001011011001101110010100");
    // LinkList<char> charList = hTree.DeCode(strCode);
    // cout << "密码串译码结果" << endl;
    // for (i = 1; i <= charList.Length(); i++)
    // {
    //     char c;
    //     charList.GetElem(i, c);
    //     cout << c;
    // }
    // cout << endl;

    // // Test Disjkstra
    // char *elems = new char[5];
    // for (int i = 0; i < 5; ++i)
    // {
    //     elems[i] = (char)('A' + i);
    // }
    // AdjMatrixDirNetwork<char, int> net(elems, 5, 100000);
    // net.InsertEdge(0, 1, 100);
    // net.InsertEdge(0, 2, 30);
    // net.InsertEdge(0, 4, 10);
    // net.InsertEdge(2, 1, 60);
    // net.InsertEdge(2, 3, 60);
    // net.InsertEdge(3, 1, 10);
    // net.InsertEdge(4, 3, 50);
    // int *path = new int[5];
    // int *dist = new int[5];
    // ShortestPathDIJ(net, 0, path, dist);
    // cout << "Dijkstra算法结果:" << endl;
    // for (int i = 0; i < 5; i++)
    // {
    //     // 输出从v0到各点的最短路径长度
    //     cout << "v0到v" << i << "的最短路径长度为" << dist[i] << endl;
    // }

    // // Test Floyd
    // char *elems = new char[3];
    // for (int i = 0; i < 3; i++)
    // {
    //     elems[i] = (char)('A' + i);
    // }
    // AdjListDirNetwork<char, int> net(elems, 3, 100000);
    // net.InsertEdge(0, 1, 4);
    // net.InsertEdge(0, 2, 11);
    // net.InsertEdge(1, 0, 6);
    // net.InsertEdge(1, 2, 2);
    // net.InsertEdge(2, 0, 1);
    // int **path = new int *[3];
    // int **dist = new int *[3];
    // for (int j = 0; j < 3; j++)
    // {
    //     path[j] = new int[3];
    //     dist[j] = new int[3];
    // }
    // ShortestPathFloyd(net, path, dist);
    // cout << "Floyd算法结果:" << endl;
    // for (int u = 0; u < 3; u++)
    // {
    //     for (int v = 0; v < 3; v++)
    //     {
    //         cout << u << "到" << v << "的最短路径长度为" << dist[u][v] << endl;
    //     }
    // }

    return 0;
}
