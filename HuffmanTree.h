#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include "HuffmanTreeNode.h"
#include "String.h"

// 哈夫曼树类
template <class CharType, class WeightType>
class HuffmanTree
{
protected:
  // 哈夫曼树的数据成员：
  HuffmanTreeNode<WeightType> *nodes; // 存储结点信息，nodes[0]未用
  CharType *LeafChars;                // 叶结点字符信息，LeafChars[0]未用
  String *LeafCharCodes;              // 叶结点字符编码信息，LeafCharCodes[0]未用
  int curPos;                         // 议码时从根结点到叶结点路径的当前结点
  int num;                            // 叶结点个数

  // 辅助函数：
  void Select(int cur, int &r1, int &r2);                       // nodes[1~cur]中选择双亲为0，权值最小的两个结点r1，r2
  void CreateHuffmanTree(CharType ch[], WeightType w[], int n); // 由字符、权值和字符个数构造哈夫曼树
  void DestroyHuffmanTree();                                    // 销毁哈夫曼树

public:
  // 哈夫曼树方法声明及重载编译系统默认方法声明：
  HuffmanTree(CharType ch[], WeightType w[], int n);                                           // 由字符、权值和字符个数构造哈夫曼树
  virtual ~HuffmanTree();                                                                      // 虚析构函数
  String EnCode(CharType ch);                                                                  // 编码
  LinkList<CharType> DeCode(String strCode);                                                   // 译码
  HuffmanTree(const HuffmanTree<CharType, WeightType> &copy);                                  // 复制构造函数
  HuffmanTree<CharType, WeightType> &operator=(const HuffmanTree<CharType, WeightType> &copy); // 赋值运算符重载
};

template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::Select(int cur, int &r1, int &r2)
{
  // 操作结果：nodes[1~cur]中选择双亲为0，权值最小的两个结点r1（最小），r2（次小）
  // Select实现策略的不同可以生成多个不同的哈夫曼树，从而每个字符可有多种不同的编码
  int pos, max = 1;
  for (pos = 1; pos <= cur; pos++)
  {
    // 找出nodes[1~cur]中双亲为0的结点权值最大的结点号来初始化r1、r2
    if (nodes[pos].parent == 0)
    {
      if (nodes[pos].weight > nodes[max].weight)
      {
        max = pos;
      }
    }
  }
  r1 = r2 = max;
  for (pos = 1; pos <= cur; pos++)
  {
    if (nodes[pos].parent == 0)
    {
      // 保证r1、r2结点的双亲为0
      if (nodes[pos].weight < nodes[r1].weight)
      {
        // 当前结点的权值比r1的权值还要小
        r2 = r1;
        r1 = pos;
      }
      else if (nodes[pos].weight >= nodes[r1].weight && nodes[pos].weight < nodes[r2].weight)
      {
        // 当前结点的权值比r1大，比r2小
        r2 = pos;
      }
    }
  }
}

template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::CreateHuffmanTree(CharType ch[], WeightType w[], int n)
{
  // 操作结果：由字符、权值和字符个数构造哈夫曼树
  num = n;           // 叶结点个数
  int m = 2 * n - 1; // 结点个数

  nodes = new HuffmanTreeNode<WeightType>[m + 1]; // nodes[0]未用
  LeafChars = new CharType[n + 1];                // LeafChars[0]未用
  LeafCharCodes = new String[n + 1];              // LeafCharCodes[0]未用
  int pos = 0;
  for (pos = 1; pos <= n; pos++)
  {
    // 存储叶结点信息
    nodes[pos].weight = w[pos - 1]; // 权值
    LeafChars[pos] = ch[pos - 1];   // 字符
                                    // cout << "第pos个字符为" << LeafChars[pos] << ", 第pos个字符权值为" << nodes[pos].weight << endl;
  }

  for (pos = n + 1; pos <= m; pos++)
  {
    // 建立哈夫曼树
    int r1, r2;
    Select(pos - 1, r1, r2); // nodes[1~pos-1]中选择双亲为0，权值最小的两个结点r1，r2，这里传的是引用，直接修改了r1和r2的值
    // cout << "生成第" << pos << "个结点，合并" << r1 << ", " << r2 << "两个结点" << endl;
    // 合并以r1，r2为根的树
    nodes[r1].parent = nodes[r2].parent = pos;               // r1，r2双亲为pos
    nodes[pos].leftChild = r1;                               // r1为pos的左孩子
    nodes[pos].rightChild = r2;                              // r2为pos的右孩子
    nodes[pos].weight = nodes[r1].weight + nodes[r2].weight; // pos的权为r1和r2的权值之和
  }

  for (pos = 1; pos <= n; pos++)
  {
    // 求n个叶结点字符的编码，求一条从叶结点到根结点的路径
    LinkList<char> charCode; // 暂存叶结点字符的编码信息
    for (unsigned int child = pos, parent = nodes[child].parent; parent != 0;
         child = parent, parent = nodes[child].parent)
    {
      // 从叶结点到根结点逆向求编码
      if (nodes[parent].leftChild == child)
      {
        charCode.Insert(1, '0'); // 左分支编码为'0'
      }
      else
      {
        charCode.Insert(1, '1'); // 右分支编码为'1'
      }
    }
    LeafCharCodes[pos] = charCode; // charCode中存储字符编码，LinkList居然可以赋值给String，有意思
                                   // cout << "第" << pos << "个叶结点字符为" << LeafChars[pos] << ", 编码为";
                                   // char c;
                                   // for (int i = 1; i <= charCode.Length(); i++)
                                   // {
                                   //     charCode.GetElem(i, c);
                                   //     cout << c;
                                   // }
                                   // cout << endl;
  }

  curPos = m; // 译码时从根结点开始，m为根
}

