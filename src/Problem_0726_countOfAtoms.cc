#include <map>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string countOfAtoms(string formula)
  {
    int where = 0;
    map<string, int> map = f(formula, 0, where);
    string ans;
    for (auto& [key, cnt] : map)
    {
      ans.append(key);
      if (cnt > 1)
      {
        ans.append(std::to_string(cnt));
      }
    }
    return ans;
  }

  // s[i....]开始计算，遇到字符串终止 或者 遇到 ) 停止
  // 返回 : 自己负责的这一段字符串的结果，有序表！
  // 返回之间，更新全局变量where，为了上游函数知道从哪继续！
  map<string, int> f(string& s, int i, int& where)
  {
    // ans是总表
    map<string, int> ans;
    // 之前收集到的名字，历史一部分
    string name;
    // 之前收集到的有序表，历史一部分
    map<string, int> pre;
    // 历史翻几倍
    int cnt = 0;
    while (i < s.length() && s[i] != ')')
    {
      if (s[i] >= 'A' && s[i] <= 'Z' || s[i] == '(')
      {
        // 遇到新原子就把上一个原子填好
        fill(ans, name, pre, cnt);
        name.clear();
        pre.clear();
        cnt = 0;
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
          name.push_back(s[i++]);
        }
        else
        {
          // 遇到 (
          pre = f(s, i + 1, where);
          i = where + 1;
        }
      }
      else if (s[i] >= 'a' && s[i] <= 'z')
      {
        name.push_back(s[i++]);
      }
      else
      {
        cnt = cnt * 10 + s[i++] - '0';
      }
    }
    fill(ans, name, pre, cnt);
    where = i;
    return ans;
  }

  // 统计name和pre的词频到ans
  // cnt表示name或者pre出现了多少次
  void fill(map<string, int>& ans, string& name, map<string, int>& pre, int cnt)
  {
    if (name.length() > 0 || !pre.empty())
    {
      cnt = cnt == 0 ? 1 : cnt;
      if (name.length() > 0)
      {
        ans[name] += cnt;
      }
      else
      {
        for (auto& [key, pcnt] : pre)
        {
          ans[key] += pcnt * cnt;
        }
      }
    }
  }
};

void test()
{
  Solution s;
  EXPECT_TRUE("H2O" == s.countOfAtoms("H2O"));
  EXPECT_TRUE("H2MgO2" == s.countOfAtoms("Mg(OH)2"));
  EXPECT_TRUE("K4N2O14S4" == s.countOfAtoms("K4(ON(SO3)2)2"));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
