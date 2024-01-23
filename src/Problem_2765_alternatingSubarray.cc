#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int alternatingSubarray(vector<int>& nums)
  {
    int ans = -1;
    // 假设nums[start...end]是满足的序列
    for (int start = 0; start < nums.size(); start++)
    {
      for (int end = start + 1; end < nums.size(); end++)
      {
        int len = end - start + 1;
        if (nums[end] - nums[start] == (len - 1) % 2)
        {
          ans = std::max(ans, len);
        }
        else
        {
          break;
        }
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {2, 3, 4, 3, 4};
  vector<int> n2 = {4, 5, 6};
  EXPECT_EQ_INT(4, s.alternatingSubarray(n1));
  EXPECT_EQ_INT(2, s.alternatingSubarray(n2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
