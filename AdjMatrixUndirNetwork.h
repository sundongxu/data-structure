#ifndef ADJ_MATRIX_UNDIR_NETWORK_H
#define ADJ_MATRIX_UNDIR_NETWORK_H

#define SUCCESS 100
#define NOT_PRESENT 200
#define ENTRY_FOUND 300
#define RANGE_ERROR 400
#define OVER_FLOW 500
#define UNDER_FLOW 600

#define DEFAULT_SIZE 1
#define DEFAULT_INFINITY 100000
#define VISITED 1
#define UNVISITED 0

// 无向网的邻接矩阵类
template <class ElemType, class WeightType>
class AdjMatrixUndirNetwork
{
protected:
  // 邻接矩阵的数据成员
  int vexNum, edgeNum; // 顶点个数与边数
  WeightType **Matrix; // 邻接矩阵
  ElemType *elems;     // 顶点数据
  mutable int *tag;    // 指向标志数组的指针
  WeightType infinity; // 无穷大

  // 辅助函数
  void DestroyHelp(); // 销毁有向网，释放有向网占用的空间

public:
  // 抽象数据类型方法声明及重载编译系统默认方法声明：
  AdjMatrixUndirNetwork(ElemType es[], int vertexNum = DEFAULT_SIZE, WeightType infinit = (WeightType)DEFAULT_INFINITY);
  // 构造顶点数据为es[]，顶点个数为vertexNum，infinit表示无穷大，边数为0的有向网
  AdjMatrixUndirNetwork(int vertexNum = DEFAULT_SIZE, WeightType inifinit = (WeightType)DEFAULT_INFINITY);
  // 构造顶点个数为vertexNum，infinit表示无穷大，边数为0的有向网
  ~AdjMatrixUndirNetwork();                                                                                        // 析构函数
  int GetElem(int v, ElemType &e) const;                                                                           // 求顶点的元素值
  int SetElem(int v, const ElemType &e);                                                                           // 设置顶点的元素值
  WeightType GetInfinity() const;                                                                                  // 返回无穷大
  int GetVexNum() const;                                                                                           // 返回顶点个数
  int GetEdgeNum() const;                                                                                          // 返回边数
  bool IsVertex(int v) const;                                                                                      // 判断顶点是否存在
  bool IsEdge(int v1, int v2) const;                                                                               // 判断边是否存在
  int FirstAdjVex(int v) const;                                                                                    // 返回顶点v的第一个邻接点
  int NextAdjVex(int v1, int v2) const;                                                                            // 返回顶点v1的相对于v2的下一个邻接点
  void InsertEdge(int v1, int v2, WeightType w);                                                                   // 插入顶点为v1和v2的边
  void DeleteEdge(int v1, int v2);                                                                                 // 删除顶点为v1和v2的边
  WeightType GetWeight(int v1, int v2) const;                                                                      // 返回顶点为v1和v2的边权值
  void SetWeight(int v1, int v2, const WeightType &w);                                                             // 设置顶点为v1和v2的边的权值
  int GetTag(int v, int &val) const;                                                                               // 返回顶点v的标志
  int SetTag(int v, const int &val) const;                                                                         // 设置顶点v的标志为val
  AdjMatrixUndirNetwork(const AdjMatrixUndirNetwork<ElemType, WeightType> &copy);                                  // 复制构造函数
  AdjMatrixUndirNetwork<ElemType, WeightType> &operator=(const AdjMatrixUndirNetwork<ElemType, WeightType> &copy); // 赋值运算符重载
};

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::DestroyHelp()
{
  // 操作结果：销毁无向网，释放无向网占用的空间
  delete[] elems; // 释放顶点元素
  delete[] tag;   // 释放标志数组

  for (int iPos = 0; iPos < vexNum; iPos++)
  {
    // 释放邻接矩阵的行
    delete[] Matrix[iPos];
  }
  delete[] Matrix; // 释放邻接矩阵
}

template <class ElemType, class WeightType>
bool AdjMatrixUndirNetwork<ElemType, WeightType>::IsVertex(int v) const
{
  // 操作结果：判断顶点序号范围是否合法
  if (v < 0 || v >= vexNum)
  {
    return false;
  }
  return true;
}

