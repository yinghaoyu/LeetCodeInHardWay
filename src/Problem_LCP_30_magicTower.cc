#include <functional>
#include <queue>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 贪心
  int magicTower(vector<int>& nums)
  {
    // 小根堆
    priority_queue<int, vector<int>, greater<int>> q;
    // 调整的次数
    int ans = 0;
    long long hp = 1, delay = 0;
    for (int num : nums)
    {
      if (num < 0)
      {
        // 先把扣除的血量加入小根堆
        q.push(num);
      }
      hp += num;
      if (hp <= 0)
      {
        // 如果当前血量 <= 0，只有把之前遍历过的某房间内的扣除血量移动到最后
        // 为了使调整次数最少，那么需要保证当前得到的血量尽可能的大，
        // 因此需要把扣除血量最多的房间移动至末尾，即小根堆的堆顶
        ++ans;
        // 记录移动到末尾的房间扣除血量和
        delay += q.top();
        // 房间移动到末尾，撤销扣除血量，扣除血量保存到delay
        // 第一次 hp <= 0，移动后，一定有 hp > 0
        hp -= q.top();
        q.pop();
      }
    }
    // 加上扣除的血量，需保证最终的血量 > 0
    hp += delay;
    return hp <= 0 ? -1 : ans;
  }
};
