#include <algorithm>
#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/pile-box-lcci/solutions/140489/c-12xing-dai-ma-jie-jue-by-lzn27/
class Solution
{
 public:
  // 利用最长递增子序列
  int pileBox(vector<vector<int>>& box)
  {
    // 先对box数组按照一个维度进行排序，得到sorted_box序列
    // 那么最终答案的序列就一定是sorted_box序列的某个子序列（这点很重要）
    std::sort(box.begin(), box.end(), [](vector<int>& x, vector<int>& y) { return x[2] < y[2]; });
    int n = box.size();
    vector<int> dp(n);
    dp[0] = box[0][2];
    int ans = dp[0];
    for (int i = 1; i < box.size(); i++)
    {
      int maxh = 0;
      for (int j = 0; j < i; j++)
      {
        if (box[j][0] < box[i][0] && box[j][1] < box[i][1] && box[j][2] < box[i][2])
        {
          maxh = std::max(maxh, dp[j]);
        }
      }
      dp[i] = maxh + box[i][2];
      ans = std::max(ans, dp[i]);
    }
    return ans;
  }
};
