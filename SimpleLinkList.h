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
};

#endif // SIMPLE_LINKLIST_H
