#ifndef HUFFMAN_TREE_NODE_H
#define HUFFMAN_TREE_NODE_H

// 哈夫曼树结点类
template <class WeightType>
class HuffmanTreeNode
{
public:
  // 数据成员：
  WeightType weight;                          // 权数据域
  unsigned int parent, leftChild, rightChild; // 双亲、左右孩子域

  // 构造函数：
  HuffmanTreeNode();                                                        // 无参数的构造函数
  HuffmanTreeNode(WeightType w, int p = 0, int lChild = 0, int rChild = 0); // 已知权，双亲及左右孩子构造结构
};

template <class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode()
{
  // 操作结果：构造各数据域均为0的哈夫曼树结点
  parent = 0;
  leftChild = 0;
  rightChild = 0;
}

template <class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode(WeightType w, int p, int lChild, int rChild)
{
  // 操作结果：已知权，双亲及左右孩子构造结构
  weight = w;
  parent = p;
  leftChild = lChild;
  rightChild = rChild;
}

#endif // HUFFMAN_TREE_NODE_H