//
// Created by Administrator on 2022/10/7.
//
#include "./M.h"
/**
 * 题目描述：
 *给你一个字符串数组 words ，请你找出所有在 words 的每个字符串中都出现的共用字符（ 包括重复字符），并以数组形式返回。你可以按 任意顺序 返回答案。
 * @param words
 * @return
 */
vector<string> Solution_1002::commonChars(vector<std::string> &words) {
    vector<string> result;
    string string_result("");
    if (words.size() == 0) return result;
    int Hash[26];
    int hasHash[26];
    memset(Hash, 0, 26 * sizeof(int));
    for (auto charx: words[0]) {
        Hash[charx - 'a']++;
    }
    for (int size = 2; size <= words.size(); size++) {
        memset(hasHash, 0, 26 * sizeof(int));
        size_t index = size - 1;
        for (auto charx: words[index]) {
            hasHash[charx - 'a']++;
        }
        for (int size = 1; size <= 26; size++) {
            size_t index = size - 1;
            Hash[index] = Hash[index] < hasHash[index] ? Hash[index] : hasHash[index];
        }
    }
    //将哈希表转化为字符串
    for (int size = 1; size <= 26; size++) {
        size_t index = size - 1;
        while (Hash[index] != 0) {
            string s(1, index + 'a');
            result.push_back(s);
            Hash[index]--;
        }
    }
    return result;
}

int main(){
    vector<string> words;
    words.push_back("wordds");
    words.push_back("worldd");
    words.push_back("wdds");
    vector<string> res =  Solution_1002::commonChars(words);
    for (auto stringx: res) {
        cout << stringx << " ";
    }
    string &&sx = "we";
    return 0;
}