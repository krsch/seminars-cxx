#include <algorithm>
#include <map>
#include <string_view>
#include <locale>

std::map<std::string_view, int> count_words(std::string_view s) {
    std::map<std::string_view, int> res;
    std::locale loc{""};
    while (!s.empty()) {
      auto index =
          std::find_if(s.begin(), s.end(),
                       [&loc](char c) { return !std::isalpha(c, loc); }) -
          s.begin();
      auto word = s.substr(0, index);
      res[word] += 1;
      s.remove_prefix(index);
      index = std::find_if(s.begin(), s.end(),
                           [&loc](char c) { return std::isalpha(c, loc); }) -
              s.begin();
      s.remove_prefix(index);
    }
    return res;
}