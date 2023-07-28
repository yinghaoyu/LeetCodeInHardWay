#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
  static bool cmp(pair<int, int> &l, pair<int, int> &r) { return l.second > r.second; }

 public:
  vector<int> topKFrequent(vector<int> &nums, int k)
  {
    unordered_map<int, int> frq;
    for (auto &num : nums)
    {
      frq[num]++;
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&cmp)> q(cmp);
    for (auto &[num, f] : frq)
    {
      if (q.size() == k)
      {
        if (q.top().second < f)
        {
          q.pop();
          q.push({num, f});
        }
      }
      else
      {
        q.push({num, f});
      }
    }
    vector<int> ans;
    while (!q.empty())
    {
      ans.push_back(q.top().first);
      q.pop();
    }
    return ans;
  }
};
