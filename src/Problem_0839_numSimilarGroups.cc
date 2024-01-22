#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 private:
  vector<int> father;
  int number;

  void bulid(int n)
  {
    father.resize(n);
    for (int i = 0; i < n; i++)
    {
      father[i] = i;
    }
    number = n;
  }

  int find(int i)
  {
    if (i != father[i])
    {
      father[i] = find(father[i]);
    }
    return father[i];
  }

  void unions(int x, int y)
  {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy)
    {
      father[fx] = fy;
      number--;
    }
  }

 public:
  int numSimilarGroups(vector<string>& strs)
  {
    int n = strs.size();
    int m = strs[0].length();
    bulid(n);
    // 根据字符串建立并查集
    for (int i = 0; i < n; i++)
    {
      for (int j = i + 1; j < n; j++)
      {
        if (find(i) != find(j))
        {
          int diff = 0;
          for (int k = 0; k < m && diff < 3; k++)
          {
            if (strs[i][k] != strs[j][k])
            {
              diff++;
            }
          }
          // 只统计相同的字符串，或者只有2个字符位置需要交换的
          if (diff == 0 || diff == 2)
          {
            unions(i, j);
          }
        }
      }
    }
    return number;
  }
};

void test()
{
  Solution s;
  vector<string> s1 = {"tars", "rats", "arts", "star"};
  vector<string> s2 = {"omv", "ovm"};
  EXPECT_EQ_INT(2, s.numSimilarGroups(s1));
  EXPECT_EQ_INT(1, s.numSimilarGroups(s2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
