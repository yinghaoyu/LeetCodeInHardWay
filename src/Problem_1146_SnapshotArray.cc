#include <algorithm>
#include <vector>

using namespace std;

class SnapshotArray
{
  vector<vector<std::pair<int, int>>> arr;
  int cnt = 0;

 public:
  SnapshotArray(int length) { arr.resize(length); }

  void set(int index, int val) { arr[index].emplace_back(cnt, val); }

  // snap_id 从 0 开始
  int snap() { return cnt++; }

  int get(int index, int snap_id)
  {
    auto& cur = arr[index];
    // lower_bound(begin, end, nun)  找到第一个 >= num 的位置
    // upper_bound(begin, end, num)  找到第一个 >  num 的位置
    auto itr = upper_bound(cur.begin(), cur.end(), std::make_pair(snap_id, INT32_MAX));
    // 前面的一个位置，即 snap_id 对应的值
    return itr == cur.begin() ? 0 : prev(itr)->second;
  }
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */
