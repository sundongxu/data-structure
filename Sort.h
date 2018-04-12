#ifndef SORT_H
#define SORT_H

#include "LinkList.h"
#include <cmath>
using namespace std;
/*
    基本排序算法及功能如下：
    （1）BubbleSort(ElemType elem[], int n):
        冒泡排序
    （2）StraightInsertSort(ElemType elem[], int n):
        直接插入排序
    （3）SimpleSelectionSort(ElemType elem[], int n):
        简单选择排序
    （4）QuickSort(ElemType elem[], int n):
        快速排序
    （5）ShellSort(ElemType elem[], int n, int inc[], int t):
        希尔排序
    （6）SimpleMergeSort(ElemType elem[], int n):
        简单归并排序
    （7）MergeSort(ElemType elem[], int n):
        归并排序
    （8）HeapSort(ElemType elem[], int n):
        堆排序
    （9）RadixSort(ElemType elem[], int n, int r, int d):
        基数排序
*/

template <class ElemType>
void BubbleSort(ElemType elem[], int n);

template <class ElemType>
void StraightInsertSort(ElemType elem[], int n);

template <class ElemType>
void SimpleSelectionSort(ElemType elem[], int n);

template <class ElemType>
int Partition(ElemType elem[], int high, int low);
template <class ElemType>
void QuickSortHelp(ElemType elem[], int low, int high);
template <class ElemType>
void QuickSort(ElemType elem[], int n);

template <class ElemType>
void ShellInsert(ElemType elem[], int n, int incr);
template <class ElemType>
void ShellSort(ElemType elem[], int n, int inc[], int t);

template <class ElemType>
void SimpleMerge(ElemType elem[], int low, int mid, int high);
template <class ElemType>
void SimpleMergeSortHelp(ElemType elem[], int low, int high);
template <class ElemType>
void SimpleMergeSort(ElemType elem[], int n);

template <class ElemType>
void Merge(ElemType elem[], ElemType tmpElem[], int low, int mid, int high);
template <class ElemType>
void MergeSortHelp(ElemType elem[], ElemType tmpElem[], int low, int high);
template <class ElemType>
void MergeSort(ElemType elem[], int n);

template <class ElemType>
void SiftAdjust(ElemType elem[], int low, int high);
template <class ElemType>
void HeapSort(ElemType elem[], int n);

template <class ElemType>
void Distribute(ElemType elem[], int n, int r, int d, int i, LinkList<ElemType> list[]);
template <class ElemType>
void Collect(ElemType elem[], int n, int r, int d, int i, LinkList<ElemType> list[]);
template <class ElemType>
void RadixSort(ElemType elem[], int n, int r, int d);

template <class ElemType>
void BubbleSort(ElemType elem[], int n)
{
    for (int i = 1; i < n; i++) // 外循环只是用来计数趟数，n个元素排序需要n-1趟，i=1~n-1
    {
        // 外层循环表示一趟，每次选出本趟排序中的最大元素放在最后
        for (int j = 0; j < n - i; j++)
        {
            // 内层循环用来完成这一趟排序，共有n-i个元素参与本趟排序
            if (elem[j] > elem[j + 1])
            {
                int temp = elem[j + 1];
                elem[j + 1] = elem[j];
                elem[j] = temp;
            }
        }
    }
}

template <class ElemType>
void StraightInsertSort(ElemType elem[], int n)
{
    for (int i = 1; i < n; i++)
    {
        ElemType e = elem[i]; // 暂存elem[i]
        int j;                // 临时变量，在放置当前元素时有用
        for (j = i - 1; j >= 0 && e < elem[j]; j--)
        {
            elem[j + 1] = elem[j]; // 元素后移
        }
        elem[j + 1] = e; // j+1即为插入位置
    }
}

template <class ElemType>
void SimpleSelectionSort(ElemType elem[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int lowIndex = 0; // 记录elem[i,...,n-1]中最小元素下标，前面i个元素已经全部按从小到大顺序放好啦
        for (int j = i + 1; j < n; j++)
        {
            if (elem[j] < elem[lowIndex])
            {
                lowIndex = j; // 存储当前寻找到的最小元素的下标
            }
        }
        swap(elem[i], elem[lowIndex]); // 本轮循环找到的最小元素放到第i个位置
    }
}

template <class ElemType>
int Partition(ElemType elem[], int low, int high)
{
    // 操作结果：交换elem[low...high]中的元素，使枢轴移动到适当位置，要求在枢轴之前的元素
    // 不大于枢轴，在枢轴之后的元素不小于枢轴，并返回枢轴的位置

    // 执行一次即一次划分——Partition，找出枢轴元素，
    while (low < high)
    {
        while (low < high && elem[high] >= elem[low])
        {
            // elem[low]为枢轴，使high右边的元素不小于elem[low]
            high--;
        }
        // 跳出循环条件：elem[high]<elem[low]

        swap(elem[low], elem[high]); // 此时elem[high]>elem[low]，必然满足下面while循环条件

        while (low < high && elem[low] <= elem[high])
        {
            // elem[high]为枢轴，使low左边的元素不大于elem[high]
            low++;
        }
        swap(elem[low], elem[high]);
    }
    return low; // 返回枢轴位置
}

