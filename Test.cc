#include "MaxPriorityLinkQueue.h"

int main()
{
    // 最大优先链队列成员函数测试

    // 测试InQueue、GetHead、OutQueue
    int e;
    // q与q()的区别，后者适用于未声明无参数的构造函数的情况，即用合成的构造函数。后者使用显式声明过的无参数的构造函数
    MaxPriorityLinkQueue<int> q;
    // q.InQueue(1);
    // q.InQueue(2);
    // q.InQueue(3);
    // q.InQueue(4);
    // q.InQueue(5);
    // q.GetHead(e);
    // cout << "队首元素:" << e << endl;
    // q.Traverse(Print);
    // cout << endl;
    // q.OutQueue(e);
    // q.OutQueue(e);
    // q.Traverse(Print);
    // cout << endl;

    // // 测试拷贝构造
    // MaxPriorityLinkQueue<int> q1(q);
    // q1.Traverse(Print);
    // cout << endl;

    // // 测试赋值运算符
    // MaxPriorityLinkQueue<int> q2;
    // q2.InQueue(6);
    // q2.InQueue(7);
    // q2.Traverse(Print);
    // cout << endl;
    // q2 = q;
    // q2.Traverse(Print);

    return 0;
}