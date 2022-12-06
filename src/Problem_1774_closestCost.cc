#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 暴力递归
  void process(vector<int> &costs, int target, int i, int curCost, int &res)
  {
    if (curCost - target >= std::abs(res - target))
    {
      // 当前方案成本价 >= 已有最优方案的差值，后续选择只会使得成本更大，与target的差值更大
      // 我们可以停止继续往下搜索，及时回溯
      return;
    }
    if (std::abs(curCost - target) <= std::abs(res - target))
    {
      // 当前方案成本价与target的差值 <= 已有最优方案的与target的差值
      // 如果当前方案成本更接近target，那么更新最优方案为当前方案
      if (std::abs(curCost - target) < std::abs(res - target))
      {
        res = curCost;
      }
      else
      {
        // 如果当前方案成本与已有方案同样接近target，那么选择其中更小的成本值
        res = std::min(res, curCost);
      }
    }
    if (i >= costs.size())
    {
      // 如果所有元素已选择完毕，结束
      return;
    }
    process(costs, target, i + 1, curCost, res);
    process(costs, target, i + 1, curCost + costs[i], res);
    process(costs, target, i + 1, curCost + 2 * costs[i], res);
  }

  int closestCost1(vector<int> &baseCosts, vector<int> &toppingCosts, int target)
  {
    // 冰淇淋基料的最小值min，
    int min = *std::min_element(baseCosts.begin(), baseCosts.end());
    // 其他任何方案成本只会比min更大，与target的差值更大，此时直接返回min
    if (min >= target)
    {
      return min;
    }
    // 将 res 初始化 为 min，
    int res = min;
    // 对每一种冰淇淋基料，进行配料的回溯
    for (auto &base : baseCosts)
    {
      // idx 代表待选择配料索引，
      process(toppingCosts, target, 0, base, res);
    }
    // 返回最优方案成本
    return res;
  }

  int closestCost2(vector<int> &baseCosts, vector<int> &toppingCosts, int target)
  {
    // 冰淇淋基料的最小值min，
    int min = *std::min_element(baseCosts.begin(), baseCosts.end());
    // 其他任何方案成本只会比min更大，与target的插值更大，此时直接返回min
    if (min >= target)
    {
      return min;
    }
    int upper = 2 * target - min;
    // cost >= upper的方案
    // 其std::abs(cost - target) >= std::abs(target - min)，这时完全可以直接选min
    // 只需要考虑成本在 [min, upper-1] 间的方案是否存在
    vector<bool> dp(upper);
    // base，基料必选
    for (int baseCost : baseCosts)
    {
      // 不考虑区间外的方案
      if (baseCost < upper)
      {
        dp[baseCost] = true;
      }
    }
    // dp迭代，在基料的基础上选择辅料
    for (int toppingCost : toppingCosts)
    {
      // 为何倒序遍历dp？
      // 对于每个辅料，假如顺序遍历dp
      // dp[0]=true，更新dp[0+2x]=true， dp[0+x]=true
      // 那么当遍历到dp[x]时，又会更新dp[x+2x]=true，dp[x+x]=true
      // dp[3x] = true ？？？这相当于使用了3份辅料i，肯定不对
      for (int j = upper - 1; j >= min; --j)
      {
        // 每种辅料可以1份或2份，更新对应的dp为true，区间外不予考虑
        if (dp[j] && (j + toppingCost < upper))
        {
          dp[j + toppingCost] = true;
        }
        if (dp[j] && (j + 2 * toppingCost < upper))
        {
          dp[j + 2 * toppingCost] = true;
        }
      }
    }
    // 在 [min, upper-1]所有存在的方案种找出与target最接近的方案
    int ans = min;
    for (int i = min + 1; i < upper; ++i)
    {
      if (dp[i])
      {
        // 更接近
        if (std::abs(i - target) < std::abs(ans - target))
        {
          ans = i;
        }
        else if (std::abs(i - target) == std::abs(ans - target))
        {
          // 同样接近，选择更小成本
          ans = std::min(ans, i);
        }
      }
    }
    return ans;
  }
};

void testClosestCost()
{
  Solution s;
  vector<int> b1 = {1, 7};
  vector<int> t1 = {3, 4};

  vector<int> b2 = {2, 3};
  vector<int> t2 = {4, 5, 100};

  vector<int> b3 = {3, 10};
  vector<int> t3 = {2, 5};
  EXPECT_EQ_INT(10, s.closestCost1(b1, t1, 10));
  EXPECT_EQ_INT(17, s.closestCost1(b2, t2, 18));
  EXPECT_EQ_INT(8, s.closestCost1(b3, t3, 9));
  EXPECT_EQ_INT(10, s.closestCost2(b1, t1, 10));
  EXPECT_EQ_INT(17, s.closestCost2(b2, t2, 18));
  EXPECT_EQ_INT(8, s.closestCost2(b3, t3, 9));
  EXPECT_SUMMARY;
}

int main()
{
  testClosestCost();
  return 0;
}
