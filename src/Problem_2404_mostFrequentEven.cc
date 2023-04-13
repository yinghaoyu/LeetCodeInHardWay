#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int mostFrequentEven(vector<int> &nums)
  {
    unordered_map<int, int> map;
    int ans = -1;
    for (auto &v : nums)
    {
      if (v & 1)
      {
        continue;
      }
      if (map.count(v))
      {
        map[v]++;
      }
      else
      {
        map[v] = 1;
      }
      if (ans == -1 || map[v] > map[ans] || (map[v] == map[ans] && v < ans))
      {
        ans = v;
      }
    }
    return ans;
  }
};

void testMostFrequentEven()
{
  Solution s;
  vector<int> n1 = {0, 1, 2, 2, 4, 4, 1};
  vector<int> n2 = {4, 4, 4, 9, 2, 4};
  vector<int> n3 = {29, 47, 21, 41, 13, 37, 25, 7};
  EXPECT_EQ_INT(2, s.mostFrequentEven(n1));
  EXPECT_EQ_INT(4, s.mostFrequentEven(n2));
  EXPECT_EQ_INT(-1, s.mostFrequentEven(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testMostFrequentEven();
  return 0;
}
