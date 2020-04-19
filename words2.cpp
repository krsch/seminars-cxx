#include <string_view>
#include <vector>
#include <algorithm>
#include <locale>
#include <iostream>

std::vector<std::string_view> words(std::string_view str)
{
    auto word_end = str.begin();
    auto prev = str.begin();
    std::vector<std::string_view> result;
    std::locale loc("");
    while (word_end != str.end()) {
        word_end = std::find_if(prev, str.end(),
                            [&loc](char c) { return !std::isalpha(c, loc); });
        auto word = str.substr(prev - str.begin(), word_end - prev);
        if (!word.empty()) 
            result.push_back(word);
        prev = std::find_if(word_end, str.end(),
                            [&loc](char c) { return std::isalpha(c, loc); });
        
    }
    return result;
}

int main() {
    auto res = words(std::string_view("asjnv sfd435: sj::df"));
    for (auto it:res) 
        std::cout << it << "\n";
    return 0;
}