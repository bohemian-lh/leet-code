//
// Author info:
// Created by Hao Liang on 2022/6/18.
//
#include "../solution-class/M.h"

/*1、统计一篇英文(The_Holy_Bible.txt)文章中出现的单词和词频，
输入：某篇文章的绝对路径
        输出：词典（词典中的内容为每一行都是一个“单词 词频”）*/
/*
 * 解决思路：使用文件流（iofstream），以只读模式打开指定文件。
 * 一次读取一行（读取前判断文件流是否在eofbit状态），分割单词，或者一次读取一个单词。
 * 读取后判定是否合法：合法即存入map
 * 读取完毕，将所有map写入dictionary对象
 * */

struct Record
{
    string _word;
    int _frequency;
};
/*

void split(const string &s, const vector<string> &tokens, const string &delimiters = "") {
    string::size_type lastPos = s.find_first_not_of(delimiters, 0);
    string::size_type pos = s.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos) {
        string &&s2 = s.substr(lastPos, pos - lastPos);
        tokens.emplace_back(s2);//use emplace_back after C++11
        lastPos = s.find_first_not_of(delimiters, pos);
        pos = s.find_first_of(delimiters, lastPos);
    }
}
*/

class Dictionary
{
public:
    void readByString(const std::string &filename);
    void readByStream(const std::string &filename);
    void store(const std::string &filename);
    bool isWord(const string &word);
    void standardWord(string &word);
    void standardWord(fstream &tmp);
    void sortDictionary();
private:
    vector<Record> _dict;
    map<string, int> mapWordRecoder;
};

void Dictionary::standardWord(string &word) {
    //正则的迭代器代价很高，应该在最小范围内创建，所有使用流的形式
    regex pattern("[[:alpha:]]+");
    for (sregex_iterator it(word.begin(), word.end(), pattern) , end_it;  it != end_it ; ++it) {
        ++mapWordRecoder[it->str()];
    }
}

void Dictionary::standardWord(fstream &tmp){
    //使用流的迭代器，遵循创建正则规则的最小范围原则，只创建一次正则及其迭代器
    //是否会有内存泄露的风险？未知
    regex pattern("[[:alpha:]]+");
    std::istreambuf_iterator<char> begin(tmp);
    std::istreambuf_iterator<char> end;
    std::string word(begin, end);
    transform(word.begin(),word.end(),word.begin(),::tolower);
    for (sregex_iterator it(word.begin(), word.end(), pattern), end_it; it != end_it; ++it) {
        ++mapWordRecoder[it->str()];
    }
}


void Dictionary::readByString(const std::string &filename) {
    fstream fileInputStream;
    fileInputStream.open(filename, ios::in);
    string stringLineforFilestream;
    while (getline(fileInputStream, stringLineforFilestream) && fileInputStream.good()) {
        standardWord(stringLineforFilestream);
    }
    fileInputStream.close();
}

void Dictionary::readByStream(const std::string &filename) {
    fstream fileInputStream;
    fileInputStream.open(filename, ios::in);
    if (fileInputStream.good()) {
        standardWord(fileInputStream);
    }
    fileInputStream.close();
}

void Dictionary::store(const std::string &filename) {
    fstream fileOutputStream;
    fileOutputStream.open("../mylib/Dictionary.txt", ios::out );
    fileOutputStream.close();
    fileOutputStream.open("../mylib/Dictionary.txt", ios::out | ios::app);
    for (const auto &x : mapWordRecoder) {
        fileOutputStream << x.first << "\t" << x.second << endl;
    }
    fileOutputStream.close();
}

int main(){
    Dictionary dictionary;
    time_t time_beg = time(NULL);
    dictionary.readByStream("../mylib/bible.txt");
    dictionary.store("../mylib/Dictionary.txt");
    time_t time_end = time(NULL);
    cout << time_end - time_beg << endl;
    return 0;
}
