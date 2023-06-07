#include <algorithm>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int miceAndCheese(vector<int> &reward1, vector<int> &reward2, int k)
  {
    int ans = 0;
    int n = reward1.size();
    vector<int> diffs(n);
    for (int i = 0; i < n; i++)
    {
      ans += reward2[i];
      diffs[i] = reward1[i] - reward2[i];
    }
    std::sort(diffs.begin(), diffs.end());
    for (int i = 1; i <= k; i++)
    {
      ans += diffs[n - i];
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> r1 = {1, 1, 3, 4};
  vector<int> r2 = {4, 4, 1, 1};

  vector<int> r3 = {1, 1};
  vector<int> r4 = {1, 1};
  EXPECT_EQ_INT(15, s.miceAndCheese(r1, r2, 2));
  EXPECT_EQ_INT(2, s.miceAndCheese(r3, r4, 2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
