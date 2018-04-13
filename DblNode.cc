#include "DblNode.h"

// 双向链表结点类的实现部分
template <class ElemType>
DblNode<ElemType>::DblNode()
{
    // 操作结果：构造指针域为空的结点
    back = nullptr;
    next = nullptr;
}

template <class ElemType>
DblNode<ElemType>::DblNode(ElemType item, DblNode<ElemType> *linkBack, DblNode<ElemType> *linkNext)
{
    // 操作结果：构造一个数据域为item和指针域为linkBack和linkNext的结点
    data = item;
    back = linkBack;
    next = linkNext;
}

template <class ElemType>
DblNode<ElemType>::~DblNode()
{
    // 操作结果：析构函数，释放指针域
    delete back;
    delete next;
}