template <class ElemType>
void QuickSortHelp(ElemType elem[], int low, int high)
{
    // 操作结果：对数组elem[low...high]中的记录进行快速排序
    if (low < high) // 判断合理性
    {
        // 子序列elem[low...high]长度大于1
        int pivotLoc = Partition(elem, low, high); // 进行一趟划分
        QuickSortHelp(elem, low, pivotLoc - 1);
        // 对子表elem[low, pivotLoc-1]递归排序
        QuickSortHelp(elem, pivotLoc + 1, high);
        // 对子表elem[pivotLoc+1, high]递归排序
    }
}

template <class ElemType>
void QuickSort(ElemType elem[], int n)
{
    // 操作结果：对数组elem进行快速排序
    QuickSortHelp(elem, 0, n - 1);
}

template <class ElemType>
void ShellInsert(ElemType elem[], int n, int incr)
{
    // 操作结果：对数组elem做一趟增量为incr的shell排序，对插入排序作出的修改是子序列中前后
    // 相邻记录的增量为incr，而不是1
    for (int i = incr; i < n; i++)
    {
        ElemType e = elem[i];
        int j;
        for (j = i - incr; j >= 0 && e < elem[j]; j++)
        {
            elem[j + incr] = elem[j];
        }
        elem[j + incr] = e; // j+incr为插入位置
    }
}

template <class ElemType>
void ShellSort(ElemType elem[], int n, int inc[], int t)
{
    // 操作结果：按增量序列inc[0,...,t-1]对数组elem作希尔排序
    for (int k = 0; k < t; k++)
    {
        // 第k趟希尔排序
        ShellInsert(elem, n, inc[k]);
    }
}

template <class ElemType>
void SimpleMerge(ElemType elem[], int low, int mid, int high)
{
    // 操作结果：将有序子序列elem[low,...mid]和elem[mid+1,...,high]归并为新的有序序列elem[low,...,high]
    // 真的做了比较和排序！
    ElemType *tmpElem = new ElemType[high + 1];

    int i, j, k;
    for (i = low, j = mid + 1, k = low; i <= mid && j <= high; k++)
    {
        // i为归并时elem[low...mid]当前元素的下标，j为归并时elem[mid+1,...,high]
        // 当前元素的下标，k为tmpElem中当前元素的下标
        if (elem[i] <= elem[j])
        {
            // elem[i]较小，先归并
            tmpElem[k] = elem[i];
            i++;
        }
        else
        {
            tmpElem[k] = elem[j];
            j++;
        }
    }

    for (; i <= mid; i++, k++)
    {
        // 归并elem[low,...,mid]中剩余元素
        tmpElem[k] = elem[i];
    }

    for (; j <= high; j++, k++)
    {
        // 归并elem[mid+1,...,high]中剩余元素
        tmpElem[k] = elem[j];
    }

    for (i = low; i <= high; i++)
    {
        // 将tmpElem[low,...,high]复制到Elem[low,...,high]
        elem[i] = tmpElem[i];
    }

    delete[] tmpElem; //释放tmpElem所占用空间
}

template <class ElemType>
void SimpleMergeSortHelp(ElemType elem[], int low, int high)
{
    // 操作结果：对elem[low,...,high]进行简单归并排序
    if (low < high)
    {
        // 将elem[low,...,high]平分为elem[low,...,mid]和elem[mid+1,...,high]两个数组
        int mid = (high + low) / 2;
        SimpleMergeSortHelp(elem, low, mid);      //调用自身->递归，对elem[low,...,mid]进行简单归并排序
        SimpleMergeSortHelp(elem, mid + 1, high); // 对elem[mid+1,...,high]进行简单归并排序
        SimpleMerge(elem, low, mid, high);        // 对elem[low,...,mid]和elem[mid+1,...,high]进行归并
    }
}

template <class ElemType>
void SimpleMergeSort(ElemType elem[], int n)
{
    // 操作结果：对elem进行简单归并排序
    SimpleMergeSortHelp(elem, 0, n - 1);
}

