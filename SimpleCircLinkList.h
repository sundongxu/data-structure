#ifndef SIMPLE_CIRC_LINK_LIST_H
#define SIMPLE_CIRC_LINK_LIST_H

#include "Constant.h"
#include "Node.h"

// 简单循环链表类
template <class ElemType>
class SimpleCircLinkList
{
protected:
  // 循环链表实现的数据成员
  Node<ElemType> *head; // 头结点指针

  // 辅助函数
  Node<ElemType> *GetElemPtr(int position) const; // 返回指向第position个结点的指针
  void Init();                                    // 初始化线性表

public:
  // 抽象数据类型方法声明及重载编译系统默认方法声明
  SimpleCircLinkList();                                                              // 无参数的构造函数
  virtual ~SimpleCircLinkList();                                                     // 析构函数
  int Length() const;                                                                // 求线性表长度
  bool Empty() const;                                                                // 判断线性表是否为空
  void Clear();                                                                      // 将线性表清空
  void Traverse(void (*Visit)(ElemType &));                                          // 遍历线性表
  int GetElem(int position, ElemType &e) const;                                      // 求指定位置的元素
  int SetElem(int position, const ElemType &e);                                      // 设置指定位置的元素值
  int Delete(int position, ElemType &e);                                             // 删除元素
  int Insert(int position, const ElemType &e);                                       // 插入元素
  SimpleCircLinkList(const SimpleCircLinkList<ElemType> &copy);                      // 复制构造函数
  SimpleCircLinkList<ElemType> &operator=(const SimpleCircLinkList<ElemType> &copy); // 赋值运算符重载
};

#endif // SIMPLE_CIRC_LINK_LIST_H