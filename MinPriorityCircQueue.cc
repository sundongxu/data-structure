#include "MinPriorityCircQueue.h"

// 最小优先循环队列类的实现部分
template <class ElemType>
int MinPriorityCircQueue<ElemType>::InQueue(const ElemType &e)
{
    // 操作结果：插入元素e为新的队尾，返回SUCCESS，队列已满则返回OVER_FLOW
    if (CircQueue<ElemType>::Full())
    {
        // 队列已满
        return OVER_FLOW;
    }
    else
    {
        // 队列未满，入队成功
        int curPosition = CircQueue<ElemType>::front;
        while (curPosition != CircQueue<ElemType>::rear && CircQueue<ElemType>::elems[curPosition] <= e)
        {
            // 将所有不大于e的元素向前移动一个位置
            CircQueue<ElemType>::elems[(curPosition - 1 + CircQueue<ElemType>::maxSize) %
                                       CircQueue<ElemType>::maxSize] = CircQueue<ElemType>::elems[curPosition];
            curPosition = (curPosition + 1) % CircQueue<ElemType>::maxSize; // curPosition指向下一个元素
        }
        CircQueue<ElemType>::elems[(curPosition - 1 + CircQueue<ElemType>::maxSize) %
                                   CircQueue<ElemType>::maxSize] = e; // curPosition的前一位置为e的插入位置
        CircQueue<ElemType>::front = (CircQueue<ElemType>::front - 1 + CircQueue<ElemType>::maxSize) %
                                     CircQueue<ElemType>::maxSize; // front移向前一个位置
        return SUCCESS;
    }
}

int main()
{
    // 最大优先链队列成员函数测试

    // 测试InQueue、GetHead、OutQueue
    int e;
    MinPriorityCircQueue<int> q;
    q.InQueue(1);
    q.InQueue(2);
    q.InQueue(3);
    q.InQueue(4);
    q.InQueue(5);
    q.GetHead(e);
    cout << "队首元素:" << e << endl;
    q.Traverse(Print);
    cout << endl;
    q.OutQueue(e);
    q.OutQueue(e);
    q.Traverse(Print);
    cout << endl;

    // 测试拷贝构造
    MinPriorityCircQueue<int> q1(q);
    q1.Traverse(Print);
    cout << endl;

    // 测试赋值运算符
    MinPriorityCircQueue<int> q2;
    q2.InQueue(6);
    q2.InQueue(7);
    q2.Traverse(Print);
    cout << endl;
    q2 = q;
    q2.Traverse(Print);

    return 0;
}