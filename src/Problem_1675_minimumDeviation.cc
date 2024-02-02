#include <set>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 第一步:先把所有奇数乘2,这样就等价于只有操作1.
  // 第二步:操作1的只会减少某个数的值,而只有减少最大值结果才可能更优.
  // 第三步:使用平衡树或堆维护最大值,直到最大值为奇数不能再操作为止.
  int minimumDeviation(vector<int>& nums)
  {
    set<int> s;
    for (int num : nums)
    {
      if (num & 1)
      {
        // 把所有奇数 * 2放进有序列表
        // 这样所有元素都是偶数
        s.insert(num * 2);
      }
      else
      {
        s.insert(num);
      }
    }
    int ans = *s.rbegin() - *s.begin();
    while (ans > 0 && (*s.rbegin() & 1) == 0)
    {
      int max = *s.rbegin();
      s.erase(max);
      s.insert(max / 2);
      ans = std::min(ans, *s.rbegin() - *s.begin());
    }
    return ans;
  }
};
