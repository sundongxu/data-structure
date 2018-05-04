#ifndef NODE_H
#define NODE_H

// 链表结点类
template <class ElemType>
class Node
{
public:
  // 节点数据成员
  ElemType val;         // 数据域
  Node<ElemType> *next; // 指针域

  Node();
  Node(ElemType item, Node<ElemType> *link = nullptr); // 已知数据域和指针域构造节点
  virtual ~Node();
};

// 单链表结点类的实现部分
template <class ElemType>
Node<ElemType>::Node()
{
  // 操作结果：创建空结点
  next = nullptr;
}

template <class ElemType>
Node<ElemType>::Node(ElemType item, Node<ElemType> *link)
{
  // 操作结果：创建实际结点
  val = item;
  next = link;
}

template <class ElemType>
Node<ElemType>::~Node()
{
  // 操作结果：析构函数，释放指针域
  // next->next = nullptr;
  delete next;
}

#endif // NODE_H
