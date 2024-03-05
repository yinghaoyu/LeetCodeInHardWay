#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  int repeatedStringMatch(string a, string b)
  {
    bool exists[26] = {false};
    for (const char& c : a)
    {
      exists[c - 'a'] = true;
    }
    for (const char& c : b)
    {
      if (!exists[c - 'a'])
      {
        return -1;
      }
    }
    int k = b.size() / a.size();
    string s;
    s.reserve(b.size());
    for (int i = 0; i < k; ++i)
    {
      s.append(a);
    }
    for (int i = 0; i < 3; ++i)
    {
      if (s.find(b) != string::npos)
      {
        return k + i;
      }
      s.append(a);
    }
    return -1;
  }

  // TODO: KMP
};
