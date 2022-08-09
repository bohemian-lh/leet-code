//
// Created by Administrator on 2022/6/15.
//
#include "./M.h"

/**
 * 题目：
 * 数对 (a,b) 由整数 a 和 b 组成，其数对距离定义为 a 和 b 的绝对差值。
 * 给你一个整数数组 nums 和一个整数 k ，数对由 nums[i] 和 nums[j] 组成且满足 0 <= i < j < nums.length 。
 * 返回所有数对距离中 第 k 小的数对距离。
*/
/**
 * @解题要点 1、[i,j]的距离和[j,i]的距离是一样的。
 * @解题要点 2、对于有序数列的任一子列{[ai],...... [aj]},其距离共有(j - i -1)个，且该子列的距离都小于（aj - ai）。
 * */
/**
 * @brief smallestDistancePair(vector<int>, int) 找到传入int向量中第k小的距离的值
 * @param nums 无序的int向量
 * @param k 距离第k小
 *
 * @return 返回距离第k小的距离的值
 * */
int Solution_719::smallestDistancePair(vector<int> &nums, int k) {

    sort(nums.begin(), nums.end());    ///对于绝对值距离而言，abs(i,j)和abs（j,i）并无区别，故此，可将数组nums先排序
    vector<int>::iterator it_left, it_right;    ///滑动窗口的左右边界
    it_left = nums.begin();
    it_right = --nums.end();
    int first, last;    ///二分法的左右边界
    first = *nums.begin();
    last = *--nums.end();
    int midDistance = (first + last) / 2;///假定的第k小的距离为midDistance
    int posMid = 0;///当前距离midDistance 的位置
    /**
     * 进入循环前还应判定K是否合规
     */
    while (posMid != k) {

        }
    return midDistance;
}
/**
 * @brief 返回以it_left为首的比midDistance小的距离的总对数
 * */
int Solution_719::findPos(vector<int> &nums, int midDistance){
    int pos = 0;

}
