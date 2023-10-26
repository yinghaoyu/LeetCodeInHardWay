#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 private:
  bool dfs(string& str, int index, int pre, int target)
  {
    if (index == str.length())
    {
      return pre == target;
    }
    int num = 0;
    for (int i = index; i < str.length(); i++)
    {
      num = num * 10 + str[i] - '0';
      if (pre + num > target)
      {
        break;
      }
      if (dfs(str, i + 1, pre + num, target))
      {
        return true;
      }
    }
    return false;
  }

 public:
  int punishmentNumber(int n)
  {
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
      string str = to_string(i * i);
      if (dfs(str, 0, 0, i))
      {
        ans += i * i;
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(182, s.punishmentNumber(10));
  EXPECT_EQ_INT(1478, s.punishmentNumber(37));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
