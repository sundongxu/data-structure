#ifndef ADJ_LIST_UNDIR_NETWORK_H
#define ADJ_LIST_UNDIR_NETWORK_H

#include "Constant.h"
#include "AdjListNetworkVexNode.h"
#include "AdjListNetworkEdge.h"

// 无向网的邻接表类
template <class ElemType, class WeightType>
class AdjListUndirNetwork
{
protected:
  // 邻接表的数据成员
  int vexNum, edgeNum;                                   // 顶点个数和边数
  AdjListNetworkVexNode<ElemType, WeightType> *vexTable; // 顶点表
  mutable int *tag;                                      // 指向标志数组的指针
  WeightType infinity;                                   // 无穷大

  // 辅助函数
  void DestroyHelp();                                                             // 销毁有向网，释放有向网占用的空间
  int IndexHelp(const LinkList<AdjListNetworkEdge<WeightType>> *la, int v) const; // 定位顶点v在邻接表中的位置
  bool IsVertex(int v) const;                                                     // 判断顶点是否存在
  bool IsEdge(int v1, int v2) const;                                              // 判断边是否存在

public:
  // 抽象数据类型方法声明及重载编译系统默认方法声明：
  AdjListUndirNetwork(ElemType es[], int vertexNum = DEFAULT_SIZE, WeightType infinit = (WeightType)DEFAULT_INFINITY);
  // 构造顶点数据为es[]，顶点个数为vertexNum，infinit表示无穷大，边数为0的有向网
  AdjListUndirNetwork(int vertexNum = DEFAULT_SIZE, WeightType inifinit = (WeightType)DEFAULT_INFINITY);
  // 构造顶点个数为vertexNum，infinit表示无穷大，边数为0的有向网
  ~AdjListUndirNetwork();                                                                                      // 析构函数
  int GetElem(int v, ElemType &e) const;                                                                       // 求顶点的元素值
  int SetElem(int v, const ElemType &e);                                                                       // 设置顶点的元素值
  WeightType GetInfinity() const;                                                                              // 返回无穷大
  int GetVexNum() const;                                                                                       // 返回顶点个数
  int GetEdgeNum() const;                                                                                      // 返回边数
  int FirstAdjVex(int v) const;                                                                                // 返回顶点v的第一个邻接点
  int NextAdjVex(int v1, int v2) const;                                                                        // 返回顶点v1的相对于v2的下一个邻接点
  void InsertEdge(int v1, int v2, WeightType w);                                                               // 插入顶点为v1和v2的边
  void DeleteEdge(int v1, int v2);                                                                             // 删除顶点为v1和v2的边
  WeightType GetWeight(int v1, int v2) const;                                                                  // 返回顶点为v1和v2的边权值
  void SetWeight(int v1, int v2, WeightType w);                                                                // 设置顶点为v1和v2的边的权值
  int GetTag(int v, int &val) const;                                                                           // 返回顶点v的标志
  int SetTag(int v, const int &val);                                                                           // 设置顶点v的标志为val
  AdjListUndirNetwork(const AdjListUndirNetwork<ElemType, WeightType> &copy);                                  // 复制构造函数
  AdjListUndirNetwork<ElemType, WeightType> &operator=(const AdjListUndirNetwork<ElemType, WeightType> &copy); // 赋值运算符重载
};

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::DestroyHelp()
{
  // 操作结果：销毁有向图，释放有向图占用的空间————指针空间
  vexNum = 0;
  edgeNum = 0;
  delete[] vexTable; // 释放顶点表
  delete[] tag;      // 释放标志数组
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::IndexHelp(const LinkList<AdjListNetworkEdge<WeightType>> *la, int v) const
{
  // 操作结果：定位顶点v在邻接链表中的位置
  int curPos, adjVex;
  curPos = la->GetCurPosition(); // la是邻接表有向网的边，它的adjVex属性对应的才是顶点序号

  AdjListNetworkEdge<WeightType> edge;
  la->GetElem(curPos, edge); // 取得邻接点信息
  adjVex = edge.adjVex;
  if (adjVex == v)
  {
    return curPos; // v为线性链表的当前位置处
  }
  curPos = 1; // 一开始从链表的当前位置查找，如果不是则需要从头查找
  for (curPos = 1; curPos <= la->Length(); curPos++)
  {
    // 循环定位
    AdjListNetworkEdge<WeightType> tmpEdge;
    la->GetElem(curPos, tmpEdge); // 取得边信息
    adjVex = tmpEdge.adjVex;      // 取得邻接点信息
    if (adjVex == v)
    {
      break;
    }
  }
  return curPos; // curPos=la.Length()+1表示定位失败
}

template <class ElemType, class WeightType>
bool AdjListUndirNetwork<ElemType, WeightType>::IsVertex(int v) const
{
  // 操作结果：判断顶点v序号范围是否合法
  if (v < 0 || v >= vexNum)
  {
    return false;
  }
  return true;
}

template <class ElemType, class WeightType>
bool AdjListUndirNetwork<ElemType, WeightType>::IsEdge(int v1, int v2) const
{
  // 操作结果：判断边(v1, v2)是否存在
  if (IsVertex(v1) && IsVertex(v2))
  {
    bool isV1NoAdj = (vexTable[v1].adjLink == nullptr),
         isV2NoAdj = (vexTable[v2].adjLink == nullptr);
    if (!isV1NoAdj && !isV2NoAdj)
    {
      // 若边存在都都存在，检查两者任意一个邻接表均可
      int indexV2 = IndexHelp(vexTable[v1].adjLink, v2); // 获取v2在v1的邻接表中出现的位置
      if (indexV2 < vexTable[v1].adjLink->Length() + 1)
      {
        // 即在顶点v1的邻接表中可以找到v2，则返回true
        return true;
      }
    }
    // 先判断顶点序号合法性
  }
  return false;
}

template <class ElemType, class WeightType>
AdjListUndirNetwork<ElemType, WeightType>::AdjListUndirNetwork(ElemType es[], int vertexNum, WeightType infinit)
{
  // 操作结果：构造顶点数据为es[]，顶点个数为vertexNum，初始边权值均为infinit，边数为0的有向网
  vexNum = vertexNum;
  edgeNum = 0;        // 初始化构造图时没有边
  infinity = infinit; // 无穷的赋值
  // 创建顶点空间
  vexTable = new AdjListNetworkVexNode<ElemType, WeightType>[vexNum];
  tag = new int[vexNum];
  for (int v = 0; v < vexNum; v++)
  {
    // vexTable[v] = new AdjListNetworkVexNode<ElemType, WeightType>(es[v], nullptr); // 这个邻接表到哪里去创建？？？————插入边的时候！
    vexTable[v].SetData(es[v]);
    tag[v] = UNVISITED; // 顶点全部初始化为未访问
  }
}

template <class ElemType, class WeightType>
AdjListUndirNetwork<ElemType, WeightType>::AdjListUndirNetwork(int vertexNum, WeightType infinit)
{
  // 操作结果：构造顶点数据为es[]，顶点个数为vertexNum，初始边权值均为infinit，边数为0的有向网
  vexNum = vertexNum;
  edgeNum = 0;        // 初始化构造图时没有边
  infinity = infinit; // 无穷的赋值
  // 创建顶点空间
  vexTable = new AdjListNetworkVexNode<ElemType, WeightType>[vexNum]; // 调用默认顶点构造函数(无参)
  tag = new int[vexNum];
  for (int v = 0; v < vexNum; v++)
  {
    // vexTable[v] = new AdjListNetworkVexNode<ElemType, WeightType>(); // 这个邻接表到哪里去创建？？？————插入边的时候！
    tag[v] = UNVISITED; // 顶点全部初始化为未访问
  }
}

template <class ElemType, class WeightType>
AdjListUndirNetwork<ElemType, WeightType>::~AdjListUndirNetwork()
{
  // 操作结果：释放有向网所占空间
  DestroyHelp();
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::GetElem(int v, ElemType &e) const
{
  // 操作结果：返回顶点v对应的元素值
  // 判断v是否在合理顶点范围内，1<=v<=vexNum
  if (IsVertex(v))
  {
    // 序号合法
    e = vexTable[v].data;
    return SUCCESS;
  }
  else
  {
    // 顶点序号不合法
    return RANGE_ERROR;
  }
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::SetElem(int v, const ElemType &e)
{
  // 操作结果：设置顶点元素值
  // 判断v是否在合理顶点范围内，1<=v<=vexNum
  if (IsVertex(v))
  {
    // 序号合法
    vexTable[v].data = e;
    return SUCCESS;
  }
  else
  {
    // 顶点序号不合法
    return RANGE_ERROR;
  }
}

template <class ElemType, class WeightType>
WeightType AdjListUndirNetwork<ElemType, WeightType>::GetInfinity() const
{
  // 操作结果：返回infinity
  return infinity;
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::GetVexNum() const
{
  // 操作结果：返回顶点个数
  return vexNum;
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::GetEdgeNum() const
{
  // 操作结果：返回边个数
  return edgeNum;
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::FirstAdjVex(int v) const
{
  // 操作结果：返回顶点v的第一个邻接点
  if (IsVertex(v))
  {
    if (vexTable[v].adjLink == nullptr)
    {
      // 空邻接链表，无邻接点
      return -1;
    }
    else
    {
      // 非空邻接链表，存在邻接点
      int adjVex;
      AdjListNetworkEdge<WeightType> tmpEdge;
      vexTable[v].adjLink->GetElem(1, tmpEdge);
      adjVex = tmpEdge.adjVex;
      return adjVex;
    }
  }
  return -1;
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
{
  // 操作结果：返回顶点v1相对于v2的下一个邻接点
  if (IsVertex(v1) && IsVertex(v2))
  {
    if (v1 != v2)
    {
      if (vexTable[v1].adjLink != nullptr)
      {
        int curPos = IndexHelp(vexTable[v1].adjLink, v2); // 取出v2在邻接表中的位置
        if (curPos < vexTable[v1].adjLink->Length())
        {
          // 存在下一个邻接点
          int adjVex;
          AdjListNetworkEdge<WeightType> tmpEdge;
          vexTable[v1].adjLink->GetElem(curPos + 1, tmpEdge); // 取出后继
          adjVex = tmpEdge.adjVex;
          return adjVex;
        }
      }
    }
  }
  return -1;
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::InsertEdge(int v1, int v2, WeightType w)
{
  // 操作结果：在顶点v1和v2之间插入边，权值为w
  if (v1 == v2)
  {
    // 不能构成顶点到自身的边
    return;
  }
  else if (IsVertex(v1) && IsVertex(v2))
  {
    // v1的邻接表为空，不意味着v2的邻接表就一定为空啊！
    bool isV1NoAdj = (vexTable[v1].adjLink == nullptr),
         isV2NoAdj = (vexTable[v2].adjLink == nullptr);

    if (isV1NoAdj && isV2NoAdj)
    {
      // v1、v2的邻接表均为空
      vexTable[v1].adjLink = new LinkList<AdjListNetworkEdge<WeightType>>();
      vexTable[v2].adjLink = new LinkList<AdjListNetworkEdge<WeightType>>();
      AdjListNetworkEdge<WeightType> tmpEdge1(v2, w);
      vexTable[v1].adjLink->Insert(1, tmpEdge1);
      AdjListNetworkEdge<WeightType> tmpEdge2(v1, w);
      vexTable[v2].adjLink->Insert(1, tmpEdge2);
    }
    else if (isV1NoAdj)
    {
      // 仅v1的邻接表为空
      vexTable[v1].adjLink = new LinkList<AdjListNetworkEdge<WeightType>>();
      AdjListNetworkEdge<WeightType> tmpEdge(v2, w);
      vexTable[v1].adjLink->Insert(1, tmpEdge);
      int indexV1 = IndexHelp(vexTable[v2].adjLink, v1);
      if (indexV1 == vexTable[v2].adjLink->Length() + 1)
      {
        AdjListNetworkEdge<WeightType> tmpEdge(v1, w);
        vexTable[v2].adjLink->Insert(indexV1, tmpEdge);
      }
    }
    else if (isV2NoAdj)
    {
      // 仅v2的邻接表为空
      vexTable[v2].adjLink = new LinkList<AdjListNetworkEdge<WeightType>>();
      AdjListNetworkEdge<WeightType> tmpEdge(v1, w);
      vexTable[v2].adjLink->Insert(1, tmpEdge);
      int indexV2 = IndexHelp(vexTable[v1].adjLink, v2);
      if (indexV2 == vexTable[v1].adjLink->Length() + 1)
      {
        AdjListNetworkEdge<WeightType> tmpEdge(v2, w);
        vexTable[v1].adjLink->Insert(indexV2, tmpEdge);
      }
    }
    else
    {
      // v1与v2都存在
      // 将v2添加到v1的邻接表中去，先要检查v2是不是已经在表里了
      int indexV1 = IndexHelp(vexTable[v2].adjLink, v1); // 获取v1在v2的邻接表中出现的位置
      int indexV2 = IndexHelp(vexTable[v1].adjLink, v2); // 获取v2在v1的邻接表中出现的位置
      if (indexV2 == vexTable[v1].adjLink->Length() + 1)
      {
        // v2不在v1的邻接表中，可以加入
        // int posV2 = vexTable[v1].adjLink->Length() + 1; // v1的邻接表长度，实际就是v2要插入的位置
        AdjListNetworkEdge<WeightType> tmpEdge1(v1, w), tmpEdge2(v2, w);
        vexTable[v1].adjLink->Insert(indexV2, tmpEdge2); // 将v2插入到v1邻接表的末尾
        vexTable[v2].adjLink->Insert(indexV1, tmpEdge1); // 将v1插入到v2邻接表的末尾
      }
    }
  }
  edgeNum++;
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::DeleteEdge(int v1, int v2)
{
  // 操作结果：删除顶点v1和v2之间的边
  if (IsEdge(v1, v2))
  {
    int indexV1 = IndexHelp(vexTable[v2].adjLink, v1); // 定位v1在v2的邻接表中位置
    int indexV2 = IndexHelp(vexTable[v1].adjLink, v2); // 定位v2在v1的邻接表中的位置
    AdjListNetworkEdge<WeightType> tmpEdge;
    vexTable[v1].adjLink->Delete(indexV2, tmpEdge); // 从v1的邻接表中删除v2
    vexTable[v2].adjLink->Delete(indexV1, tmpEdge); // 从v2的邻接表中删除v1
    edgeNum--;
  }
}

template <class ElemType, class WeightType>
WeightType AdjListUndirNetwork<ElemType, WeightType>::GetWeight(int v1, int v2) const
{
  // 操作结果：返回顶点为v1和v2的边权值
  if (IsEdge(v1, v2))
  {
    if (v1 != v2)
    {
      AdjListNetworkEdge<WeightType> tmpEdge;
      int curPosV2 = IndexHelp(vexTable[v1].adjLink, v2); // 找出v2在v1的邻接表中的位置
      if (curPosV2 <= vexTable[v1].adjLink->Length())
      {
        // 存在边<v1,v2>
        vexTable[v1].adjLink->GetElem(curPosV2, tmpEdge); // 取出边
        return tmpEdge.weight;
      }
    }
  }
  return infinity;
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType w)
{
  // 操作结果：设置顶点为v1、v2的边的权值
  if (IsEdge(v1, v2))
  {
    if (w == infinity)
    {
      // 权值不能无穷大
      return;
    }

    AdjListNetworkEdge<WeightType> tmpEdge1;
    int curPosV2 = IndexHelp(vexTable[v1].adjLink, v2); // 找出v2在v1的邻接表中的位置
    if (curPosV2 <= vexTable[v1].adjLink->Length())
    {
      // 存在边<v1,v2>
      vexTable[v1].adjLink->GetElem(curPosV2, tmpEdge1); // 取出边
      tmpEdge1.weight = w;                               // 修改<v1,v2>权值
      vexTable[v1].adjLink->SetElem(curPosV2, tmpEdge1); // 设置边
    }

    AdjListNetworkEdge<WeightType> tmpEdge2;
    int curPosV1 = IndexHelp(vexTable[v2].adjLink, v1); // 找出v2在v1的邻接表中的位置
    if (curPosV1 <= vexTable[v2].adjLink->Length())
    {
      // 存在边<v1,v2>
      vexTable[v2].adjLink->GetElem(curPosV1, tmpEdge2); // 取出边
      tmpEdge2.weight = w;                               // 修改<v1,v2>权值
      vexTable[v2].adjLink->SetElem(curPosV1, tmpEdge2); // 设置边
    }
  }
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::GetTag(int v, int &val) const
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
int AdjListUndirNetwork<ElemType, WeightType>::SetTag(int v, const int &val)
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
AdjListUndirNetwork<ElemType, WeightType>::AdjListUndirNetwork(const AdjListUndirNetwork<ElemType, WeightType> &copy)
{
  // 操作结果：拷贝构造，从无到有，新图与copy内存空间不同
  vexNum = copy.vexNum;
  edgeNum = copy.edgeNum;
  vexTable = new AdjListNetworkVexNode<ElemType, WeightType>[vexNum];
  tag = new int[vexNum];
  for (int v = 0; v < vexNum; v++)
  {
    // vexTable[v] = new AdjListNetworkVexNode<ElemType, WeightType>; // 给每个顶点分配内存空间
    vexTable[v].data = copy.vexTable[v].data;
    vexTable[v].adjLink = copy.vexTable[v].adjLink;
    tag[v] = copy.tag[v];
  }
}

template <class ElemType, class WeightType>
AdjListUndirNetwork<ElemType, WeightType> &AdjListUndirNetwork<ElemType, WeightType>::operator=(const AdjListUndirNetwork<ElemType, WeightType> &copy)
{
  // 操作结果：赋值运算符重载，从老到新，新图与copy内存空间不同
  if (&copy != this)
  {
    // 非自赋值
    DestroyHelp(); // 释放旧图内存空间，之后再申请新空间
    vexNum = copy.vexNum;
    edgeNum = copy.edgeNum;
    vexTable = new AdjListNetworkVexNode<ElemType, WeightType>[vexNum];
    tag = new int[vexNum];
    for (int v = 0; v < vexNum; v++)
    {
      // vexTable[v] = new AdjListNetworkVexNode<ElemType, WeightType>; // 给每个顶点分配内存空间
      vexTable[v].data = copy.vexTable[v].data;
      vexTable[v].adjLink = copy.vexTable[v].adjLink;
      tag[v] = copy.tag[v];
    }
  }
  return *this;
}

#endif // ADJ_LIST_UNDIR_NETWORK_H