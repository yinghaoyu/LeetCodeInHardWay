#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> filterRestaurants(vector<vector<int>> &restaurants, int veganFriendly, int maxPrice, int maxDistance)
  {
    int n = restaurants.size();
    vector<vector<int>> filter;
    for (int i = 0; i < n; i++)
    {
      int vf = restaurants[i][2];
      int price = restaurants[i][3];
      int distance = restaurants[i][4];
      if (price <= maxPrice && distance <= maxDistance && !(veganFriendly && !vf))
      {
        filter.push_back(restaurants[i]);
      }
    }
    std::sort(filter.begin(), filter.end(),
              [](const vector<int> &lhs, const vector<int> &rhs) { return lhs[1] == rhs[1] ? lhs[0] > rhs[0] : lhs[1] > rhs[1]; });
    vector<int> ans;
    for (auto &x : filter)
    {
      ans.push_back(x[0]);
    }
    return ans;
  }
};
