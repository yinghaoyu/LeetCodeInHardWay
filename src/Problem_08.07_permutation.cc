#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  void f(string& str, int index, vector<string>& ans)
  {
    if (index == str.length())
    {
      ans.push_back(str);
      return;
    }
    for (int i = index; i < str.length(); i++)
    {
      swap(str[index], str[i]);
      f(str, index + 1, ans);
      swap(str[index], str[i]);
    }
  }

  vector<string> permutation(string S)
  {
    vector<string> ans;
    f(S, 0, ans);
    return ans;
  }
};
