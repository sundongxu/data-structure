#ifndef MAX_PRIORITY_CIRC_QUEUE_H
#define MAX_PRIORITY_CIRC_QUEUE_H

#include "CircQueue.h"

// 最大优先循环队列类
template <class ElemType>
class MaxPriorityCircQueue : public CircQueue<ElemType>
{
  public:
    // 声明并实现子类的构造函数，并在初始化列表中调用基类的构造器
    MaxPriorityCircQueue(int size = DEFAULT_SIZE) : CircQueue<ElemType>(size) {}
    // 重载入队操作声明：
    int InQueue(const ElemType &e); // 重载入队操作
};

// 最大优先循环队列类的实现部分
template <class ElemType>
int MaxPriorityCircQueue<ElemType>::InQueue(const ElemType &e)
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
        while (curPosition != CircQueue<ElemType>::rear && CircQueue<ElemType>::elem[curPosition] >= e)
        {
            // 将所有不小于e的元素向前移动一个位置
            CircQueue<ElemType>::elem[(curPosition - 1 + CircQueue<ElemType>::maxSize) %
                                      CircQueue<ElemType>::maxSize] = CircQueue<ElemType>::elem[curPosition];
            curPosition = (curPosition + 1) % CircQueue<ElemType>::maxSize; // curPosition指向下一个元素
        }
        CircQueue<ElemType>::elem[(curPosition - 1 + CircQueue<ElemType>::maxSize) %
                                  CircQueue<ElemType>::maxSize] = e; // curPosition的前一位置为e的插入位置
        CircQueue<ElemType>::front = (CircQueue<ElemType>::front - 1 + CircQueue<ElemType>::maxSize) %
                                     CircQueue<ElemType>::maxSize; // front移向前一个位置
        return SUCCESS;
    }
}

#endif // MAX_PRIORITY_CIRC_QUEUE_H