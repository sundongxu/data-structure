#ifndef MIN_PRIORITY_LINK_QUEUE_H
#define MIN_PRIORITY_LINK_QUEUE_H

#include "LinkQueue.h"

// 最小优先链队列类
template <class ElemType>
class MinPriorityLinkQueue : public LinkQueue<ElemType>
{
  public:
    // 重载入队操作声明：
    int InQueue(const ElemType &e); // 重载入队操作
};

#endif // MIN_PRIORITY_LINK_QUEUE_H