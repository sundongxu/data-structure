#ifndef CIRC_QUEUE_H
#define CIRC_QUEUE_H

#include "Constant.h"
#include "Utils.h"

// 循环(顺序)队列类
template <class ElemType>
class CircQueue
{
protected:
  int front, rear; // 队头(指向第一个数据元素)、队尾(指向最后一个数据元素的下一个位置)
  int maxSize;     // 队列最大元素个数
  ElemType *elems; // 元素存储空间

  // 辅助函数：
  bool Full() const; // 判断栈是否已满
  void Init();       // 初始化队列

public:
  // 抽象数据类型方法声明及重载编译系统默认方法声明：
  CircQueue(int size = DEFAULT_SIZE); // 构造函数
  virtual ~CircQueue();               // 析构函数
  int Length() const;                 // 求队列长度

  bool Empty() const;                                              // 判断队列是否为空
  void Clear();                                                    // 将队列清空
  void Traverse(void (*Visit)(ElemType &));                        // 遍历队列
  int OutQueue(ElemType &e);                                       // 出队操作
  int InQueue(const ElemType &e);                                  // 入队操作
  int GetHead(ElemType &e) const;                                  // 取队头操作
  CircQueue(const CircQueue<ElemType> &copy);                      // 拷贝构造函数
  CircQueue<ElemType> &operator=(const CircQueue<ElemType> &copy); // 赋值运算符重载
};

#endif // Circ_QUEUE_H