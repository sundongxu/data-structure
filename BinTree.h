#ifndef BIN_TREE_H
#define BIN_TREE_H

#include <iostream>
#include "Constant.h"
#include "BinTreeNode.h"
#include "LinkQueue.h"

using namespace std;

// 二叉树类，链表实现
template <class ElemType>
class BinTree
{
protected:
  // 二叉树的数据成员
  BinTreeNode<ElemType> *root; // 树的根结点

  // 辅助函数
  void Init();                                                                                         // 初始化根结点
  BinTreeNode<ElemType> *CopyTreeHelp(BinTreeNode<ElemType> *copy);                                    // 复制二叉树
  void DestroyHelp(BinTreeNode<ElemType> *r);                                                          // 销毁以r为根结点的二叉树
  void PreOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(ElemType &));                              // 先序遍历
  void InOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(ElemType &));                               // 中序遍历
  void PostOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(ElemType &));                             // 后序遍历
  int HeightHelp(const BinTreeNode<ElemType> *r) const;                                                // 返回二叉树的高度
  int NodeCountHelp(const BinTreeNode<ElemType> *r) const;                                             // 返回二叉树的结点个数
  BinTreeNode<ElemType> *ParentHelp(BinTreeNode<ElemType> *r, const BinTreeNode<ElemType> *cur) const; // 返回cur的双亲

public:
  // 二叉树方法声明及重载编译系统默认方法声明
  BinTree();                                                                 // 构造函数
  virtual ~BinTree();                                                        // 析构函数
  BinTreeNode<ElemType> *GetRoot() const;                                    // 返回根结点
  bool Empty() const;                                                        // 判断二叉树是否为空
  bool IsLeaf(BinTreeNode<ElemType> *cur) const;                             // 判断是否为叶子结点
  int GetElem(BinTreeNode<ElemType> *cur, ElemType &e) const;                // 用e返回结点元素值
  int SetElem(BinTreeNode<ElemType> *cur, const ElemType &e);                // 将结点cur的元素值设为e
  void InOrder(void (*Visit)(ElemType &));                                   // 中序遍历
  void PreOrder(void (*Visit)(ElemType &));                                  // 先序遍历
  void PostOrder(void (*Visit)(ElemType &));                                 // 后序遍历
  void LevelOrder(void (*Visit)(ElemType &));                                // 层次遍历
  int NodeCount() const;                                                     // 返回二叉树的结点数
  BinTreeNode<ElemType> *LeftChild(const BinTreeNode<ElemType> *cur) const;  // 返回结点cur的左孩子
  BinTreeNode<ElemType> *RightChild(const BinTreeNode<ElemType> *cur) const; // 返回结点cur的右孩子
  BinTreeNode<ElemType> *Parent(const BinTreeNode<ElemType> *cur) const;     // 返回结点cur的双亲结点
  void InsertLeftChild(BinTreeNode<ElemType> *cur, const ElemType &e);       // 插入左孩子
  void InsertRightChild(BinTreeNode<ElemType> *cur, const ElemType &e);      // 插入右孩子
  void DeleteLeftChild(BinTreeNode<ElemType> *cur);                          // 删除左子树
  void DeleteRightChild(BinTreeNode<ElemType> *cur);                         // 删除右子树
  int Height() const;                                                        // 返回二叉树的高度
  BinTree(const ElemType &e);                                                // 构造以e为根结点元素值的二叉树
  BinTree(BinTreeNode<ElemType> *r);                                         // 构造以r为根结点的二叉树
  BinTree(const BinTree<ElemType> &copy);                                    // 复制构造
  BinTree<ElemType> &operator=(const BinTree<ElemType> &copy);               // 赋值运算符重载
};

template <class ElemType>
// 按树状形式显示以r为根的二叉树，level为层次数，可设根结点的层次数为1
void DisplayBTWithTreeShapeHelp(BinTreeNode<ElemType> *r, int level);

template <class ElemType>
void DisplayBTWithTreeShape(BinTree<ElemType> &bt); //以树状形式显示二叉树

