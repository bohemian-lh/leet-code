//
// Created by Administrator on 2022/6/15.
//
#include "./M.h"

/**
 * ��Ŀ��
 * ���� (a,b) ������ a �� b ��ɣ������Ծ��붨��Ϊ a �� b �ľ��Բ�ֵ��
 * ����һ���������� nums ��һ������ k �������� nums[i] �� nums[j] ��������� 0 <= i < j < nums.length ��
 * �����������Ծ����� �� k С�����Ծ��롣
*/
/**
 * @����Ҫ�� 1��[i,j]�ľ����[j,i]�ľ�����һ���ġ�
 * @����Ҫ�� 2�������������е���һ����{[ai],...... [aj]},����빲��(j - i -1)�����Ҹ����еľ��붼С�ڣ�aj - ai����
 * */
/**
 * @brief smallestDistancePair(vector<int>, int) �ҵ�����int�����е�kС�ľ����ֵ
 * @param nums �����int����
 * @param k �����kС
 *
 * @return ���ؾ����kС�ľ����ֵ
 * */
int Solution_719::smallestDistancePair(vector<int> &nums, int k) {

    sort(nums.begin(), nums.end());    ///���ھ���ֵ������ԣ�abs(i,j)��abs��j,i���������𣬹ʴˣ��ɽ�����nums������
    vector<int>::iterator it_left, it_right;    ///�������ڵ����ұ߽�
    it_left = nums.begin();
    it_right = --nums.end();
    int first, last;    ///���ַ������ұ߽�
    first = *nums.begin();
    last = *--nums.end();
    int midDistance = (first + last) / 2;///�ٶ��ĵ�kС�ľ���ΪmidDistance
    int posMid = 0;///��ǰ����midDistance ��λ��
    /**
     * ����ѭ��ǰ��Ӧ�ж�K�Ƿ�Ϲ�
     */
    while (posMid != k) {

        }
    return midDistance;
}
/**
 * @brief ������it_leftΪ�׵ı�midDistanceС�ľ�����ܶ���
 * */
int Solution_719::findPos(vector<int> &nums, int midDistance){
    int pos = 0;

}
