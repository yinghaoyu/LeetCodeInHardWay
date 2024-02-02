#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  bool canConvert(string str1, string str2)
  {
    if (str1 == str2)
    {
      return true;
    }
    // map[x] : str2中字符x的词频
    vector<int> map(26);
    // kinds : str2中字符的种类数
    int kinds = 0;
    for (int i = 0; i < str2.length(); i++)
    {
      if (map[str2[i] - 'a']++ == 0)
      {
        kinds++;
      }
    }
    if (kinds == 26)
    {
      // 如果本来就有26种字符，任意转换都会使得字符数变少
      return false;
    }
    std::fill(map.begin(), map.end(), -1);
    // map[x] = y : str1中的字符x上次出现在str1中的y位置
    for (int i = 0, cur; i < str1.length(); i++)
    {
      cur = str1[i] - 'a';
      // TODO: figure  it out.
      if (map[cur] != -1 && str2[map[cur]] != str2[i])
      {
        return false;
      }
      map[cur] = i;
    }
    return true;
  }
};
