#ifndef DBL_NODE_H
#define DBL_NODE_H

// 双向链表结点类
template <class ElemType>
class DblNode
{
  public:
    // 数据成员：
    ElemType data;           // 数据域
    DblNode<ElemType> *back; // 指向前驱的指针域
    DblNode<ElemType> *next; // 指向后继的指针域

    // 构造函数：
    DblNode();                                                                                            // 无数据的构造函数
    DblNode(ElemType item, DblNode<ElemType> *linkBack = nullptr, DblNode<ElemType> *linkNext = nullptr); // 已知数据域和指针域建立结构
    ~DblNode();
    // DblNode<ElemType> &operator=(const DblNode<ElemType> &copy);  // 重载赋值运算符                                                                          // 析构函数
};

#endif // DBL_NODE_H