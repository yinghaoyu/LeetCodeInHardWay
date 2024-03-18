#include <algorithm>
#include <any>
#include <string>
#include <utility>
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
    vector<bool> map(256);
    for (int i = index; i < str.length(); i++)
    {
      if (!map[str[i]])
      {
        map[str[i]] = true;
        swap(str[index], str[i]);
        f(str, index + 1, ans);
        swap(str[index], str[i]);
      }
    }
  }

  vector<string> permutation(string S)
  {
    vector<string> ans;
    f(S, 0, ans);
    return ans;
  }
};
