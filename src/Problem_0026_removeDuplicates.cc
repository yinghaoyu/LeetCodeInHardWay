#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int removeDuplicates(vector<int> &nums)
  {
    int i = 0;
    int j = 0;
    int n = nums.size();
    while (i < n && j < n)
    {
      while (j < n && nums[j] == nums[i])
      {
        // 找到第一个不同的元素
        j++;
      }
      if (j == n)
      {
        break;
      }
      // 覆盖
      nums[i + 1] = nums[j];
      i++;
    }
    return i + 1;
  }
};

bool isVectorEqual(vector<int> a, vector<int> b)
{
  return a == b;
}

void testRemoveDuplicates()
{
  Solution s;
  vector<int> n1 = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
  vector<int> v1 = {0, 1, 2, 3, 4};
  EXPECT_EQ_INT(5, s.removeDuplicates(n1));
  vector<int> v2(n1.begin(), n1.begin() + 5);
  EXPECT_TRUE(isVectorEqual(v1, v2));
  EXPECT_SUMMARY;
}

int main()
{
  testRemoveDuplicates();
  return 0;
}
