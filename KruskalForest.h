#ifndef KRUSKAL_FOREST_H
#define KRUSKAL_FOREST_H

#include "Constant.h"

// Kruskal算法实现，森林类
class KruskalForest
{
private:
  int *treeNo; // 顶点所在树的编号
  int vexNum;  // 顶点数目

public:
  KruskalForest(int num = DEFAULT_SIZE); // 构造函数
  ~KruskalForest();                      // 析构函数
  bool IsSameTree(int v1, int v2);       // 判断v1和v2是否在同一棵树上
  void Union(int v1, int v2);            // 将v2所在树的所有顶点合并到v1所在树上
};

// Kruskal森林类实现
KruskalForest::KruskalForest(int num)
{
  // 操作结果：构造顶点数为num的Kruskal森林
  vexNum = num;             // 顶点数
  treeNo = new int[vexNum]; // 分配存储空间
  for (int v = 0; v < vexNum; v++)
  {
    // 初始时，每棵树只有一个顶点，树的个数与顶点个数相同
    treeNo[v] = v;
  }
}

KruskalForest::~KruskalForest()
{
  // 操作结果：销毁Kruskal森林，主要是释放treeNo数组空间
  if (treeNo != nullptr)
  {
    delete[] treeNo;
    treeNo = nullptr;
  }
}

bool KruskalForest::IsSameTree(int v1, int v2)
{
  // 操作结果：如果v1和v2在同一棵树上，则返回true，否则返回false
  return treeNo[v1] == treeNo[v2];
}

void KruskalForest::Union(int v1, int v2)
{
  // 操作结果：将v2所在树的所有顶点合并到v1所在树上
  int v1TNo = treeNo[v1], v2TNo = treeNo[v2];
  for (int v = 0; v < vexNum; v++)
  {
    // 查找v2所在树的顶点
    if (treeNo[v] == v2TNo)
    {
      // 将v2所在树上的顶点所在树编号改为v1所在树的编号
      treeNo[v] = v1TNo;
    }
  }
}

#endif // KRUSKAL_FOREST_H