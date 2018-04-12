#include "Node.h"

template <class ElemType>
Node<ElemType>::Node()
{
    // 操作结果：创建空结点
    next = NULL;
}

template <class ElemType>
Node<ElemType>::Node(ElemType item, Node<ElemType> *link)
{
    // 操作结果：创建实际结点
    data = item;
    next = link;
}

template <class ElemType>
Node<ElemType>::~Node()
{
    // 操作结果：析构函数，释放指针域
    // next->next = NULL;
    delete next;
}