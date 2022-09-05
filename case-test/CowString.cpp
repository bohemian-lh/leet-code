#include <stddef.h>
#include <sched.h>
#include <stdio.h>
#include <string.h>
//issue#1: 构建采用经过一次中间转化的容器会出错 例如 std::vector<String> veStr{"WE", "Find"};
//         已解决

#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::cin;
// cow的几个要点
// 浅拷贝时：指针对应的引用计数+1，指针指向同一内存地址
// 深拷贝时：1、创建时深拷贝，正常的申请地址创建。
//	     2、对于创建完成的string深拷贝，释放引用计数，若计数为0，则释放空间；然后申请空间完成深拷贝。
//copy on write:属于拷贝控制的范畴，同时考虑下标运算符和<<>>运算符，共有8个基本函数。
class String{
private:
    //辅助类：CharIndex
    //CharIndex 内部类需要完成的功能(String的下标运算符返回一个CharIndex对象)
    //1、String[] = char
    //2、String[] = String[]
    //3、cout << String[];
    // 总的来说两个功能：一个赋值，一个输出。
    // 可能要解决的问题：
    //	1、赋值运算符第一问题：是否自赋值
    //	2、浅引用、深拷贝问题：仅仅输出为浅拷贝、赋值则为深拷贝。-》所以CharIndex 第二个数据成员设计，也可以设计为String &father。
    //	tips:第二个成员函数设计为引用的好处，不干涉其他的行为和操作。在此例中，设计为引用后，charindex类不涉及，引用计数以及pstr的管理。
    //	tips:还应考虑标准库容器的移动问题。
    class CharIndex{
    public:
        //普通构造函数：构造完检查index和合法性，引用计数加一。
        //CharIndex作为String的内部类解决下标运算的问题，不存在拷贝构造和移动构造的情况。
        //如果考虑标准库的容器操作，应当3/5操作补全
        CharIndex(String &father, size_t index):_father(father), _index(index){
            if(_index >= strlen(_father._pstr)){
                _index = 0;
                cout << "Warning: Invalid Input size_t " << endl;
            }
            cout << "CharIndex() " << endl;
        }

        //char类型的内存空间占用少，可以不考虑移动赋值运算符。
        CharIndex &operator=(const char &rhs){
            if((char *)this != &rhs){//凡是赋值运算符都要考虑自赋值，否则释放自身后，会丢失数据
                char *tmp = new char[5 + strlen(_father._pstr)]() + 4;
                strcpy(tmp, _father._pstr);
                tmp[_index] = rhs;
                _father.release();
                _father._pstr = tmp;
                cout << "CharIndex &operator=(const char &rhs)" << endl;
            }
            return *this;
        }

        CharIndex &operator=(const CharIndex &rhs){
            if(this != &rhs){//凡是赋值运算符都要考虑自赋值，否则释放自身后，会丢失数据
                char *tmp = new char[5 + strlen(_father._pstr)] + 4;
                strcpy(tmp, _father._pstr);
                tmp[_index] = rhs._father._pstr[rhs._index];
                _father.release();
                _father._pstr = tmp;
            }
            return *this;
        }

        //移动赋值运算符，若是考虑到标准库容器，最好加上移动赋值运算符
        CharIndex &operator=(char &&rhs) noexcept {
            if((char*)this != &rhs){//凡是赋值运算符都要考虑自赋值，否则释放自身后，会丢失数据
                char *tmp = new char[5 + strlen(_father._pstr)] + 4;
                strcpy(tmp, _father._pstr);
                tmp[_index] = rhs;
                _father = String(tmp);
                delete [] (tmp - 4);
            }
            return *this;
        }

        operator char() const{
            cout << "char operator()" << endl;
            return (char)_father._pstr[_index];
        }
    public:
        size_t _index;
        String &_father;
    };

    friend std::ostream &operator<<(std::ostream &os, const String &rhs);

    friend std::ostream &operator<<(std::ostream &os, const CharIndex &charindex);

public:
    //默认的构造函数,深拷贝。
    String():_pstr(new char[5]() + 4), _refCount((int *)(_pstr - 4)){
        initPstr();
        initRefCount();
        cout << "String() " << endl;
    }

    //普通的构造函数，参数接受一个字符串数组,深拷贝。
    String(const char *rhs):_pstr(new char[5 + strlen(rhs)]() + 4), _refCount((int *)(_pstr - 4)){
        strcpy(_pstr,rhs);
        initRefCount();
        cout << "String(const char *rhs) " << endl;
    }

    //拷贝构造函数，参数接收一个String类对象，浅拷贝，引用计数+1，字符串指针指向同一内存地址。
    String(const String &rhs):_pstr(rhs._pstr), _refCount((int *)(_pstr - 4)){
        increaseRefCount();
        cout << "String(const String &rhs)" << endl;
    }

    //移动构造函数，参数接收一个String类对象的右值，浅拷贝，引用计数不变，字符串指针指向其内存地址。
    String(String &&rhs) noexcept :_pstr(rhs._pstr), _refCount(rhs._refCount){
        increaseRefCount();
        rhs.release();
        cout << "String(String &&rhs) " << endl;
    }

    //拷贝赋值函数，参数接收一个String类对象。
    //如果不是自赋值，则先释放左对象，然后浅拷贝，引用计数加1，字符串指针指向同一内存地址。
    String &operator=(const String &rhs){
        if(this != &rhs){//检查自赋值情况，主要检查参数对象是move调用返回的结果的情况。
            release();
            _pstr = rhs._pstr;
            _refCount = rhs._refCount;
            increaseRefCount();
        }
        return *this;
    }

    //移动赋值函数，参数接收一个String类对象的右值。
    String &operator=(String &&rhs){
        if(this != &rhs){// 检查自赋值情况，主要检查参数对象是move调用返回的结果的情况。
            release();
            _pstr = rhs._pstr;
            _refCount = rhs._refCount;
            increaseRefCount();
            rhs.release();
        }
        return *this;
    }

    //析构函数
    ~String(){
        if(_refCount != nullptr && _pstr != nullptr) {//判断是否是移后源，保证对象可析构
            release();
        }
        cout << "~String() " << endl;
    }

    //相关函数1：下标运算符
    CharIndex operator[](size_t index){
        CharIndex tmp = CharIndex(*this, index);
        return  tmp;
    }

    void initPstr(){
        *_pstr = '\0';
    }

    void initRefCount(){
        if(_refCount)
            *_refCount = 0;
        increaseRefCount();
    }

    void increaseRefCount(){
        ++*_refCount;
    }

    void decreaseRefCount(){
        --*_refCount;
    }

    int getRefCount(){
        return *_refCount;
    }

    const char *c_str(){
        return _pstr;
    }

    void release(){
        if(_refCount != nullptr && _pstr != nullptr){//判断是否是移后源，保证对象可析构
            decreaseRefCount();
            if(*_refCount == 0){
                delete [] (_pstr - 4);
            }
            _pstr = nullptr;
            _refCount = nullptr;}
    }

private:
    char *_pstr = nullptr;
    int *_refCount = nullptr;
};

std::ostream &operator<<(std::ostream &os, const String &rhs){
    os << rhs._pstr;
    return os;
}

std::ostream &operator<<(std::ostream &os, const String::CharIndex &charindex){
    os << (char)charindex;
    return os;
}
