#include <iostream>

using namespace std;

class Base
{
public:
  virtual void f() { cout << "Base::f" << endl; }
  virtual void g() { cout << "Base::g" << endl; }
  virtual void h() { cout << "Base::h" << endl; }

private:
  virtual void ff() { cout << endl; };
};

class Sub : public Base
{
public:
  void f() { cout << "Sub::f" << endl; }
  void g() { cout << "Sub::g" << endl; }
  void h() { cout << "Sub::h" << endl; }

  void ff() {}
};

void f()
{
  cout << "f() invoked!" << endl;
}

int i = 0;

int main()
{
  typedef void (*Fun)(void);
  Fun p = f;
  // Fun p = &f;  // 取地址符是可选的
  cout << "全局函数f()地址：" << (void *)p << endl; // 函数指针没有重载<<运算符，必须将函数指针转换为指针类型才能输出地址值
  cout << "函数指针值：" << *p << endl;
  p();    // 调用f
  (*p)(); // 调用f

  cout << "全局变量i地址：" << &i << endl; // 全局变量，在已初始化的数据段data
  cout << endl;
  cout << "基类对象：" << endl;
  Base b;
  Fun pFun_base = nullptr;
  cout << "基类对象地址：" << &b << endl;
  cout << "虚函数表地址：" << (int *)(&b) << endl;
  cout << *(int *)(&b) << endl;         // 十进制，编译器只知道它是个整型值int，并不知道它是个指针(地址值)
  cout << (int *)*(int *)(&b) << endl;  // 十六进制
  cout << *(int *)*(int *)(&b) << endl; // 十进制，编译器只知道它是个int整型值，并不知道它是个指针(地址值)

  cout << "虚函数表 — 第一个函数地址：" << (int *)*(int *)(&b) << endl;
  // cout << "虚函数表 — 第二个函数地址：" << (int *)*(int *)(&b) + 2 << endl;
  // cout << "虚函数表 — 第三个函数地址：" << (int *)*(int *)(&b) + 4 << endl;

  // Invoke the first virtual function
  pFun_base = (Fun) * (int *)*(int *)(&b);  // 转换指向函数的指针
  pFun_base = *(Fun) * (int *)*(int *)(&b); // 对函数指针再解引用一次得到函数本身，即函数名，也可以隐式转换为Fun这种函数指针类型
  pFun_base();
  // pFun_base = (Fun) * ((int *)*(int *)(&b) + 2);
  // pFun_base();
  // pFun_base = (Fun) * ((int *)*(int *)(&b) + 4);
  // pFun_base();

  // cout << endl
  //      << "派生类对象：" << endl;
  // Sub sub;
  // Fun pFun_sub = nullptr;
  // cout << "派生类对象地址：" << &sub << endl;
  // cout << "虚函数表地址：" << (int *)(&sub) << endl;
  // cout << "虚函数表 — 第一个函数地址：" << (int *)*(int *)(&sub) << endl;
  // cout << "虚函数表 — 第一个函数地址：" << (int *)*(int *)(&sub) << endl;
  // cout << "虚函数表 — 第一个函数地址：" << (int *)*(int *)(&sub) << endl;

  // // Invoke the first virtual function
  // pFun_sub = (Fun) * ((int *)*(int *)(&sub));
  // pFun_sub();
  // pFun_sub = (Fun) * ((int *)*(int *)(&sub) + 2);
  // pFun_sub();
  // pFun_sub = (Fun) * ((int *)*(int *)(&sub) + 4);
  // pFun_sub();

  return 0;
}