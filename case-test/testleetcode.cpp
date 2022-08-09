//
// Author info:
// Created by Hao Liang on 2022/7/23.
//
#include "../solution-class/M.h"
#include "../solution-class/MyLinkedList_707.cpp"


int main(){
    MyLinkedList_707 m;
    m.addAtHead(4);
    m.get(1);
    m.addAtHead(5);
    m.addAtHead(3);
    m.deleteAtIndex(7);
    m.addAtHead(3);
    m.get(3);
    m.get(3);
    m.addAtHead(1);
    m.deleteAtIndex(4);
    return 0;

}
