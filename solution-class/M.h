//
// Created by Administrator on 2022/6/13.
//

#ifndef LEETCODE_M_H
#define LEETCODE_M_H

#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <array>
#include <string>
#include <map>
#include <regex>
#include <algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
//数组经典题目
class Solution_209 {
public:
    static int minSubArrayLen(int target, vector<int> &nums);
};

class Solution_704{
public:
    int search(vector<int>& nums, int target) ;
};

class Solution_719{
public:
    int smallestDistancePair(vector<int>& nums, int k) ;
    int findPos(vector<int> &nums, int midDistance);
};

class Solution_977{
public:
    static vector<int> sortedSquares(vector<int>& nums);
};
//链表经典题目
class Solution_206{
public:
    static ListNode* reverseList(ListNode *head);
};
#endif //LEETCODE_M_H
