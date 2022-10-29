#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int countMatches(vector<vector<string>> &items, string ruleKey, string ruleValue)
  {
    int ans = 0;
    unordered_map<string, int> map = {{"type", 0}, {"color", 1}, {"name", 2}};
    for (int i = 0; i < items.size(); i++)
    {
      if (ruleValue == items[i][map[ruleKey]])
      {
        ans++;
      }
    }
    return ans;
  }
};

void testCountMatches()
{
  Solution s;
  vector<vector<string>> i1 = {{"phone", "blue", "pixel"}, {"computer", "silver", "lenovo"}, {"phone", "gold", "iphone"}};
  vector<vector<string>> i2 = {{"phone", "blue", "pixel"}, {"computer", "silver", "phone"}, {"phone", "gold", "iphone"}};
  EXPECT_EQ_INT(1, s.countMatches(i1, "color", "silver"));
  EXPECT_EQ_INT(2, s.countMatches(i2, "type", "phone"));
  EXPECT_SUMMARY;
}

int main()
{
  testCountMatches();
  return 0;
}