template <class ElemType, class WeightType>
bool AdjMatrixUndirNetwork<ElemType, WeightType>::IsEdge(int v1, int v2) const
{
  // 操作结果：判断边（v1,v2）是否存在
  if (IsVertex(v1) && IsVertex(v2))
  {
    // 先判断顶点序号合法性
    if (Matrix[v1][v2] < infinity)
    {
      // 邻接矩阵中指定位置元素不是无穷（权值为无穷就是没有边）
      return true;
    }
  }
  return false;
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType>::AdjMatrixUndirNetwork(ElemType es[], int vertexNum, WeightType infinit)
{
  // 操作结果：构造顶点数据为es[]，顶点个数为vertexNum，初始边权值均为infinit，边数为0的无向网
  elems = es;
  vexNum = vertexNum;
  edgeNum = 0;
  infinity = infinit;
  // 初始化邻接矩阵Matrix，此时无边，故全部元素都为0，但需先创建空间
  Matrix = new WeightType *[vexNum];
  tag = new int[vexNum];
  for (int row = 0; row < vexNum; row++)
  {
    Matrix[row] = new WeightType[vexNum];
    for (int col = 0; col < vexNum; col++)
    {
      Matrix[row][col] = infinit;
    }
    tag[row] = UNVISITED;
  }
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType>::AdjMatrixUndirNetwork(int vertexNum, WeightType infinit)
{
  // 操作结果：构造顶点个数为vertexNum，边数为0的无向网
  elems = new int[vertexNum]; // 默认数组元素就是按int数字序号表示，顶点依次为1，2，...，vertexNum
  vexNum = vertexNum;
  edgeNum = 0;
  infinity = infinit;
  // 初始化邻接矩阵Matrix，此时无边，故全部元素都为0，但需先创建空间
  Matrix = new WeightType *[vexNum];
  tag = new int[vexNum];
  for (int row = 0; row < vexNum; row++)
  {
    Matrix[row] = new WeightType[vexNum];
    for (int col = 0; col < vexNum; col++)
    {
      Matrix[row][col] = infinit;
    }
    tag[row] = UNVISITED;
  }
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType>::~AdjMatrixUndirNetwork()
{
  // 操作结果：析构函数
  DestroyHelp();
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::GetElem(int v, ElemType &e) const
{
  // 操作结果：返回顶点元素值
  // 判断v是否在合理顶点范围内，1<=v<=vexNum
  if (IsVertex(v))
  {
    // 序号合法
    e = elems[v];
    return SUCCESS;
  }
  else
  {
    // 顶点序号不合法
    return RANGE_ERROR;
  }
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::SetElem(int v, const ElemType &e)
{
  // 操作结果：设置顶点元素值
  // 判断v是否在合理顶点范围内，1<=v<=vexNum
  if (IsVertex(v))
  {
    // 序号合法
    elems[v] = e;
    return SUCCESS;
  }
  else
  {
    // 顶点序号不合法
    return RANGE_ERROR;
  }
}

template <class ElemType, class WeightType>
WeightType AdjMatrixUndirNetwork<ElemType, WeightType>::GetInfinity() const
{
  // 操作结果：返回infinity
  return infinity;
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::GetVexNum() const
{
  // 操作结果：返回顶点个数
  return vexNum;
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::GetEdgeNum() const
{
  // 操作结果：返回边个数
  return edgeNum;
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::FirstAdjVex(int v) const
{
  // 操作结果：返回与v相关联的第一个顶点，遍历邻接矩阵对应v的那一行，找到第一个不为1的元素对应的列下标
  if (IsVertex(v))
  {
    for (int col = 0; col < vexNum; col++)
    {
      // 遍历v对应的邻接矩阵行
      if (Matrix[v][col] < DEFAULT_INFINITY)
      {
        // 按顶点下标从小到大，取第一个对应元素小于无穷的顶点下标返回，即与顶点v相关联的第一个顶点
        return col;
      }
    }
    return -1;
  }
  return -1;
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
{
  // 操作结果：返回v1相对于v2的下一个顶点
  if (IsVertex(v1) && IsVertex(v2))
  {
    for (int col = v2 + 1; col < vexNum; col++)
    {
      // 从v2的下一个顶点开始遍历v对应的邻接矩阵行
      if (Matrix[v1][col] < DEFAULT_INFINITY)
      {
        // 按顶点从小到大，取v2之后，与v1相关联的第一个顶点
        return col;
      }
    }
    return -1;
  }
  return -1;
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::InsertEdge(int v1, int v2, WeightType w)
{
  // 操作结果：在顶点v1和v2之间插入边(无向)
  if (v1 == v2)
  {
    // 不能构成顶点到自身的边
    return;
  }
  else if (IsVertex(v1) && IsVertex(v2))
  {
    // v1与v2都存在
    Matrix[v1][v2] = w; // 邻接矩阵中指定元素（v1,v2）赋值为1
    Matrix[v2][v1] = w; // 无向网对称位置元素（v2,v1）也赋值为1
    edgeNum++;
  }
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::DeleteEdge(int v1, int v2)
{
  // 操作结果：删除顶点v1和v2之间的边
  if (IsEdge(v1, v2))
  {
    Matrix[v1][v2] = DEFAULT_INFINITY; // 邻接矩阵中指定元素（v1,v2）赋值为0
    Matrix[v2][v1] = DEFAULT_INFINITY;
    edgeNum--;
  }
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::GetTag(int v, int &val) const
{
  // 操作结果：返回顶点v的访问标志位(没做合法性检查)
  if (IsVertex(v))
  {
    val = tag[v]; // 返回0/1，表示未访问/已访问
    return SUCCESS;
  }
  else
  {
    return NOT_PRESENT; // 对应顶点不存在
  }
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::SetTag(int v, const int &val) const
{
  // 操作结果：设置顶点v的访问标志位（没做合法性检查）
  if (IsVertex(v))
  {
    tag[v] = val;
    return SUCCESS;
  }
  else
  {
    return NOT_PRESENT; // 对应顶点不存在
  }
}

template <class ElemType, class WeightType>
WeightType AdjMatrixUndirNetwork<ElemType, WeightType>::GetWeight(int v1, int v2) const
{
  // 操作结果：返回v1与v2之间的边的权值
  if (IsEdge(v1, v2))
  {
    return Matrix[v1][v2];
  }
  return infinity;
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::SetWeight(int v1, int v2, const WeightType &w)
{
  // 操作结果：设置顶点v1和v2的边的权值
  if (IsEdge(v1, v2))
  {
    Matrix[v1][v2] = w;
    Matrix[v2][v1] = w;
  }
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType>::AdjMatrixUndirNetwork(const AdjMatrixUndirNetwork<ElemType, WeightType> &copy)
{
  // 操作结果：拷贝构造，从无到有，新网与copy内存空间不同
  vexNum = copy.vexNum;
  edgeNum = copy.edgeNum;
  elems = new ElemType[vexNum];
  tag = new int[vexNum];
  Matrix = new WeightType *[vexNum];
  for (int row = 0; row < vexNum; row++)
  {
    Matrix[row] = new WeightType[vexNum];
    for (int col = 0; col < vexNum; col++)
    {
      Matrix[row][col] = copy.Matrix[row][col];
    }
    elems[row] = copy.elems[row];
    tag[row] = copy.tag[row];
  }
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType> &AdjMatrixUndirNetwork<ElemType, WeightType>::operator=(const AdjMatrixUndirNetwork<ElemType, WeightType> &copy)
{
  // 操作结果：赋值运算符重载，从老到新，新网与copy内存空间不同
  if (&copy != this)
  {
    // 非自赋值
    DestroyHelp();
    vexNum = copy.vexNum;
    edgeNum = copy.edgeNum;
    elems = new ElemType[vexNum];
    tag = new int[vexNum];
    Matrix = new WeightType *[vexNum];
    for (int row = 0; row < vexNum; row++)
    {
      Matrix[row] = new WeightType[vexNum];
      for (int col = 0; col < vexNum; col++)
      {
        Matrix[row][col] = copy.Matrix[row][col];
      }
      elems[row] = copy.elems[row];
      tag[row] = copy.tag[row];
    }
  }
}

#endif // ADJ_MATRIX_UNDIR_NETWORK_H
