#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <iostream>
#include "Constant.h"

using namespace std;

// 最小堆类
template <class ElemType>
class MinHeap
{
protected:
  ElemType *heap;                  // 存放
  int currentSize;                 // 最小堆中元素的数组
  int maxHeapSize;                 // 最小堆最多允许元素个数
  void siftDown(int start, int m); // 从start到m下滑调整成为最小堆
  void siftUp(int start);          // 从start到0上滑调整成为最小堆

public:
  MinHeap(int size = DEFAULT_SIZE); // 构造函数：建立空堆
  MinHeap(ElemType arr[], int n);   // 通过一个数组建堆
  ~MinHeap() { delete[] heap; };    // 析构函数

  bool Insert(const ElemType &e);
  bool RemoveMin(ElemType &e);                               // 删除堆顶元素，即最小元素
  bool IsEmpty() const { return currentSize == 0; };         // 判读堆是否为空
  bool IsFull() const { return currentSize == maxHeapSize; } // 判断堆是否为满
  void Clear() { currentSize = 0; }                          // 清空堆

  MinHeap(const MinHeap<ElemType> &copy);                // 复制构造函数
  MinHeap<ElemType> &operator=(MinHeap<ElemType> &copy); // 重载赋值运算符

  template <class T>
  friend std::ostream &operator<<(std::ostream &os, MinHeap<T> &heap);
};

#endif // MIN_HEAP_H
