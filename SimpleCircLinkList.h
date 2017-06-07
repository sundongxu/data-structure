#ifndef SIMPLE_CIRC_LINK_LIST_H
#define SIMPLE_CIRC_LINK_LIST_H

#include "Constant.h"
#include "Node.h"

// 简单循环链表类
template <class ElemType>
class SimpleCircLinkList
{
  protected:
    // 循环链表实现的数据成员
    Node<ElemType> *head; // 头结点指针

    // 辅助函数
    Node<ElemType> *GetElemPtr(int position) const; // 返回指向第position个结点的指针
    void Init();                                    // 初始化线性表

  public:
    // 抽象数据类型方法声明及重载编译系统默认方法声明
    SimpleCircLinkList();                                                              // 无参数的构造函数
    virtual ~SimpleCircLinkList();                                                     // 析构函数
    int Length() const;                                                                // 求线性表长度
    bool Empty() const;                                                                // 判断线性表是否为空
    void Clear();                                                                      // 将线性表清空
    void Traverse(void (*Visit)(ElemType &));                                          // 遍历线性表
    int GetElem(int position, ElemType &e) const;                                      // 求指定位置的元素
    int SetElem(int position, const ElemType &e);                                      // 设置指定位置的元素值
    int Delete(int position, ElemType &e);                                             // 删除元素
    int Insert(int position, const ElemType &e);                                       // 插入元素
    SimpleCircLinkList(const SimpleCircLinkList<ElemType> &copy);                      // 复制构造函数
    SimpleCircLinkList<ElemType> &operator=(const SimpleCircLinkList<ElemType> &copy); // 赋值运算符重载
};

template <class ElemType>
Node<ElemType> *SimpleCircLinkList<ElemType>::GetElemPtr(int position) const
{
    // 操作结果：返回指向第position个结点的指针
    if (position == 0)
    {
        // 头结点的序号为0
        return head;
    }
    Node<ElemType> *tmpPtr = head->next; // 用tmpPtr遍历线性表以查找第position个结点
    int curPosition = 1;                 // tmpPtr所指结点的位置

    while (tmpPtr != head && curPosition < position)
    {
        // 顺时针向后查找，知道tmpPtr指向第position个结点
        tmpPtr = tmpPtr->next;
        curPosition++;
    }
    if (tmpPtr != head && curPosition == position)
    {
        // 查找成功
        return tmpPtr;
    }
    else
    {
        // 查找失败
        return NULL;
    }
}

template <class ElemType>
void SimpleCircLinkList<ElemType>::Init()
{
    // 操作结果：初始化线性表
    head = new Node<ElemType>; // 构造头指针
    head->next = head;         // 空循环链表的头结点后继为头结点本身
}

template <class ElemType>
SimpleCircLinkList<ElemType>::SimpleCircLinkList()
{
    // 操作结果：创建空链表
    Init();
}

template <class ElemType>
SimpleCircLinkList<ElemType>::~SimpleCircLinkList()
{
    // 操作结果：析构函数，待释放的存储空间包括数据节点和头结点
    Clear();           // 释放非头结点空间
    head->next = NULL; // 这步很关键啊！！！
    delete head;       // 释放头结点空间
}

