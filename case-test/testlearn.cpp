//
// Author info:
// Created by Hao Liang on 2022/7/4.
//
#include <cstring>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
//һ��Ҫע�ⷵ��ֵ�ǲ��Ǿֲ���������û���þֲ�����������ֵ
/**
 *@
 * */

class String{
public:
    class charIndex;
    friend std::ostream &operator<<(std::ostream &os, const String &rhs);
    friend std::ostream &operator<<(std::ostream &os, const charIndex &rhs);

public:
    String()
            :_pstr(new char[5]() + 4)
            ,_refCount((int *)(_pstr - 4))
    {
        cout << "String()" << endl;
        *_refCount = 1;
    };


    String(const String &rhs)
            :_pstr(rhs._pstr)
            ,_refCount(rhs._refCount){
        increaseRefCount();
    }

    String(const char *pstr)
    :_pstr(new char[5 + strlen(pstr)] + 4)
     ,_refCount((int *)(_pstr - 4)){
        strcpy(_pstr,pstr);
        *_refCount = 1;
    }

    ~String(){
        cout << "~String()" << endl;
        release();
    }

    size_t size() const {
        return strlen(_pstr);
    }

    int getRefcount(){
        return *_refCount;
    }

    const char *c_str() const{
        return _pstr;
    }
    /**
     *@biefly ����operator=�����������Ը��ƣ��򷵻����������ͷŵ�ǰ����Ȼ�����ǳ�������������ü���
     * */
    String &operator=(const String &rhs)
    {
        if(this == &rhs)
            return *this;
        else{
            release();
            _pstr = rhs._pstr;
            _refCount = rhs._refCount;
            ++*_refCount;
        }
        return *this;
    }


    /**
     * string[0] = 'H'
     * @briefly ����operator[]���������������±�Ƿ����򷵻�һ��'\0'
     * 	    �±�Ϸ����ж����ڴ��Ƿ����Ǿͽ������Ȼ���ͷ�ԭ�����ڴ�
     * */
    charIndex &operator[](size_t index){
        if(index < size()){
            idx->_index = index;
            idx->_tmp = this;
        }
        return *idx;
    }
private:
    void decreaseRefCount(){
        --*_refCount;
    }

    void increaseRefCount(){
        ++*_refCount;
    }

    void initRefCount(){
        *_refCount == 1;
    }

    void release(){
        decreaseRefCount();
        if(*_refCount == 0){
            delete [](_pstr - 4);
        }
    }
public:
    class charIndex{
    public:
        charIndex &operator=(const char &rhs){
            if(_tmp->_pstr[_index] != rhs){
                char *tmpstr = new char[1 + _tmp->size()] ;
                //�ֲ��������ܸ�������ʹ�õ�ֵ
                strcpy(tmpstr, _tmp->_pstr);
                _tmp->release();
                _tmp->_pstr = new char[5 + strlen(tmpstr)] + 4;
                _tmp->_refCount = (int *)(_tmp->_pstr - 4);
                strcpy(_tmp->_pstr, tmpstr);
                * (_tmp->_refCount) = 1;
                _tmp->_pstr[_index] = rhs;
            }
            return *this;
        }

        ~charIndex(){
            if(_tmp){
                _tmp = nullptr;
            }
        }

        int _index = 0;
        String *_tmp = nullptr;
    };
private:
    char *_pstr;
    int *_refCount;
    static charIndex *idx;
};

String::charIndex *String::idx = new String::charIndex();


std::ostream &operator<<(std::ostream &os, const String &rhs){
    if(rhs._pstr){
        os << rhs._pstr;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const String::charIndex &rhs){
    char *ps = rhs._tmp->_pstr;
    if(ps[rhs._index]){
        os <<ps[rhs._index];
    }
    return os;
}
int main() {
    String s1 = "helloworld";
    cout << "s1 = " << s1 << endl;
    cout << "s1.getRefcount() = " << s1.getRefcount() << endl;
    printf("s1's address : %p\n", s1.c_str());

    cout << endl;
    String s2 = s1;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s1.getRefcount() = " << s1.getRefcount() << endl;
    cout << "s2.getRefcount() = " << s2.getRefcount() << endl;
    printf("s1's address : %p\n", s1.c_str());
    printf("s2's address : %p\n", s2.c_str());

    cout << endl;
    String s3("world");
    cout << "s3 = " << s3 << endl;
    cout << "s3.getRefcount() = " << s3.getRefcount() << endl;
    printf("s3's address : %p\n", s3.c_str());

    cout << endl << endl;
    s3 = s1;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s1.getRefcount() = " << s1.getRefcount() << endl;
    cout << "s2.getRefcount() = " << s2.getRefcount() << endl;
    cout << "s3.getRefcount() = " << s3.getRefcount() << endl;
    printf("s1's address : %p\n", s1.c_str());
    printf("s2's address : %p\n", s2.c_str());
    printf("s3's address : %p\n", s3.c_str());

    cout << endl << "��s3[0]ִ��д����" << endl;
    s3[0] = 'H';//char ='H'
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s1.getRefcount() = " << s1.getRefcount() << endl;
    cout << "s2.getRefcount() = " << s2.getRefcount() << endl;
    cout << "s3.getRefcount() = " << s3.getRefcount() << endl;
    printf("s1's address : %p\n", s1.c_str());
    printf("s2's address : %p\n", s2.c_str());
    printf("s3's address : %p\n", s3.c_str());

    cout << endl << "��s1[0]ִ�ж�����" << endl;
    cout << "s1[0] = " << s1[0] << endl;//char
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s1.getRefcount() = " << s1.getRefcount() << endl;
    cout << "s2.getRefcount() = " << s2.getRefcount() << endl;

    String y ="holyshit";
    String x = y;
    cout << "x[2] = " << x[2] << endl;
    cout << "x = " << x << endl;
    cout << "x.getRefcount() = " << x.getRefcount() << endl;
    printf("x's address : %p\n", x.c_str());
    x[2] = 'L';
    cout << "x = " << x << endl;
    cout << "x.getRefcount() = " << x.getRefcount() << endl;
    cout << "y.getRefcount() = " << y.getRefcount() << endl;
    printf("x's address : %p\n", x.c_str());

    return 0;

}