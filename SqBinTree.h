#ifndef SQ_BIN_TREE_H
#define SQ_BIN_TREE_H

#include "SqBinTreeNode.h"
#include "BinTreeNode.h"

#define DEFAULT_SIZE 1

// 顺序二叉树类(数组)
template <class ElemType>
class SqBinTree
{

protected:
  // 二叉树的数据成员
  int maxSize;                    // 二叉树的最大结点个数
  SqBinTreeNode<ElemType> *elems; // 结点存储空间
  int root;                       // 二叉树的根

  // 辅助函数
  void DisplayBTWithTreeShapeHelp(int r, int level);    // 按树状显示以r为根的二叉树，level为层次数，可设根结点的层次数为1
  void DisplayBTWithTreeShape(SqBinTree<ElemType> &bt); // 树状形式显示二叉树
  // 已知二叉树的先序序列pre[preLeft..preRight]和中序序列in[inLeft..inRight]构造以r为树的二叉树
  void CreateSqBinTreeHelp(BinTreeNode<ElemType> *&r, ElemType pre[], ElemType in[], int preLeft, int preRight, int inLeft, int inRight);
  // 已知先序和中序序列构造二叉树
  SqBinTree<ElemType> &CreateSqBinTree(ElemType pre[], ElemType in[], int n);

public:
  // 二叉树方法声明及重载编译系统默认方法声明
  SqBinTree();
  virtual ~SqBinTree();
  int GetRoot() const;                                             // 返回二叉树的根
  bool NodeEmpty(int cur) const;                                   // 判断结点cur是否为空
  int GetItem(int cur, ElemType &e);                               // 返回结点cur的元素值
  int SetItem(int cur, const ElemType &e);                         // 将结点cur的元素值置为e
  bool Empty() const;                                              // 判断二叉树是否为空
  void InOrder(void (*Visit)(ElemType &));                         // 中序遍历
  void PreOrder(void (*Visit)(ElemType &));                        // 先序遍历
  void PostOrder(void (*Visit)(ElemType &));                       // 后序遍历
  void LevelOrder(void (*Visit)(ElemType &));                      // 层次遍历
  int NodeCount() const;                                           // 返回结点个数
  int LeftChild(const int cur) const;                              // 返回结点cur的左孩子结点
  int RightChild(const int cur) const;                             // 返回结点cur的右孩子结点
  int Parent(const int cur) const;                                 // 返回结点cur的双亲结点
  void InsertLeftChild(int cur);                                   // 插入左孩子
  void InsertRightChild(int cur);                                  // 插入右孩子
  void DeleteLeftChild(int cur);                                   // 删除左孩子
  void DeleteRightChild(int cur);                                  // 删除右孩子
  int Height() const;                                              // 求二叉树的高
  SqBinTree(const ElemType &e, int size = DEFAULT_SIZE);           // 建立以e为根的二叉树
  SqBinTree(const SqBinTree<ElemType> &copy);                      // 复制构造函数
  SqBinTree<ElemType> &operator=(const SqBinTree<ElemType> &copy); // 赋值运算符重载
};

#endif // SQ_BIN_TREE_H
