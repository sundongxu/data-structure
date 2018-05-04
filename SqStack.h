#ifndef SQ_STACK_H
#define SQ_STACK_H

#include "Constant.h"
#include "Utils.h"

// 顺序栈类
template <class ElemType>
class SqStack
{
protected:
  // 顺序栈的数据成员
  int count;       // 元素个数
  int maxSize;     // 栈最大元素个数
  ElemType *elems; // 元素存储空间

  // 辅助函数
  bool Full() const;   // 判断栈是否已满
  void Init(int size); // 初始化栈

public:
  // 抽象数据类型方法生命及重载编译系统默认方法声明
  SqStack(int size = DEFAULT_SIZE);                            // 构造函数
  virtual ~SqStack();                                          // 析构函数
  int Length() const;                                          // 栈长度
  bool Empty() const;                                          // 判断栈是否为空
  void Clear();                                                // 清空栈
  void Traverse(void (*Visit)(ElemType &));                    // 遍历栈
  int Push(const ElemType &e);                                 // 入栈
  int Top(ElemType &e) const;                                  // 返回栈顶元素
  int Pop(ElemType &e);                                        // 栈顶元素出栈
  SqStack(const SqStack<ElemType> &copy);                      // 复制构造函数
  SqStack<ElemType> &operator=(const SqStack<ElemType> &copy); // 赋值运算符重载
};

#endif // SQ_STACK_H