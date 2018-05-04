#include "MaxPriorityLinkQueue.h"

// 最大优先链队列类的实现部分，其余成员继承自LinkQueue类
template <class ElemType>
int MaxPriorityLinkQueue<ElemType>::InQueue(const ElemType &e)
{
    // 操作结果：插入元素e为新的队尾，返回SUCCESS
    Node<ElemType> *curPtr = LinkQueue<ElemType>::front->next; // 指向当前结点
    Node<ElemType> *curPrePtr = LinkQueue<ElemType>::front;    // 指向当前结点的前驱结点

    while (curPtr != nullptr && curPtr->val >= e)
    {
        // curPtr与curPrePtr都指向下一元素
        curPrePtr = curPtr;
        curPtr = curPtr->next;
    }

    Node<ElemType> *tmpPtr = new Node<ElemType>(e, curPtr); // 生成新结点
    curPrePtr->next = tmpPtr;                               // 将tmpPtr插入在curPrePtr与curPtr之间

    if (curPrePtr == LinkQueue<ElemType>::rear)
    {
        // 新结点插在rear的后面
        LinkQueue<ElemType>::rear = tmpPtr; // rear指向新队尾
    }
    return SUCCESS;
}

int main()
{
    // 最大优先链队列成员函数测试

    // 测试InQueue、GetHead、OutQueue
    int e;
    MaxPriorityLinkQueue<int> q;
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
    MaxPriorityLinkQueue<int> q1(q);
    q1.Traverse(Print);
    cout << endl;

    // 测试赋值运算符
    MaxPriorityLinkQueue<int> q2;
    q2.InQueue(6);
    q2.InQueue(7);
    q2.Traverse(Print);
    cout << endl;
    q2 = q;
    q2.Traverse(Print);

    return 0;
}