template <class ElemType>
int SimpleCircLinkList<ElemType>::Length() const
{
    // 操作结果：返回线性表元素个数
    int count = 0; // 计数器
    for (Node<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
    {
        // 用tmpPtr依次指向每个元素
        count++; // 对线性表的每个元素进行计数
    }
    return count;
}

template <class ElemType>
bool SimpleCircLinkList<ElemType>::Empty() const
{
    // 操作结果：如线性表为空，则返回true，否则返回false
    return head->next == head;
}

template <class ElemType>
void SimpleCircLinkList<ElemType>::Clear()
{
    // 操作结果：清空线性表，只留下头结点
    // 释放数据结点空间，不管头结点
    // 只要链表非空就不断删除其第1个结点
    ElemType tmpItem;
    while (Length() > 0)
    {
        Delete(1, tmpItem);
    }
}

template <class ElemType>
void SimpleCircLinkList<ElemType>::Traverse(void (*Visit)(ElemType &))
{
    // 操作结果：依次对线性表的每个元素调用函数(*Visit)
    for (Node<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
    {
        // 用tmpPtr指向每个元素
        (*Visit)(tmpPtr->data); // 对线性表的每个元素调用(*Visit)
    }
}

template <class ElemType>
int SimpleCircLinkList<ElemType>::GetElem(int position, ElemType &e) const
{
    // 操作结果：e返回第position个位置的结点的数据域
    // position的合理性判断
    if (position < 1 || position > Length())
    {
        return NOT_PRESENT;
    }
    else
    {
        Node<ElemType> *tmpPtr = GetElemPtr(position);
        e = tmpPtr->data;
        return ENTRY_FOUND;
    }
}

template <class ElemType>
int SimpleCircLinkList<ElemType>::SetElem(int position, const ElemType &e)
{
    // 操作结果：设置第position个位置的结点数据域为e
    // position的合理性判断
    if (position < 1 || position > Length())
    {
        return RANGE_ERROR;
    }
    else
    {
        Node<ElemType> *tmpPtr = GetElemPtr(position);
        tmpPtr->data = e;
        return SUCCESS;
    }
}

template <class ElemType>
int SimpleCircLinkList<ElemType>::Insert(int position, const ElemType &e)
{
    // 操作结果：在第position个位置插入数据域为e的新结点
    // position的合理性判断
    if (position < 1 || position > Length() + 1)
    {
        return RANGE_ERROR;
    }
    else
    {
        Node<ElemType> *tmpPtr = GetElemPtr(position - 1); //这个地方重点注意下！！！
        Node<ElemType> *newPtr = new Node<ElemType>(e, tmpPtr->next);
        tmpPtr->next = newPtr;
        return SUCCESS;
    }
}

template <class ElemType>
int SimpleCircLinkList<ElemType>::Delete(int position, ElemType &e)
{
    // 操作结果：删除第position个位置的结点，用e返回被删结点的数据域
    // position的合理性判断
    if (position < 1 || position > Length())
    {
        return RANGE_ERROR;
    }
    else
    {
        // 做到两点：改变连接关系 + 释放节点指针域
        Node<ElemType> *tmpPtr = GetElemPtr(position - 1); // 获取待删除的结点的前一个结点
        Node<ElemType> *nextPtr = tmpPtr->next;            // 真正要删除的结点

        tmpPtr->next = nextPtr->next;
        e = nextPtr->data;

        nextPtr->next = NULL; // 这一步非常关键，为什么？

        delete nextPtr;
        return SUCCESS;
    }
}

template <class ElemType>
SimpleCircLinkList<ElemType>::SimpleCircLinkList(const SimpleCircLinkList<ElemType> &copy)
{
    // 操作结果：复制构造，从无到有
    head = new Node<ElemType>; // 头指针空间申请
    head->next = head;         // 完成Init()里面做的事情！
    int copyLength = copy.Length();
    ElemType tmp;
    for (int curPosition = 1; curPosition <= copyLength; curPosition++)
    {
        copy.GetElem(curPosition, tmp);
        Insert(Length() + 1, tmp);
    }
}

template <class ElemType>
SimpleCircLinkList<ElemType> &SimpleCircLinkList<ElemType>::operator=(const SimpleCircLinkList<ElemType> &copy)
{
    // 操作结果：赋值运算符重载，从老到新
    if (&copy != this)
    {
        int copyLength = copy.Length();
        ElemType tmp;
        Clear();
        for (int curPosition = 1; curPosition <= copyLength; curPosition++)
        {
            copy.GetElem(curPosition, tmp);
            Insert(Length() + 1, tmp);
        }
    }
    return *this;
}

#endif // SIMPLE_CIRC_LINK_LIST_H