#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int maxEqualFreq(vector<int> &nums)
  {
    unordered_map<int, int> count;  // 每个数出现的次数
    unordered_map<int, int> freq;   // 出现次数相同的数有几个
    int maxCount = 0;               // 最多出现次数的数，出现了多少次
    int ans = 0;
    for (int i = 0; i < nums.size(); i++)
    {
      if (count[nums[i]] > 0)
      {
        // 先--再++相当于啥都没干
        freq[count[nums[i]]]--;
      }
      count[nums[i]]++;
      maxCount = max(maxCount, count[nums[i]]);
      freq[count[nums[i]]]++;
      maxCount = std::max(maxCount, count[nums[i]]);
      // 贪心：怎么获得最长的数组
      // 以 nums[i] 结尾的数组前缀符合要求的充要条件为满足以下三个条件之一:
      // 条件一：所有数的出现次数都是一次，随意删除一个数既可符合要求
      bool p1 = maxCount == 1;
      // 条件二：所有数的出现次数都是 maxFreq 或 maxFreq−1，并且最大出现次数的数只有一个：删除一个最大出现次数的数，那么所有数的出现次数都是 maxFreq−1
      bool p2 = freq[maxCount] * maxCount + freq[maxCount - 1] * (maxCount - 1) == i + 1 && freq[maxCount] == 1;
      // 条件三：除开一个数，其他所有数的出现次数都是 maxFreq，并且该数的出现次数为 1：直接删除出现次数为 1 的数，那么所有数的出现次数都是 maxFreq
      bool p3 = freq[maxCount] * maxCount + 1 == i + 1 && freq[1] == 1;
      if (p1 || p2 || p3)
      {
        ans = std::max(ans, i + 1);
      }
    }
    return ans;
  }
};

void testMaxEqualFreq()
{
  Solution s;
  vector<int> arr1 = {2, 2, 1, 1, 5, 3, 3, 5};
  vector<int> arr2 = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5};
  vector<int> arr3 = {1, 2, 2, 1, 1, 5, 3, 3, 5};
  vector<int> arr4 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_EQ_INT(7, s.maxEqualFreq(arr1));
  EXPECT_EQ_INT(13, s.maxEqualFreq(arr2));
  EXPECT_EQ_INT(9, s.maxEqualFreq(arr3));
  EXPECT_EQ_INT(9, s.maxEqualFreq(arr4));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxEqualFreq();
  return 0;
}
