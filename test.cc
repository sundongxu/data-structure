#include "Sort.h"
#include <iostream>

using namespace std;
int main()
{
    int a[5] = {5, 4, 2, 3, 1};
    for (int i = 0; i < 5; i++)
        cout << a[i] << " ";
    cout << endl;
    SimpleMergeSort(a, 5);
    for (int i = 0; i < 5; i++)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}