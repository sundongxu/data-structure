#ifndef LINK_STACK_H
#define LINK_STACK_H

#include "Node.h"
#include "Constant.h"
#include "Utils.h"

// 链式栈类
template <class ElemType>
class LinkStack
{
protected:
  // 链式栈实现的数据成员
  Node<ElemType> *top; // 栈顶指针

  // 辅助函数
  void Init(); // 初始化栈

public:
  // 抽象数据类型方法声明及重载编译系统默认方法声明
  LinkStack();                                                     // 无参数的构造函数
  virtual ~LinkStack();                                            // 析构函数
  int Length() const;                                              // 返回栈长度
  bool Empty() const;                                              // 判断栈是否为空
  void Clear();                                                    // 清空栈
  void Traverse(void (*Visit)(ElemType &));                        // 遍历栈
  int Push(const ElemType &e);                                     // 入栈
  int Top(ElemType &e) const;                                      // 返回栈顶元素
  int Pop(ElemType &e);                                            // 出栈
  LinkStack(const LinkStack<ElemType> &copy);                      // 复制构造函数
  LinkStack<ElemType> &operator=(const LinkStack<ElemType> &copy); // 赋值运算符重载
};

#endif // LINK_STACK_H