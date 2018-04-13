#ifndef DB_LINK_LIST_H
#define DB_LINK_LIST_H

#include "Constant.h"
#include "DblNode.h"

// 双向链表类
template <class ElemType>
class DbLinkList
{
protected:
  // 循环链表实现的数据成员：
  DblNode<ElemType> *head;           // 头结点指针
  mutable int curPosition;           // 当前位置序号
  mutable DblNode<ElemType> *curPtr; // 指向当前位置的指针
  int count;                         // 元素个数

  // 辅助函数：
  DblNode<ElemType> *GetElemPtr(int position) const; // 返回指向第position个结点的指针
  void Init();                                       // 初始化线性表

public:
  // 抽象数据类型方法声明及重载编译系统默认方法声明：
  DbLinkList();                                                      // 无参数的构造函数
  virtual ~DbLinkList();                                             // 析构函数
  int Length() const;                                                // 求线性表长度
  bool Empty() const;                                                // 判断线性表是否为空
  void Clear();                                                      // 将线性表清空
  void Traverse(void (*Visit)(ElemType &));                          // 遍历线性表
  int GetElem(int position, ElemType &e) const;                      // 求指定位置的元素
  int SetElem(int position, const ElemType &e);                      // 设置指定位置的元素值
  int Delete(int position, ElemType &e);                             // 删除元素
  int Insert(int position, const ElemType &e);                       // 插入元素
  DbLinkList(const DbLinkList<ElemType> &copy);                      // 复制构造函数
  DbLinkList<ElemType> &operator=(const DbLinkList<ElemType> &copy); // 赋值运算符重载
};

#endif // DB_LINK_LIST_H