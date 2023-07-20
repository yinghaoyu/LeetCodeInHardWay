#include <iostream>
#include <vector>

using namespace std;

// seem as leetcode 0735
// https://leetcode-cn.com/problems/asteroid-collision/
// see at Problem_0735_asteroidCollision.cc
class Solution
{
 public:
  vector<int> asteroidCollision(vector<int> &asteroids)
  {
    vector<int> st;
    // 负数在左，正数在右，这种情况根本不会碰撞
    // 所以只要考虑正数在左，负数在右的情况，利用栈模拟
    for (auto &asteroid : asteroids)
    {
      bool alive = true;
      while (alive && asteroid < 0 && !st.empty() && st.back() > 0)
      {
        alive = st.back() < -asteroid;
        if (st.back() <= -asteroid)
        {
          st.pop_back();
        }
      }
      if (alive)
      {
        st.push_back(asteroid);
      }
    }
    return st;
  }
};
