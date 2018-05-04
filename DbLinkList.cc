#include "DbLinkList.h"

// 双向链表类的实现部分
template <class ElemType>
DblNode<ElemType> *DbLinkList<ElemType>::GetElemPtr(int position) const
{
    // 操作结果：返回指向第position个结点的指针
    if (curPosition < position)
    {
        // 当前位置在所查找位置之前，向后查找
        for (; curPosition < position; curPosition++)
        {
            curPtr = curPtr->next; // 查找位置position
        }
    }
    else if (curPosition > position)
    {
        // 当前位置在所查找位置之后，向前查找
        for (; curPosition > position; curPosition--)
        {
            curPtr = curPtr->back; // 查找位置position
        }
    }
    return curPtr;
}

template <class ElemType>
void DbLinkList<ElemType>::Init()
{
    // 操作结果：初始化线性表
    head = new DblNode<ElemType>; // 构造头指针
    head->next = head;            // 空循环链表的头结点后继为头结点本身
    head->back = head;            // 空循环链表的头结点前驱为头结点本身
    curPosition = 0;              // 初始化当前位置
    curPtr = head;                // 初始化当前位置指针
    count = 0;
}

template <class ElemType>
DbLinkList<ElemType>::DbLinkList()
{
    // 操作结果：创建空链表
    Init();
}

template <class ElemType>
DbLinkList<ElemType>::~DbLinkList()
{
    // 操作结果：析构函数，待释放的存储空间包括数据节点和头结点
    Clear();              // 释放非头结点空间
    head->next = nullptr; // 这步很关键啊！！！
    head->back = nullptr; // 这步很关键啊！！！
    delete head;          // 释放头结点空间
}

template <class ElemType>
int DbLinkList<ElemType>::Length() const
{
    // 操作结果：返回线性表元素个数
    return count;
}

template <class ElemType>
bool DbLinkList<ElemType>::Empty() const
{
    // 操作结果：如线性表为空，则返回true，否则返回false
    return head->next == head;
}

template <class ElemType>
void DbLinkList<ElemType>::Clear()
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
void DbLinkList<ElemType>::Traverse(void (*Visit)(ElemType &))
{
    // 操作结果：依次对线性表的每个元素调用函数(*Visit)
    for (DblNode<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
    {
        // 用tmpPtr指向每个元素
        (*Visit)(tmpPtr->val); // 对线性表的每个元素调用(*Visit)
    }
}

template <class ElemType>
int DbLinkList<ElemType>::GetElem(int position, ElemType &e) const
{
    // 操作结果：e返回第position个位置的结点的数据域
    // position的合理性判断
    if (position < 1 || position > Length())
    {
        return NOT_PRESENT;
    }
    else
    {
        DblNode<ElemType> *tmpPtr = GetElemPtr(position);
        e = tmpPtr->val;
        return ENTRY_FOUND;
    }
}

template <class ElemType>
int DbLinkList<ElemType>::SetElem(int position, const ElemType &e)
{
    // 操作结果：设置第position个位置的结点数据域为e
    // position的合理性判断
    if (position < 1 || position > Length())
    {
        return RANGE_ERROR;
    }
    else
    {
        DblNode<ElemType> *tmpPtr = GetElemPtr(position);
        tmpPtr->val = e;
        return SUCCESS;
    }
}

template <class ElemType>
int DbLinkList<ElemType>::Delete(int position, ElemType &e)
{
    // 操作结果：删除线性表的第position个位置的元素，并用e返回其值
    // position的取值范围为1<=position<=Length()，
    // position合法时函数返回SUCCESS，否则函数返回RANGE_ERROR
    if (position < 1 || position > Length())
    {
        // position范围错
        return RANGE_ERROR;
    }
    else
    {
        // position合法
        DblNode<ElemType> *tmpPtr;
        tmpPtr = GetElemPtr(position);     // 取出指向第position个结点的指针
        tmpPtr->back->next = tmpPtr->next; // 修改向右的指针
        tmpPtr->next->back = tmpPtr->back; // 修改向左的指针
        e = tmpPtr->val;                   //用e返回被删结点元素值
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
        tmpPtr->back = nullptr;
        tmpPtr->next = nullptr;
        delete tmpPtr; // 释放被删结点，肯定会有坑！tmpPtr->back = nullptr, tmpPtr->next = nullptr
        return SUCCESS;
    }
}

template <class ElemType>
int DbLinkList<ElemType>::Insert(int position, const ElemType &e)
{
    // 操作结果：在线性表的第position个位置前插入元素e
    // position的取值范围为1<=position<=Length()+1
    // position合法时返回SUCCESS，否则函数RANGE_ERROR
    if (position < 1 || position > Length() + 1)
    {
        // position范围错
        return RANGE_ERROR; // 位置不合法
    }
    else
    {
        // position合法
        DblNode<ElemType> *tmpPtr, *nextPtr, *newPtr;
        tmpPtr = GetElemPtr(position - 1);                  // 取出指向第position-1个结点的指针
        nextPtr = tmpPtr->next;                             // nextPtr指向第position个结点
        newPtr = new DblNode<ElemType>(e, tmpPtr, nextPtr); // 生成新结点
        tmpPtr->next = newPtr;                              // 修改向右的指针
        nextPtr->back = newPtr;                             // 修改向左的指针
        curPosition = position;                             // 设置当前位置的序号
        curPtr = newPtr;                                    // 设置指向当前位置的指针
        count++;
        return SUCCESS;
    }
}

template <class ElemType>
DbLinkList<ElemType>::DbLinkList(const DbLinkList<ElemType> &copy)
{
    // 操作结果：复制构造，从无到有
    int copyLength = copy.Length();
    head = new DblNode<ElemType>; // 头指针空间申请
    head->next = head;            // 完成Init()里面做的所有事情！
    head->back = head;
    curPosition = 0; // 初始化当前位置
    curPtr = head;   // 初始化当前位置指针
    count = 0;
    ElemType tmp;
    for (int curPosition = 1; curPosition <= copyLength; curPosition++)
    {
        copy.GetElem(curPosition, tmp);
        Insert(Length() + 1, tmp);
    }
}

template <class ElemType>
DbLinkList<ElemType> &DbLinkList<ElemType>::operator=(const DbLinkList<ElemType> &copy)
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

int main()
{
    // 双向链表成员函数测试
    return 0;
}