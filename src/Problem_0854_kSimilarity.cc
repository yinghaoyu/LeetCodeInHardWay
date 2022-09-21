#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minSwap(const string &s1, const string &s2, const int &pos)
  {
    int tot = 0;
    for (int i = pos; i < s1.size(); i++)
    {
      tot += s1[i] != s2[i];
    }
    return (tot + 1) / 2;
  }

  // dfs
  int kSimilarity1(string s1, string s2)
  {
    string str1, str2;
    for (int i = 0; i < s1.size(); i++)  // 相同字符不用参与交换
    {
      if (s1[i] != s2[i])
      {
        str1.push_back(s1[i]);
        str2.push_back(s2[i]);
      }
    }
    int n = str1.size();
    if (n == 0)
    {
      return 0;
    }
    // 因为每一次有效交换，可以将s1的字符调整到与s2相同，这样只需调整n-1个字符，最后一个字符也一定相等
    int ans = n - 1;  // 最多交换n - 1
    function<void(int, int)> dfs = [&](int pos, int cost) {
      if (cost > ans)
      {
        return;
      }
      while (pos < n && str1[pos] == str2[pos])
      {
        pos++;
      }
      if (pos == n)
      {
        ans = min(ans, cost);
        return;
      }
      /* 当前状态的交换次数下限大于等于当前的最小交换次数 */
      if (cost + minSwap(str1, str2, pos) >= ans)
      {
        return;
      }
      for (int i = pos + 1; i < n; i++)
      {
        if (str1[i] == str2[pos])
        {
          std::swap(str1[i], str1[pos]);
          dfs(pos + 1, cost + 1);
          std::swap(str1[i], str1[pos]);
        }
      }
    };
    dfs(0, 0);
    return ans;
  }

  // bfs
  int kSimilarity2(string s1, string s2)
  {
    int N = s1.size();
    queue<pair<string, int>> q;
    unordered_set<string> visit;
    q.emplace(s1, 0);
    visit.emplace(s1);
    for (int step = 0;; step++)
    {
      int sz = q.size();
      for (int i = 0; i < sz; i++)
      {
        // cur 表示当前 s1 调整后的新字符串
        // pos 表示当前cur[0 ... pos-1] == s2[0 ... pos-1]，需要从pos开始尝试交换
        string cur = q.front().first;
        int pos = q.front().second;
        q.pop();
        if (cur == s2)
        {
          // 满足条件
          return step;
        }
        while (pos < N && cur[pos] == s2[pos])
        {
          // 剪枝，如果 cur[0 ... pos] 和s2[0 ... pos] 之间的字符相等，就不用尝试交换
          pos++;
        }
        // 从 pos 开始尝试交换
        for (int j = pos + 1; j < N; j++)
        {
          // 这里cur[pos] != s2[pos]
          if (cur[j] != s2[j] && cur[j] == s2[pos])
          {
            // 当 cur[j] == s2[j] 时，交换cur[pos]和cur[j]反而增加了交换次数
            // 同时最终结果又不一定符合条件
            // 剪枝，只在 cur[j] != s2[j] 时去交换
            std::swap(cur[pos], cur[j]);
            if (!visit.count(cur))
            {
              visit.emplace(cur);
              q.emplace(cur, pos + 1);
            }
            std::swap(cur[pos], cur[j]);
          }
        }
      }
    }
  }

  void process(string &s1, string &s2, int index, int cost, int &step)
  {
    if (index == s1.size())
    {
      // 这时s1 == s2，需要结算答案
      step = std::min(step, cost);
      return;
    }
    if (cost >= step)
    {
      // 如果cost >= step，说明没有必要继续尝试
      return;
    }

    if (s1[index] != s2[index])  // 不相等才交换
    {
      for (int i = index + 1; i < s1.size(); i++)
      {
        // 这里已经满足s1[index] != s2[index]
        // 如果s1[i] == s2[i]，这时交换反而增加了交换次数
        if (s1[i] != s2[i] && s1[i] == s2[index])
        {
          swap(s1[index], s1[i]);
          // 尝试下一个位置，cost + 1
          process(s1, s2, index + 1, cost + 1, step);
          swap(s1[index], s1[i]);
        }
      }
    }
    else
    {
      // 本次没交换，cost不变
      process(s1, s2, index + 1, cost, step);
    }
  }

  int kSimilarity3(string s1, string s2)
  {
    int ans = s1.length() - 1;
    process(s1, s2, 0, 0, ans);
    return ans;
  }
};

void testKSimilarity()
{
  Solution s;
  EXPECT_EQ_INT(1, s.kSimilarity1("ab", "ba"));
  EXPECT_EQ_INT(2, s.kSimilarity1("abc", "bca"));

  EXPECT_EQ_INT(1, s.kSimilarity2("ab", "ba"));
  EXPECT_EQ_INT(2, s.kSimilarity2("abc", "bca"));

  EXPECT_EQ_INT(1, s.kSimilarity3("ab", "ba"));
  EXPECT_EQ_INT(2, s.kSimilarity3("abc", "bca"));
  EXPECT_SUMMARY;
}

int main()
{
  testKSimilarity();
  return 0;
}
