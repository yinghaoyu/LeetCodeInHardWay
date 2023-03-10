#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Solution
{
 private:
  vector<int> origin;
  vector<int> sf;
  int N;
  int random(int min, int max)
  {
    random_device seed;
    ranlux48 engine(seed());
    uniform_int_distribution<> distrib(min, max);
    int res = distrib(engine);
    return res;
  }

 public:
  Solution(vector<int> &nums)
  {
    origin = nums;
    N = nums.size();
    sf = nums;
  }

  vector<int> reset() { return origin; }

  vector<int> shuffle()
  {
    for (int i = N - 1; i >= 0; i++)
    {
      int r = random(0, i);
      int tmp = sf[r];
      sf[r] = sf[i];
      sf[i] = tmp;
    }
    return sf;
  }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
