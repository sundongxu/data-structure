#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H

#include <stddef.h>
#include "Constant.h"
#include "Node.h"

// 链式队列类
template <class ElemType>
class LinkQueue
{
protected:
  // 链队列实现的数据成员：
  Node<ElemType> *front, *rear; // 队头队尾指针
  // 队头指针指向头结点（无数据域，指针域指向队列的第一个含有效数据域的结点），队尾指针则真的指向队列的最后一个含有效数据域的结点）,即有rear->next==NULL

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
  // 操作结果：返回队列长度，即有效数据结点个数（怎么不用上尾结点？？？tmpPtr==NULL实际就是tmpPtr==rear->next）
  int count = 0;
  for (Node<ElemType> *tmpPtr = front->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
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
  for (Node<ElemType> *tmpPtr = front->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
  {
    // 将tmpPtr依次指向队列的各个元素
    (*Visit)(tmpPtr->data);
  }
}

template <class ElemType>
int LinkQueue<ElemType>::InQueue(const ElemType &e)
{
  // 操作结果：数据域为e的新结点入队
  Node<ElemType> *tmpPtr = new Node<ElemType>(e);
  if (tmpPtr == NULL)
  {
    // 内存分配失败
    return OVER_FLOW;
  }
  else
  {
    // 新建结点成功
    tmpPtr->data = e;
    rear->next = tmpPtr; // 新结点追加在队尾
    rear = tmpPtr;
    return SUCCESS;
  }
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
    e = tmpPtr->data; // 保存第一个有效数据结点的数据域
    front->next = tmpPtr->next;
    if (rear == tmpPtr)
    {
      rear = front; // 出队元素为队末元素，即出队前队中只有一个数据结点，此时应该将队尾指针指向front，否则之后队末结点空间被释放了，rear会变成野指针
    }
    tmpPtr->next = NULL;
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
    e = tmpPtr->data;
    return SUCCESS;
  }
}

template <class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType> &copy)
{
  // 操作结果：由队列copy构造新队列——————复制构造函数
  if (copy.Empty())
  {
    // copy为空
    Init(); // 初始化空栈（分配队头、队末两个指针的空间），这里不用考虑原栈是否为空，一定为空，因为是构造函数！！！
  }
  else
  {
    // copy非空，复制整个队列空间（全部结点）
    for (Node<ElemType> *tmpPtr = copy.front->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
    {
      // 对copy队列每个元素对当前队列作入队操作
      InQueue(tmpPtr->data);
    }
  }
}

template <class ElemType>
LinkQueue<ElemType> &LinkQueue<ElemType>::operator=(const LinkQueue<ElemType> &copy)
{
  // 操作结果：将队列copy赋值给当前队列——————赋值运算符重载
  if (&copy != this)
  {
    Clear();
    for (Node<ElemType> *tmpPtr = copy.front->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
    {
      // 对copy队列每个元素对当前队列作入队操作
      InQueue(tmpPtr->data);
    }
  }
  return *this;
}

#endif // LINK_QUEUE_H