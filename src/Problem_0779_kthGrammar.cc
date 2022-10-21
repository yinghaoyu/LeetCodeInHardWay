#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string process(char c) { return c == '0' ? "01" : "10"; }
  // 暴力解
  int kthGrammar1(int n, int k)
  {
    string str = "0";
    for (int i = 0; i < n; i++)  // n <= 30
    {
      string tmp;
      for (int j = 0; j < str.length(); j++)  // k <= 2 ^ 30 -1
      {
        tmp += process(str[j]);
      }
      str.swap(tmp);
    }
    return str[k - 1] == '0' ? 0 : 1;
  }

  int bitCount(int x)
  {
    int c;
    c = (x & 0x55555555) + ((x >> 1) & 0x55555555);
    c = (c & 0x33333333) + ((c >> 2) & 0x33333333);
    c = (c & 0x0f0f0f0f) + ((c >> 4) & 0x0f0f0f0f);
    c = (c & 0x00ff00ff) + ((c >> 8) & 0x00ff00ff);
    c = (c & 0x0000ffff) + ((c >> 16) & 0x0000ffff);
    return c;
  }

  // 先不考虑题设，
  // 用前缀树对叶子节点进行编码，从根节点开始，往左孩子走+0，往右孩子走+1
  // 以最后一个节点(从下标1开始算，第8个叶子节点)为例，
  // 因为它从根节点开始，往右孩子走了3次，所以它的前缀码为111(二进制)
  //
  // 结合题设，
  // 可以发现，往左走不翻转，往右走会翻转，翻转2次会抵消
  // 根据前缀码111，说明第8个叶子节点翻转了3次，0 -> 1 -> 0 -> 1，因此可以得到第8个叶子节点字符为1
  //
  // 总结，第k个叶子节点的前缀码是 k - 1(因为前缀编码是从000开始的)
  //
  // 所以只需要计算 k - 1 在二进制中1的个数，再检查他的奇偶性就可以了
  //               0
  //          /          \
  //        0              1
  //     /    \          /    \
  //   0       1        1       0
  //  / \     /  \     /  \    / \
  // 0   1   1    0   1    0  0   1
  int kthGrammar2(int n, int k) { return bitCount(k - 1) & 1; }

  //看样例找规律
  // 0
  // 01
  // 0110
  // 01101001
  //可以看出，后一半和前一半是取反的，所以如果k在后一半，那答案就是!kthGrammar(n-1,k-(1<<(n-2))) 否则是 kthGrammar(n-1,k)
  //注：1<<(n-2)是当前长度的一半，k在后一半时，需要转换到前一半对应位置: k-(1<<(n-2))

  int kthGrammar3(int n, int k)
  {
    if (n == 1)
      return 0;
    if (n == 2)
      return k != 1;  // k=1,return 0; k=2; return 1;
    if (k > (1 << (n - 2)))
      return !kthGrammar3(n - 1, k - (1 << (n - 2)));
    return kthGrammar3(n - 1, k);
  }

  //               0
  //          /          \
  //        0              1
  //     /    \          /    \
  //   0       1        1       0
  //  / \     /  \     /  \    / \
  // 0   1   1    0   1    0  0   1
  int kthGrammar4(int n, int k)
  {
    if (n == 1)
      return 0;
    //算出这个数字的父节点是多少，父节点是上一行(n - 1)的第(k + 1) /  2个
    int father = kthGrammar4(n - 1, (k + 1) >> 1);
    //如果k是奇数，那它和父节点一样，否则，它和父节点相反(0->1, 1->0)
    return (k & 1) == 1 ? father : 1 ^ father;
  }

  // 构建的包含 n 行的表看成是一棵 满二叉树
  // 目标字符，即第 n 行中第 k 个字符，为满二叉树最后一层的叶子结点
  // 从 1 开始对满二叉树进行编号，
  // 根结点编号为 1，根结点的左孩子编号为 2 * 1，右孩子编号为 2 * 1 + 1
  // 编号为 i 的结点，其左孩子编号为 2 * i, 右孩子编号为 2 * i + 1
  // 目标字符的编号为 2^n - 1 + k
  //
  // 根据题意，不难发现：非叶子结点的值与其左孩子的值相同，与其右孩子的值相反！
  // 可以从目标字符（叶子结点），反向遍历二叉树到根结点，假设目标字符的值为 0，
  // 根据上面的结论，我们可以反推出根结点的值，如果推测出根结点的值为 0，说明假设成立，
  // 即目标字符的值为 0，如果推测出根结点的值为 1，这与已知根结点的值为 0 矛盾，假设不成立，
  // 即目标字符的值为 1。
  int kthGrammar5(int n, int k)
  {
    // ptr 初始指向目标字符，即第 n 行中第 k 个字符
    int ptr = (1 << n) - 1 + k;
    // 假设目标字符的值为 0
    int val = 0;
    // 从目标字符到根结点进行反向遍历
    while (ptr > 1)
    {
      // 如果 ptr 指向结点的编号为奇数，
      // 则 ptr 指向一个右孩子，其值与父结点的值相反，翻转结点值，即其父结点的值
      // 如果 ptr 指向结点的编号为偶数，
      // 则 ptr 指向一个左孩子，其值与父结点的值相同，值不变
      if (ptr & 1)
      {
        //翻转结点的值，即 0->1 或 1->0
        val ^= 1;
      }
      // ptr 指向父结点
      ptr >>= 1;
    }
    // while 循环结束以后，
    // ptr = 1，即指向根结点，此时的 val 为根结点的值
    // 如果 val = 0，那么假设成立，即目标字符的值为 0，返回 0，即 val
    // 如果 val = 1，那么假设不成立，即目标字符的值为 1，返回 1，即 val
    // 综上，最终 val 的值就是目标字符的真实值
    return val;
  }
};

void testkthGrammar()
{
  Solution s;
  EXPECT_EQ_INT(0, s.kthGrammar1(1, 1));
  EXPECT_EQ_INT(0, s.kthGrammar1(2, 1));
  EXPECT_EQ_INT(1, s.kthGrammar1(2, 2));

  EXPECT_EQ_INT(0, s.kthGrammar2(1, 1));
  EXPECT_EQ_INT(0, s.kthGrammar2(2, 1));
  EXPECT_EQ_INT(1, s.kthGrammar2(2, 2));

  EXPECT_EQ_INT(0, s.kthGrammar3(1, 1));
  EXPECT_EQ_INT(0, s.kthGrammar3(2, 1));
  EXPECT_EQ_INT(1, s.kthGrammar3(2, 2));

  EXPECT_EQ_INT(0, s.kthGrammar4(1, 1));
  EXPECT_EQ_INT(0, s.kthGrammar4(2, 1));
  EXPECT_EQ_INT(1, s.kthGrammar4(2, 2));

  EXPECT_EQ_INT(0, s.kthGrammar5(1, 1));
  EXPECT_EQ_INT(0, s.kthGrammar5(2, 1));
  EXPECT_EQ_INT(1, s.kthGrammar5(2, 2));
  EXPECT_SUMMARY;
}
int main()
{
  testkthGrammar();
  return 0;
}
