#include <cstring>
#include <iostream>

using std::cout;
using std::endl;

//定义引用，函数可以返回局部对象，不能返回局部指针，引用，类型转化操作符
//返回值是非const引用，编译器会默认该引用还能在用到和修改，所以不能传入const到返回值
//同样不能返回局部指针也是道理

char nullchar = '\0';

class String{
    friend std::ostream &operator<<(std::ostream &os, String &rhs);
    
    private:
    	class charIndex{
	    public:
		charIndex(size_t index, String &father)
		:_index(index)
		 ,_father(father){}

		char &operator=(const char &rhs){
            if (_index < strlen(_father._pstr)) {

                if (_father.getRefCount() > 1) {
                    char *tmp = new char[5 + strlen(_father._pstr)] + 4;
                    strcpy(tmp, _father._pstr);
                    _father.release();
                    _father._pstr = tmp;
                    _father._refCount = (int *) (_father._pstr - 4);
                    _father.initRefCount();
                }
                _father._pstr[_index] = rhs;
                return _father._pstr[_index];
            }
            else {
                return nullchar;
            }
		}
		
		operator char(){
		    if(_index < _father.size())
                return _father._pstr[_index];
		    else
                return nullchar;
		}

	    private:
		size_t _index;
		String &_father;
	};

    friend std::ostream &operator<<(std::ostream &os, charIndex &rhs);

    public:
	    String()
	    :_pstr(new char[5]() + 4)
	     ,_refCount((int *)(_pstr - 4)){
            initRefCount();
            cout << "String() " << endl;
	     }

	    String(const char *rhs)
	    :_pstr(new char[5 + strlen(rhs)] + 4)
	     ,_refCount((int *)(_pstr - 4)){
            strcpy(_pstr, rhs);
            initRefCount();
            cout << "String(const char *)" << endl;
	    }

	    String(const String &rhs)
	    :_pstr(rhs._pstr)
	     ,_refCount((int *)(rhs._pstr - 4)){
            increaseRefCount();
	    }

	    ~String(){
            release();
	    }
	    
	    String &operator=(const String &rhs){
            if (this != &rhs) {
                release();
                _pstr = rhs._pstr;
                _refCount = (int *) (_pstr - 4);
                increaseRefCount();
            }
            return *this;
	    }
	    
	    charIndex operator[](size_t index){
            return charIndex(index, *this);
	    }


	    size_t size(){
            return strlen(_pstr);
	    }

	    int getRefCount(){
            return *_refCount;
	    }

	    const char *c_str(){
            return _pstr;
	    }
    private:
	    void initRefCount(){
            *_refCount = 1;
	    }

	    void increaseRefCount(){
            ++*_refCount;
	    }

	    void decreaseRefCount(){
            --*_refCount;
	    }
	    
	    void release(){
            decreaseRefCount();
            if (*_refCount == 0) {
                delete[] (_pstr - 4);
            }
	    }


    private:
	char *_pstr;
    int *_refCount;
};


 std::ostream &operator<<(std::ostream &os, String &rhs){
     if (rhs._pstr) {
         os << rhs._pstr;
     }
     return os;
 }

std::ostream &operator<<(std::ostream &os, String::charIndex &rhs){
     char tmp = rhs;
    os << tmp;
     os.clear();
     return os;
}

int main(){
    String s1("hello");
    cout << "s1 = " << s1 << endl;
    cout << "s1.getRefCount() = " << s1.getRefCount() <<endl;
    printf("s1's address : %p\n", s1.c_str());

    cout << endl;
    String s2 = s1;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s1.getRefCount() = " << s1.getRefCount() <<endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() <<endl;
    printf("s1's address : %p\n", s1.c_str());
    printf("s2's address : %p\n", s2.c_str());

    cout << endl;
    String s3("world");
    cout << "s3 = " << s3 << endl;
    cout << "s3.getRefCount() = " << s3.getRefCount() <<endl;
    printf("s3's address : %p\n", s3.c_str());

    cout << endl << endl;
    s3 = s1;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s1.getRefCount() = " << s1.getRefCount() <<endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() <<endl;
    cout << "s3.getRefCount() = " << s3.getRefCount() <<endl;
    printf("s1's address : %p\n", s1.c_str());
    printf("s2's address : %p\n", s2.c_str());
    printf("s3's address : %p\n", s3.c_str());

    cout << endl << "对s3[0]执行写操作" << endl;
    s3[0] = 'H';//char ='H'
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s1.getRefCount() = " << s1.getRefCount() <<endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() <<endl;
    cout << "s3.getRefCount() = " << s3.getRefCount() <<endl;
    printf("s1's address : %p\n", s1.c_str());
    printf("s2's address : %p\n", s2.c_str());
    printf("s3's address : %p\n", s3.c_str());

    cout << endl << "对s1[0]执行读操作" << endl;
    cout << "s1[0] = " << s1[0] << endl;//char
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s1.getRefCount() = " << s1.getRefCount() <<endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() <<endl;
    cout << "s3.getRefCount() = " << s3.getRefCount() <<endl;
    printf("s1's address : %p\n", s1.c_str());
    printf("s2's address : %p\n", s2.c_str());
    printf("s3's address : %p\n", s3.c_str());
	return 0;
    }

