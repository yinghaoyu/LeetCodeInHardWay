#include <vector>

using namespace std;

class StreamRank
{
 public:
  vector<int> arr;
  int index;
  StreamRank()
  {
    arr.resize(2001);
    index = 0;
  }

  void track(int x)
  {
    // 插入排序
    arr[index++] = x;
    int i = index - 1;
    for (int j = i - 1; j >= 0 && arr[j] > x; j--)
    {
      swap(arr[j], arr[j + 1]);
    }
  }

  // 二分搜索
  int getRankOfNumber(int x)
  {
    int l = 0;
    int r = index - 1;
    int idx = -1;
    while (l <= r)
    {
      int m = (r - l) / 2 + l;
      if (arr[m] <= x)
      {
        // 当 arr[m] 与 x 相等时，l 取 m + 1，重新在[m+1, r]区间找 <= x 的可性能
        idx = m;
        l = m + 1;
      }
      else
      {
        r = m - 1;
      }
    }
    // 当 x = 4，index最终指向的位置
    // 1 2 2 3 4 4 5
    //           ↑
    //          idx
    // 总共有 idx + 1 项
    return idx + 1;
  }
};

/**
 * Your StreamRank object will be instantiated and called as such:
 * StreamRank* obj = new StreamRank();
 * obj->track(x);
 * int param_2 = obj->getRankOfNumber(x);
 */
