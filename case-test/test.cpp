//
// Created by Administrator on 2022/6/13.
//
#include "../solution-class/M.h"

int minSubArrayLen(int target, vector<int>& nums){
    int currenDiantance = 0;//当前最小长度
    int left = 0, right = 0;//双指针初始化
    int cend = nums.size();
    int sum = nums[0];//记录当前窗口内的和值
    while(1){//采用左闭右开的区间界限
        if(sum < target){
            right++;
            if(right == cend) break;
            sum += nums[right];
        }
        else {
            if(currenDiantance == 0 || currenDiantance > right - left + 1)
                currenDiantance = right - left + 1;
            if(currenDiantance == 1) break;
            sum -= nums[left];
            left++;
        }
    }
    return currenDiantance;
}

int main(){
    /*
    regex regex1("([[:alpha:]]){1,}");
    string string1("(&&&&aaaaaaaaaaaaaa?%^&*aaefae");
    for (sregex_iterator it(string1.begin(), string1.end(), regex1),end_it ; it != end_it ; ++it) {
        cout << it->str() << endl;
    }*/
    vector<int> nums{2,3,1,2,4,3};
    int a = minSubArrayLen(7, nums);
    vector<vector<int>> matrix(10,vector<int>(10));
    string s = "saof";
    cout << s.
}