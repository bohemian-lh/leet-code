//
// Created by Administrator on 2022/6/13.
//
#include "./M.h"
/*���⻹�ж��ַ���*/
int Solution_209::minSubArrayLen(int target, vector<int> &nums) {
    int flagCurrent = 0;//��ǰ����С����
    int flagRunning = 0;//���εĴ��Ƚϵ���С����
    vector<int>::iterator it_left, it_right;//�������ڵ�һ�Է�ʽ
    it_left = it_right = nums.begin();//�������ڳ�ʼ��
    int sum = *it_left;//��¼��ǰ�������ڵĺ�ֵ
    while(it_right != nums.end()){
        if(sum >= target){ //��ǰ��ֵ����target��������С��������������ƶ�;����ʱ�����ƻ�������Χ��ʽ
            if (it_right == it_left)
                return 1;
            else{
                flagRunning =it_right - it_left +1;
                sum =sum - *it_left++;
            }
        }
        else{//��ǰ��ֵС��target,���������ҵ����������ƶ�
            if (++it_right == nums.end()) break;
            sum += *it_right;
        }
        if (flagCurrent == 0 || flagRunning < flagCurrent)
            flagCurrent = flagRunning;
    }
    return flagCurrent;
}


