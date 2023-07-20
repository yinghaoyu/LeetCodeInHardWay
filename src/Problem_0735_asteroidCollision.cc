#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> asteroidCollision(vector<int> &asteroids)
  {
    vector<int> stack;
    for (auto &asteroid : asteroids)
    {
      bool alive = true;
      while (alive && asteroid < 0 && !stack.empty() && stack.back() > 0)
      {
        alive = stack.back() < -asteroid;
        if (stack.back() <= -asteroid)
        {
          stack.pop_back();
        }
      }
      if (alive)
      {
        stack.push_back(asteroid);
      }
    }
    return stack;
  }
};

void test()
{
  Solution s;
  vector<int> a1 = {5, 10, -5};
  vector<int> a2 = {8, -8};
  vector<int> a3 = {10, 2, -5};
  vector<int> o1 = {5, 10};
  vector<int> o2 = {};
  vector<int> o3 = {10};
  EXPECT_TRUE(o1 == s.asteroidCollision(a1));
  EXPECT_TRUE(o2 == s.asteroidCollision(a2));
  EXPECT_TRUE(o3 == s.asteroidCollision(a3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
