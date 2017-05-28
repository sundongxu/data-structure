#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <cstring>
#include "LinkList.h"
using namespace std;

// 字符串类
class String
{
protected:
  // 串实现的数据成员：
  mutable char *strVal; // 串值
  int length;           // 串长

public:
  // 抽象数据类型方法声明及重载编译系统默认方法声明：
  String();                              // 构造函数
  virtual ~String();                     // 析构函数
  String(const String &copy);            // 复制构造函数
  String(const char *copy);              // 从C风格串转换的构造函数
  String(LinkList<char> &copy);          // 从线性表转换得构造函数
  int Length() const;                    // 返回串长度
  bool Empty() const;                    // 判断是否为空串
  const char *CStr() const;              // 将串转换为C风格串
  String &operator=(const String &copy); // 赋值运算符重载
  char &operator[](int pos) const;       // 重载下标运算符
};

// 串相关操作
String Read(istream &input);                                         // 从输入流读入串
String Read(istream &input, char &teminalChar);                      // 从输入流读入串，并用terminalChar返回串结束字符
void Write(String &s);                                               // 输出串
void Concat(String &AddTo, const String &AddOn);                     // 将串AddOn连接到AddTo串的后面
void Copy(String &copy, const String &original);                     // 将串original复制到串copy
void Copy(String &copy, const String &original, int n);              // 将串original复制n个字符到串copy
int Index(const String &target, const String &pattern, int pos = 0); // 查找模式串pattern第一次在目标串target中从第pos个字符开始出现的位置
String SubString(const String &s, int pos, int len);                 // 返回串s的第pos个字符开始的长度为len的子串
bool operator==(const String &first, const String &second);          // 重载关系运算符==
bool operator<(const String &first, const String &second);           // 重载关系运算符<
bool operator>(const String &first, const String &second);           // 重载关系运算符>
bool operator!=(const String &first, const String &second);          // 重载关系运算符!=
bool operator<=(const String &first, const String &second);          // 重载关系运算符<=
bool operator>=(const String &first, const String &second);          // 重载关系运算符>=

String::String()
{
  // 操作结果：构造空串，有效字符数为0
  strVal = NULL;
  length = 0;
}

String::~String()
{
  // 操作结果：释放字符串内存空间，之后将指针置空
  length = 0;
  if (strVal != NULL)
  {
    delete strVal;
    strVal = NULL;
  }
}

String::String(const String &copy)
{
  // 操作结果：复制构造
  length = strlen(copy.CStr());
  strVal = new char[length + 1];
  strcpy(strVal, copy.CStr());
}

String::String(const char *copy)
{
  // 操作结果：从C风格串转换构造新串————转换构造函数
  length = strlen(copy);         // 串长
  strVal = new char[length + 1]; // 分配存储空间，需要比length多1，用来存储结束符'/0'
  strcpy(strVal, copy);          // 复制串值
}

String::String(LinkList<char> &copy)
{
  // 操作结果：从线性表转换构造新串————转换构造函数
  length = copy.Length();
  strVal = new char[length + 1];
  for (int i = 0; i < length; i++)
  {
    // 复制串值
    copy.GetElem(i + 1, strVal[i]);
  }
  strVal[length] = '\0'; // 串值以'\0'结束
}

const char *String::CStr() const
{
  // 操作结果：将串转换成C风格串
  return (const char *)strVal; // 串值类型转化
}

int String::Length() const
{
  // 操作结果：返回字符串长度
  return length;
}

bool String::Empty() const
{
  // 操作结果：判断字符串是否为空，即字符串的有效长度
  return length == 0;
}

String &String::operator=(const String &copy)
{
  // 操作结果：赋值运算符重载
  if (&copy != this)
  {
    // 检查自赋值
    delete[] strVal; // 回访
    length = strlen(copy.CStr());
    strVal = new char[length + 1];
    strcpy(strVal, copy.CStr());
  }
  return *this;
}

char &String::operator[](int pos) const
{
  // 操作结果：重载下标运算符，返回String（字符数组）下标对应的字符
  return strVal[pos];
}

