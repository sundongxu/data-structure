#ifndef C_LARGE_INT_H
#define C_LARGE_INT_H

#include <iostream>
#include <cstring>
#include "DbLinkList.h"

// 非负大整数类
class CLargeInt
{
  protected:
    // 非负大整数的数据成员
    DbLinkList<unsigned int> num; // 每个结点的数据域存储一个整数，第一个结点的数据域为大整数的最高位上的数字

    // 辅助函数
    CLargeInt Multi10Power(CLargeInt &largeInt, unsigned int exponent) const; // 乘10的阶幂

  public:
    CLargeInt(unsigned int n = 0);                                                          // 构造函数
    CLargeInt(char *strNum);                                                                // 构造函数
    CLargeInt &operator=(const CLargeInt &copy);                                            // 赋值运算符重载
    CLargeInt operator+(const CLargeInt &largeInt) const;                                   // 加法运算符重载(加上一个非负大整数)
    CLargeInt operator*(unsigned int digit) const;                                          // 乘法运算符重载(乘以一位数)
    CLargeInt operator*(const CLargeInt &largeInt) const;                                   // 乘法运算符重载(乘以一个非负大整数)
    friend std::ostream &operator<<(std::ostream &outStream, const CLargeInt &outLargeInt); // 重载运算符<<
};

CLargeInt CLargeInt::Multi10Power(CLargeInt &largeInt, unsigned int exponent) const
{
    // 操作结果：乘10的阶幂，直接在num链表后面加上exponent个0
    int len = largeInt.num.Length();
    for (int i = 1; i <= exponent; i++)
    {
        largeInt.num.Insert(len + i, 0);
    }
    return largeInt;
}

CLargeInt CLargeInt::operator*(unsigned int digit) const
{
    // 操作结果：乘法运算符重载(乘以一位数)
    // 原数的每一位都与digit相乘，每一位都可能进位
    CLargeInt tmpLargeInt;               // 存放临时结果
    unsigned int digit1 = 0, digit2 = 0; // 各位上的数字和乘digit后的该位数
    unsigned int carry = 0;              // 进位
    unsigned int pos = num.Length();     // 本数位数
    unsigned int tmp;
    tmpLargeInt.num.Delete(1, tmp); // 多了个0
    while (pos > 0)
    {
        // 从个位开始求乘积
        num.GetElem(pos--, digit1); // digit1表示原数第len-pos+1个位置上的数
        digit2 = (digit * digit1 + carry) % 10;
        tmpLargeInt.num.Insert(1, digit2);
        carry = (digit * digit1 + carry) / 10;
    }
    if (carry > 0)
    {
        tmpLargeInt.num.Insert(1, carry);
    }
    return tmpLargeInt;
}

CLargeInt::CLargeInt(unsigned int n)
{
    // 构造函数，参数为无符号整数n，依次取n的每一位赋值给num中结点
    // 获取n的位数
    unsigned int digit1 = 0;
    while (n > 10)
    {
        digit1 = n % 10;
        num.Insert(1, digit1);
        n = n / 10;
    }
    num.Insert(1, n); // 最后需要把n插入，此时n表示原大数的个位数字
}

CLargeInt::CLargeInt(char *strNum)
{
    // 构造函数，参数为字符串strNum，依次取strNum的每一位赋值给num中结点
    unsigned int len = strlen(strNum);
    for (int pos = 1; pos <= len; pos++)
    {
        num.Insert(pos, strNum[pos]);
    }
}

CLargeInt &CLargeInt::operator=(const CLargeInt &copy)
{
    // 赋值运算符重载
    if (&copy != this)
    {
        // 非自赋值
        num = copy.num;
    }
    return *this;
}

CLargeInt CLargeInt::operator+(const CLargeInt &largeInt) const
{
    // 操作结果：加法运算符重载(加上一个非负大整数)
    CLargeInt tmpLargeInt;       // 存放临时计算结果
    unsigned int carry = 0;      // 进位
    unsigned int digit1, digit2; // 表示非负大整数的各位
    unsigned int pos1, pos2;     // 表示非负大整数的各位的位置

    pos1 = num.Length();          // 被加数的个位位置
    pos2 = largeInt.num.Length(); // largeInt的个位位置

    unsigned int tmp;
    tmpLargeInt.num.Delete(1, tmp);
    while (pos1 > 0 && pos2 > 0)
    {
        // 从个位开始求和
        num.GetElem(pos1--, digit1);                               // 被加数的一位
        largeInt.num.GetElem(pos2--, digit2);                      // 加数的一位
        tmpLargeInt.num.Insert(1, (digit1 + digit2 + carry) % 10); // 插入和的新的一位
        carry = (digit1 + digit2 + carry) / 10;                    // 新的进位
    }

    while (pos1 > 0)
    {
        // 被加数还有位没有求和
        num.GetElem(pos1--, digit1);                      // a的一位
        tmpLargeInt.num.Insert(1, (digit1 + carry) % 10); // 插入和的新的一位
        carry = (digit1 + carry) / 10;                    // 新的进位
    }

    while (pos2 > 0)
    {
        // 加数还有位没有求和
        largeInt.num.GetElem(pos2--, digit2);             // 加数的一位
        tmpLargeInt.num.Insert(1, (digit2 + carry) % 10); // 插入和的新的一位
        carry = (digit2 + carry) / 10;                    // 新的进位
    }

    if (carry > 0)
    {
        // 存在进位
        tmpLargeInt.num.Insert(1, carry); // 向高位进位
    }

    return tmpLargeInt;
}

CLargeInt CLargeInt::operator*(const CLargeInt &largeInt) const
{
    // 操作结果：乘法运算符重载(乘以一个非负大整数)
    CLargeInt tmpLargeInt;           // 存放临时结算结果
    unsigned int digit;              // 表示一位数字
    unsigned int len = num.Length(); // 位数

    for (int pos = len; pos > 0; pos--)
    {
        // digit依次乘当前非负大整数的各位
        num.GetElem(pos, digit); // 取出一位
        CLargeInt tmmpLargeInt = largeInt * digit;
        tmpLargeInt = tmpLargeInt + Multi10Power(tmmpLargeInt, len - pos); // 将当前非负大整数的每一位与largeInt的乘积进行累加
    }

    return tmpLargeInt;
}

std::ostream &operator<<(std::ostream &outStream, const CLargeInt &outLargeInt)
{
    // 操作结果：输出运算符重载
    unsigned int digit = 0;
    unsigned int len = outLargeInt.num.Length();
    for (int pos = 1; pos <= len; pos++)
    {
        // 从高位到低位逐个输出字符
        outLargeInt.num.GetElem(pos, digit);
        outStream << digit;
    }
    return outStream;
}

#endif // C_LARGE_INT_H