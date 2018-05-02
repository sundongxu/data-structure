#ifndef IN_THREAD_BIN_TREE_H
#define IN_THREAD_BIN_TREE_H

#include "ThreadBinTreeNode.h"
#include "BinTreeNode.h"
#include "BinTree.h"

// 中序线索二叉树类
template <class ElemType>
class InThreadBinTree
{
  protected:
    // 线索二叉树的数据成员：
    ThreadBinTreeNode<ElemType> *root;

    // 辅助函数：
    void InThreadHelp(ThreadBinTreeNode<ElemType> *cur, ThreadBinTreeNode<ElemType> *&pre); // 中序线索化以cur为根的二叉树
    ThreadBinTreeNode<ElemType> *TransformHelp(BinTreeNode<ElemType> *r);
    // 以r为根的二叉树转换成新的未线索化的中序线索二叉树，返回新二叉树的根
    ThreadBinTreeNode<ElemType> *CopyTreeHelp(ThreadBinTreeNode<ElemType> *copy); // 复制线索二叉树
    void DestroyHelp(ThreadBinTreeNode<ElemType> *&r);                            // 销毁以r为根的二叉树

  public:
    // 线索二叉树方法声明及重载编译系统默认方法声明：
    InThreadBinTree(const BinTree<ElemType> &br);                                // 由二叉树构造中序线索二叉树——转换构造函数
    virtual ~InThreadBinTree();                                                  // 析构函数
    ThreadBinTreeNode<ElemType> *GetRoot() const;                                // 返回线索二叉树的根
    void InThread();                                                             // 中序线索化二叉树
    void InOrder(void (*Visit)(ElemType &));                                     // 二叉树的中序遍历
    InThreadBinTree(const InThreadBinTree<ElemType> &copy);                      // 复制构造函数
    InThreadBinTree<ElemType> &operator=(const InThreadBinTree<ElemType> &copy); // 赋值运算符重载
};

template <class ElemType>
void InThreadBinTree<ElemType>::InThreadHelp(ThreadBinTreeNode<ElemType> *cur, ThreadBinTreeNode<ElemType> *&pre)
{
    // 操作结果：中序线索化以cur为根的二叉树，pre表示cur的前驱
    if (cur != nullptr)
    {
        // 按中序遍历方式进行线索化
        if (cur->leftTag == CHILD_PTR)
        {
            InThreadHelp(cur->leftChild, pre); // 线索化左子树
        }

        if (cur->leftChild == nullptr)
        {
            // cur无左孩子，加线索
            cur->leftChild = pre;      // cur前驱为pre
            cur->leftTag = THREAD_PTR; // 线索标志
        }
        else
        {
            // cur有左孩子，修改标志，可省去，leftTag默认为CHILD_PTR
            cur->leftTag = CHILD_PTR; // 孩子指针标志
        }

        if (pre != nullptr && pre->rightChild == nullptr)
        {
            // pre无右孩子，加线索
            pre->rightChild = cur;      // pre后继为cur
            pre->rightTag = THREAD_PTR; // 线索标志
        }
        else if (pre != nullptr)
        {
            // cur有右孩子，修改标志，可省去，rightTag默认为CHILD_TAG
            pre->rightTag = CHILD_PTR; // 孩子指针标志
        }
        pre = cur; // 遍历下一结点时，cur为下一结点的前驱

        if (cur->rightTag == CHILD_PTR)
        {
            InThreadHelp(cur->rightChild, pre); // 线索化右子树
        }
    }
}

template <class ElemType>
ThreadBinTreeNode<ElemType> *InThreadBinTree<ElemType>::TransformHelp(BinTreeNode<ElemType> *r)
{
    // 操作结果：以r为根的二叉树转换成新的未线索化的中序线索二叉树，返回新二叉树的根
}

template <class ElemType>
ThreadBinTreeNode<ElemType> *CopyTreeHelp(ThreadBinTreeNode<ElemType> *copy)
{
    // 操作结果：复制线索二叉树
}

template <class ElemType>
void InThreadBinTree<ElemType>::DestroyHelp(ThreadBinTreeNode<ElemType> *&r)
{
    // 操作结果：销毁以r为根的二叉树
}

template <class ElemType>
InThreadBinTree<ElemType>::InThreadBinTree(const BinTree<ElemType> &br)
{
    // 操作结果：由二叉树构造中序线索二叉树——转换构造函数
}

template <class ElemType>
InThreadBinTree<ElemType>::~InThreadBinTree()
{
    // 操作结果：析构函数
    DestroyHelp(root);
}

template <class ElemType>
ThreadBinTreeNode<ElemType> *InThreadBinTree<ElemType>::GetRoot() const
{
    // 操作结果：返回线索二叉树的根
}

template <class ElemType>
void InThreadBinTree<ElemType>::InThread()
{
    // 操作结果：中序线索化二叉树
    ThreadBinTreeNode<ElemType> *pre = nullptr; // 开始线索化时前驱为空
    InThreadHelp(root, pre);                 // 中序线索化以root为根的二叉树
    if (pre->rightChild == nullptr)
    {
        // pre为中序序列中最后一个结点
        pre->rightTag = THREAD_PTR; // 如无右孩子，则加线索标记
    }
}

template <class ElemType>
void InThreadBinTree<ElemType>::InOrder(void (*Visit)(ElemType &))
{
    // 操作结果：二叉树的中序遍历
    if (root != nullptr)
    {
        ThreadBinTreeNode<ElemType> *cur = root; // 从根开始遍历
        while (cur->leftTag == CHILD_PTR)        // 查找最左侧的结点，此结点为中序序列的第一个结点
        {
            cur = cur->leftChild;
        }
        while (cur != nullptr)
        {
            (*Visit)(cur->data); // 访问当前结点
            if (cur->rightTag == THREAD_PTR)
            {
                // 右链域为线索，后继为cur->rightChild
                cur = cur->rightChild;
            }
            else
            {
                // 右链域为孩子，cur右子树最左侧的结点为后继
                cur = cur->rightChild; // cur指向右孩子
                while (cur->leftTag == CHILD_PTR)
                {
                    cur = cur->leftChild; // 查找原cur右子树最左侧的结点
                }
            }
        }
    }
}

template <class ElemType>
InThreadBinTree<ElemType>::InThreadBinTree(const InThreadBinTree<ElemType> &copy)
{
    // 操作结果：复制构造函数
}

template <class ElemType>
InThreadBinTree<ElemType> &InThreadBinTree<ElemType>::operator=(const InThreadBinTree<ElemType> &copy)
{
    // 操作结果：赋值运算符重载
}

#endif // IN_THREAD_BIN_TREE_H