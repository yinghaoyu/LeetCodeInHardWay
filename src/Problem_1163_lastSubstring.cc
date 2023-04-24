#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // https://leetcode.cn/problems/last-substring-in-lexicographical-order/solution/javapython3shuang-zhi-zhen-bi-jiao-tu-ji-pvb6/
  // 双指针
  string lastSubstring1(string s)
  {
    int n = s.length();
    int i = 0;
    int j = 1;
    int k = 0;
    char ch1;
    char ch2;
    while (j + k < n)
    {
      ch1 = s[i + k];
      ch2 = s[j + k];
      if (ch1 == ch2)
      {
        k++;
      }
      else if (ch1 < ch2)
      {
        i += k + 1;
        k = 0;
        if (i >= j)
        {
          // 保证 j > i
          j = i + 1;
        }
      }
      else
      {
        j += k + 1;
        k = 0;
      }
    }
    return s.substr(i);
  }

  // TODO: figure it out
  // DC3 算法
  string lastSubstring2(string s)
  {
    if (s.length() == 0)
    {
      return s;
    }
    int N = s.length();
    int min = INT32_MAX;
    int max = INT32_MIN;
    for (char cha : s)
    {
      min = std::min(min, (int) cha);
      max = std::max(max, (int) cha);
    }
    vector<int> arr(N);
    for (int i = 0; i < N; i++)
    {
      arr[i] = s[i] - min + 1;
    }
    DC3 dc3(arr, max - min + 1);
    return s.substr(dc3.sa[N - 1]);
  }

  class DC3
  {
   public:
    vector<int> sa;

    vector<int> rank;

    DC3(vector<int> &nums, int max)
    {
      sa = getSa(nums, max);
      rank = getRank();
    }

   private:
    vector<int> getSa(vector<int> &nums, int max)
    {
      int n = nums.size();
      vector<int> arr(n + 3);
      for (int i = 0; i < n; i++)
      {
        arr[i] = nums[i];
      }
      return skew(arr, n, max);
    }

    vector<int> skew(vector<int> &nums, int n, int K)
    {
      int n0 = (n + 2) / 3, n1 = (n + 1) / 3, n2 = n / 3, n02 = n0 + n2;
      vector<int> s12(n02 + 3);
      vector<int> sa12(n02 + 3);
      for (int i = 0, j = 0; i < n + (n0 - n1); ++i)
      {
        if (0 != i % 3)
        {
          s12[j++] = i;
        }
      }
      radixPass(nums, s12, sa12, 2, n02, K);
      radixPass(nums, sa12, s12, 1, n02, K);
      radixPass(nums, s12, sa12, 0, n02, K);
      int name = 0, c0 = -1, c1 = -1, c2 = -1;
      for (int i = 0; i < n02; ++i)
      {
        if (c0 != nums[sa12[i]] || c1 != nums[sa12[i] + 1] || c2 != nums[sa12[i] + 2])
        {
          name++;
          c0 = nums[sa12[i]];
          c1 = nums[sa12[i] + 1];
          c2 = nums[sa12[i] + 2];
        }
        if (1 == sa12[i] % 3)
        {
          s12[sa12[i] / 3] = name;
        }
        else
        {
          s12[sa12[i] / 3 + n0] = name;
        }
      }
      if (name < n02)
      {
        sa12 = skew(s12, n02, name);
        for (int i = 0; i < n02; i++)
        {
          s12[sa12[i]] = i + 1;
        }
      }
      else
      {
        for (int i = 0; i < n02; i++)
        {
          sa12[s12[i] - 1] = i;
        }
      }
      vector<int> s0(n0);
      vector<int> sa0(n0);
      for (int i = 0, j = 0; i < n02; i++)
      {
        if (sa12[i] < n0)
        {
          s0[j++] = 3 * sa12[i];
        }
      }
      radixPass(nums, s0, sa0, 0, n0, K);
      vector<int> sa(n);
      for (int p = 0, t = n0 - n1, k = 0; k < n; k++)
      {
        int i = sa12[t] < n0 ? sa12[t] * 3 + 1 : (sa12[t] - n0) * 3 + 2;
        int j = sa0[p];
        if (sa12[t] < n0 ? leq(nums[i], s12[sa12[t] + n0], nums[j], s12[j / 3])
                         : leq(nums[i], nums[i + 1], s12[sa12[t] - n0 + 1], nums[j], nums[j + 1], s12[j / 3 + n0]))
        {
          sa[k] = i;
          t++;
          if (t == n02)
          {
            for (k++; p < n0; p++, k++)
            {
              sa[k] = sa0[p];
            }
          }
        }
        else
        {
          sa[k] = j;
          p++;
          if (p == n0)
          {
            for (k++; t < n02; t++, k++)
            {
              sa[k] = sa12[t] < n0 ? sa12[t] * 3 + 1 : (sa12[t] - n0) * 3 + 2;
            }
          }
        }
      }
      return sa;
    }

    void radixPass(vector<int> &nums, vector<int> &input, vector<int> &output, int offset, int n, int k)
    {
      vector<int> cnt(k + 1);
      for (int i = 0; i < n; ++i)
      {
        cnt[nums[input[i] + offset]]++;
      }
      for (int i = 0, sum = 0; i < cnt.size(); ++i)
      {
        int t = cnt[i];
        cnt[i] = sum;
        sum += t;
      }
      for (int i = 0; i < n; ++i)
      {
        output[cnt[nums[input[i] + offset]]++] = input[i];
      }
    }

    bool leq(int a1, int a2, int b1, int b2) { return a1 < b1 || (a1 == b1 && a2 <= b2); }

    bool leq(int a1, int a2, int a3, int b1, int b2, int b3) { return a1 < b1 || (a1 == b1 && leq(a2, a3, b2, b3)); }

    vector<int> getRank()
    {
      int n = sa.size();
      vector<int> ans(n);
      for (int i = 0; i < n; i++)
      {
        ans[sa[i]] = i + 1;
      }
      return ans;
    }
  };
};

void testLastSubstring()
{
  Solution s;
  EXPECT_TRUE("bab" == s.lastSubstring1("abab"));
  EXPECT_TRUE("tcode" == s.lastSubstring1("leetcode"));
  EXPECT_TRUE("bab" == s.lastSubstring2("abab"));
  EXPECT_TRUE("tcode" == s.lastSubstring2("leetcode"));
  EXPECT_SUMMARY;
}

int main()
{
  testLastSubstring();
  return 0;
}
