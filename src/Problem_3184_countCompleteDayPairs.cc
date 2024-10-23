#include <vector>

using namespace std;

// @sa Problem_3185_countCompleteDayPairs.cc
class Solution
{
 public:
  // 这里不写暴力解
  long long countCompleteDayPairs(vector<int>& hours)
  {
    long long ans = 0;
    vector<int> cnt(24);
    for (int h : hours)
    {
      ans += cnt[(24 - h % 24) % 24];
      cnt[h % 24]++;
    }
    return ans;
  }
};
