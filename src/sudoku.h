#include <iostream>
#include <cstring>

class Sudoku {
private:
    int grid[9][9]{};

public:
    explicit Sudoku(int (*grid)[9]) {
        memcpy(this->grid, grid, 9 * 9 * sizeof(int));
    }

    bool operator ==(const int (*otherGrid)[9]) {
        for (int i=0; i<9*9; i++) {
            if (grid[i%3][i/3] != otherGrid[i%3][i/3]) {
                return false;
            }
        }
        return true;
    }

    bool operator ==(const Sudoku & other) {
        for (int i=0; i<9*9; i++) {
#ifdef PRINT
            printf("comparing grid(%d, %d)\n", i%9, i/9);
#endif
            if (grid[i%9][i/9] != other.grid[i%9][i/9]) {
                return false;
            }
        }
        return true;
    }

    int get(int i, int j) {
        if (i >= 0 && i < 9 && j >= 0 && j < 9) {
            return grid[i][j];
        }

        return -1;
    }

    int set(int i, int j, int val) {
        if (i >= 0 && i < 9 && j >= 0 && j < 9) {
            return grid[i][j] = val;
        }
        return -1;
    }

    void print() {
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) {
                printf(" [%d] ", get(i, j));
                if (j == 8) {
                    printf("\n");
                }
            }
        }
    }
    //https://www.geeksforgeeks.org/sudoku-backtracking-7/
    //inspired by its dividing up of the 3 checks: rows, columns, box
    bool isEmpty(int grid[9][9], int &row, int &col){//finds empty cells
        for (row = 0; row < 9; row++) {
            for (col = 0; col < 9; col++) {
                if (grid[row][col] == 0) {
                    return true;
                }
            }
        }
        return false;
    }

    bool UsedInRow(int grid[9][9], int row, int val){//taken from source
        for (int col = 0; col < 9; col++) {
            if (grid[row][col] == val) {
                return true;
            }
        }
        return false;
    }

    bool UsedInCol(int grid[9][9], int col, int val){
        for (int row = 0; row < 9; row++) {
            if (grid[row][col] == val) {
                return true;
            }
        }
        return false;
    }

    bool UsedInBox(int grid[9][9], int boxStartRow, int boxStartCol, int val){
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (grid[row + boxStartRow][col + boxStartCol] == val) {
                    return true;
                }
            }
        }
        return false;

    }

    bool legal(int grid[9][9], int row, int col, int val){//groups all the 3 checks
        if(UsedInRow(grid, row, val)){
            return false;
        }

        if(UsedInCol(grid, col, val)){
            return false;
        }

        if(UsedInBox(grid, row - row%3 ,col - col%3, val)){
            return false;
        }
        
        if(!(grid[row][col]==0)){
            return false;
        }
        return true;//not used in row, column, or box and is not 0
    }

    bool _solve(int grid[9][9]) {
        int row, col;

        if (!isEmpty(grid, row, col)) {//when full
            return true;
        }

        for (int val = 0; val < 9; val++){//iterates through all boxes checking for legality
            if (!UsedInRow(grid, row, val+1) &&
                !UsedInCol(grid, col, val+1) &&
                !UsedInBox(grid, row - row % 3 ,col - col % 3, val+1) &&
                grid[row][col] == 0){//checks the legality of the 4 constraints
                grid[row][col] = val+1;//arbitrary assignment

                if (_solve(grid)) {
                    return true;
                }

                //failure, unmake & try again
                //backtrack
                grid[row][col] = 0;
            }
        }
        return false;
    }

    bool solve() {//constraints: numbers 1-9 that dont repeat in row, column, or box.
        // homework
        _solve(grid);
        return true;
    }
};
