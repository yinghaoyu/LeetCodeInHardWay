#include <algorithm>
#include <cstdint>
#include <queue>
#include <vector>

using namespace std;

// TODO: figure it out.
class Solution
{
 private:
  class Employee
  {
   public:
    double ratio;  // 薪水 / 质量比例
    int quality;   // 质量

    Employee(double r, int q)
    {
      ratio = r;
      quality = q;
    }
  };

 public:
  double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k)
  {
    int n = quality.size();
    vector<Employee> employees;
    for (int i = 0; i < n; i++)
    {
      // 定义 ratio，表示每单位工作质量的工资
      employees.emplace_back(Employee((double) wage[i] / quality[i], quality[i]));
    }
    // 根据比例排序，比例小的在前，比例大的在后
    std::sort(employees.begin(), employees.end(),
              [](Employee& a, Employee& b) { return a.ratio < b.ratio; });
    // 大根堆，用来收集最小的前k个质量数值
    priority_queue<int> heap;
    // 堆里，最小的前k个质量数值，总和是多少
    int qualitySum = 0;
    double ans = INT32_MAX;
    for (int i = 0; i < n; i++)
    {
      int curQuality = employees[i].quality;
      if (heap.size() < k)
      {
        // 堆没满
        qualitySum += curQuality;
        heap.push(curQuality);
        if (heap.size() == k)
        {
          ans = std::min(ans, qualitySum * employees[i].ratio);
        }
      }
      else
      {
        // 堆满了
        if (heap.top() > curQuality)
        {
          qualitySum += curQuality - heap.top();
          heap.pop();
          heap.push(curQuality);
          ans = std::min(ans, qualitySum * employees[i].ratio);
        }
      }
    }
    return ans;
  }
};
