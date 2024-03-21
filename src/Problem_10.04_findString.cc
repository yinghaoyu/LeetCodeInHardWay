#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  int findString(vector<string>& words, string s)
  {
    int left = 0, right = words.size() - 1;

    while (left <= right)
    {
      int mid = (left + right) / 2;

      if (words[mid] == "")
      {
        // 退化成线性
        // 为了效率，只需找到距离最近的非空单词位置
        int l = mid - 1, r = mid + 1;
        while (true)
        {
          if (l < left && r > right)
          {
            return -1;
          }
          if (r <= right && words[r] != "")
          {
            mid = r;
            break;
          }
          if (l >= left && words[l] != "")
          {
            mid = l;
            break;
          }
          l--;
          r++;
        }
      }

      if (words[mid] == s)
      {
        return mid;
      }
      else if (words[mid] < s)
      {
        left = mid + 1;
      }
      else
      {
        right = mid - 1;
      }
    }

    return -1;
  }
};
