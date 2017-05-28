#ifndef BIN_TREE_NODE_H
#define BIN_TREE_NODE_H

#include <stddef.h>

// 二叉树结点类，链表实现
template <class ElemType>
class BinTreeNode
{
public:
  //数据成员
  ElemType data;                     //数据域
  BinTreeNode<ElemType> *leftChild;  //左孩子指针域
  BinTreeNode<ElemType> *rightChild; //右孩子指针域

  BinTreeNode();                                                                                                //无参构造
  BinTreeNode(const ElemType &val, BinTreeNode<ElemType> *lChild = NULL, BinTreeNode<ElemType> *rChild = NULL); //已知元素值和指向左右孩子的指针构造一个结点
};

template <class ElemType>
BinTreeNode<ElemType>::BinTreeNode()
{
  //构造一个叶节点
  leftChild = rightChild = NULL; //叶节点左右孩子为空
}

template <class ElemType>
BinTreeNode<ElemType>::BinTreeNode(const ElemType &val, BinTreeNode<ElemType> *lChild, BinTreeNode<ElemType> *rChild)
{
  //构造一个数据域为val，左孩子为lChild，右孩子为rChild的结点
  data = val;
  leftChild = lChild;
  rightChild = rChild;
}

#endif // BIN_TREE_NODE_H
