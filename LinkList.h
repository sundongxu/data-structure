#ifndef LINK_LIST_H
#define LINK_LIST_H

#include <iostream>
#include "stddef.h"
#include "Node.h"

#define SUCCESS 100
#define NOT_PRESENT 200
#define ENTRY_FOUND 300
#define RANGE_ERROR 400
#define OVER_FLOW 500
#define UNDER_FLOW 600

// 线性链表类
template <class ElemType>
class LinkList
{
protected:
  // 链表实现的数据成员
  Node<ElemType> *head;           // 头结点指针
  mutable int curPosition;        // 当前位置的序号，使得在position在curPosition之后时GetElem时不用从头开始，直接从curPtr往后移动即可
  mutable Node<ElemType> *curPtr; // 指向当前位置的指针
  int count;                      // 元素个数

  // 辅助函数
  Node<ElemType> *GetElemPtr(int position) const; // 返回指向第position个结点的指针
  void Init();                                    // 初始化线性表

public:
  // 抽象数据类型方法声明及重载编译系统默认方法声明
  LinkList();                                              // 无参数的构造函数
  virtual ~LinkList();                                     // 析构函数
  int Length() const;                                      // 返回线性表长度
  bool Empty() const;                                      // 判断线性表是否为空
  void Clear();                                            // 将线性表清空
  void Traverse(void (*Visit)(ElemType &));                // 遍历线性表
  int GetCurPosition() const;                              // 返回当前位置序号
  int GetElem(int position, ElemType &e) const;            // 获取指定位置的元素
  int SetElem(int position, const ElemType &e);            // 设置指定位置的元素
  int Delete(int position, ElemType &e);                   // 删除指定位置的元素
  int Insert(int position, const ElemType &e);             // 在指定位置插入新元素
  LinkList(const LinkList<ElemType> &copy);                // 复制构造函数
  LinkList<ElemType> &operator=(LinkList<ElemType> &copy); // 重载赋值运算符

  friend std::ostream &operator<<(std::ostream &os, LinkList<ElemType> &ll);
};

template <class ElemType>
Node<ElemType> *LinkList<ElemType>::GetElemPtr(int position) const
{
  // 操作结果：返回指向第position个结点的指针
  if (curPosition > position)
  {
    // 当前位置在所查找位置之后，只能从表头开始查询
    curPosition = 0;
    curPtr = head;
  }
  // curPosition从0开始计数
  for (; curPosition < position; curPosition++)
  {
    curPtr = curPtr->next; // 查找位置position
  }
  return curPtr;
}

template <class ElemType>
void LinkList<ElemType>::Init()
{
  // 操作结果：初始化线性表，创建头结点(无数据域)
  head = new Node<ElemType>; // 构造头指针（头结点）
  curPtr = head;
  curPosition = 0;
  count = 0;
}

template <class ElemType>
LinkList<ElemType>::LinkList()
{
  // 操作结果：创建空链表
  Init();
}

template <class ElemType>
LinkList<ElemType>::~LinkList()
{
  // 操作结果：析构函数，待释放的存储空间包括数据节点和头结点
  Clear();     // 释放非头结点空间
  delete head; // 释放头结点空间
  head = NULL;
  curPtr = NULL; // 在Clear中其占用的空间已被释放
  curPosition = 0;
  count = 0;
}

template <class ElemType>
int LinkList<ElemType>::Length() const
{
  // 操作结果：返回链表结点总个数，头指针（头结点）head不算（无数据域）
  return count;
}

template <class ElemType>
bool LinkList<ElemType>::Empty() const
{
  // 操作结果：判断链表是否为空，从头指针（结点）的下一个开始判断）
  return count == 0;
}

template <class ElemType>
void LinkList<ElemType>::Clear()
{
  // 操作结果：清空线性表，仅保留头结点
  // 释放数据结点空间，不管头结点
  // 只要链表非空就不断删除其第1个结点
  ElemType tmpItem;
  while (count > 0)
  {
    Delete(1, tmpItem);
  }
}

