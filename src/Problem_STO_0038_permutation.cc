#include <iostream>
#include <vector>

using namespace std;

class Solution
{
 public:
  void process(string &s, int index, vector<string> &ans)
  {
    if (index == s.length())
    {
      ans.push_back(s);
    }
    else
    {
      vector<bool> seen(256);
      for (int i = index; i < s.length(); i++)
      {
        // 保证交换后, index 位置的字符只出现 1 次
        if (!seen[s[i]])
        {
          seen[s[i]] = true;
          std::swap(s[index], s[i]);
          process(s, index + 1, ans);
          std::swap(s[index], s[i]);
        }
      }
    }
  }

  vector<string> permutation(string s)
  {
    vector<string> ans;
    process(s, 0, ans);
    return ans;
  }
};