/*
    在SimpleMerge中，每次归并都要为临时数组分配存储空间，归并结束后还需释放空间，要花费不少时间
    要进一步提高运行速度，可在主归并函数MergeSort()中统一为临时数据分配存储空间与释放空间
    修改如下：
*/
template <class ElemType>
void Merge(ElemType elem[], ElemType tmpElem[], int low, int mid, int high)
{
    // 将有序子序列elem[low,...mid]和elem[mid+1,...,midhigh]归并为新的有序序列elem[low,...,high]
    int i, j, k;
    for (i = low, j = mid + 1, k = low; i <= mid && j <= high; k++)
    {
        // i为归并时elem[low,...,mid]当前元素的下标，j为归并时elem[mid+1,...,high]当前元素的下标，k为tmpElem
        // 中当前元素的下标
        if (elem[i] <= elem[j])
        {
            // elem[i]较小，先归并
            elem[k] = elem[i];
            i++;
        }
        else
        {
            // elem[j]较小，先归并
            elem[k] = elem[j];
            j++;
        }
    }
    for (; i <= mid; i++, k++)
    {
        // 归并elem[low,...,mid]中剩余元素
        tmpElem[k] = elem[i];
    }
    for (; j <= high; j++)
    {
        // 归并elem[mid+1,...,high]中剩余元素
        tmpElem[k] = elem[j];
    }
    for (i = low; i < high; i++)
    {
        elem[i] = tmpElem[i];
    }
}

template <class ElemType>
void MergeSortHelp(ElemType elem[], ElemType tmpElem[], int low, int high)
{
    // 操作结果：对elem[low,...,high]进行归并排序
    if (low < high)
    {
        int mid = (low + high) / 2;
        MergeSortHelp(elem, tmpElem, low, mid);
        MergeSortHelp(elem, tmpElem, mid + 1, high);
        Merge(elem, tmpElem, low, mid, high);
    }
}

template <class ElemType>
void MergeSort(ElemType elem[], int n)
{
    // 操作结果：对elem进行归并排序
    ElemType *tmpElem = new ElemType[n]; // 提前申请好这部分临时空间，免得每次都要新申请
    MergeSortHelp(elem, tmpElem, 0, n - 1);
    delete[] tmpElem;
}

template <class ElemType>
void SiftAdjust(ElemType elem[], int low, int high)
{
    // 操作结果：elem[low,...,high]中记录除elem[low]以外都满足堆定义，
    // 调整elem[low]使elem[low,...,high]成为一个最大堆
    for (int f = low, i = 2 * low + 1; i <= high; i = 2 * i + 1)
    {
        // f为被调整结点，i记录f的最大孩子下标
        if (i < high && elem[i] < elem[i + 1])
        {
            // 右孩子更大，i指向右孩子
            i++;
        }
        if (elem[f] >= elem[i])
        {
            // 已经成为最大堆，跳出循环
            break;
        }
        swap(elem[f], elem[i]);
        f = i;
    }
}

template <class ElemType>
void HeapSort(ElemType elem[], int n)
{
    // 操作结果：对数组elem进行排序
    int i;
    for (i = (n - 2) / 2; i >= 0; --i)
    {
        // 将elem[0,...,n-1]构造成最大堆
        SiftAdjust(elem, i, n - 1);
    }

    for (i = n - 1; i > 0; --i)
    {
        // 第i趟堆排序
        swap(elem[i], elem[0]);     // 将堆顶元素和当前未经排序的子序列elem[0,...,i]中最后一个元素交换
        SiftAdjust(elem, 0, i - 1); // 将elem[0,...,i-1]重新调整为最大堆
    }
}

template <class ElemType>
void Distribute(ElemType elem[], int n, int r, int d, int i, LinkList<ElemType> list[])
{
    // 初始条件：r为基数，d为关键字位数，list[0,...,r-1]为被分配的线性表数组
    // 操作结果：进行第i趟分配
    for (int power = (int)pow((double)r, i - 1), j = 0; j < n; j++)
    {
        // 进行第i趟分配
        int index = (elem[j] / power) % r;
        list[index].Insert(list[index].Length() + 1, elem[j]);
    }
}

template <class ElemType>
void Collect(ElemType elem[], int n, int r, int d, int i, LinkList<ElemType> list[])
{
    // 初始条件：r为基数，d为关键字位数，list[0,...,r-1]为被分配的线性表数组
    // 操作结果：进行第i趟收集
    for (int k = 0, j = 0; j < r; j++)
    {
        // 进行第i趟分配
        ElemType tmpElem;
        while (!list[j].Empty())
        {
            // 收集list[j]
            list[j].Delete(1, tmpElem);
            elem[k++] = tmpElem;
        }
    }
}

template <class ElemType>
void RadixSort(ElemType elem[], int n, int r, int d)
{
    // 初始条件：r为基数，d为关键字位数
    // 操作结果：对elem进行基数排序
    LinkList<ElemType> *list; // 用于存储被分配的线性表数组
    list = new LinkList<ElemType>[r];
    for (int i = 1; i <= d; i++)
    {
        //第i趟分配与收集
        Distribute(elem, n, r, d, i, list); //分配
        Collect(elem, n, r, d, i, list);    //收集
    }
    delete[] list;
}

#endif // SORT_H