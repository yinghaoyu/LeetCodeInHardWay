#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 贪心
  string maximumBinaryString(string binary)
  {
    int n = binary.length();
    for (int i = 0, j = 0; i < n; i++)
    {
      // 找到第一个 0
      if (binary[i] == '0')
      {
        while (j < n && binary[j] == '1')
        {
          // 找到第二个 0
          j++;
        }
        if (j < n)
        {
          // 先通过操作 2 把 10 变成 01
          // 再通过操作 1 把 00 变成 10
          // 例如：
          // 先把 0111110 变成 0011111
          // 再把 0011111 变成 1011111
          binary[i] = '1';
          binary[i + 1] = '0';
          binary[j] = '0';
        }
      }
    }
    return binary;
  }
};
