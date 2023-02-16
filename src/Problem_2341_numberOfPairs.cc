#include <algorithm>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> numberOfPairs(vector<int> &nums)
  {
    unordered_map<int, bool> cnt;
    int ans = 0;
    for (int num : nums)
    {
      if (cnt.count(num))
      {
        cnt[num] = !cnt[num];
      }
      else
      {
        cnt[num] = true;
      }
      if (!cnt[num])
      {
        ans++;
      }
    }
    return {ans, (int) nums.size() - 2 * ans};
  }
};

bool isVectorEqual(vector<int> a, vector<int> b)
{
  return a == b;
}

void testNumberOfPairs()
{
  Solution s;
  vector<int> n1 = {1, 3, 2, 1, 3, 2, 2};
  vector<int> o1 = {3, 1};
  vector<int> n2 = {1, 1};
  vector<int> o2 = {1, 0};
  EXPECT_TRUE(isVectorEqual(o1, n1));
  EXPECT_TRUE(isVectorEqual(o2, n2));
  EXPECT_SUMMARY;
}

int main()
{
  testNumberOfPairs();
  return 0;
}
