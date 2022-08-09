//
// Author info:
// Created by Hao Liang on 2022/6/27.
//
#include "./M.h"

vector<int> Solution_977::sortedSquares(vector<int>& nums) {
    for(int index = 0;index != nums.size();++index){//左闭右开的区间界限
        nums[index] = nums[index]*nums[index];
    }
    int left, right;//正常情况使用双指针
    left = 0;
    right = nums.size() - 1;
    vector<int> sortedSquares(nums.size(), 0);
    int k = nums.size() - 1;
    for(;left <= right;) {//左闭右闭
        if(nums[left] <= nums[right]){
            sortedSquares[k--]=nums[right--];
        }
        else {
            sortedSquares[k--]=nums[left++];
        }
    }
    return sortedSquares;
}
