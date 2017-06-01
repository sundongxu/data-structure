#ifndef LINK_STACK_H
#define LINK_STACK_H

#include <stddef.h>
#include "Constant.h"
#include "Node.h"

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

template <class ElemType>
void LinkStack<ElemType>::Init()
{
  // 操作结果：初始化栈
  top = NULL;
}

template <class ElemType>
LinkStack<ElemType>::LinkStack()
{
  // 操作结果：构造一个空栈
  Init();
}

template <class ElemType>
LinkStack<ElemType>::~LinkStack()
{
  // 操作结果：销毁栈
  Clear();
}

template <class ElemType>
int LinkStack<ElemType>::Length() const
{
  // 操作结果：返回栈元素个数
  int count = 0; //计数器
  for (Node<ElemType> *tmpPtr = top; tmpPtr != NULL; tmpPtr = tmpPtr->next)
  {
    // 用tmpPtr依次指向每个元素
    count++; // 对栈内每个元素进行计数
  }
  return count;
}

template <class ElemType>
bool LinkStack<ElemType>::Empty() const
{
  // 操作结果：如栈为空，返回true，否则返回false
  return top == NULL;
}

template <class ElemType>
void LinkStack<ElemType>::Clear()
{
  // 操作结果：清空栈
  ElemType tmpElem; // 临时元素值，实际好像也没什么用
  while (!Empty())
  {
    Pop(tmpElem);
  }
}

template <class ElemType>
void LinkStack<ElemType>::Traverse(void (*Visit)(ElemType &))
{
  // 操作结果：从栈底到栈顶依次对栈的每个元素调用函数（*Visit）
  Node<ElemType> *tmpPtr;
  LinkStack<ElemType> tmpS; // 临时栈，tmpS中元素顺序与当前栈元素顺序相反
  for (tmpPtr = top; tmpPtr != NULL; tmpPtr = tmpPtr->next)
  {
    // 用tmpPtr依次指向当前栈的每个元素
    tmpS.Push(tmpPtr->data); // 对当前栈的每个元素入栈到临时栈tmpS中
  }

  for (tmpPtr = tmpS.top; tmpPtr != NULL; tmpPtr = tmpPtr->next)
  {
    // 用tmpPtr从栈顶到栈底依次指向临时栈tmpS的每个元素
    (*Visit)(tmpPtr->data); // 对临时栈的每个元素调用Visit函数
  }
}

template <class ElemType>
int LinkStack<ElemType>::Push(const ElemType &e)
{
  // 操作结果：将元素e追加到栈顶，如成功则返回SUCCESS，否则如动态内存好近将返回OVER_FLOW
  Node<ElemType> *new_top = new Node<ElemType>(e, top); // 两个元素依次是data和next指针
  if (new_top == NULL)
  {
    // 动态内存耗尽，申请空间失败
    return OVER_FLOW;
  }
  else
  {
    // 申请成功
    top = new_top;
    return SUCCESS;
  }
}

template <class ElemType>
int LinkStack<ElemType>::Top(ElemType &e) const
{
  // 操作结果：如栈非空，用e返回栈顶元素，函数返回SUCCESS，否则函数返回UNDER_FLOW
  if (Empty())
  {
    // 栈空
    return UNDER_FLOW;
  }
  else
  {
    // 栈非空，操作成功
    e = top->data; // 用e返回栈顶元素
    return SUCCESS;
  }
}

template <class ElemType>
int LinkStack<ElemType>::Pop(ElemType &e)
{
  // 操作结果：如栈非空，删除栈顶元素，并用e返回栈顶元素，函数返回SUCCESS，否则函数返回UNDER_FLOW
  if (Empty())
  {
    // 栈空
    return UNDER_FLOW;
  }
  else
  {
    // 栈非空，操作成功
    Node<ElemType> *old_top = top; // 旧栈顶
    e = old_top->data;             // 用e返回栈顶元素
                                   //        top = top->next;               // top指向新栈顶
    top = top->next;
    old_top->next = NULL; // 神来之笔!!!
    delete old_top;       // 删除旧栈顶
    return SUCCESS;
  }
}

template <class ElemType>
LinkStack<ElemType>::LinkStack(const LinkStack<ElemType> &copy)
{
  // 操作结果：由栈copy构造新栈——————复制构造函数
  if (copy.Empty())
  {
    Init(); //copy为空，构造空栈
  }
  else
  {
    // copy非空，复制整个栈空间
    top = new Node<ElemType>(copy.top->data); // 当前栈顶指针
    Node<ElemType> *buttomPtr = top;          // 当前栈底指针
    for (Node<ElemType> *tmpPtr = copy.top->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
    {
      // 用tmpPtr依次指向旧栈的各个元素
      buttomPtr->next = new Node<ElemType>(tmpPtr->data); // 新建数据域与旧栈中对应位置的数据域相同的元素追加到新栈栈底
      buttomPtr = buttomPtr->next;                        // 不断下移栈底指针使其始终指向新栈底
    }
  }
}

template <class ElemType>
LinkStack<ElemType> &LinkStack<ElemType>::operator=(const LinkStack<ElemType> &copy)
{
  // 操作结果：将栈copy赋值给当前栈——————赋值运算符重载
  if (&copy != this)
  {
    if (copy.Empty())
    {
      // copy为空，构造一空栈
      Clear(); // 先清空当前栈
      Init();  // 当前栈构造为空栈
    }
    else
    {
      // copy非空，复制栈
      Clear(); // 清空当前栈
      top = new Node<ElemType>(copy.top->data);
      Node<ElemType> *buttomPtr = top; // 当前栈底指针
      for (Node<ElemType> *tmpPtr = copy.top->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
      {
        // 用tmpPtr依次指向旧栈的各个元素
        buttomPtr->next = new Node<ElemType>(tmpPtr->data); // 新建数据域与旧栈中对应位置的数据域相同的元素追加到新栈栈底
        buttomPtr = buttomPtr->next;                        // 不断下移栈底指针使其始终指向新栈底
      }
    }
  }
  return *this;
}

#endif // LINK_STACK_H