String Read(istream &input)
{
  // 操作结果：从输入流读入串，并用terminalChar返回串结束字符
  LinkList<char> temp;                // 临时线性表
  int size = 0;                       // 初始线性表长度
  char c;                             // 临时字符
  while ((c = input.peek()) != EOF && // peek()从输入流中取一个字符，输入流指针不变
         (c = input.get()) != '\n')   // get()从输入流中取一个字符，输入流指针指向下一个字符
  {
    // 将输入的字符追加到线性表中
    temp.Insert(++size, c);
  }
  String answer(temp); // 构造串
  return answer;       // 返回串
}

String Read(istream &input, char &terminalChar)
{
  // 操作结果：从输入流读入串，并用terminalChar返回串结束字符
  LinkList<char> temp;                // 临时线性表
  int size = 0;                       // 初始线性表长度
  char c;                             // 临时字符
  while ((c = input.peek()) != EOF && // peek()从输入流中取一个字符，输入流指针不变
         (c = input.get()) != '\n')   // get()从输入流中取一个字符，输入流指针指向下一个字符
  {
    // 将输入的字符追加到线性表中
  }
  terminalChar = c;    // 用terminalChar返回串结束字符
  String answer(temp); // 构造串
  return answer;       //返回串
}

void Write(String &s)
{
  // 操作结果：输入串
  cout << s.CStr() << endl; // 输出串值
}

void Concat(String &addTo, String &addOn)
{
  // 操作结果：将串addOn连接到addTo串的后面
  const char *cFirst = addTo.CStr();                           // 指向第一个串
  const char *cSecond = addOn.CStr();                          // 指向第二个串
  char *copy = new char[strlen(cFirst) + strlen(cSecond) + 1]; //分配存储空间
  strcpy(copy, cFirst);                                        // 复制第一个串
  strcat(copy, cSecond);                                       // 连接第二个串
  addTo = copy;                                                // 串赋值
  delete[] copy;                                               // 释放copy，这里会不会把addTo所指向内存空间也一并释放了？
}

void Copy(String &copy, const String &original)
{
  // 操作结果：将串original复制到串copy
}

void Copy(String &copy, const String &original, int n)
{
  // 操作结果：将串original复制n个字符到串copy
}

int Index(const String &target, const String &pattern, int pos)
{
  // 操作结果：如果匹配成功，返回模式串pattern第一次在目标串target中从第pos个字符开始出现的位置，否则返回-1
  const char *cTarget = target.CStr();
  const char *cPattern = pattern.CStr();
  const char *ptr = strstr(cTarget, cPattern);
  if (ptr == NULL)
  {
    // 目标串中没找到pattern串，返回-1
    return -1;
  }
  else
  {
    // 找到匹配
    return ptr - cTarget;
    // ptr指向cTarget串中第一次出现cPattern串时其第一个字符的内存位置（绝对位置），减去cTarget串的起始内存位置，故得到cPattern串的相对位置
    // 即子串首字符在字符数组target中的下标
  }
}

String SubString(const String &s, int pos, int len)
{
  // 操作结果：返回串s从第pos个字符开始的长度为len的子串
  const char *cStr = s.CStr();
  char *subStr = new char[len + 1];
  int count = 0;
  for (int i = pos; i < pos + len; i++)
  {
    // 逐个字符赋值
    subStr[count++] = cStr[i];
  }
  subStr[len] = '\0'; // 串值以'\0'结束
  // strcpy(substr,"aaa");
  return String(subStr);
}

bool operator==(const String &first, const String &second)
{
  // 操作结果：重载关系运算符==
  return strcmp(first.CStr(), second.CStr()) == 0;
}

bool operator<(const String &first, const String &second)
{
  // 操作结果：重载关系运算符<
  return strcmp(first.CStr(), second.CStr()) < 0;
}

bool operator>(const String &first, const String &second)
{
  // 操作结果：重载关系运算符<
  return strcmp(first.CStr(), second.CStr()) > 0;
}
bool operator!=(const String &first, const String &second)
{
  // 操作结果：重载关系运算符<
  return strcmp(first.CStr(), second.CStr()) != 0;
}
bool operator<=(const String &first, const String &second)
{
  // 操作结果：重载关系运算符<
  return strcmp(first.CStr(), second.CStr()) <= 0;
}
bool operator>=(const String &first, const String &second)
{
  // 操作结果：重载关系运算符<
  return strcmp(first.CStr(), second.CStr()) >= 0;
}

#endif // STRING_H