//
// Author info:
// Created by Hao Liang on 2022/6/26.
//
#include "./M.h"

int Solution_704::search(vector<int> &nums, int target) {
    vector<int>::iterator right, left;
    right = nums.end();
    left = nums.begin();
    while(right != left){
        vector<int>::iterator middle = left + (right - left) / 2;///防止溢出 等同于(left + right)/2,同时对于迭代器而言，operator+ is meanless
        if (*middle > target){
        right = middle;
        }
        else if(*middle < target){
        left = middle +1;
        }
        else
        {return distance(nums.begin(),middle);}
    }
    return -1;
}
