#include <cstdint>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

class Solution
{
 private:
  class Node
  {
   public:
    int v;  // 值
    int i;  // 当前值来自哪个数组
    int j;  // 当前值来自i号数组的什么位置

    bool operator<(const Node& other) const { return v != other.v ? v < other.v : i < other.i; }
  };

 public:
  // 时间复杂度O(n*logk)
  // n是数字总数，k是数组数量
  vector<int> smallestRange(vector<vector<int>>& nums)
  {
    int k = nums.size();
    // 根据值排序
    // 为什么排序的时候i要参与
    // 因为有序表中比较相等的样本只会保留一个
    // 为了值一样的元素都保留，于是i要参与排序
    // 在有序表中的所有元素i必然都不同
    set<Node> s;
    for (int i = 0; i < k; i++)
    {
      // nums中每个序列原本就有序

      // 先把所有序列第一个元素加入有序列表
      s.insert({nums[i][0], i, 0});
    }
    // 记录最窄区间的宽度
    int r = INT32_MAX;
    // 记录最窄区间的开头
    int a = 0;
    // 记录最窄区间的结尾
    int b = 0;
    while (s.size() == k)  // 保证每个序列至少有一个元素在区间内
    {
      // 在有序表中，值最大的记录
      auto max = *s.rbegin();
      // 在有序表中，值最小的记录，并弹出
      auto min = *s.begin();
      s.erase(s.begin());
      if (max.v - min.v < r)
      {
        r = max.v - min.v;
        a = min.v;
        b = max.v;
      }
      if (min.j + 1 < nums[min.i].size())
      {
        // min从s中移除，就要从这个序列中取出下一个元素
        s.insert({nums[min.i][min.j + 1], min.i, min.j + 1});
      }
    }
    return {a, b};
  }
};
