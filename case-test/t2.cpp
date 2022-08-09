//
// Author info:
// Created by Hao Liang on 2022/7/6.
//
#include <iostream>
#include <string>

using namespace std;

/*class String{
    string _string;
};*/
void printArray(int array[][3], int row, int col){
    for (int _row = 0; _row < row; ++_row) {
        for (int _col = 0; _col < col; ++_col) {
            static int count = 0;
            cout << *(*(array + _row) + _col);
//            printf("%i  ", *(array + _row) + _col);
//            cout << *(array + count);
            ++ count;
        }
    }
}

void printArray2(int *array, int row, int col){
    for (int _row = 0; _row < row; ++_row) {
        for (int _col = 0; _col < col; ++_col) {
            static int count = 0;
            cout << *(array + count);
//            printf("%i  ", *(array + _row) + _col);
//            cout << *(array + count);
            ++ count;
        }
    }
}

void printArray3(int **array, int row, int col){
    for (int _row = 0; _row < row; ++_row) {
        for (int _col = 0; _col < col; ++_col) {
            static int count = 0;
            cout << *(array + count);
//            printf("%i  ", *(array + _row) + _col);
//            cout << *(array + count);
            ++ count;
        }
    }
}
int main(){
    int pInt[3][3] = {1, 2, 3, 4, 5, 6,7, 8, 9};
    printArray2(*pInt, 3, 3);
    printArray(pInt, 3, 3);
    return 1;
}