template <class ElemType>
// 已知二叉树的先序序列pre[preLeft..preRight]和中序列in[inLeft..inRight]构造以r为树的二叉树
void CreateBinTreeHelp(BinTreeNode<ElemType> *&r, ElemType pre[], ElemType in[], int preLeft, int preRight, int inLeft,
                       int inRight);

template <class ElemType>
// 已知先序和中序序列构造二叉树
BinTree<ElemType> &CreateBinTree(ElemType pre[], ElemType in[], int n);

// 方法定义格式：
// 返回值类型 类名<模板指定数据类型> :: 方法名(参数1, 参数2, ...)
template <class ElemType>
void BinTree<ElemType>::Init()
{
  // 操作结果：初始化根结点
  root = new BinTreeNode<ElemType>;
}

template <class ElemType>
BinTree<ElemType>::BinTree()
{
  // 操作结果：构造一个空二叉树
  //    root = nullptr;
  Init();
}

template <class ElemType>
BinTree<ElemType>::~BinTree()
{
  // 操作结果：销毁二叉树——析构函数
  DestroyHelp(root);
}

template <class ElemType>
BinTreeNode<ElemType> *BinTree<ElemType>::GetRoot() const
{
  // 操作结果：返回二叉树的根结点
  return root;
}

template <class ElemType>
bool BinTree<ElemType>::Empty() const
{
  // 操作结果：判断二叉树是否为空
  return root == nullptr;
}

template <class ElemType>
bool BinTree<ElemType>::IsLeaf(BinTreeNode<ElemType> *cur) const
{
  // 操作结果：判断结点cur是否为叶结点
  return cur->leftChild == nullptr && cur->rightChild == nullptr;
}

template <class ElemType>
int BinTree<ElemType>::GetElem(BinTreeNode<ElemType> *cur, ElemType &e) const
{
  // 操作结果：用e返回结点元素值
  if (cur == nullptr)
  {
    // 结点为空，无数据域，即结点不存在
    return NOT_PRESENT;
  }
  else
  {
    e = cur->val;
    return ENTRY_FOUND;
  }
}

template <class ElemType>
int BinTree<ElemType>::SetElem(BinTreeNode<ElemType> *cur, const ElemType &e)
{
  // 操作结果：将结点cur数据域置为e
  if (cur == nullptr)
  {
    // 结点为空，即结点不存在（位置不对）
    return RANGE_ERROR;
  }
  else
  {
    cur->val = e;
    return SUCCESS;
  }
}

template <class ElemType>
void BinTree<ElemType>::PreOrder(void (*Visit)(ElemType &))
{
  // 操作结果：先序遍历二叉树
  PreOrderHelp(root, Visit);
}

template <class ElemType>
void BinTree<ElemType>::InOrder(void (*Visit)(ElemType &))
{
  // 操作结果：中序遍历二叉树
  InOrderHelp(root, Visit);
}

template <class ElemType>
void BinTree<ElemType>::PostOrder(void (*Visit)(ElemType &))
{
  // 操作结果：后序遍历二叉树
  PostOrderHelp(root, Visit);
}

template <class ElemType>
void BinTree<ElemType>::LevelOrder(void (*Visit)(ElemType &))
{
  // 操作结果：层次遍历以r为根的二叉树
  BinTreeNode<ElemType> *t = root;
  LinkQueue<BinTreeNode<ElemType> *> q;

  if (t != nullptr)
  {
    q.InQueue(t);
  }
  while (!q.Empty())
  {
    // q非空说明还有结点没被访问
    q.OutQueue(t);
    (*Visit)(t->val);
    if (t->leftChild != nullptr)
    {
      q.InQueue(t->leftChild);
    }
    if (t->rightChild != nullptr)
    {
      q.InQueue(t->rightChild);
    }
  }
}

template <class ElemType>
int BinTree<ElemType>::NodeCount() const
{
  // 操作结果：返回二叉树的结点个数
  return NodeCountHelp(root);
}

