#ifndef LINK_LIST_H
#define LINK_LIST_H

#include <iostream>
#include "Constant.h"
#include "Node.h"

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

  template <class T>
  friend std::ostream &operator<<(std::ostream &os, LinkList<T> &ll);
};
#endif // LINK_LIST_H