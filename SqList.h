#ifndef SQLIST_H
#define SQLIST_H

#include <stddef.h>

#define SUCCESS 100
#define NOT_PRESENT 200
#define ENTRY_FOUND 300
#define RANGE_ERROR 400
#define OVER_FLOW 500
#define UNDER_FLOW 600

// 线性顺序表类
template <class ElemType>
class SqList
{
public:
  SqList();
  virtual ~SqList();
  //非自动生成方法
  SqList(int size);                                          //创建大小为size的线性表
  int Length() const;                                        //返回线性表长度
  bool Empty() const;                                        //判空
  void Clear();                                              //清空
  void Traverse(void (*Visit)(ElemType &));                  //遍历线性表
  int GetElem(int position, ElemType &e) const;              //返回指定位置元素
  int SetElem(int position, const ElemType &e);              //设置指定位置的元素值
  int Insert(int position, const ElemType &e);               //插入
  int Delete(int positon, ElemType &e);                      //删除
  SqList(const SqList<ElemType> &copy);                      //复制构造
  SqList<ElemType> &operator=(const SqList<ElemType> &copy); //赋值运算符

protected:
  //顺序表实现的数据成员
  int count;       //元素个数
  int maxSize;     //表大小
  ElemType *elems; //动态指针分配的元素存储空间

  //辅助函数
  bool Full() const;   // 判断线性表是否已满
  void Init(int size); //初始化空间大小为size的线性表

private:
};

template <class ElemType>
bool SqList<ElemType>::Full() const
{
  // 操作结果：判断线性表是否满
  return count == maxSize;
}

template <class ElemType>
void SqList<ElemType>::Init(int size)
{
  // 操作结果：初始化线性表
  count = 0;
  maxSize = size;
  if (elems != NULL)
  {
    delete[] elems;
  }
  elems = new ElemType[size];
}

template <class ElemType>
SqList<ElemType>::SqList(int size)
{
  // 操作结果：创建含size个元素的线性表
  elems = NULL;
  Init(size);
}

template <class ElemType>
SqList<ElemType>::~SqList()
{
  // 操作结果：析构函数，释放指针所指向的内存空间
  delete[] elems; // 释放存储空间，只有这个空间值得释放
}

template <class ElemType>
int SqList<ElemType>::Length() const
{
  // 操作结果：返回线性表长度，即元素个数
  return count;
}

template <class ElemType>
bool SqList<ElemType>::Empty() const
{
  // 操作结果：判断线性表是否空
  return count == 0;
}

template <class ElemType>
void SqList<ElemType>::Clear()
{
  // 操作结果：清空线性表
  count = 0;
}

template <class ElemType>
void SqList<ElemType>::Traverse(void (*Visit)(ElemType &))
{
  // 操作结果：遍历线性表
  for (int curPosition = 1; curPosition <= count; curPosition++)
  {
    (*Visit)(elems[curPosition - 1]);
  }
}

template <class ElemType>
int SqList<ElemType>::GetElem(int position, ElemType &e) const
{
  // 操作结果：用e返回线性表第position个位置的元素
  //position的合理性判断
  if (position < 1 || position > Length())
  {
    return NOT_PRESENT; //元素不存在
  }
  else
  {
    e = elems[position - 1];
    return ENTRY_FOUND; //元素存在
  }
}

template <class ElemType>
int SqList<ElemType>::SetElem(int position, const ElemType &e)
{
  // 操作结果：设置线性表第position个位置的元素为e
  //position的合理性判断
  if (position < 1 || position > Length())
  {
    return RANGE_ERROR; //位置错
  }
  else
  {
    elems[position - 1] = e;
    return SUCCESS; //设置成功
  }
}

//SetElem和Insert还是有差别的，同样是设置加入新元素，只能用Insert，因为它会添加同时扩展元素数目（count=Length()）
//但是SetElem不会，而且它在设置指定位置元素值的时候还会检查位置的合法性，超出已有元素的位置范围将报错
template <class ElemType>
int SqList<ElemType>::Insert(int position, const ElemType &e)
{
  // 操作结果：在线性表第position个位置插入新元素
  ElemType tmp;
  //判满，满则无法插入
  if (Full())
  {
    return OVER_FLOW;
  }
  else if (position < 1 || position > Length() + 1)
  {
    //position插入位置合理性判断
    return RANGE_ERROR;
  }
  else
  {
    //能够插入
    for (int curPosition = count; curPosition >= position; curPosition--)
    {
      //elems[curPosition] = elems[curPosition - 1];
      GetElem(curPosition, tmp);
      SetElem(curPosition + 1, tmp);
    }
    count++;
    SetElem(position, e);
    return SUCCESS;
  }
}

template <class ElemType>
int SqList<ElemType>::Delete(int position, ElemType &e)
{
  // 操作结果：删除线性表第position个位置的元素
  ElemType tmp;
  //判空，空则无法删除
  if (Empty())
  {
    return UNDER_FLOW;
  }
  else if (position < 1 || position > Length())
  {
    return RANGE_ERROR;
  }
  else
  {
    //能够删除
    GetElem(position, e);
    for (int curPosition = position; curPosition <= Length() - 1; curPosition++)
    {
      GetElem(curPosition + 1, tmp);
      SetElem(curPosition, tmp);
    }
    count--;
    return SUCCESS;
  }
}

template <class ElemType>
SqList<ElemType>::SqList(const SqList<ElemType> &copy)
{
  //操作结果：复制构造，从无到有
  elems = NULL; //清空原来的线性表
  int copyLength = copy.Length();
  ElemType tmp;
  Init(copy.maxSize);

  for (int curPosition = 1; curPosition <= copyLength; curPosition++)
  {
    copy.GetElem(curPosition, tmp);
    Insert(Length() + 1, tmp); //为什么不用SetElem，为什么参数不传curPosition
  }
}

template <class ElemType>
SqList<ElemType> &SqList<ElemType>::operator=(const SqList<ElemType> &copy)
{
  // 操作结果：赋值运算符重载，从老到新
  if (&copy != this)
  {
    ElemType tmp;
    int copyLength = copy.Length();

    Init(copy.maxSize);

    for (int curPosition = 1; curPosition <= copyLength; curPosition++)
    {
      copy.GetElem(curPosition, tmp);
      Insert(Length() + 1, tmp);
    }
  }
  return *this;
}

#endif // SQLIST_H
