//
// Author info:
// Created by Hao Liang on 2022/7/22.
//
#include "M.h"
/**
 * @number:203
 * @brief 给你一个链表的头节点 head 和一个整数 val ，
 * 请你删除链表中所有满足 Node.val == val 的节点，并返回 新的头节点 。
 * */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution_203{
public:
    ListNode* removeElements(ListNode* head, int val){
        ListNode *dummyHead = new ListNode(0, head);
        ListNode *loopNode = dummyHead;
        while (loopNode->next != nullptr) {
            if (loopNode->next->val == val) {
                ListNode *loopNode2 = loopNode->next;
                loopNode->next = loopNode->next->next;
                delete loopNode2;
            }
            else loopNode = loopNode->next;
        }
        head = dummyHead->next;
        delete dummyHead;
        return head;
    }
};