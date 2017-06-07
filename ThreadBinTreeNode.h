#ifndef THREAD_BIN_TREE_NODE_H
#define THREAD_BIN_TREE_NODE_H

#include <stddef.h>

enum PointerTagType
{
  CHILD_PTR,
  THREAD_PTR
};
// 指针标志类型，CHILD_PTR(0):指向孩子的THREAD_PTR(1):指向线索的指针

// 线索二叉树结点类
template <class ElemType>
class ThreadBinTreeNode
{
public:
  // 数据成员：
  ElemType data;                           // 数据域
  ThreadBinTreeNode<ElemType> *lefChild;   // 左孩子指针域
  ThreadBinTreeNode<ElemType> *rightChild; // 右孩子指针域
  PointerTagType leftTag, rightTag;        // 左右标志域

  // 构造函数：
  ThreadBinTreeNode(); // 无参构造函数
  ThreadBinTreeNode(const ElemType &val, ThreadBinTreeNode<ElemType> *lChild = NULL, ThreadBinTreeNode<ElemType> *rChild = NULL,
                    PointerTagType leftTag = CHILD_PTR, PointerTagType rightTag = CHILD_PTR);
};

#endif // THREAD_BIN_TREE_NODE_H