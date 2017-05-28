#ifndef ADJ_LIST_GRAPH_VEX_NODE_H
#define ADJ_LIST_GRAPH_VEX_NODE_H

#include "LinkList.h"

// 邻接表图顶点结点类
template <class ElemType>
class AdjListGraphVexNode
{
public:
  // 数据成员
  ElemType data;          // 数据元素值
  LinkList<int> *adjLink; // 邻接链表，邻接链表中的顶点的序号列表

  AdjListGraphVexNode();                                         // 无参数的构造函数
  AdjListGraphVexNode(ElemType item, LinkList<int> *adj = NULL); // 构造顶点数据为item，指向邻接链表的指针为adj的结点
  ~AdjListGraphVexNode();                                        // 析构函数
};

template <class ElemType>
AdjListGraphVexNode<ElemType>::AdjListGraphVexNode()
{
  // 操作结果：构造空结点，邻接链表为空，数据域未知(类型都未知...无法赋初值)
  adjLink = NULL;
}

template <class ElemType>
AdjListGraphVexNode<ElemType>::AdjListGraphVexNode(ElemType item, LinkList<int> *adj)
{
  // 操作结果：构造顶点数据为item，指向邻接链表的指针为adj的结点
  data = item;
  adjLink = adj;
}

template <class ElemType>
AdjListGraphVexNode<ElemType>::~AdjListGraphVexNode()
{
  // 操作结果：销毁顶点，即释放邻接链表空间
  data = 0;       // 无所谓
  delete adjLink; // 释放邻接表空间，是个LinkList对象
  // new的内存空间一定要用delete释放，new[]的内存空间则要用delete[]释放
  adjLink = NULL;
}

#endif // ADJ_LIST_GRAPH_VEX_NODE_H