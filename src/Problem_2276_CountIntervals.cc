#include <vector>

using namespace std;

// 开点线段树的实现
class CountIntervals
{
 private:
  // 支持的最大范围
  static const int n = 1000000000;

  // 空间大小定成这个值是实验的结果
  static const int LIMIT = 700001;

  vector<int> left = vector<int>(LIMIT);
  vector<int> right = vector<int>(LIMIT);
  vector<int> sum = vector<int>(LIMIT);
  int cnt = 1;

 public:
  CountIntervals() {}

  void up(int h, int l, int r) { sum[h] = sum[l] + sum[r]; }

  // 这个题的特殊性在于，只有改1的操作，没有改0的操作
  // 理解这个就可以分析出不需要懒更新机制，原因有两个
  // 1) 查询操作永远查的是整个范围1的数量，不会有小范围的查询，每次都返回sum[1]
  //    这意味着只要能把sum[1]更新正确即可，up函数可以保证这一点
  // 2) 一个范围已经全是1，那以后都会是1，没有必要把全是1的懒更新信息向下传递
  // 这个函数的功能比线段树能做到的范围修改功能简单很多
  // 功能有阉割就意味着存在优化的点
  void setOne(int jobl, int jobr, int l, int r, int i)
  {
    if (sum[i] == r - l + 1)
    {
      return;
    }
    if (jobl <= l && r <= jobr)
    {
      sum[i] = r - l + 1;
    }
    else
    {
      int mid = (l + r) >> 1;
      if (jobl <= mid)
      {
        if (left[i] == 0)
        {
          left[i] = ++cnt;
        }
        setOne(jobl, jobr, l, mid, left[i]);
      }
      if (jobr > mid)
      {
        if (right[i] == 0)
        {
          right[i] = ++cnt;
        }
        setOne(jobl, jobr, mid + 1, r, right[i]);
      }
      up(i, left[i], right[i]);
    }
  }

  void add(int left, int right) { setOne(left, right, 1, n, 1); }

  int count() { return sum[1]; }
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */
