#include "CircQueue.h"

// 循环队列类的实现部分
template <class ElemType>
bool CircQueue<ElemType>::Full() const
{
    // 操作结果：如队列已满，则返回true，否则返回false
    return Length() == maxSize - 1; // 浪费一个元素空间，当front在rear的下一个位置时队列为满
}

template <class ElemType>
void CircQueue<ElemType>::Init()
{
    // 操作结果：初始化队列
    rear = front = 0;
}

template <class ElemType>
CircQueue<ElemType>::CircQueue(int size)
{
    // 操作结果：构造一个最大元素个数为size的空循环队列
    maxSize = size;                // 最大元素个数
    elems = new ElemType[maxSize]; // 分配存储空间
    Init();                        // 初始化队列
}

template <class ElemType>
CircQueue<ElemType>::~CircQueue()
{
    // 操作结果：销毁队列
    delete[] elems;
}

template <class ElemType>
int CircQueue<ElemType>::Length() const
{
    // 操作结果：返回队列长度
    return (rear - front + maxSize) % maxSize;
}

template <class ElemType>
bool CircQueue<ElemType>::Empty() const
{
    // 操作结果：如队列为空，则返回true，否则返回false
    return rear == front;
}

template <class ElemType>
void CircQueue<ElemType>::Clear()
{
    // 操作结果：清空队列
    rear = front = 0;
}

template <class ElemType>
void CircQueue<ElemType>::Traverse(void (*Visit)(ElemType &))
{
    // 操作结果：依次对队列的每个元素调用函数(*Visit)
    for (int curPosition = front; curPosition != rear; curPosition = (curPosition + 1) % maxSize)
    {
        // 对队列每个元素调用函数(*Visit)
        (*Visit)(elems[curPosition]);
    }
}

template <class ElemType>
int CircQueue<ElemType>::OutQueue(ElemType &e)
{
    // 操作结果：如果队列非空，那么删除队头元素，并用e返回其值，函数返回SUCCESS，否则函数返回UNDER_FLOW
    if (!Empty())
    {
        // 队列非空
        e = elems[front];              // 用e返回队头元素
        front = (front + 1) % maxSize; // 用front指向下一元素
        return SUCCESS;
    }
    else
    {
        // 队列为空
        return UNDER_FLOW;
    }
}

template <class ElemType>
int CircQueue<ElemType>::InQueue(const ElemType &e)
{
    // 操作结果：如果队列已满，返回OVER_FLOW，否则插入元素e为新的队尾，返回SUCCESS
    if (Full())
    {
        // 队列已满
        return OVER_FLOW;
    }
    else
    {
        // 队列未满
        elems[rear] = e;             // 插入e为新队尾
        rear = (rear + 1) % maxSize; // rear指向新队尾
        return SUCCESS;
    }
}

template <class ElemType>
int CircQueue<ElemType>::GetHead(ElemType &e) const
{
    // 操作结果：如果队列为空，那么用e返回队头元素，函数返回SUCCESS，否则函数返UNDER_FLOW
    if (!Empty())
    {
        // 队列非空
        e = elems[front]; // 用e返回队头元素
        return SUCCESS;
    }
    else
    {
        // 队列为空
        return UNDER_FLOW;
    }
}

template <class ElemType>
CircQueue<ElemType>::CircQueue(const CircQueue<ElemType> &copy)
{
    // 操作结果：由队列copy构造新队列——复制构造函数
    maxSize = copy.maxSize;        // 最大元素个数
    elems = new ElemType[maxSize]; // 分配存储空间
    front = copy.front;            // 复制队头位置
    rear = copy.rear;              // 复制队尾位置
    for (int curPosition = front; curPosition != rear; curPosition = (curPosition + 1) % maxSize)
    {
        // 复制循环队列元素
        elems[curPosition] = copy.elems[curPosition];
    }
}

template <class ElemType>
CircQueue<ElemType> &CircQueue<ElemType>::operator=(const CircQueue<ElemType> &copy)
{
    // 操作结果：将队列copy赋值给当前队列——赋值运算符重载
    if (&copy != this)
    {
        if (elems != nullptr)
            delete[] elems;
        front = copy.front; // 复制队头位置
        rear = copy.rear;   // 复制队尾位置
        elems = new ElemType[copy.maxSize];
        for (int curPosition = front; curPosition != rear; curPosition = (curPosition + 1) % maxSize)
        {
            // 复制循环队列元素
            elems[curPosition] = copy.elems[curPosition];
        }
    }
    return *this;
}

int main()
{
    // 循环队列成员函数测试

    // 测试InQueue、GetHead、OutQueue
    int e;
    CircQueue<int> q; // 默认长度为5
    // 但是会少用一个元素空间，约定队头在队尾指针的下一个位置时作为队满的标志
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
    CircQueue<int> q1(q);
    q1.Traverse(Print);
    cout << endl;

    // 测试赋值运算符
    CircQueue<int> q2;
    q2.InQueue(6);
    q2.InQueue(7);
    q2.Traverse(Print);
    cout << endl;
    q2 = q;
    q2.Traverse(Print);

    return 0;
}