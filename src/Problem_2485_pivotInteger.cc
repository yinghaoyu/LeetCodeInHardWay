#include <vector>
#include <iostream>

#include "UnitTest.h"

using namespace std;

class Solution {
public:
    int pivotInteger(int n) {
        vector<int> sum(n+1);
        for(int i = 1; i <= n; i++)
        {
          sum[i] = sum[i-1] + i;
        }
        for(int i = 1; i <= n; i++)
        {
          if(sum[n] - sum[i-1] == sum[i])
          {
            return i;
          }
        }
        return -1;
    }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(6, s.pivotInteger(8));
  EXPECT_EQ_INT(1, s.pivotInteger(1));
  EXPECT_EQ_INT(-1, s.pivotInteger(4));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