template <class ElemType>
BinTreeNode<ElemType> *BinTree<ElemType>::LeftChild(const BinTreeNode<ElemType> *cur) const
{
  // 操作结果：返回结点cur的左孩子
  return (cur == nullptr) ? nullptr : cur->leftChild;
}

template <class ElemType>
BinTreeNode<ElemType> *BinTree<ElemType>::RightChild(const BinTreeNode<ElemType> *cur) const
{
  // 操作结果：返回结点cur的右孩子
  return (cur == nullptr) ? nullptr : cur->rightChild;
}

template <class ElemType>
BinTreeNode<ElemType> *BinTree<ElemType>::Parent(const BinTreeNode<ElemType> *cur) const
{
  // 操作结果：返回结点cur的父结点
  return ParentHelp(root, cur);
}

template <class ElemType>
void BinTree<ElemType>::InsertLeftChild(BinTreeNode<ElemType> *cur, const ElemType &e)
{
  // 操作结点：在结点cur处插入元素值为e的左孩子结点
  if (cur != nullptr)
  {
    BinTreeNode<ElemType> *new_node = new BinTreeNode<ElemType>(e, nullptr, nullptr);
    if (new_node == nullptr)
    {
      // 开辟内存失败
      cout << "BinTree::InsertLeftChild()申请内存空间失败!" << endl;
      return;
    }
    if (cur->leftChild == nullptr)
    {
      // cur左孩子为空，直接插入
      cur->leftChild = new_node;
    }
    else
    {
      // cur左孩子非空，插入时将新结点作为cur的左子树的根，原来的左子树作为新结点的左子树
      new_node->leftChild = cur->leftChild;
      cur->leftChild = new_node;
    }
  }
}

template <class ElemType>
void BinTree<ElemType>::InsertRightChild(BinTreeNode<ElemType> *cur, const ElemType &e)
{
  // 操作结点：在结点cur处插入元素值为e的右孩子结点
  if (cur != nullptr)
  {
    BinTreeNode<ElemType> *new_node = new BinTreeNode<ElemType>(e, nullptr, nullptr);
    if (new_node == nullptr)
    {
      // 开辟内存失败
      cout << "BinTree::InsertRightChild()申请内存空间失败!" << endl;
      return;
    }
    if (cur->rightChild == nullptr)
    {
      // cur左孩子为空，直接插入
      cur->rightChild = new_node;
    }
    else
    {
      // cur左孩子非空，插入时将新结点作为cur的左子树的根，原来的左子树作为新结点的左子树
      new_node->rightChild = cur->rightChild;
      cur->rightChild = new_node;
    }
  }
}

template <class ElemType>
void BinTree<ElemType>::DeleteLeftChild(BinTreeNode<ElemType> *cur)
{
  // 操作结点：删除结点cur的左子树，调用DestroyHelp方法
  if (cur != nullptr)
  {
    BinTreeNode<ElemType> *leftChild = cur->leftChild;
    if (leftChild != nullptr)
    {
      DestroyHelp(cur->leftChild);  // 销毁cur的左子树
      DestroyHelp(cur->rightChild); // 销毁cur的右子树
      delete (leftChild);
      leftChild = nullptr;
    }
  }
}

template <class ElemType>
void BinTree<ElemType>::DeleteRightChild(BinTreeNode<ElemType> *cur)
{
  // 操作结点：删除结点cur的右子树，调用DestroyHelp方法
  if (cur != nullptr)
  {
    BinTreeNode<ElemType> *rightChild = cur->rightChild;
    if (rightChild != nullptr)
    {
      DestroyHelp(cur->leftChild);  // 销毁cur的左子树
      DestroyHelp(cur->rightChild); // 销毁cur的右子树
      delete (rightChild);
      rightChild = nullptr;
    }
  }
}

template <class ElemType>
int BinTree<ElemType>::Height() const
{
  // 操作结果：返回二叉树的高度
  return HeightHelp(root);
}

template <class ElemType>
BinTree<ElemType>::BinTree(const ElemType &e)
{
  // 操作结果：构造以e为根结点数据域的二叉树
  Init();
  root->val = e;
}

