
#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  bool isSubseq(string& s, string& t)
  {
    int i = 0;
    for (int j = 0; i < s.length() && j < t.length(); j++)
    {
      if (s[i] == t[j])
      {
        i++;
      }
    }
    return i == s.length();
  }

  // 如果它的一个子序列 sub 是「特殊序列」，那么 str[i] 本身也是一个「特殊序列」。
  int findLUSlength(vector<string>& strs)
  {
    int n = strs.size();
    int ans = -1;
    for (int i = 0; i < n; i++)
    {
      bool check = true;
      for (int j = 0; j < n; j++)
      {
        if (i != j && isSubseq(strs[i], strs[j]))
        {
          check = false;
          break;
        }
      }
      if (check)
      {
        ans = std::max(ans, static_cast<int>(strs[i].size()));
      }
    }
    return ans;
  }
};
