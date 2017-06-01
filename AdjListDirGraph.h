#ifndef ADJ_LIST_DIR_GRAPH_H
#define ADJ_LIST_DIR_GRAPH_H

#include "Constant.h"
#include "LinkList.h"
#include "AdjListGraphVexNode.h"

// 有向图的邻接表类
template <class ElemType>
class AdjListDirGraph
{
protected:
  // 邻接表的数据成员
  int vexNum, edgeNum;                     // 顶点个数和边数
  AdjListGraphVexNode<ElemType> *vexTable; // 顶点表，ElemType是顶点data数据类型
  mutable int *tag;                        // 指向访问标志数组的指针

  // 辅助函数
  void DestroyHelp();                                  // 销毁有向图，释放有向图占用的空间
  int IndexHelp(const LinkList<int> *la, int v) const; // 定位顶点v在邻接链表中的位置
  bool IsVertex(int v) const;                          // 判断顶点是否存在
  bool IsEdge(int v1, int v2) const;                   // 判断边是否存在

public:
  // 抽象数据类型方法声明及重载编译系统默认方法声明
  AdjListDirGraph(ElemType es[], int vextexNum = DEFAULT_SIZE);                // 构造顶点数据为es[]，顶点个数为vertexNum，边数为0的有向图
  AdjListDirGraph(int vertexNum = DEFAULT_SIZE);                               // 构造顶点个数为vertexNum，边数为0的有向图
  ~AdjListDirGraph();                                                          // 析构函数
  int GetElem(int v, ElemType &e) const;                                       // 求顶点的元素值
  int SetElem(int v, const ElemType &e);                                       // 设置顶点的元素值
  int GetVexNum() const;                                                       // 返回顶点个数
  int GetEdgeNum() const;                                                      // 返回边数
  int FirstAdjVex(int v) const;                                                // 返回顶点v的第一个邻接点
  int NextAdjVex(int v1, int v2) const;                                        // 返回顶点v1相对于顶点v2的下一个邻接点
  void InsertEdge(int v1, int v2);                                             // 插入顶点为v1和v2的边
  void DeleteEdge(int v1, int v2);                                             // 删除顶点为v1和v2的边
  int GetTag(int v, int &val) const;                                           // 返回顶点v的标志
  int SetTag(int v, const int &val);                                           // 设置顶点v的标志为val
  AdjListDirGraph(const AdjListDirGraph<ElemType> &copy);                      // 复制构造函数
  AdjListDirGraph<ElemType> &operator=(const AdjListDirGraph<ElemType> &copy); // 赋值运算符重载
};

template <class ElemType>
void AdjListDirGraph<ElemType>::DestroyHelp()
{
  // 操作结果：销毁有向图，释放有向图占用的空间————指针空间
  vexNum = 0;
  edgeNum = 0;
  delete[] vexTable; // 释放顶点表
  delete[] tag;      // 释放标志数组
}

template <class ElemType>
int AdjListDirGraph<ElemType>::IndexHelp(const LinkList<int> *la, int v) const
{
  // 操作结果：定位序号为v的顶点在邻接链表中的位置
  int curPos, adjVex;
  curPos = la->GetCurPosition();

  la->GetElem(curPos, adjVex); // 取得邻接点信息
  if (adjVex == v)
  {
    return curPos; // v为线性链表的当前位置处
  }
  curPos = 1; // 一开始从链表的当前位置查找，如果不是则需要从头查找
  // 不能从curPos往后查找是因为无法确定该顶点是在curPos之前还是之后
  for (curPos = 1; curPos <= la->Length(); curPos++)
  {
    // 循环定位序号为v的顶点在邻接表la中的位置
    la->GetElem(curPos, adjVex); // 取得边信息
    if (adjVex == v)
    {
      break;
    }
  }
  return curPos; // curPos=la.Length()+1表示定位失败
}

template <class ElemType>
bool AdjListDirGraph<ElemType>::IsVertex(int v) const
{
  // 操作结果：判断顶点v序号范围是否合法
  if (v < 0 || v >= vexNum)
  {
    return false;
  }
  return true;
}

