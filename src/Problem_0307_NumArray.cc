#include <iostream>
#include <vector>

using namespace std;

class NumArray
{
 private:
  vector<int> A;  // 原数组
  vector<int> C;  // 树状数组

  int lowBit(int x) { return x & -x; }

  void add(int index, int u)
  {
    for (int i = index; i < C.size(); i += lowBit(i))
    {
      C[i] += u;
    }
  }

  int query(int index)
  {
    int sum = 0;
    for (int i = index; i > 0; i -= lowBit(i))
    {
      sum += C[i];
    }
    return sum;
  }

 public:
  NumArray(vector<int>& nums)
  {
    A = nums;
    // 防止 lowBit(i) 结果为 0，所以 C 的下标从 1 开始
    C = vector<int>(A.size() + 1);
    for (int i = 0; i < A.size(); i++)
    {
      add(i + 1, A[i]);
    }
  }

  void update(int index, int val)
  {
    int diff = val - A[index];
    add(index + 1, diff);
    A[index] = val;
  }

  int sumRange(int left, int right) { return query(right + 1) - query(left); }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
