#ifndef CIRC_LINK_LIST_H
#define CIRC_LINK_LIST_H

#include "Constant.h"
#include "Node.h"

// 循环链表类
template <class ElemType>
class CircLinkList
{
  protected:
    // 循环链表实现的数据成员
    Node<ElemType> *head;           // 头结点指针
    mutable int curPosition;        // 当前位置的序号
    mutable Node<ElemType> *curPtr; // 指向当前位置结点的指针
    int count;

    // 辅助函数
    Node<ElemType> *GetElemPtr(int position) const; // 返回指向第position个结点的指针
    void Init();                                    // 初始化线性表

  public:
    // 抽象数据类型方法声明及重载编译系统默认方法声明
    CircLinkList();                                                        // 无参数的构造函数
    virtual ~CircLinkList();                                               // 析构函数
    int Length() const;                                                    // 求线性表长度
    bool Empty() const;                                                    // 判断线性表是否为空
    void Clear();                                                          // 将线性表清空
    void Traverse(void (*Visit)(ElemType &));                              // 遍历线性表
    int GetElem(int position, ElemType &e) const;                          // 求指定位置的元素
    int SetElem(int position, const ElemType &e);                          // 设置指定位置的元素值
    int Delete(int position, ElemType &e);                                 // 删除元素
    int Insert(int position, const ElemType &e);                           // 插入元素
    CircLinkList(const CircLinkList<ElemType> &copy);                      // 复制构造函数
    CircLinkList<ElemType> &operator=(const CircLinkList<ElemType> &copy); // 赋值运算符重载
};

template <class ElemType>
Node<ElemType> *CircLinkList<ElemType>::GetElemPtr(int position) const
{
    // 操作结果：返回指向第position个结点的指针
    while (curPosition != position)
    {
        curPosition = (curPosition + 1) % (Length() + 1); // 序号在-0~Length()之间
        curPtr = curPtr->next;                            // curPtr指向后继
    }
    return curPtr;
}

template <class ElemType>
void CircLinkList<ElemType>::Init()
{
    // 操作结果：初始化线性表
    head = new Node<ElemType>; // 构造头指针
    head->next = head;         // 空循环链表的头结点后继为头结点本身
    curPosition = 0;           // 指向当前位置
    curPtr = head;             // 初始化当前位置结点指针
    count = 0;                 // 初始化元素个数
}

template <class ElemType>
CircLinkList<ElemType>::CircLinkList()
{
    // 操作结果：创建空链表
    Init();
}

template <class ElemType>
CircLinkList<ElemType>::~CircLinkList()
{
    // 操作结果：析构函数，待释放的存储空间包括数据节点和头结点
    Clear();           // 释放非头结点空间
    head->next = NULL; // 这步很关键啊！！！
    delete head;       // 释放头结点空间
}

template <class ElemType>
int CircLinkList<ElemType>::Length() const
{
    // 操作结果：返回线性表元素个数
    return count;
}

template <class ElemType>
bool CircLinkList<ElemType>::Empty() const
{
    // 操作结果：如线性表为空，则返回true，否则返回false
    return head->next == head;
}

template <class ElemType>
void CircLinkList<ElemType>::Clear()
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
void CircLinkList<ElemType>::Traverse(void (*Visit)(ElemType &))
{
    // 操作结果：依次对线性表的每个元素调用函数(*Visit)
    for (Node<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
    {
        // 用tmpPtr指向每个元素
        (*Visit)(tmpPtr->data); // 对线性表的每个元素调用(*Visit)
    }
}

template <class ElemType>
int CircLinkList<ElemType>::GetElem(int position, ElemType &e) const
{
    // 操作结果：e返回第position个位置的结点的数据域
    // position的合理性判断
    if (position < 1 || position > Length())
    {
        // 该位置不存在
        return NOT_PRESENT;
    }
    else
    {
        // 找到并返回元素数据域
        Node<ElemType> *tmpPtr = GetElemPtr(position);
        e = tmpPtr->data;
        return ENTRY_FOUND;
    }
}

template <class ElemType>
int CircLinkList<ElemType>::SetElem(int position, const ElemType &e)
{
    // 操作结果：设置第position个位置的结点数据域为e
    // position的合理性判断
    if (position < 1 || position > Length())
    {
        // position范围错
        return RANGE_ERROR;
    }
    else
    {
        // position合法
        Node<ElemType> *tmpPtr = GetElemPtr(position);
        tmpPtr->data = e;
        return SUCCESS;
    }
}

template <class ElemType>
int CircLinkList<ElemType>::Insert(int position, const ElemType &e)
{
    // 操作结果：在第position个位置插入数据域为e的新结点
    // position的合理性判断
    int len = Length();
    if (position < 1 || position > Length() + 1)
    {
        // position范围错
        return RANGE_ERROR;
    }
    else
    {
        // position合法
        Node<ElemType> *tmpPtr = GetElemPtr(position - 1); //这个地方重点注意下！！！
        Node<ElemType> *newPtr = new Node<ElemType>(e, tmpPtr->next);
        tmpPtr->next = newPtr;
        curPosition = position;
        curPtr = newPtr;
        count++;
        return SUCCESS;
    }
}

template <class ElemType>
int CircLinkList<ElemType>::Delete(int position, ElemType &e)
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
        if (position == Length())
        {
            // 删除尾结点，当前结点变为头结点
            curPosition = 0; // 设置当前位置的序号
            curPtr = head;   // 设置指向当前位置的指针
        }
        else
        {
            // 删除非尾结点，当前结点变为第position个结点
            curPosition = position; // 设置当前位置的序号
            curPtr = tmpPtr->next;  // 设置指向当前位置的指针
        }
        count--;

        nextPtr->next = NULL; // 这一步非常关键，为什么？
        delete nextPtr;
        return SUCCESS;
    }
}

template <class ElemType>
CircLinkList<ElemType>::CircLinkList(const CircLinkList<ElemType> &copy)
{
    // 操作结果：复制构造，从无到有
    int copyLength = copy.Length();
    head = new Node<ElemType>; // 头指针空间申请
    head->next = head;         // 完成Init()里面做的事情！
    curPosition = 0;           // 指向当前位置
    curPtr = head;             // 初始化当前位置结点指针
    count = 0;                 // 初始化元素个数
    ElemType tmp;
    for (int curPosition = 1; curPosition <= copyLength; curPosition++)
    {
        copy.GetElem(curPosition, tmp);
        Insert(Length() + 1, tmp);
    }
}

template <class ElemType>
CircLinkList<ElemType> &CircLinkList<ElemType>::operator=(const CircLinkList<ElemType> &copy)
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

#endif // CIRC_LINK_LIST_H