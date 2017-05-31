#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#define DEFAULT_SIZE 1
#define SUCCESS 100
#define OVER_FLOW 200
#define UNDER_FLOW 300

template <class ElemType>
class CircularQueue
{
  protected:
    int front, rear; // 队头(指向第一个数据元素)、队尾(指向最后一个数据元素的下一个位置)
    int maxSize;     // 队列最大元素个数
    ElemType *elem;  // 元素存储空间

    // 辅助函数：
    bool Full() const; // 判断栈是否已满
    void Init();       // 初始化队列

  public:
    // 抽象数据类型方法声明及重载编译系统默认方法声明：
    CircularQueue(int size = DEFAULT_SIZE); // 构造函数
    virtual ~CircularQueue();               // 析构函数
    int Length() const;                     // 求队列长度

    bool Empty() const;                                                      // 判断队列是否为空
    void Clear();                                                            // 将队列清空
    void Traverse(void (*Visit)(ElemType &));                                // 遍历队列
    int OutQueue(ElemType &e);                                               // 出队操作
    int InQueue(const ElemType &e);                                          // 入队操作
    int GetHead(ElemType &e) const;                                          // 取队头操作
    CircularQueue(const CircularQueue<ElemType> &copy);                      // 拷贝构造函数
    CircularQueue<ElemType> &operator=(const CircularQueue<ElemType> &copy); // 赋值运算符重载
};

template <class ElemType>
bool CircularQueue<ElemType>::Full() const
{
    // 操作结果：如队列已满，则返回true，否则返回false
    return Length() == maxSize - 1; // 浪费一个元素空间，当front在rear的下一个位置时队列为满
}

template <class ElemType>
void CircularQueue<ElemType>::Init()
{
    // 操作结果：初始化队列
    rear = front = 0;
}

template <class ElemType>
CircularQueue<ElemType>::CircularQueue(int size)
{
    // 操作结果：构造一个最大元素个数为size的空循环队列
    maxSize = size;               // 最大元素个数
    elem = new ElemType[maxSize]; // 分配存储空间
    Init();                       // 初始化队列
}

template <class ElemType>
CircularQueue<ElemType>::~CircularQueue()
{
    // 操作结果：销毁队列
    delete[] elem;
}

template <class ElemType>
int CircularQueue<ElemType>::Length() const
{
    // 操作结果：返回队列长度
    return (rear - front + maxSize) % maxSize;
}

template <class ElemType>
bool CircularQueue<ElemType>::Empty() const
{
    // 操作结果：如队列为空，则返回true，否则返回false
    return rear == front;
}

template <class ElemType>
void CircularQueue<ElemType>::Clear()
{
    // 操作结果：清空队列
    rear = front = 0;
}

template <class ElemType>
void CircularQueue<ElemType>::Traverse(void (*Visit)(ElemType &))
{
    // 操作结果：依次对队列的每个元素调用函数(*Visit)
    for (int curPosition = front; curPosition != rear; curPosition = (curPosition + 1) % maxSize)
    {
        // 对队列每个元素调用函数(*Visit)
        (*Visit)(elem[curPosition]);
    }
}

template <class ElemType>
int CircularQueue<ElemType>::OutQueue(ElemType &e)
{
    // 操作结果：如果队列非空，那么删除队头元素，并用e返回其值，函数返回SUCCESS，否则函数返回UNDER_FLOW
    if (!Empty())
    {
        // 队列非空
        e = elem[front];               // 用e返回队头元素
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
int CircularQueue<ElemType>::InQueue(const ElemType &e)
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
        elem[rear] = e;              // 插入e为新队尾
        rear = (rear + 1) % maxSize; // rear指向新队尾
        return SUCCESS;
    }
}

template <class ElemType>
int CircularQueue<ElemType>::GetHead(ElemType &e) const
{
    // 操作结果：如果队列为空，那么用e返回队头元素，函数返回SUCCESS，否则函数返UNDER_FLOW
    if (!Empty())
    {
        // 队列非空
        e = elem[front]; // 用e返回队头元素
        return SUCCESS;
    }
    else
    {
        // 队列为空
        return UNDER_FLOW;
    }
}

template <class ElemType>
CircularQueue<ElemType>::CircularQueue(const CircularQueue<ElemType> &copy)
{
    // 操作结果：由队列copy构造新队列——复制构造函数
    front = copy.front; // 复制队头位置
    rear = copy.rear;   // 复制队尾位置
    for (int curPosition = front; curPosition != rear; curPosition = (curPosition + 1) % maxSize)
    {
        // 复制循环队列元素
        elem[curPosition] = copy.elem[curPosition];
    }
}

template <class ElemType>
CircularQueue<ElemType> &CircularQueue<ElemType>::operator=(const CircularQueue<ElemType> &copy)
{
    // 操作结果：将队列copy赋值给当前队列——赋值运算符重载
    if (&copy != this)
    {
        front = copy.front; // 复制队头位置
        rear = copy.rear;   // 复制队尾位置
        for (int curPosition = front; curPosition != rear; curPosition = (curPosition + 1) % maxSize)
        {
            // 复制循环队列元素
            elem[curPosition] = copy.elem[curPosition];
        }
    }
    return *this;
}

#endif // CIRCULAR_QUEUE_H