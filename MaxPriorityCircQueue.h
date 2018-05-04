#ifndef MAX_PRIORITY_CIRC_QUEUE_H
#define MAX_PRIORITY_CIRC_QUEUE_H

#include "CircQueue.h"

using namespace std;

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

#endif // MAX_PRIORITY_CIRC_QUEUE_H