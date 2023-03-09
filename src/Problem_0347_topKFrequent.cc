#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 private:
  class Node
  {
   public:
    int num;
    int count;
    Node()
    {
      num = -1;
      count = -1;
    }

    Node(int k)
    {
      num = k;
      count = 1;
    }

    bool operator<(const Node &other) const { return this->count > other.count; }
  };

 public:
  vector<int> topKFrequent(vector<int> &nums, int k)
  {
    unordered_map<int, Node> map;
    for (int num : nums)
    {
      if (!map.count(num))
      {
        map.emplace(num, Node(num));
      }
      else
      {
        map[num].count++;
      }
    }
    // 小根堆
    priority_queue<Node> q;

    for (auto &[_, node] : map)
    {
      if (q.size() < k || (q.size() == k && node.count > q.top().count))
      {
        q.push(node);
      }
      if (q.size() > k)
      {
        q.pop();
      }
    }
    vector<int> ans(k);
    int index = k-1;
    while (!q.empty())
    {
      ans[index--] = q.top().num;
      q.pop();
    }
    return ans;
  }
};

void testTopKFrequent()
{
  Solution s;
  vector<int> n1 = {1, 1, 1, 2, 2, 3};
  vector<int> o1 = {1, 2};
  vector<int> n2 = {1};
  vector<int> o2 = {1};
  EXPECT_TRUE(o1 == s.topKFrequent(n1, 2));
  EXPECT_TRUE(o2 == s.topKFrequent(n2, 1));
  EXPECT_SUMMARY;
}

int main()
{
  testTopKFrequent();
  return 0;
}
