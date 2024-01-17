#include <deque>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int longestSubarray(vector<int>& nums, int limit)
  {
    deque<int> queMax;
    deque<int> queMin;
    int n = nums.size();
    int left = 0;
    int right = 0;
    int ans = 0;
    while (right < n)
    {
      while (!queMax.empty() && queMax.back() < nums[right])
      {
        queMax.pop_back();
      }
      while (!queMin.empty() && queMin.back() > nums[right])
      {
        queMin.pop_back();
      }
      queMax.push_back(nums[right]);
      queMin.push_back(nums[right]);
      while (!queMax.empty() && !queMin.empty() && queMax.front() - queMin.front() > limit)
      {
        if (nums[left] == queMin.front())
        {
          queMin.pop_front();
        }
        if (nums[left] == queMax.front())
        {
          queMax.pop_front();
        }
        left++;
      }
      ans = std::max(ans, right - left + 1);
      right++;
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {8, 2, 4, 7};
  vector<int> n2 = {10, 1, 2, 4, 7, 2};
  vector<int> n3 = {4, 2, 2, 2, 4, 4, 2, 2};
  EXPECT_EQ_INT(2, s.longestSubarray(n1, 4));
  EXPECT_EQ_INT(4, s.longestSubarray(n2, 5));
  EXPECT_EQ_INT(3, s.longestSubarray(n3, 0));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
