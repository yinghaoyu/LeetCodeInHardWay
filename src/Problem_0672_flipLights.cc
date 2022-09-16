#include <iostream>
#include <queue>
#include <unordered_set>

#include "UnitTest.h"

using namespace std;

using TdArray = vector<vector<int>>;

class Solution
{
 public:
  int flipLights(int n, int presses)
  {
    if (presses == 0)
    {
      return 1;
    }
    if (n == 1)
    {
      return 2;
    }
    else if (n == 2)
    {
      return presses == 1 ? 3 : 4;
    }
    else
    {
      return presses == 1 ? 4 : presses == 2 ? 7 : 8;
    }
  }

  void process(int state, int mask, int presses, TdArray &visited, unordered_set<int> &sets)
  {
    if (presses == 0)
    {
      sets.emplace(state);
      return;
    }
    if (visited[state][presses] == 1)
    {
      return;
    }
    visited[state][presses] = 1;
    process((state ^ 0b111111) & mask, mask, presses - 1, visited, sets);
    process((state ^ 0b101010) & mask, mask, presses - 1, visited, sets);
    process((state ^ 0b010101) & mask, mask, presses - 1, visited, sets);
    process((state ^ 0b001001) & mask, mask, presses - 1, visited, sets);
  }

  int flipLights2(int n, int presses)
  {
    int mask = (1 << std::min(n, 6)) - 1;
    TdArray visited(0b111111, vector<int>(presses));
    unordered_set<int> sets;
    process(0b111111 & mask, mask, presses, visited, sets);
    return sets.size();
  }

  int flipLights1(int n, int presses)
  {
    // 按偶数次：亮
    // 按奇数次：暗

    // 操作1：灯泡 k
    // 操作2：灯泡 2k
    // 操作3：灯泡 2k+1
    // 操作4：灯泡 3k+1

    // 1：k         (1 2 3 4 5 6  | 7 8 9 10 11 12 | ... | )
    // 2: 2k        (  2   4   6  |   8   10    12 | ... | )
    // 3: 2k+1      (1   3   5    | 7   9    11    | ... | )
    // 4: 3k+1      (1     4      | 7     10       | ... | )
    // 可以看到周期为6, 因此只需要考虑前6个灯泡即可

    const int mask = (1 << std::min(n, 6)) - 1;

    const int op1 = 0b111111;
    const int op2 = 0b101010;
    const int op3 = 0b010101;
    const int op4 = 0b001001;

    queue<int> q;
    q.push(op1);

    while (!q.empty() && presses--)
    {
      unordered_set<int> next_states;  // 每一轮都进行了去重，所以不会超时
      // 这个for循环用于处理同一深度的操作
      for (int _ = q.size(); _; --_)
      {
        int state = q.front();
        q.pop();
        // 枚举操作
        // 操作1
        next_states.insert((state ^ op1) & mask);
        // 操作2
        next_states.insert((state ^ op2) & mask);
        // 操作3
        next_states.insert((state ^ op3) & mask);
        // 操作4
        next_states.insert((state ^ op4) & mask);
      }

      for (int state : next_states)
        q.push(state);
    }
    return q.size();
  }
};

void testFlipLights()
{
  Solution s;
  EXPECT_EQ_INT(2, s.flipLights1(1, 1));
  EXPECT_EQ_INT(3, s.flipLights1(2, 1));
  EXPECT_EQ_INT(4, s.flipLights1(3, 1));
  EXPECT_EQ_INT(8, s.flipLights1(4, 100));

  EXPECT_EQ_INT(2, s.flipLights2(1, 1));
  EXPECT_EQ_INT(3, s.flipLights2(2, 1));
  EXPECT_EQ_INT(4, s.flipLights2(3, 1));
  EXPECT_EQ_INT(8, s.flipLights2(4, 100));
  EXPECT_SUMMARY;
}

int main()
{
  testFlipLights();
  return 0;
}
