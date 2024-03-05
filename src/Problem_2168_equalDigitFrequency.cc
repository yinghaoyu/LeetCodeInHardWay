#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution
{
 public:
  int equalDigitFrequency(string s)
  {
    long base = 499;
    int n = s.length();
    unordered_set<long> set;
    vector<int> cnt(10);
    for (int left = 0; left < n; left++)
    {
      long hashCode = 0;
      int curVal = 0;
      int maxCnt = 0;
      int maxCntkinds = 0;
      int allKinds = 0;
      for (int right = left; right < n; right++)
      {
        curVal = s[right] - '0';
        hashCode = hashCode * base + curVal + 1;
        cnt[curVal]++;
        if (cnt[curVal] == 1)
        {
          // 新种类字符
          allKinds++;
        }
        if (cnt[curVal] > maxCnt)
        {
          // 最大数量的字符
          maxCnt = cnt[curVal];
          maxCntkinds = 1;
        }
        else if (cnt[curVal] == maxCnt)
        {
          // 新的字符串达到最大数量
          maxCntkinds++;
        }
        if (maxCntkinds == allKinds)
        {
          // 所有的字符都达到最大数量
          set.emplace(hashCode);
        }
      }
    }
    return set.size();
  }
};
