#ifndef SQ_BIN_TREE_NODE_H
#define SQ_BIN_TREE_NODE_H

#include "SqBinTreeNodeTagType.h"

// 顺序二叉树结点类
template <class ElemType>
class SqBinTreeNode
{
public:
  // 数据成员
  ElemType val;             // 数据域
  SqBinTreeNodeTagType tag; // 结点使用标志

  SqBinTreeNode();                                                    // 无参构造函数
  SqBinTreeNode(ElemType item, SqBinTreeNodeTagType tg = EMPTY_NODE); // 已知数据域和使用标志构造结点

protected:
private:
};

#endif // SQ_BIN_TREE_NODE_H
