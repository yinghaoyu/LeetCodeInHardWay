#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

/* The knows API is defined for you.
      bool knows(int a, int b); */

bool knows(int a, int b);

class Solution
{
 public:
  int findCelebrity(int n)
  {
    int cand = 0;
    // 先找出可能是明星的人
    for (int i = 0; i < n; i++)
    {
      if (knows(cand, i))
      {
        cand = i;
      }
    }
    // 到这里，说明cand不认识区间 (cand , n) 的所有人
    // 再验证cand不认识区间 [0, cand) 的所有人
    for (int i = 0; i < cand; i++)
    {
      if (knows(cand, i))
      {
        return -1;
      }
    }
    // 再验证所有人都认识cand
    for (int i = 0; i < n; i++)
    {
      if (!knows(i, cand))
      {
        return -1;
      }
    }
    return cand;
  }
};
