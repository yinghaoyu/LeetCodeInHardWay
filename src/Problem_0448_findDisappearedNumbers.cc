#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> findDisappearedNumbers(vector<int> &nums)
  {
    vector<int> ans;
    if (nums.size() == 0)
    {
      return ans;
    }
    int N = nums.size();
    for (int i = 0; i < N; i++)
    {
      walk(nums, i);
    }
    for (int i = 0; i < N; i++)
    {
      if (nums[i] != i + 1)
      {
        ans.push_back(i + 1);
      }
    }
    return ans;
  }

  // 下标循环怼
  void walk(vector<int> &nums, int i)
  {
    while (nums[i] != i + 1)
    {
      int nexti = nums[i] - 1;
      if (nums[nexti] == nexti + 1)
      {
        break;
      }
      swap(nums, i, nexti);
    }
  }

  void swap(vector<int> &nums, int i, int j)
  {
    int tmp = nums[i];
    nums[i] = nums[j];
    nums[j] = tmp;
  }
};

void testFindDisappearedNumbers()
{
  Solution s;
  vector<int> n1 = {4, 3, 2, 7, 8, 2, 3, 1};
  vector<int> o1 = {5, 6};
  vector<int> n2 = {1, 1};
  vector<int> o2 = {2};
  EXPECT_TRUE(o1 == s.findDisappearedNumbers(n1));
  EXPECT_TRUE(o2 == s.findDisappearedNumbers(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testFindDisappearedNumbers();
  return 0;
}
