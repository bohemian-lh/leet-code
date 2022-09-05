//
// Author info:
// Created by Hao Liang on 2022/6/18.
//
#include "../solution-class/M.h"

/*1��ͳ��һƪӢ��(The_Holy_Bible.txt)�����г��ֵĵ��ʺʹ�Ƶ��
���룺ĳƪ���µľ���·��
        ������ʵ䣨�ʵ��е�����Ϊÿһ�ж���һ�������� ��Ƶ����*/
/*
 * ���˼·��ʹ���ļ�����iofstream������ֻ��ģʽ��ָ���ļ���
 * һ�ζ�ȡһ�У���ȡǰ�ж��ļ����Ƿ���eofbit״̬�����ָ�ʣ�����һ�ζ�ȡһ�����ʡ�
 * ��ȡ���ж��Ƿ�Ϸ����Ϸ�������map
 * ��ȡ��ϣ�������mapд��dictionary����
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
    //����ĵ��������ۺܸߣ�Ӧ������С��Χ�ڴ���������ʹ��������ʽ
    regex pattern("[[:alpha:]]+");
    for (sregex_iterator it(word.begin(), word.end(), pattern) , end_it;  it != end_it ; ++it) {
        ++mapWordRecoder[it->str()];
    }
}

void Dictionary::standardWord(fstream &tmp){
    //ʹ�����ĵ���������ѭ��������������С��Χԭ��ֻ����һ�������������
    //�Ƿ�����ڴ�й¶�ķ��գ�δ֪
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
