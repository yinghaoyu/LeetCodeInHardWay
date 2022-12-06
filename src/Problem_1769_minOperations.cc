#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 暴力解
  vector<int> minOperations1(string boxes)
  {
    int n = boxes.length();
    vector<int> ans(n);
    for (int i = 0; i < n; i++)
    {
      int j = i + 1;
      int k = i - 1;
      while (j < n)
      {
        ans[i] += (boxes[j] - '0') * (j - i);
        j++;
      }
      while (0 <= k)
      {
        ans[i] += (boxes[k] - '0') * (i - k);
        k--;
      }
    }
    return ans;
  }

  vector<int> minOperations2(string boxes)
  {
    int n = boxes.size();
    vector<int> res(n);

    // 从前往后遍历，计算将前面的所有球都移动到当前位置 i 上需要多少步操作。
    int pre = 0;  // 所有球移动到前一个位置需要多少步操作
    int cnt = 0;  // 前面有多少球
    for (int i = 1; i < n; i++)
    {
      if (boxes[i - 1] == '1')
      {
        cnt++;
      }
      res[i] = pre + cnt;
      pre += cnt;
    }

    // 从后往前遍历，计算将后面的所有球都移动到当前位置 i 上需要多少步操作。
    pre = 0, cnt = 0;
    for (int i = n - 2; i >= 0; i--)
    {
      if (boxes[i + 1] == '1')
        cnt++;
      res[i] += pre + cnt;
      pre += cnt;
    }

    return res;
  }
};

bool isVectorEqual(vector<int> a, vector<int> b)
{
  if (a.size() != b.size())
  {
    return false;
  }
  for (int i = 0; i < a.size(); i++)
  {
    if (a[i] != b[i])
    {
      return false;
    }
  }
  return true;
}

void testMinOperations()
{
  Solution s;
  vector<int> n1 = {1, 1, 3};
  vector<int> n2 = {11, 8, 5, 4, 3, 4};
  EXPECT_TRUE(isVectorEqual(n1, s.minOperations1("110")));
  EXPECT_TRUE(isVectorEqual(n2, s.minOperations1("001011")));
  EXPECT_SUMMARY;
}

int main()
{
  testMinOperations();
  return 0;
}
