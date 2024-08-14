#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

// TODO: figure it out
class Solution
{
 public:
  long long maxBalancedSubsequenceSum(vector<int>& nums)
  {
    build(nums);
    long pre;
    for (int i = 0, k; i < n; i++)
    {
      // k的含义为当前的指标是第几号指标
      k = rank(nums[i] - i);
      // dp[1号..k号指标]中的最大值是多少
      pre = max(k);
      if (pre < 0)
      {
        // 如果之前的最好情况是负数，那么不要之前的数了
        // 当前数字自己单独形成平衡子序列
        // 去更新dp[k号指标]，看能不能变得更大
        update(k, nums[i]);
      }
      else
      {
        // 如果之前的最好情况不是负数，那么和当前数字一起形成更大的累加和
        // 去更新dp[k号指标]，看能不能变得更大
        update(k, pre + nums[i]);
      }
    }
    // 返回dp[1号..m号指标]中的最大值
    return max(m);
  }

 private:
  static constexpr int MAXN = 100001;

  vector<int> sort = vector<int>(MAXN);

  vector<long> tree = vector<long>(MAXN);

  int n, m;

  void build(vector<int>& nums)
  {
    n = nums.size();
    for (int i = 1, j = 0; i <= n; i++, j++)
    {
      sort[i] = nums[j] - j;
    }
    std::sort(sort.begin() + 1, sort.begin() + n + 1);
    m = 1;
    for (int i = 2; i <= n; i++)
    {
      if (sort[m] != sort[i])
      {
        sort[++m] = sort[i];
      }
    }
    std::fill(tree.begin() + 1, tree.begin() + m + 1, LONG_MIN);
  }

  // 当前的指标值是v，返回这是第几号指标
  int rank(int v)
  {
    int left = 1, right = m, mid;
    int ans = 0;
    while (left <= right)
    {
      mid = (left + right) / 2;
      if (sort[mid] <= v)
      {
        ans = mid;
        left = mid + 1;
      }
      else
      {
        right = mid - 1;
      }
    }
    return ans;
  }

  // dp[i号指标]，当前算出的值是v
  void update(int i, long v)
  {
    while (i <= m)
    {
      tree[i] = std::max(tree[i], v);
      i += i & -i;
    }
  }

  // dp[1..i]，最大值多少返回
  long max(int i)
  {
    long ans = LONG_MIN;
    while (i > 0)
    {
      ans = std::max(ans, tree[i]);
      i -= i & -i;
    }
    return ans;
  }
};
