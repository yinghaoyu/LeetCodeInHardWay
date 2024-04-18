#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
  {
    // 万事不决先排序
    std::sort(nums1.begin(), nums1.end());
    std::sort(nums2.begin(), nums2.end());
    vector<int> ans;
    int i = 0;
    int j = 0;
    int n = nums1.size();
    int m = nums2.size();
    while (i < n && j < m)
    {
      if (nums1[i] == nums2[j])
      {
        if (ans.empty() || nums1[i] != ans.back())
        {
          // 保证元素唯一
          ans.push_back(nums1[i]);
        }
        i++;
        j++;
      }
      else if (nums1[i] > nums2[j])
      {
        j++;
      }
      else
      {
        i++;
      }
    }
    return ans;
  }
};
