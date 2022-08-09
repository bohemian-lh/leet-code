//
// Created by Administrator on 2022/6/13.
//
#include "./M.h"
/*该题还有二分法解*/
int Solution_209::minSubArrayLen(int target, vector<int> &nums) {
    int flagCurrent = 0;//当前的最小长度
    int flagRunning = 0;//本次的待比较的最小长度
    vector<int>::iterator it_left, it_right;//滑动窗口的一对范式
    it_left = it_right = nums.begin();//滑动窗口初始化
    int sum = *it_left;//记录当前滑动窗口的和值
    while(it_right != nums.end()){
        if(sum >= target){ //当前和值大于target，窗口缩小，左迭代器向右移动;左移时不得破坏迭代范围范式
            if (it_right == it_left)
                return 1;
            else{
                flagRunning =it_right - it_left +1;
                sum =sum - *it_left++;
            }
        }
        else{//当前和值小于target,窗口扩大，右迭代器向右移动
            if (++it_right == nums.end()) break;
            sum += *it_right;
        }
        if (flagCurrent == 0 || flagRunning < flagCurrent)
            flagCurrent = flagRunning;
    }
    return flagCurrent;
}


