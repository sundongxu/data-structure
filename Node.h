#ifndef NODE_H
#define NODE_H

#include <stddef.h>

// 链表结点类
template <class ElemType>
class Node
{
public:
  // 节点数据成员
  ElemType data;        // 数据域
  Node<ElemType> *next; // 指针域

  Node();
  Node(ElemType item, Node<ElemType> *link = NULL); // 已知数据域和指针域构造节点
  virtual ~Node();

protected:
private:
};

template <class ElemType>
Node<ElemType>::Node()
{
  // 操作结果：创建空结点
  next = NULL;
}

template <class ElemType>
Node<ElemType>::Node(ElemType item, Node<ElemType> *link)
{
  // 操作结果：创建实际结点
  data = item;
  next = link;
}

template <class ElemType>
Node<ElemType>::~Node()
{
  // 操作结果：析构函数，释放指针域
  delete next;
}

#endif // NODE_H
