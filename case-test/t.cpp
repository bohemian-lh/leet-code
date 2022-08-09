//
// Author info:
// Created by Hao Liang on 2022/7/3.
//
#include "../solution-class/M.h"
#include <stdlib.h>
#include <iostream>
#include <string>

using  std::cout;
using  std::endl;
using std:: string;

class Base{
    public:
        Base() =default;
        Base(int a)
        :_a(a){
            cout << "Base(int a) " << endl;
        }

        virtual void show(){
            cout << "_a " << _a << endl
                 << "void show() " << endl;
        }

    private:
        int _a = 0;
 };

class Deliver : protected Base{
    public:
        Deliver() = default;
        Deliver(int b)
        :_b(b){
            cout << "Deliver() " << endl;
        }

        virtual void show(){
            cout << "_b " << _b << endl
                 << "void show() " << endl;
        }

    private:
        int _b = 0;
};



void test(Base *rhs) {

    rhs->show();
}

void test1(Base &ref){
    ref.show();
    Base tmp(2);
    ref = tmp;
    ref.show();
}

int main(){
     Base *base = new Base();
     Base base2(2);

    Deliver *deliver = new Deliver(1);
     Base &refBase = *base;
    test1(refBase);

 }