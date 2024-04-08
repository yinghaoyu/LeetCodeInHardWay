#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  int compareVersion(string version1, string version2)
  {
    int n = version1.length();
    int m = version2.length();
    int i = 0;
    int j = 0;
    while (i < n || j < m)
    {
      long x = 0;
      for (; i < n && version1[i] != '.'; i++)
      {
        x = x * 10 + (version1[i] - '0');
      }
      // 跳过点
      i++;
      long y = 0;
      for (; j < m && version2[j] != '.'; j++)
      {
        y = y * 10 + version2[j] - '0';
      }
      // 跳过点
      j++;
      if (x != y)
      {
        return x > y ? 1 : -1;
      }
    }
    return 0;
  }
};
