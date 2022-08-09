//
// Author info:
// Created by Hao Liang on 2022/7/1.
//
#include <iostream>

using namespace std;

class Singleton{
public:
    Singleton *getInstance(){
        if(_pInstance){
            _pInstance = new Singleton();
        }
        return _pInstance;
    }
private:
    Singleton(){
        cout << "";
    }
private:
    static Singleton *_pInstance;
};

Singleton *Singleton::_pInstance = nullptr;

int main(){
    return 0;
}