template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::DestroyHuffmanTree()
{
  // 操作结果：销毁哈夫曼树，释放内存空间
  delete[] nodes;
  delete[] LeafChars;
  delete[] LeafCharCodes;
}

template <class CharType, class WeighType>
HuffmanTree<CharType, WeighType>::HuffmanTree(CharType ch[], WeighType w[], int n)
{
  // 操作结果：由字符、权值和字符个数构造哈夫曼树
  CreateHuffmanTree(ch, w, n); // 由字符、权值和字符个数构造哈夫曼树
}

template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::~HuffmanTree()
{
  // 操作结果：销毁哈夫曼树，释放内存空间
  DestroyHuffmanTree();
}

template <class CharType, class WeightType>
String HuffmanTree<CharType, WeightType>::EnCode(CharType ch)
{
  // 操作结果：返回字符编码
  for (int pos = 1; pos <= num; pos++)
  {
    // 查找字符的位置
    if (LeafChars[pos] == ch)
    {
      return LeafCharCodes[pos]; // 找到字符，得到编码
    }
  }
  // throw Error("非法字符，无法编码");
  return NULL;
}

template <class CharType, class WeightType>
LinkList<CharType> HuffmanTree<CharType, WeightType>::DeCode(String strCode)
{
  // 操作结果：对编码串strCode进行译码，返回编码前的字符序列
  LinkList<CharType> charList; // 编码前的字符序列
  for (int pos = 0; pos < strCode.Length(); pos++)
  {
    // 处理每位编码
    if (strCode[pos] == '0')
    {
      curPos = nodes[curPos].leftChild; // '0'表示左分支
    }
    else
    {
      curPos = nodes[curPos].rightChild; // ’1‘表示右分支
    }
    if (nodes[curPos].leftChild == 0 && nodes[curPos].rightChild == 0)
    {
      // 译码时从根结点到叶结点路径的当前结点为叶结点
      charList.Insert(charList.Length() + 1, LeafChars[curPos]);
      curPos = 2 * num - 1; // curPos回归根起点
    }
  }
  return charList; // 返回编码前的字符序列
}

template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree(const HuffmanTree<CharType, WeightType> &copy)
{
  // 操作结果：拷贝构造函数，从无到有
  curPos = copy.curPos;
  num = copy.num;
  int m = 2 * num - 1; // 结点个数
  nodes = new HuffmanTreeNode<WeightType>[m + 1];
  LeafChars = new CharType[num + 1];
  LeafCharCodes = new String[num + 1];
  // nodes、LeafChars、LeafCharCodes赋值
  int pos;
  for (pos = 1; pos <= m; pos++)
  {
    // nodes挨个赋值
    nodes[pos].parent = copy.nodes[pos].parent;
    nodes[pos].leftChild = copy.nodes[pos].leftChild;
    nodes[pos].rightChild = copy.nodes[pos].rightChild;
    nodes[pos].weight = copy.nodes[pos].weight;
  }
  for (pos = 1; pos <= num; pos++)
  {
    // LeafChars和LeafCharCodes挨个赋值
    LeafChars[pos] = copy.LeafChars[pos];
    LeafCharCodes[pos] = copy.LeafCharCodes[pos];
  }
}

template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType> &HuffmanTree<CharType, WeightType>::operator=(const HuffmanTree<CharType, WeightType> &copy)
{
  // 操作结果：赋值运算符重载，从老到新
  if (&copy != this)
  {
    // 非自赋值
    DestroyHuffmanTree(); // 释放原树所占用内存空间，再根据copy重新申请
    curPos = copy.curPos;
    num = copy.num;
    int m = 2 * num - 1; // 结点个数
    nodes = new HuffmanTreeNode<WeightType>[m + 1];
    LeafChars = new CharType[num + 1];
    LeafCharCodes = new String[num + 1];
    // nodes、LeafChars、LeafCharCodes赋值
    int pos;
    for (pos = 1; pos <= m; pos++)
    {
      // nodes挨个赋值
      nodes[pos].parent = copy.nodes[pos].parent;
      nodes[pos].leftChild = copy.nodes[pos].leftChild;
      nodes[pos].rightChild = copy.nodes[pos].rightChild;
      nodes[pos].weight = copy.nodes[pos].weight;
    }
    for (pos = 1; pos <= num; pos++)
    {
      // LeafChars和LeafCharCodes挨个赋值
      LeafChars[pos] = copy.LeafChars[pos];
      LeafCharCodes[pos] = copy.LeafCharCodes[pos];
    }
  }
  return *this;
}

#endif // HUFFMAN_TREE_H
