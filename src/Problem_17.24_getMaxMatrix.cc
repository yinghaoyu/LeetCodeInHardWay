#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

class Solution
{
 public:
  // @sa
  // https://www.bilibili.com/video/BV1pw411M7Du/
  // https:leetcode.cn/problems/max-submatrix-lcci/solutions/137568/zhe-yao-cong-zui-da-zi-xu-he-shuo-qi-you-jian-dao-/
  vector<int> getMaxMatrix(vector<vector<int>>& matrix)
  {
    int n = matrix.size();
    int m = matrix[0].size();
    // 记录最大值
    int max = INT32_MIN;
    // 保存最大子矩阵的左上角和右下角的行列坐标
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    vector<int> nums(m);
    // 以up为上边，从上而下扫描
    for (int up = 0; up < n; up++)
    {
      // 每次更换子矩形上边，就要清空nums，重新计算每列的和
      std::fill(nums.begin(), nums.end(), 0);
      // 子矩阵的下边，从i到N-1，不断增加子矩阵的高
      for (int down = up; down < n; down++)
      {
        // 如下代码就是题目`Problem_0053_maxSubArray.cc`的附加问题:
        // 子数组中找到拥有最大累加和的子数组，只不过这里变成了二维
        for (int l = 0, r = 0, pre = INT32_MIN; r < m; r++)
        {
          // 我们只是不断增加其高，也就是下移矩阵下边，所有这个矩阵每列的和只需要加上新加的哪一行的元素
          nums[r] += matrix[down][r];
          // 因为我们求dp[i]的时候只需要dp[i-1]和nums[i],所有在我们不断更新nums数组时就可以求出当前位置的dp_i
          if (pre >= 0)
          {
            pre += nums[r];
          }
          else
          {
            pre = nums[r];
            // 自立门户
            l = r;
          }
          if (pre > max)
          {
            max = pre;
            a = up;
            b = l;
            c = down;
            d = r;
          }
        }
      }
    }
    return {a, b, c, d};
  }
};
