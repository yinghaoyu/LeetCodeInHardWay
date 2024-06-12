#include <vector>

using namespace std;

// 例如 A B A B C B C D B
// 模拟下投票过程:
//    前面两列是候选人，第三列是抵消者 , X 是抵消记号
//
//    第 N 轮情况      输入      说明
//    A                A         第 1 个候选人空缺，选择为 A
//
//    A B              B         第 2 个候选人空缺，选择为 B
//
//    A B              A         候选人 A 票数+1
//    A
//
//    A B              B         候选人 B 票数+1
//    A B
//
//    X X X            C         抵消一次
//    A B
//
//    X X X            B         候选人 B 票数+1
//    A B
//      B
//
//    X X X            C         再抵消一次
//    X X X
//      B
//
//    X X X            D         第一个候选人空缺，选用 D
//    X X X
//    D B
//
//    X X X
//    X X X            B         候选人 B 票数+1
//    D B
//      B
//
// 观察最后的图像，可以看到
//  1. 最终的候选者并不一定是要找的众数，比如数字 D
//  2. 但是消掉的数字一定不是要找的众数.
//     因为被消的任一行 X 表示的数字互不相同, 一个数字在所有 X 矩阵中出现的次数最多的情况只能是
//     在每个行都只出现一次的情况。而被消掉的行数不超过 n/3. 所以 X 中的任何数字，都不会是目标。
//
//  最终我们只需要再次检查下最终剩余的两个候选人，确定其是否真正为要找的众数

// 摩尔投票

class Solution
{
 public:
  vector<int> majorityElement(vector<int>& nums) { return majority(nums, 3); }

  vector<int> majority(vector<int>& nums, int k)
  {
    // 注意这里的 --k
    vector<vector<int>> cands(--k, vector<int>(2));
    for (int num : nums)
    {
      // 计数或者抵消数字
      update(cands, k, num);
    }
    vector<int> ans;
    collect(cands, k, nums, nums.size(), ans);
    return ans;
  }

  void update(vector<vector<int>>& cands, int k, int num)
  {
    for (int i = 0; i < k; i++)
    {
      // num 已存在，增加计数
      if (cands[i][0] == num && cands[i][1] > 0)
      {
        cands[i][1]++;
        return;
      }
    }
    for (int i = 0; i < k; i++)
    {
      // num 第一次计数，选一个空位置保存
      if (cands[i][1] == 0)
      {
        cands[i][0] = num;
        cands[i][1] = 1;
        return;
      }
    }
    for (int i = 0; i < k; i++)
    {
      // num 没位置保存了，那就抵掉 cands 的数
      if (cands[i][1] > 0)
      {
        cands[i][1]--;
      }
      // 注意这里没有 return，num 去抵消 k 份数
    }
  }

  void collect(vector<vector<int>>& cands, int k, vector<int>& nums, int n, vector<int> ans)
  {
    for (int i = 0, cur, real; i < k; i++)
    {
      if (cands[i][1] > 0)
      {
        cur = cands[i][0];
        real = 0;
        for (int num : nums)
        {
          if (cur == num)
          {
            real++;
          }
        }
      }
      // 前面已有 --k，k + 1 只是取原来的值
      if (real > n / (k + 1))
      {
        ans.push_back(cur);
      }
    }
  }
};
