#include <iostream>
using namespace std;

int main()
{
    int a[3] = {1, 2, 3};
    cout << a << endl;
    cout << a + 1 << endl;
    cout << a + 2 << endl
         << endl;

    int *p = a;
    cout << p << endl;
    cout << p + 1 << endl;
    cout << p + 2 << endl
         << endl;

    cout << &a[0] << endl;
    cout << &a[1] << endl;
    cout << &a[2] << endl;
    return 0;
}