template <class ElemType>
BinTree<ElemType>::BinTree(BinTreeNode<ElemType> *r)
{
  // 操作结果：构造以r为根结点的二叉树
  root = r;
}

template <class ElemType>
BinTree<ElemType>::BinTree(const BinTree<ElemType> &copy)
{
  // 操作结果：由已知二叉树构造新二叉树—————复制构造函数
  CopyTreeHelp(copy.root);
}

template <class ElemType>
BinTree<ElemType> &BinTree<ElemType>::operator=(const BinTree<ElemType> &copy)
{
  // 操作结果：由已知二叉树复制到当前二叉树——————复制运算符重载
  if (&copy != this) // 已知二叉树与当前二叉树不一致
  {
    DestroyHelp(root);              // 释放原二叉树所占空间（应被赋值覆盖））
    root = CopyTreeHelp(copy.root); // 复制二叉树
  }
  return *this;
}

template <class ElemType>
BinTreeNode<ElemType> *BinTree<ElemType>::CopyTreeHelp(BinTreeNode<ElemType> *copy)
{
  // 操作结果：将以copy为根的二叉树复制成新的二叉树，返回新二叉树的根
  if (copy == nullptr)
  {
    return nullptr;
  }
  else
  {
    // 复制非空二叉树
    BinTreeNode<ElemType> *lChild = CopyTreeHelp(copy->leftChild);                   // 复制左子树，获取左子树的根
    BinTreeNode<ElemType> *rChild = CopyTreeHelp(copy->rightChild);                  // 复制右子树，获取右子树的根
    BinTreeNode<ElemType> *r = new BinTreeNode<ElemType>(copy->val, lChild, rChild); // 复制根结点
    return r;
  }
}

template <class ElemType>
void BinTree<ElemType>::DestroyHelp(BinTreeNode<ElemType> *r)
{
  // 操作结果：销毁以r为根的二叉树
  if (r != nullptr)
  {
    // r非空，实施销毁
    DestroyHelp(r->leftChild);
    DestroyHelp(r->rightChild);
    delete r;
    r = nullptr; // 先释放指针指向空间的内存，再将指针置空！！！
  }
}

// 先序、中序、后序遍历的递归实现
template <class ElemType>
void BinTree<ElemType>::PreOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(ElemType &))
{
  // 操作结果：先序遍历以r为根的二叉树
  if (r != nullptr)
  {
    (*Visit)(r->val);                   //访问根结点
    PreOrderHelp(r->leftChild, Visit);  // 递归访问左子树
    PreOrderHelp(r->rightChild, Visit); // 递归访问右子树
  }
}

template <class ElemType>
void BinTree<ElemType>::InOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(ElemType &))
{
  // 操作结果：中序遍历以r为根的二叉树
  if (r != nullptr)
  {
    InOrderHelp(r->leftChild, Visit);
    (*Visit)(r->val);
    InOrderHelp(r->rightChild, Visit);
  }
}

template <class ElemType>
void BinTree<ElemType>::PostOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(ElemType &))
{
  // 操作结果：后序遍历以r为根的二叉树
  if (r != nullptr)
  {
    PostOrderHelp(r->leftChild, Visit);
    PostOrderHelp(r->rightChild, Visit);
    (*Visit)(r->val);
  }
}

template <class ElemType>
int BinTree<ElemType>::HeightHelp(const BinTreeNode<ElemType> *r) const
{
  // 操作结果：返回以r为根的二叉树的高
  if (r == nullptr)
  {
    return 0;
  }
  else
  {
    // 非空二叉树的高为左右子树的高的最大值再加一
    int lHeight, rHeight;
    lHeight = HeightHelp(r->leftChild);
    rHeight = HeightHelp(r->rightChild);
    return 1 + (lHeight > rHeight ? lHeight : rHeight); // 高为左右子树的高的最大值再加一
  }
}

