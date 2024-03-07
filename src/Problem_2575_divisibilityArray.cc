#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> divisibilityArray(string word, int m)
  {
    vector<int> ans;
    long long cur = 0;
    for (auto& c : word)
    {
      // 利用同余原理
      cur = (cur * 10 + c - '0') % m;
      ans.push_back(cur == 0 ? 1 : 0);
    }
    return ans;
  }
};
