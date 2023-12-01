#include <string>
#include <vector>

using namespace std;

class Bitset
{
 private:
  vector<int> set;
  int size;
  int zeros;
  int ones;
  bool reverse;

 public:
  Bitset(int sz)
  {
    set = vector<int>((sz + 31) / 32);
    size = sz;
    zeros = sz;
    ones = 0;
    reverse = false;
  }

  // 把idx这个数字加入到位图
  void fix(int idx)
  {
    int index = idx / 32;
    int bit = idx % 32;
    if (!reverse)
    {
      // 位图所有位的状态，维持原始含义
      // 0 : 不存在
      // 1 : 存在
      if ((set[index] & (1 << bit)) == 0)
      {
        zeros--;
        ones++;
        set[index] |= (1 << bit);
      }
    }
    else
    {
      // 位图所有位的状态，翻转了
      // 0 : 存在
      // 1 : 不存在
      if ((set[index] & (1 << bit)) != 0)
      {
        zeros--;
        ones++;
        set[index] ^= (1 << bit);
      }
    }
  }

  // 把idx这个数字从位图中移除
  void unfix(int idx)
  {
    int index = idx / 32;
    int bit = idx % 32;
    if (!reverse)
    {
      if ((set[index] & (1 << bit)) != 0)
      {
        ones--;
        zeros++;
        set[index] ^= (1 << bit);
      }
    }
    else
    {
      if ((set[index] & (1 << bit)) == 0)
      {
        ones--;
        zeros++;
        set[index] |= (1 << bit);
      }
    }
  }

  void flip()
  {
    reverse = !reverse;
    std::swap(zeros, ones);
  }

  bool all() { return ones == size; }

  bool one() { return ones > 0; }

  int count() { return ones; }

  string toString()
  {
    string ans;
    // i 表示总偏移
    for (int i = 0, k = 0, number, status; i < size; k++)
    {
      number = set[k];
      // j 表示数内偏移
      for (int j = 0; j < 32 && i < size; j++, i++)
      {
        status = (number >> j) & 1;
        status ^= reverse ? 1 : 0;
        ans.push_back(status + '0');
      }
    }
    return ans;
  }
};

/**
 * Your Bitset object will be instantiated and called as such:
 * Bitset* obj = new Bitset(size);
 * obj->fix(idx);
 * obj->unfix(idx);
 * obj->flip();
 * bool param_4 = obj->all();
 * bool param_5 = obj->one();
 * int param_6 = obj->count();
 * string param_7 = obj->toString();
 */

int main()
{
  return 0;
}
