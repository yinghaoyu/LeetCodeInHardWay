#include <cctype>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 利用前缀和
  vector<string> findLongestSubarray(vector<string>& array)
  {
    int N = array.size();
    vector<int> sum(N + 1);
    for (int i = 0; i < N; i++)
    {
      sum[i + 1] = sum[i] + (isalpha(array[i][0]) ? 1 : -1);
    }
    int begin = 0;
    int end = 0;
    // 前缀和，下标
    unordered_map<int, int> map;
    for (int i = 0; i <= N; i++)
    {
      auto it = map.find(sum[i]);
      if (it == map.end())
      {
        map[sum[i]] = i;
      }
      else if (i - it->second > end - begin)
      {
        // 当前子串长度更长
        begin = it->second;
        end = i;
      }
    }
    return {array.begin() + begin, array.begin() + end};
  }
};

void testFindLongestSubarray()
{
  Solution s;
  vector<string> n1 = {"A", "1", "B", "C", "D", "2", "3", "4", "E", "5",
                       "F", "G", "6", "7", "H", "I", "J", "K", "L", "M"};
  vector<string> o1 = {"A", "1", "B", "C", "D", "2", "3", "4", "E", "5", "F", "G", "6", "7"};
  vector<string> n2 = {"A", "A"};
  vector<string> o2;
  EXPECT_TRUE(o1 == s.findLongestSubarray(n1));
  EXPECT_TRUE(o2 == s.findLongestSubarray(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testFindLongestSubarray();
  return 0;
}
