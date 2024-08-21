#include <vector>

using namespace std;

class Solution
{
 public:
  // 注意到每次计算形式都是 a + 1 / b
  // 只有最后一项计算形式是 cont[i]，可以由 cont[i] + 0 / 1 生成
  // 因此我们初始时，可以设 n = 0， m = 1，这样就可以循环调用 a + 1 / b 了
  // a + n / m 等价于 (a * m + n) / m
  vector<int> fraction(vector<int>& cont)
  {
    int n = 0;  // 分子
    int m = 1;  // 分母
    for (int i = cont.size() - 1; i >= 0; i--)
    {
      n = cont[i] * m + n;
      std::swap(n, m);
    }
    // 理论上返回{n, m}
    // 但我们最后多进行了 1 次交换，这里返回{m, n}
    return {m, n};
  }
};
