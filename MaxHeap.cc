#include "MaxHeap.h"

// 最大堆类的实现部分
template <class ElemType>
MaxHeap<ElemType>::MaxHeap(int size)
{
    maxHeapSize = size;
    heap = new ElemType[maxHeapSize];
    if (heap == nullptr)
    {
        cerr << "heap create failed!" << endl;
        exit(1);
    }
    currentSize = 0;
}

template <class ElemType>
MaxHeap<ElemType>::MaxHeap(ElemType arr[], int n)
{
    maxHeapSize = (DEFAULT_SIZE < n) ? n : DEFAULT_SIZE;
    heap = new ElemType[maxHeapSize];
    if (heap == nullptr)
    {
        cerr << "heap create failed!" << endl;
        exit(1);
    }
    for (int pos = 0; pos < n; pos++)
        heap[pos] = arr[pos];
    currentSize = n;
    int currentPos = (currentSize - 2) / 2; // 找最初调整位置：最后分支结点(最后一个有孩子的结点)
    while (currentPos >= 0)                 // 自底向上逐步调整形成堆
    {
        siftDown(currentPos, currentSize - 1); // 局部自上向下下滑调整
        currentPos--;                          // 再向前换一个分支结点
    }
}

template <class ElemType>
void MaxHeap<ElemType>::siftDown(int start, int m)
{
    // 从结点start开始到结点m为止，自上向下比较，如果子女的值大于父结点的值
    // 则关键码更大的子女上浮，继续向下层比较，这样将一个集合局部调整为最大堆
    int i = start, j = 2 * i + 1; // j是i的左孩子
    ElemType temp = heap[i];
    while (j <= m)
    {
        if (j < m && heap[j] < heap[j + 1]) // i的右孩子比j(i的左孩子)更小，j指向右孩子(更小的)
            j++;
        if (temp >= heap[j]) // i已经比其子女j大了，调整结束
            break;
        else
        {
            heap[i] = heap[j]; // i比子女j小，则j上浮替代i的位置，调整位置i和j均下降
            i = j;
            j = 2 * j + 1;
        }
    }
    heap[i] = temp; // 放回start结点
}

template <class ElemType>
void MaxHeap<ElemType>::siftUp(int start)
{
    // 从结点start开始到结点0为止，自下而上比较，如果子女的值大于父结点的值
    // 则子女上浮，继续向上层比较，这样将一个集合重新调整为最大堆，元素类型ElemType应自行定义">="运算符
    int j = start, i = (j - 1) / 2;
    ElemType temp = heap[j];
    while (j > 0) // 沿父结点路径向上直达根，i是j的父结点
    {
        if (heap[i] >= temp) // 父结点值大，无需调整
            break;
        else
        {
            heap[j] = heap[i]; // i比子女j小，则i下滑取代j的位置，调整位置i和j均上滑
            j = i;
            i = (i - 1) / 2;
        }
    }
    heap[j] = temp;
}

template <class ElemType>
bool MaxHeap<ElemType>::Insert(const ElemType &e)
{
    if (currentSize == maxHeapSize) // 堆满
    {
        cerr << "Heap already full!" << endl;
        return false;
    }
    heap[currentSize] = e; // 每次新元素总会插入到堆末尾
    siftUp(currentSize);   // 从当前元素即尾元素开始向上调整
    currentSize++;
    return true;
}

template <class ElemType>
bool MaxHeap<ElemType>::RemoveMax(ElemType &e)
{
    if (currentSize == 0) // 堆空
    {
        cerr << "Heap already empty!" << endl;
        return false;
    }
    e = heap[0];
    heap[0] = heap[currentSize - 1]; // 最后元素填补到根结点
    currentSize--;
    siftDown(0, currentSize - 1); // 因为尾元素放到了堆顶，故从堆顶元素开始自上而下调整
    return true;
}

template <class ElemType>
MaxHeap<ElemType>::MaxHeap(const MaxHeap<ElemType> &copy)
{
    // 操作结果： 复制构造函数，从无到有
    // 一开始没有这个对象，重新申请空间构造一个与之前对象完全不同内存空间的对象
    heap = new ElemType[copy.maxHeapSize];
    maxHeapSize = copy.maxHeapSize;
    currentSize = copy.currentSize;
    for (int pos = 0; pos < copy.currentSize; pos++)
        // 遍历最大堆copy，将其每个元素插入到本堆
        heap[pos] = copy.heap[pos];
}

template <class ElemType>
MaxHeap<ElemType> &MaxHeap<ElemType>::operator=(MaxHeap<ElemType> &copy)
{
    // 操作结果：赋值运算符重载，从老到新
    // 一开始已经有了对象this，要检查自赋值并清空原线性表，仍需重新申请空间构造与之前完全不同的内存位置的表
    if (&copy != this)
    {
        // 非自赋值
        Clear();       // 清空当前表，原有内存空间全被释放，需重新申请
        delete[] heap; // 释放原堆内存
        heap = new ElemType[copy.maxHeapSize];
        maxHeapSize = copy.maxHeapSize;
        currentSize = copy.currentSize;
        for (int pos = 0; pos < copy.currentSize; pos++)
            // 遍历最大堆copy，将其每个元素插入到本堆
            heap[pos] = copy.heap[pos];
    }
    return *this;
}

template <class ElemType>
std::ostream &operator<<(std::ostream &os, MaxHeap<ElemType> &heap)
{
    // 操作结果：遍历输出最大堆元素
    for (int i = 0; i < heap.currentSize; i++)
    {
        os << i << ": " << heap.heap[i] << endl;
    }
    return os;
}

int main()
{
    // 最大堆成员函数测试
    int arr[8] = {53, 17, 78, 9, 45, 65, 87, 23};
    MaxHeap<int> heap1(arr, 8); // 数组参数的构造函数
    cout << "heap1:" << endl;
    cout << heap1 << endl;
    MaxHeap<int> heap2(heap1); // 拷贝构造函数
    cout << "heap2:" << endl;
    cout << heap2 << endl;
    MaxHeap<int> heap3; // 无参数的构造函数，空堆
    cout << "heap3 (before assignment):" << endl;
    cout << heap3 << endl;
    heap3 = heap2; // 赋值拷贝
    cout << "heap3 (after assignment):" << endl;
    cout << heap3 << endl;
    return 0;
}