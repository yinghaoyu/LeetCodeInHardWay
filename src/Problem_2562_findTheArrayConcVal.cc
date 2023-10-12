#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution {
public:
    long long findTheArrayConcVal(vector<int>& nums) {
        long long ans = 0;
        for(int i = 0, j = nums.size() - 1; i <= j; i++, j--)
        {
            if(i != j)
            {
                ans += stoi(to_string(nums[i]) + to_string(nums[j]));
            }
            else
            {
                ans += nums[i];
            }
        }
        return ans;
    }
};

void test()
{
  Solution s;
  vector<int> n1 = {7,52,2,4};
  vector<int> n2 = {5,14,13,8,12};
  EXPECT_EQ_INT(596, s.findTheArrayConcVal(n1));
  EXPECT_EQ_INT(673, s.findTheArrayConcVal(n2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
