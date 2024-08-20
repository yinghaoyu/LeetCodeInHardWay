#include <vector>

using namespace std;

// @sa
// https://leetcode.cn/problems/gray-code/solutions/13637/gray-code-jing-xiang-fan-she-fa-by-jyd/

// 设 n 阶格雷码集合为 G(n)，则 G(n+1) 阶格雷码可以通过以下三步得到：

// 1. 给 G(n) 阶格雷码每个元素二进制形式前面添加 0，得到 G'(n)；
// 2. 设 G(n) 集合倒序（镜像）为 R(n)，给 R(n) 每个元素二进制形式前面添加 1，得到 R'(n)；
// 3. G(n+1)=G'(n)∪ R'(n) 拼接两个集合即可得到下一阶格雷码。
// 根据以上规律，我们可从 0 阶格雷码推导致任何阶格雷码。

class Solution
{
 public:
  // 格雷码
  vector<int> grayCode(int n)
  {
    vector<int> ans;
    ans.push_back(0);
    int head = 1;
    for (int i = 0; i < n; i++)
    {
      for (int j = ans.size() - 1; j >= 0; j--)
      {
        ans.push_back(head + ans[j]);
      }
      head <<= 1;
    }
    return ans;
  }
};
