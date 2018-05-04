#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H

#include "Node.h"
#include "Constant.h"
#include "Utils.h"

// 链式队列类
template <class ElemType>
class LinkQueue
{
protected:
  // 链队列实现的数据成员：
  Node<ElemType> *front, *rear; // 队头队尾指针
  // 队头指针指向头结点（无数据域，指针域指向队列的第一个含有效数据域的结点），队尾指针则真的指向队列的最后一个含有效数据域的结点）,即有rear->next==nullptr

  // 辅助函数：
  void Init(); // 初始化队列

public:
  // 抽象数据类型方法声明及重载编译系统默认方法声明：
  LinkQueue();                                                     // 构造函数
  virtual ~LinkQueue();                                            // 无参数的析构函数
  int Length() const;                                              // 返回队列长度
  bool Empty() const;                                              // 判断队列是否为空
  void Clear();                                                    // 清空队列
  void Traverse(void (*Visit)(ElemType &));                        // 遍历队列
  int InQueue(const ElemType &e);                                  // 入队操作
  int OutQueue(ElemType &e);                                       // 出队操作
  int GetHead(ElemType &e) const;                                  // 获取队头操作
  LinkQueue(const LinkQueue<ElemType> &copy);                      // 复制构造函数
  LinkQueue<ElemType> &operator=(const LinkQueue<ElemType> &copy); // 赋值运算符重载
};

#endif // LINK_QUEUE_H