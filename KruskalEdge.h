#ifndef KRUSKAL_EDGE_H
#define KRUSKAL_EDGE_H

#include <stddef.h> // 包含NULL定义，实际NULL==0

// Kruskal算法实现，图边类
template <class WeightType>
class KruskalEdge
{

public:
  int vertex1, vertex2;                             // 边的顶点
  WeightType weight;                                // 边的权重
  KruskalEdge(int v1 = -1, int v2 = -1, int w = 0); // 构造函数
                                                    // ~KruskalEdge();                                   // 析构函数，默认就好————没有指针空间需要人为释放
};

template <class WeightType>
KruskalEdge<WeightType>::KruskalEdge(int v1, int v2, int w)
{
  // 操作结果：由顶点v1、v2和权w构造边————构造函数
  vertex1 = v1;
  vertex2 = v2;
  weight = w;
}

#endif // KRUSKAL_EDGE_H