template <class ElemType>
bool AdjListDirGraph<ElemType>::IsEdge(int v1, int v2) const
{
  // 操作结果：判断边(v1, v2)是否存在
  if (IsVertex(v1) && IsVertex(v2))
  {
    // 先判断顶点序号合法性
    if (vexTable[v1].adjLink != NULL) // v1的邻接表不为空，再去找v2在其中的位置
    {
      int indexV2 = IndexHelp(vexTable[v1].adjLink, v2); // 获取v2在v1的邻接表中出现的位置
      if (indexV2 < vexTable[v1].adjLink->Length() + 1)
      {
        // 即在顶点v1的邻接表中可以找到v2，则返回true
        return true;
      }
    }
  }
  return false;
}

template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(ElemType es[], int vertexNum)
{
  // 操作结果：构造顶点数据为es[] ，顶点个数为vertexNum，边数为0的有向图
  vexNum = vertexNum;
  edgeNum = 0; // 初始化构造图时没有边
  // 创建顶点空间
  vexTable = new AdjListGraphVexNode<ElemType>[vexNum];
  tag = new int[vexNum];
  for (int v = 0; v < vexNum; v++)
  {
    // new返回的是指针！这里vexTable[v]不是一个指针了，而是一个对象！！！二维指针才能这么赋值
    // vexTable[v] = new AdjListGraphVexNode<ElemType>(es[v], NULL);
    vexTable[v].data = es[v]; // 这个邻接表到哪里去创建？？？————插入边的时候！
    tag[v] = UNVISITED;       // 顶点全部初始化为未访问
  }
}

template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(int vertexNum)
{
  // 操作结果：构造顶点个数为vertexNum，边数为0的有向图
  vexNum = vertexNum;
  edgeNum = 0; // 初始化构造图时没有边
  // 创建顶点空间
  vexTable = new AdjListGraphVexNode<ElemType>[vexNum];
  tag = new int[vexNum];
  for (int v = 0; v < vexNum; v++)
  {
    // vexTable[v] = new AdjListGraphVexNode<ElemType>(); // 这个邻接表到哪里去创建？？？————插入边的时候！
    tag[v] = UNVISITED; // 顶点全部初始化为未访问
  }
}

template <class ElemType>
AdjListDirGraph<ElemType>::~AdjListDirGraph()
{
  // 操作结果：释放有向图所占空间
  DestroyHelp();
}

template <class ElemType>
int AdjListDirGraph<ElemType>::GetElem(int v, ElemType &e) const
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

template <class ElemType>
int AdjListDirGraph<ElemType>::SetElem(int v, const ElemType &e)
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

template <class ElemType>
int AdjListDirGraph<ElemType>::GetVexNum() const
{
  // 操作结果：返回顶点个数
  return vexNum;
}

template <class ElemType>
int AdjListDirGraph<ElemType>::GetEdgeNum() const
{
  // 操作结果：返回边个数
  return edgeNum;
}

template <class ElemType>
int AdjListDirGraph<ElemType>::FirstAdjVex(int v) const
{
  // 操作结果：返回顶点v的第一个邻接点
  if (IsVertex(v))
  {
    if (vexTable[v].adjLink != NULL)
    {
      // 非空邻接链表，存在邻接点
      int adjVex;
      vexTable[v].adjLink->GetElem(1, adjVex);
      return adjVex;
    }
  }
  return -1;
}

template <class ElemType>
int AdjListDirGraph<ElemType>::NextAdjVex(int v1, int v2) const
{
  // 操作结果：返回顶点v1相对于v2的下一个邻接点
  if (IsVertex(v1) && IsVertex(v2))
  {
    if (v1 != v2)
    {
      if (vexTable[v1].adjLink != NULL)
      {
        int curPos = IndexHelp(vexTable[v1].adjLink, v2); // 取出v2在邻接表中的位置
        if (curPos < vexTable[v1].adjLink->Length())
        {
          // 存在下一个邻接点
          int adjVex;
          vexTable[v1].adjLink->GetElem(curPos + 1, adjVex); // 取出后继
          return adjVex;
        }
      }
    }
  }
  return -1;
}

