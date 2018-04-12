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
};

#endif // NODE_H
