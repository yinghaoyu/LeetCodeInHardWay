#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class WordsFrequency
{
  unordered_map<string, int> freq;

 public:
  WordsFrequency(vector<string>& book)
  {
    for (auto& word : book)
    {
      freq[word]++;
    }
  }

  int get(string word)
  {
    if (!freq.count(word))
    {
      return 0;
    }
    return freq[word];
  }
};

/**
 * Your WordsFrequency object will be instantiated and called as such:
 * WordsFrequency* obj = new WordsFrequency(book);
 * int param_1 = obj->get(word);
 */
