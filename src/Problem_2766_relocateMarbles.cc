#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> relocateMarbles(vector<int>& nums, vector<int>& moveFrom, vector<int>& moveTo)
  {
    vector<int> ans;
    unordered_map<int, bool> map;
    for (int i = 0; i < nums.size(); i++)
    {
      map[nums[i]] = true;
    }
    for (int i = 0; i < moveFrom.size(); i++)
    {
      map.erase(moveFrom[i]);
      map[moveTo[i]] = true;
    }
    for (auto& [i, exists] : map)
    {
      ans.push_back(i);
    }
    std::sort(ans.begin(), ans.end());
    return ans;
  }
};