template <class ElemType>
int BinTree<ElemType>::NodeCountHelp(const BinTreeNode<ElemType> *r) const
{
  // 操作结果：返回以r为根的二叉树的结点个数
  if (r == nullptr)
  {
    return 0;
  }
  else
  {
    return 1 + NodeCountHelp(r->leftChild) + NodeCountHelp(r->rightChild);
    // 非空二叉树结点个数为左右子树的结点个数之和再加一（自己本身）
  }
}

template <class ElemType>
BinTreeNode<ElemType> *
BinTree<ElemType>::ParentHelp(BinTreeNode<ElemType> *r, const BinTreeNode<ElemType> *cur) const
{
  // 操作结点：在根为r的二叉树中找到结点cur的双亲结点，用递归
  BinTreeNode<ElemType> *tmpPtr = r; // 前驱指针
  if (r == nullptr || cur == nullptr)
  {
    // 树为空或参数为空
    return nullptr;
  }
  else
  {
    if (tmpPtr->leftChild == cur || tmpPtr->rightChild == cur)
    {
      // 找到cur的双亲结点即为tmpPtr
      return tmpPtr;
    }
    else
    {
      // tmpPtr不是cur的双亲结点，递归寻找
      BinTreeNode<ElemType> *lParent = ParentHelp(tmpPtr->leftChild, cur);
      BinTreeNode<ElemType> *rParent = ParentHelp(tmpPtr->rightChild, cur);
      return lParent ? lParent : (rParent ? rParent : nullptr);
    }
  }
}

template <class ElemType>
void DisplayBTWithTreeShapeHelp(BinTreeNode<ElemType> *r, int level)
{
  // 操作结果：按树状形式显示以r为根的二叉树，level为层次数，可设根结点的层次数为1
  if (r != nullptr)
  {
    // 空树不显示
    DisplayBTWithTreeShapeHelp<ElemType>(r->rightChild, level + 1);
    // 显示右子树
    cout << endl; // 显示新行
    for (int i = 0; i < level - 1; i++)
    {
      cout << " "; // 确保在第level列显示结点
    }
    cout << r->val;                                                // 显示结点
    DisplayBTWithTreeShapeHelp<ElemType>(r->leftChild, level + 1); // 显示左子树
  }
}

template <class ElemType>
void DisplayBTWithTreeShape(BinTree<ElemType> &bt)
{
  // 操作结果：树状形式显示二叉树
  DisplayBTWithTreeShapeHelp<ElemType>(bt.GetRoot(), 1);
  cout << endl;
}

template <class ElemType>
void CreateBinTreeHelp(BinTreeNode<ElemType> *&r, ElemType pre[], ElemType in[], int preLeft, int preRight, int inLeft,
                       int inRight)
{
  // 操作结果：已知二叉树的先序序列pre[preLeft,...,preRight]和中序序列in[inLeft,...,inRight]构造以r为根的二叉树
  if (inLeft > inRight)
  {
    // 二叉树无结点，空二叉树
    r = nullptr;
  }
  else
  {
    // 二叉树有结点，非空二叉树
    r = new BinTreeNode<ElemType>(pre[preLeft]); // 生成根结点
    int mid = inLeft;
    while (in[mid] != pre[preLeft])
    {
      // 查找pre[preLeft]在in[]中的位置，也就是中序序列中根的位置
      mid++;
    }
    CreateBinTreeHelp(r->leftChild, pre, in, preLeft + 1, preLeft + mid - inLeft, inLeft, mid - 1);    // 生成左子树
    CreateBinTreeHelp(r->rightChild, pre, in, preLeft + mid - inLeft + 1, preRight, mid + 1, inRight); // 生成右子树
  }
}

template <class ElemType>
BinTree<ElemType> &CreateBinTree(ElemType pre[], ElemType in[], int n)
{
  // 操作结果：已知先序序列和中序序列构造二叉树
  BinTreeNode<ElemType> *r;                                    // 二叉树的根
  CreateBinTreeHelp<ElemType>(r, pre, in, 0, n - 1, 0, n - 1); // 由先序序列和中序序列构造以r为根的二叉树
  BinTree<ElemType> *bt = new BinTree<ElemType>(r);            //生成二叉树
  return *bt;
}

#endif // BIN_TREE