template <class ElemType>
void AdjListDirGraph<ElemType>::InsertEdge(int v1, int v2)
{
  // 操作结果：在顶点v1和v2之间插入边(无向)
  if (v1 == v2)
  {
    // 不能构成顶点到自身的边
    // assert(0);  // 直接报错
    return;
  }
  if (IsVertex(v1) && IsVertex(v2))
  {
    // v1与v2都存在，先判断v1的邻接表是否存在
    if (vexTable[v1].adjLink == NULL)
    {
      // v1的邻接表为空，没有任何邻接点，初始情况，怎么给adjLink初始化呢? -> new一个LinkList对象给它
      vexTable[v1].adjLink = new LinkList<int>();
      vexTable[v1].adjLink->Insert(1, v2);
    }
    else
    {
      // 将v2添加到v1的邻接表中去，先要检查v2是不是已经在表里了
      int indexV2 = IndexHelp(vexTable[v1].adjLink, v2); // 获取v2在v1的邻接表中出现的位置
      if (indexV2 == vexTable[v1].adjLink->Length() + 1)
      {
        // v2不在v1的邻接表中，可以加入
        // int posV2 = vexTable[v1].adjLink->Length() + 1; // v1的邻接表长度，实际就是v2要插入的位置
        vexTable[v1].adjLink->Insert(indexV2, v2); // 将v2插入到v1邻接表的末尾
      }
    }
  }
  edgeNum++;
}

template <class ElemType>
void AdjListDirGraph<ElemType>::DeleteEdge(int v1, int v2)
{
  // 操作结果：删除顶点v1和v2之间的边
  if (IsEdge(v1, v2))
  {
    int indexV2 = IndexHelp(vexTable[v1].adjLink, v2); // 定位v2在v1的邻接表中的位置
    int tmp;
    vexTable[v1].adjLink->Delete(indexV2, tmp); // 从v1的邻接表中删除v2
    edgeNum--;
  }
}

template <class ElemType>
int AdjListDirGraph<ElemType>::GetTag(int v, int &val) const
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

template <class ElemType>
int AdjListDirGraph<ElemType>::SetTag(int v, const int &val)
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

template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(const AdjListDirGraph<ElemType> &copy)
{
  // 操作结果：拷贝构造，从无到有，新图与copy内存空间不同
  vexNum = copy.vexNum;
  edgeNum = copy.edgeNum;
  vexTable = new AdjListGraphVexNode<ElemType>[vexNum]; // 已经给每个顶点分配了内存空间
  tag = new int[vexNum];
  for (int v = 0; v < vexNum; v++)
  {
    // vexTable[v] = new AdjListGraphVexNode<ElemType>(); // 给每个顶点分配内存空间
    vexTable[v].data = copy.vexTable[v].data;
    vexTable[v].adjLink = copy.vexTable[v].adjLink;
    tag[v] = copy.tag[v];
  }
}

template <class ElemType>
AdjListDirGraph<ElemType> &AdjListDirGraph<ElemType>::operator=(const AdjListDirGraph<ElemType> &copy)
{
  // 操作结果：赋值运算符重载，从老到新，新图与copy内存空间不同
  if (&copy != this)
  {
    // 非自赋值
    DestroyHelp(); // 释放旧图内存空间，之后再申请新空间
    vexNum = copy.vexNum;
    edgeNum = copy.edgeNum;
    vexTable = new AdjListGraphVexNode<ElemType>[vexNum];
    tag = new int[vexNum];
    for (int v = 0; v < vexNum; v++)
    {
      // vexTable[v] = new AdjListGraphVexNode<ElemType>(); // 给每个顶点分配内存空间
      vexTable[v].data = copy.vexTable[v].data;
      vexTable[v].adjLink = copy.vexTable[v].adjLink;
      tag[v] = copy.tag[v];
    }
  }
  return *this;
}

#endif // ADJ_LIST_DIR_GRAPH_H