#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<string> getValidT9Words(string num, vector<string>& words)
  {
    static const string map = "22233344455566677778889999";
    vector<string> ans;
    string str;
    str.reserve(4);
    for (auto& word : words)
    {
      str.clear();
      for (char c : word)
      {
        str.push_back(map[c - 'a']);
      }
      if (str == num)
      {
        ans.push_back(word);
      }
    }
    return ans;
  }
};
