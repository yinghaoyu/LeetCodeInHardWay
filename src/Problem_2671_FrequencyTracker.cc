#include <unordered_map>

using namespace std;

class FrequencyTracker
{
 private:
  unordered_map<int, int> freq;
  unordered_map<int, int> freq_cnt;

 public:
  FrequencyTracker() {}

  void add(int number)
  {
    freq_cnt[freq[number]]--;
    freq_cnt[++freq[number]]++;
  }

  void deleteOne(int number)
  {
    if (freq[number] == 0)
    {
      return;
    }
    freq_cnt[freq[number]]--;
    freq_cnt[--freq[number]]++;
  }

  bool hasFrequency(int frequency) { return freq_cnt[frequency] > 0; }
};

/**
 * Your FrequencyTracker object will be instantiated and called as such:
 * FrequencyTracker* obj = new FrequencyTracker();
 * obj->add(number);
 * obj->deleteOne(number);
 * bool param_3 = obj->hasFrequency(frequency);
 */
