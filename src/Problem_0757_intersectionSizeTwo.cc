#include <vector>

using namespace std;
class Solution
{
 public:
  void help(vector<vector<int>>& intervals, vector<vector<int>>& temp, int pos, int num)
  {
    // 往左枚举区间
    for (int i = pos; i >= 0; i--)
    {
      // 验证当前的数是否在左区间内
      if (intervals[i][1] < num)
      {
        // FIXME: 为什么这里用break而不是continue? continue更容易理解
        break;
      }
      // 在这个区间内，说明这个整数可以纳入左边的区间
      temp[i].push_back(num);
    }
  }

  int intersectionSizeTwo(vector<vector<int>>& intervals)
  {
    int n = intervals.size();
    int ans = 0;
    int m = 2;
    // 左区间升序排序，右区间降序排序
    std::sort(intervals.begin(), intervals.end(), [](const vector<int>& l, const vector<int>& r)
              { return l[0] != r[0] ? l[0] < r[0] : l[1] > r[1]; });
    // temp[i]为每个区间存放的整数
    vector<vector<int>> temp(n);
    // 尝试每个区间放m个元素
    for (int i = n - 1; i >= 0; i--)
    {
      // 从当前区间的左边界开始枚举每一个整数
      for (int j = intervals[i][0], k = temp[i].size(); k < m; j++, k++)
      {
        ans++;
        // 验证当前选取的整数是否可以纳入前面区间
        help(intervals, temp, i - 1, j);
      }
    }

    return ans;
  }
};
