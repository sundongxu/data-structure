#ifndef SIMPLE_LINKLIST_H
#define SIMPLE_LINKLIST_H

#include <stddef.h>
#include "Constant.h"
#include "Node.h"

// 简单线性链表表类
template <class ElemType>
class SimpleLinkList
{
public:
  // 抽象数据类型方法声明及重载编译系统默认方法声明
  SimpleLinkList();                                                          // 构造函数
  virtual ~SimpleLinkList();                                                 // 析构函数
  int Length() const;                                                        // 返回链表节点个数（注意考虑头结点嘛？）
  bool Empty() const;                                                        // 判空
  void Clear();                                                              // 清空链表
  void Traverse(void (*Visit)(ElemType));                                    // 遍历节点
  int GetElem(int position, ElemType &e) const;                              // 返回指定位置节点的数据域
  int SetElem(int position, const ElemType &e);                              // 设置指定位置节点的数据域
  int Insert(int position, const ElemType &e);                               // 在position位置插入数据域为e的新节点
  int Delete(int position, ElemType &e);                                     // 删除
  SimpleLinkList(const SimpleLinkList<ElemType> &copy);                      // 复制构造
  SimpleLinkList<ElemType> &operator=(const SimpleLinkList<ElemType> &copy); // 赋值运算符重载，返回值必须是本类对象的引用
  Node<ElemType> *GetElemPtr(int position) const;                            // 返回指向第position个节点的指针

protected:
  // 链表实现的数据成员
  Node<ElemType> *head; // 头结点指针，注意头结点并没有数据域

  // 辅助函数
  void Init(); // 初始化线性表

private:
};

template <class ElemType>
Node<ElemType> *SimpleLinkList<ElemType>::GetElemPtr(int position) const
{
  // 操作结果：返回指向第position个结点的指针
  // 从头结点开始遍历，然后计数
  Node<ElemType> *tmpPtr = head;
  int curPosition = 0; // 头结点开始，无数据域

  while (tmpPtr != NULL && curPosition < position)
  {
    tmpPtr = tmpPtr->next;
    curPosition++;
  }
  if (tmpPtr != NULL && curPosition == position)
  {
    return tmpPtr;
  }
  else
  {
    // 当然是有可能失败的
    return NULL;
  }
}

template <class ElemType>
void SimpleLinkList<ElemType>::Init()
{
  // 操作结果：初始化简单线性表，创建头结点(无数据域)
  head = new Node<ElemType>; // 构造头指针（头结点）
}

template <class ElemType>
SimpleLinkList<ElemType>::SimpleLinkList()
{
  // 操作结果：创建空链表
  Init();
}

template <class ElemType>
SimpleLinkList<ElemType>::~SimpleLinkList()
{
  // 操作结果：析构函数，待释放的存储空间包括数据节点和头结点
  Clear();           // 释放非头结点空间
  head->next = NULL; // 这步很关键
  delete head;       // 释放头结点空间
}

template <class ElemType>
int SimpleLinkList<ElemType>::Length() const
{
  // 操作结果：统计链表结点总个数，头指针（头结点）head不算
  int count = 0;
  for (Node<ElemType> *tmpPtr = head->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
  {
    count++;
  }
  return count;
}

template <class ElemType>
bool SimpleLinkList<ElemType>::Empty() const
{
  // 操作结果：判断链表是否为空，从头指针（结点）的下一个开始判断）
  return head->next == NULL;
}

template <class ElemType>
void SimpleLinkList<ElemType>::Clear()
{
  // 操作结果：清空简单线性表，只留下头结点
  // 释放数据结点空间，不管头结点
  // 只要链表非空就不断删除其第1个结点
  ElemType tmpItem;
  while (Length() > 0)
  {
    Delete(1, tmpItem);
  }
}

template <class ElemType>
void SimpleLinkList<ElemType>::Traverse(void (*Visit)(ElemType))
{
  // 操作结果：遍历简单线性表
  for (Node<ElemType> *tmpPtr = head->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
  {
    (*Visit)(tmpPtr->data);
  }
}

template <class ElemType>
int SimpleLinkList<ElemType>::GetElem(int position, ElemType &e) const
{
  // 操作结果：e返回第position个位置的结点的数据域
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
int SimpleLinkList<ElemType>::SetElem(int position, const ElemType &e)
{
  // 操作结果：设置第position个位置的结点数据域为e
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
int SimpleLinkList<ElemType>::Insert(int position, const ElemType &e)
{
  // 操作结果：在第position个位置插入数据域为e的新结点
  // position的合理性判断
  if (position < 1 || position > Length() + 1)
  {
    return RANGE_ERROR;
  }
  else
  {
    Node<ElemType> *tmpPtr = GetElemPtr(position - 1); //这个地方重点注意下！！！
    Node<ElemType> *newPtr = new Node<ElemType>(e, tmpPtr->next);
    tmpPtr->next = newPtr;
    return SUCCESS;
  }
}

template <class ElemType>
int SimpleLinkList<ElemType>::Delete(int position, ElemType &e)
{
  // 操作结果：删除第position个位置的结点，用e返回被删结点的数据域
  // position的合理性判断
  if (position < 1 || position > Length())
  {
    return RANGE_ERROR;
  }
  else
  {
    // 做到两点：改变连接关系 + 释放节点指针域
    Node<ElemType> *tmpPtr = GetElemPtr(position - 1); // 获取待删除的结点的前一个结点
    Node<ElemType> *nextPtr = tmpPtr->next;            // 真正要删除的结点

    tmpPtr->next = nextPtr->next;
    e = nextPtr->data;

    nextPtr->next = NULL; // 这一步非常关键，为什么？

    delete nextPtr;
    return SUCCESS;
  }
}

template <class ElemType>
SimpleLinkList<ElemType>::SimpleLinkList(const SimpleLinkList<ElemType> &copy)
{
  // 操作结果：复制构造，从无到有
  head = new Node<ElemType>; // 头指针空间申请
  int copyLength = copy.Length();
  ElemType tmp;
  for (int curPosition = 1; curPosition <= copyLength; curPosition++)
  {
    copy.GetElem(curPosition, tmp);
    Insert(Length() + 1, tmp);
  }
}

template <class ElemType>
SimpleLinkList<ElemType> &SimpleLinkList<ElemType>::operator=(const SimpleLinkList<ElemType> &copy)
{
  // 操作结果：赋值运算符重载，从老到新
  if (&copy != this)
  {
    int copyLength = copy.Length();
    ElemType tmp;
    Clear();
    for (int curPosition = 1; curPosition <= copyLength; curPosition++)
    {
      copy.GetElem(curPosition, tmp);
      Insert(Length() + 1, tmp);
    }
  }
  return *this;
}

#endif // SIMPLE_LINKLIST_H
