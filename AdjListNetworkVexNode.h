#ifndef ADJ_LIST_NETWORK_VEX_NODE_H
#define ADJ_LIST_NETWORK_VEX_NODE_H

#include "LinkList.h"
#include "AdjListNetworkEdge.h"

// 邻接表网顶点结点类
template <class ElemType, class WeightType>
class AdjListNetworkVexNode
{
public:
  // 数据成员
  ElemType data;                                     // 数据元素值
  LinkList<AdjListNetworkEdge<WeightType>> *adjLink; // 邻接链表

  // 构造函数
  AdjListNetworkVexNode();                                                                    // 无参数的构造函数
  AdjListNetworkVexNode(ElemType item, LinkList<AdjListNetworkEdge<WeightType>> *adj = nullptr); // 构造顶点数据为item，指向邻接链表的指针为adj的结构
  void SetData(const int d);
};

template <class ElemType, class WeightType>
AdjListNetworkVexNode<ElemType, WeightType>::AdjListNetworkVexNode()
{
  // 操作结果：默认构造一个邻接表网的空结点
  adjLink = nullptr;
}

template <class ElemType, class WeightType>
AdjListNetworkVexNode<ElemType, WeightType>::AdjListNetworkVexNode(ElemType item, LinkList<AdjListNetworkEdge<WeightType>> *adj)
{
  // 操作结果：构造一个数据值为item，邻接表为adj的邻接表网的结点
  data = item;
  adjLink = adj;
}

template <class ElemType, class WeightType>
void AdjListNetworkVexNode<ElemType, WeightType>::SetData(const int d)
{
  // 操作结果：给顶点的数据成员data赋值d
  data = d;
}

#endif // ADJ_LIST_NETWORK_VEX_NODE_H