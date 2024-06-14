#include <algorithm>
#include <stack>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution
{
 public:
  long long findMaximumElegance(vector<vector<int>>& items, int k)
  {
    std::sort(items.begin(), items.end(), [](auto& a, auto& b) { return a[0] > b[0]; });
    unordered_set<int> category;
    long long ans = 0;
    long long profit = 0;
    stack<int> st;
    for (int i = 0; i < items.size(); i++)
    {
      // 不足 k 种类型项目
      if (i < k)
      {
        profit += items[i][0];
        if (category.count(items[i][1]) == 0)
        {
          // 这个类型的项目只有 1 个
          category.insert(items[i][1]);
        }
        else
        {
          // 这个类型的项目有多个
          // 由于前面已对 items[i][0] 从小到大排过序，因此 st 是从大到小进栈的
          st.push(items[i][0]);
        }
      }
      else if (category.count(items[i][1]) == 0 && !st.empty())
      {
        // 当前的类型是之前没有的，并且
        // 淘汰掉之前某个类型内，多数项目之中的最小值
        // 只有这种情况，才开肯使得 profit 变大
        profit += items[i][0] - st.top();
        st.pop();
        category.insert(items[i][1]);
      }
      ans = std::max(ans, static_cast<long long>(profit + category.size() * category.size()));
    }
    return ans;
  }
};
