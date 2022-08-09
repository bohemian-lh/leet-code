//
// Author info:
// Created by Hao Liang on 2022/7/24.
//
// 给你单链表的头节点 head ，请你反转链表，并返回反转后的链表
#include "./M.h"
// 反转链表循环体中只进行以下操作：
//                          1、断链，并指向前节点;
//                          2、断链之后产生新的头节点;
//整个循环过程中，不断移动的是头节点，知道反转完成
ListNode *Solution_206::reverseList(ListNode *head) {
    ListNode *reg;
    ListNode *front = nullptr;
    while (head->next != nullptr) {
        reg = head->next;
        head->next = front;
        front = head;
        head = reg;
    }
    vector<int>::size_type
    return front;
}

/**
 * 后向递归写法
 * reverseList(ListNode *head) {
 * if(head == nullptr){
 *
 * }
 * }
 *
 * */

