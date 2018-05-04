#ifndef MAX_PRIORITY_LINK_QUEUE_H
#define MAX_PRIORITY_LINK_QUEUE_H

#include "LinkQueue.h"

// 最大优先链队列类
template <class ElemType>
class MaxPriorityLinkQueue : public LinkQueue<ElemType>
{
public:
  // 重载入队操作声明：
  int InQueue(const ElemType &e); // 重载入队操作
};

#endif // MAX_PRIORITY_LINK_QUEUE_H