#ifndef ADJ_LIST_NETWORK_EDGE_H
#define ADJ_LIST_NETWORK_EDGE_H

// 邻接表网的边数据类
template <class WeightType>
class AdjListNetworkEdge
{
public:
  // 数据成员
  int adjVex;        // 邻接点
  WeightType weight; // 权值

  // 构造函数
  AdjListNetworkEdge();                    // 无参数的构造函数
  AdjListNetworkEdge(int v, WeightType w); // 构造邻接点为v，权为w的邻接边
};

template <class WeightType>
AdjListNetworkEdge<WeightType>::AdjListNetworkEdge()
{
  // 操作结果：构造默认邻接表网的边，直接空函数即可
}

template <class WeightType>
AdjListNetworkEdge<WeightType>::AdjListNetworkEdge(int v, WeightType w)
{
  // 操作结果：构造邻接点为v，权为w的邻接边
  adjVex = v;
  weight = w;
}

#endif // ADJ_LIST_NETWORK_EDGE_H