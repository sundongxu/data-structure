#include "SqStack.h"

// 顺序栈类的实现部分
template <class ElemType>
bool SqStack<ElemType>::Full() const
{
    // 操作结果：判断栈是否已满
    return count == maxSize;
}

template <class ElemType>
void SqStack<ElemType>::Init(int size)
{
    // 操作结果：初始化栈为最大元素个数为size的空栈
    maxSize = size;
    if (elems != nullptr)
        delete[] elems;
    elems = new ElemType[maxSize];
    count = 0;
}

template <class ElemType>
SqStack<ElemType>::SqStack(int size)
{
    // 操作结果：构造一个最大元素个数为size的空栈
    elems = nullptr;
    Init(size);
}

template <class ElemType>
SqStack<ElemType>::~SqStack()
{
    // 操作结果：销毁栈
    delete[] elems;
}

template <class ElemType>
int SqStack<ElemType>::Length() const
{
    // 操作结果：返回栈元素个数
    return count;
}

template <class ElemType>
bool SqStack<ElemType>::Empty() const
{
    // 操作结果：如栈为空，则返回true，否则返回false
    return count == 0;
}

template <class ElemType>
void SqStack<ElemType>::Clear()
{
    // 操作结果：清空栈
    count = 0;
}

template <class ElemType>
void SqStack<ElemType>::Traverse(void (*Visit)(ElemType &))
{
    // 操作结果：从栈底到栈顶依次对栈的每个元素调用函数(*Visit)
    for (int curPosition = 1; curPosition <= Length(); curPosition++)
    {
        // 从栈底到栈顶对栈的每个元素调用函数(*Visit)
        (*Visit)(elems[curPosition - 1]);
    }
}

template <class ElemType>
int SqStack<ElemType>::Push(const ElemType &e)
{
    // 将元素e追加到栈顶，如成功则返回SUCCESS，如栈已满则返回OVER_FLOW
    if (Full())
    {
        // 栈已满
        return OVER_FLOW;
    }
    else
    {
        // 操作成功
        elems[count++] = e; // 将元素追加到栈顶
        return SUCCESS;
    }
}

template <class ElemType>
int SqStack<ElemType>::Top(ElemType &e) const
{
    // 操作结果：如栈非空，用e返回栈顶元素，函数返回SUCCESS，否则函数返回UNDER_FLOW
    if (Empty())
    {
        // 栈空
        return UNDER_FLOW;
    }

    else
    {
        // 栈非空，操作成功
        e = elems[count - 1];
        return SUCCESS;
    }
}

template <class ElemType>
int SqStack<ElemType>::Pop(ElemType &e)
{
    // 操作结果：如栈非空，删除栈顶元素，并用e返回栈顶元素，函数返回SUCCESS
    // 否则函数返回UNDER_FLOW
    if (Empty())
    {
        // 栈空
        return UNDER_FLOW;
    }

    else
    {
        // 操作成功
        e = elems[count - 1]; // 用e返回栈顶元素
        count--;
        return SUCCESS;
    }
}

template <class ElemType>
SqStack<ElemType>::SqStack(const SqStack<ElemType> &copy)
{
    // 操作结果：拷贝构造，从无到有
    elems = nullptr;
    Init(copy.maxSize);
    count = copy.count;
    for (int curPosition = 1; curPosition <= Length(); curPosition++)
    {
        // 从栈底到栈顶对栈copy的每个元素进行复制
        elems[curPosition - 1] = copy.elems[curPosition - 1];
    }
}

template <class ElemType>
SqStack<ElemType> &SqStack<ElemType>::operator=(const SqStack<ElemType> &copy)
{
    // 操作结果：赋值运算符重载，从老到新
    if (&copy != this) // 不是自赋值
    {
        Init(copy.maxSize);
        count = copy.count;
        for (int curPosition = 1; curPosition <= Length(); curPosition++)
        {
            // 从栈底到栈顶对栈copy的每个元素进行复制
            elems[curPosition - 1] = copy.elems[curPosition - 1];
        }
    }
    return *this;
}

int main()
{
    // 顺序栈成员函数测试

    // 测试Push、Top、Pop
    int e;
    SqStack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(3);
    s.Push(4);
    s.Push(5);
    s.Top(e);
    cout << "栈顶元素:" << e << endl;
    s.Traverse(Print);
    cout << endl;
    s.Pop(e);
    s.Pop(e);
    s.Traverse(Print);
    cout << endl;

    // 测试拷贝构造
    SqStack<int> s1(s);
    s1.Traverse(Print);
    cout << endl;

    // 测试赋值运算符
    SqStack<int> s2;
    s2.Push(6);
    s2.Push(7);
    s2.Traverse(Print);
    cout << endl;
    s2 = s;
    s2.Traverse(Print);

    return 0;
}