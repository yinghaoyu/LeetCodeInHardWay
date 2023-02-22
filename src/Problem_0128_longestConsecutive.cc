#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int longestConsecutive(vector<int> &nums)
  {
    unordered_map<int, int> map;
    int len = 0;
    for (auto &num : nums)
    {
      if (!map.count(num))
      {
        map.emplace(num, 1);
        int preLen = map.count(num - 1) ? map.at(num - 1) : 0;
        int posLen = map.count(num + 1) ? map.at(num + 1) : 0;
        int all = preLen + posLen + 1;
        map[num - preLen] = all;
        map[num + posLen] = all;
        len = std::max(len, all);
      }
    }
    return len;
  }
};

void testLongestConsecutive()
{
  Solution s;
  vector<int> n1 = {100, 4, 200, 1, 3, 2};
  vector<int> n2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
  EXPECT_EQ_INT(4, s.longestConsecutive(n1));
  EXPECT_EQ_INT(9, s.longestConsecutive(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testLongestConsecutive();
  return 0;
}
