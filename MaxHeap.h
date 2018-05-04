#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <iostream>
#include "Constant.h"

using namespace std;

// 最大堆类
template <class ElemType>
class MaxHeap
{
  protected:
    ElemType *heap;                  // 存放
    int currentSize;                 // 最大堆中元素的数组
    int maxHeapSize;                 // 最大堆最多允许元素个数
    void siftDown(int start, int m); // 从start到m下滑调整成为最大堆
    void siftUp(int start);          // 从start到0上滑调整成为最大堆

  public:
    MaxHeap(int size = DEFAULT_SIZE); // 构造函数：建立空堆
    MaxHeap(ElemType arr[], int n);   // 通过一个数组建堆
    ~MaxHeap() { delete[] heap; };    // 析构函数

    bool Insert(const ElemType &e);
    bool RemoveMax(ElemType &e);                               // 删除堆顶元素，即最大元素
    bool IsEmpty() const { return currentSize == 0; };         // 判读堆是否为空
    bool IsFull() const { return currentSize == maxHeapSize; } // 判断堆是否为满
    void Clear() { currentSize = 0; }                          // 清空堆

    MaxHeap(const MaxHeap<ElemType> &copy);                // 复制构造函数
    MaxHeap<ElemType> &operator=(MaxHeap<ElemType> &copy); // 重载赋值运算符

    template <class T>
    friend std::ostream &operator<<(std::ostream &os, MaxHeap<T> &heap);
};

#endif // MAX_HEAP_H