template <class ElemType>
void LinkList<ElemType>::Traverse(void (*Visit)(ElemType &))
{
  // 操作结果：遍历线性表
  for (Node<ElemType> *tmpPtr = head->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
  {
    (*Visit)(tmpPtr->data);
  }
}

template <class ElemType>
int LinkList<ElemType>::GetCurPosition() const
{
  // 操作结果：返回当前位置序号
  return curPosition;
}

template <class ElemType>
int LinkList<ElemType>::GetElem(int position, ElemType &e) const
{
  // 操作结果：获取第pos个位置的结点的元素值
  // position的合理性判断
  if (position < 1 || position > Length())
  {
    return NOT_PRESENT;
  }
  else
  {
    Node<ElemType> *tmpPtr = GetElemPtr(position);
    e = tmpPtr->data;
    return ENTRY_FOUND;
  }
}

template <class ElemType>
int LinkList<ElemType>::SetElem(int position, const ElemType &e)
{
  // 操作结果：设置第pos个位置的结点的元素值
  // position的合理性判断
  if (position < 1 || position > Length())
  {
    return RANGE_ERROR;
  }
  else
  {
    Node<ElemType> *tmpPtr = GetElemPtr(position);
    tmpPtr->data = e;
    return SUCCESS;
  }
}

template <class ElemType>
int LinkList<ElemType>::Delete(int position, ElemType &e)
{
  // 操作结果：删除线性表第position个位置的元素，并用e返回其值
  // position的取值范围为1<=position<=Length()=count
  // position合法时函数返回SUCESS，否则返回RANGE_ERROR
  if (position < 1 || position > count)
  {
    // position范围错
    return RANGE_ERROR;
  }
  else
  {
    // position合法
    Node<ElemType> *tmpPtr;                 // 临时结点指针，用来存储第position-1个结点
    tmpPtr = GetElemPtr(position - 1);      // GetElem从1开始取结点元素,tmpPtr指向待删除结点的前一个结点
    Node<ElemType> *nextPtr = tmpPtr->next; // 待删除结点的下一个结点
    tmpPtr->next = nextPtr->next;
    e = nextPtr->data;
    if (position == count)
    {
      // 删除尾结点，当前结点变为头结点
      curPosition = 0; // 设置当前位置的序号
      curPtr = head;   // 设置指向当前位置的指针
    }
    else
    {
      // 删除非尾结点，当前结点变为第position个结点
      curPosition = position; // 设置当前位置的序号
      curPtr = tmpPtr->next;  // 设置指向当前位置的指针
    }
    count--;
    // 关键一步：在释放nextPtr指向结点内存空间前，先把它的全部指针域置空
    nextPtr->next = NULL; // 记住这个坑！
    delete nextPtr;       // 释放被删结点
    nextPtr = NULL;
    return SUCCESS;
  }
}

template <class ElemType>
int LinkList<ElemType>::Insert(int position, const ElemType &e)
{
  // 操作结果；在线性表的第position个位置前插入元素e
  // position和取值范围为1<=position<=Length()+1=count+1
  // position合法时返回SUCCESS，否则函数返回RANGE_ERROR
  if (position < 1 || position > count + 1)
  {
    // position范围错
    return RANGE_ERROR;
  }
  else
  {
    // position合法
    Node<ElemType> *tmpPtr;
    tmpPtr = GetElemPtr(position - 1); // 取出指向第position-1个结点的指针
    Node<ElemType> *newPtr;
    newPtr = new Node<ElemType>(e, tmpPtr->next); // 生成新结点
    tmpPtr->next = newPtr;                        // 将tmpPtr插入到链表中
    curPosition = position;                       // 设置当前位置的序号
    curPtr = newPtr;                              // 设置指向当前位置的指针
    count++;                                      // 插入成功后将元素个数加1
    return SUCCESS;
  }
}

template <class ElemType>
LinkList<ElemType>::LinkList(const LinkList<ElemType> &copy)
{
  // 操作结果： 复制构造函数，从无到有
  // 一开始没有这个对象，重新申请空间构造一个与之前对象完全不同内存空间的对象
  head = new Node<ElemType>;
  curPosition = 0;
  curPtr = head;
  count = 0;
  ElemType tmp;
  for (int pos = 1; pos <= copy.count; pos++)
  {
    // 遍历线性表copy，将其每个元素插入到本表
    copy.GetElem(pos, tmp);
    Insert(pos, tmp);
  }
}

template <class ElemType>
LinkList<ElemType> &LinkList<ElemType>::operator=(LinkList<ElemType> &copy)
{
  // 操作结果：赋值运算符重载，从老到新
  // 一开始已经有了对象this，要检查自赋值并清空原线性表，仍需重新申请空间构造与之前完全不同的内存位置的表
  if (&copy != this)
  {
    // 非自赋值
    Clear(); // 清空当前表，原有内存空间全被释放，需重新申请
    ElemType tmp;
    for (int pos = 1; pos <= copy.count; pos++)
    {
      // 遍历线性表copy，将其每个元素插入到本表
      copy.GetElem(pos, tmp);
      Insert(pos, tmp);
    }
  }
  return *this;
}

template <class ElemType>
std::ostream &operator<<(std::ostream &os, LinkList<ElemType> &list)
{
  // 操作结果：遍历输出LinkList元素
  ElemType e;
  for (int i = 0; i < list.Length(); i++)
  {
    list.GetElem(i, e);
    os << e;
  }
  return os;
}

#endif // LINK_LIST_H