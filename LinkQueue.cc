#include "LinkQueue.h"

// 链式队列类的实现部分
template <class ElemType>
void LinkQueue<ElemType>::Init()
{
    // 操作结果：初始化队列
    rear = front = new Node<ElemType>; // 生成头结点
}

template <class ElemType>
LinkQueue<ElemType>::LinkQueue()
{
    // 操作结果：构造一个空队列（仅包含头结点）
    Init();
}

template <class ElemType>
LinkQueue<ElemType>::~LinkQueue()
{
    // 操作结果：销毁队列
    Clear();
}

template <class ElemType>
int LinkQueue<ElemType>::Length() const
{
    // 操作结果：返回队列长度，即有效数据结点个数（怎么不用上尾结点？？？tmpPtr==nullptr实际就是tmpPtr==rear->next）
    int count = 0;
    for (Node<ElemType> *tmpPtr = front->next; tmpPtr != nullptr; tmpPtr = tmpPtr->next)
    {
        // 用tmpPtr依次指向每个结点,front->next是指队列的有效结点数要从队列第一个含有效数据域的结点开始算起
        count++;
    }
    return count;
}

template <class ElemType>
bool LinkQueue<ElemType>::Empty() const
{
    // 操作结果：判断队列是否为空
    return front == rear; // 队头队尾指针相等，嗯，好好思考
}

template <class ElemType>
void LinkQueue<ElemType>::Clear()
{
    // 操作结果：清空队列，只留下front和rear，即删除全部有效数据结点
    ElemType tmpElem; // 临时元素值
    while (Length() > 0)
    {
        OutQueue(tmpElem);
    }
}

template <class ElemType>
void LinkQueue<ElemType>::Traverse(void (*Visit)(ElemType &))
{
    // 操作结果：对队列的每个元素调用函数(*Visit)
    for (Node<ElemType> *tmpPtr = front->next; tmpPtr != nullptr; tmpPtr = tmpPtr->next)
    {
        // 将tmpPtr依次指向队列的各个元素
        (*Visit)(tmpPtr->val);
    }
}

template <class ElemType>
int LinkQueue<ElemType>::InQueue(const ElemType &e)
{
    // 操作结果：数据域为e的新结点入队
    Node<ElemType> *tmpPtr = new Node<ElemType>(e);
    // 新建结点成功
    rear->next = tmpPtr; // 新结点追加在队尾
    rear = tmpPtr;
    return SUCCESS;
}

template <class ElemType>
int LinkQueue<ElemType>::OutQueue(ElemType &e)
{
    // 操作结果：队末元素出队，并将其数据域赋值给e
    if (Empty())
    {
        // 队列为空
        return UNDER_FLOW;
    }
    else
    {
        // 队列非空，队头元素出队成功
        Node<ElemType> *tmpPtr = front->next;
        e = tmpPtr->val; // 保存第一个有效数据结点的数据域
        front->next = tmpPtr->next;
        if (rear == tmpPtr)
        {
            rear = front; // 出队元素为队末元素，即出队前队中只有一个数据结点，此时应该将队尾指针指向front，否则之后队末结点空间被释放了，rear会变成野指针
        }
        tmpPtr->next = nullptr;
        delete tmpPtr;
        return SUCCESS;
    }
}

template <class ElemType>
int LinkQueue<ElemType>::GetHead(ElemType &e) const
{
    // 操作结果：将队头元素的数据域赋值给e
    if (Empty())
    {
        // 队列为空，无队头元素
        return UNDER_FLOW;
    }
    else
    {
        // 队列非空，取队头结点的数据域赋值给e
        Node<ElemType> *tmpPtr = front->next;
        e = tmpPtr->val;
        return SUCCESS;
    }
}

template <class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType> &copy)
{
    // 操作结果：由队列copy构造新队列——————复制构造函数
    Init();
    for (Node<ElemType> *tmpPtr = copy.front->next; tmpPtr != nullptr; tmpPtr = tmpPtr->next)
    {
        // 对copy队列每个元素对当前队列作入队操作
        InQueue(tmpPtr->val);
    }
}

template <class ElemType>
LinkQueue<ElemType> &LinkQueue<ElemType>::operator=(const LinkQueue<ElemType> &copy)
{
    // 操作结果：将队列copy赋值给当前队列——————赋值运算符重载
    if (&copy != this)
    {
        Clear();
        for (Node<ElemType> *tmpPtr = copy.front->next; tmpPtr != nullptr; tmpPtr = tmpPtr->next)
        {
            // 对copy队列每个元素对当前队列作入队操作
            InQueue(tmpPtr->val);
        }
    }
    return *this;
}

int main()
{
    // 链式队列成员函数测试

    // 测试InQueue、GetHead、OutQueue
    int e;
    LinkQueue<int> q;
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
    LinkQueue<int> q1(q);
    q1.Traverse(Print);
    cout << endl;

    // 测试赋值运算符
    LinkQueue<int> q2;
    q2.InQueue(6);
    q2.InQueue(7);
    q2.Traverse(Print);
    cout << endl;
    q2 = q;
    q2.Traverse(Print);

    return 0;
}