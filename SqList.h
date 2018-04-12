#ifndef SQLIST_H
#define SQLIST_H

#include <cstddef>
#include "Constant.h"

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
};

#endif // SQLIST_H
