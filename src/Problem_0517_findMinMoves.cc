#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

class Solution
{
 public:
  int findMinMoves(vector<int>& machines)
  {
    int n = machines.size();
    int sum = accumulate(machines.begin(), machines.end(), 0);
    if (sum % n != 0)
    {
      return -1;
    }
    int avg = sum / n;   // 每台洗衣机最终要求的衣服数量一定是平均值
    int leftSum = 0;     // 左侧累加和
    int leftNeed = 0;    // 左边还需要多少件衣服
    int rightNeed = 0;   // 右边还需要多少件衣服
    int bottleNeck = 0;  // 每一步的瓶颈
    int ans = 0;
    for (int i = 0; i < n; leftSum += machines[i], i++)
    {
      leftNeed = i * avg - leftSum;
      rightNeed = (n - i - 1) * avg - (sum - leftSum - machines[i]);
      if (leftNeed > 0 && rightNeed > 0)
      {
        bottleNeck = leftNeed + rightNeed;
      }
      else
      {
        bottleNeck = std::max(std::abs(leftNeed), std::abs(rightNeed));
      }
      ans = std::max(bottleNeck, ans);
    }
    return ans;
  }
};
