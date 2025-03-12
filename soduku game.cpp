#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 9

// Sample Sudoku grid (0 means empty)
int sudoku[SIZE][SIZE] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};

// Function to print the Sudoku grid
void printSudoku() {
    printf("\n   1 2 3   4 5 6   7 8 9\n");
    printf("  -----------------------\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d | ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            if (sudoku[i][j] == 0)
                printf(". ");
            else
                printf("%d ", sudoku[i][j]);
            if ((j + 1) % 3 == 0) printf("| ");
        }
        printf("\n");
        if ((i + 1) % 3 == 0) printf("  -----------------------\n");
    }
}

// Function to check if a number is valid in the given position
int isValid(int row, int col, int num) {
    for (int i = 0; i < SIZE; i++) {
        if (sudoku[row][i] == num || sudoku[i][col] == num)
            return 0;
    }
    
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (sudoku[i + startRow][j + startCol] == num)
                return 0;

    return 1;
}

// Function to provide a hint (suggest a possible number)
void hint() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (sudoku[i][j] == 0) {
                for (int num = 1; num <= SIZE; num++) {
                    if (isValid(i, j, num)) {
                        printf("\nHint: Try placing %d at row %d, column %d.\n", num, i + 1, j + 1);
                        return;
                    }
                }
            }
        }
    }
    printf("\nNo hints available, Sudoku might be solved!\n");
}

// Function to check if the Sudoku is completely filled
int isSudokuComplete() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (sudoku[i][j] == 0)
                return 0;
    return 1;
}

// Function to play the game
void playGame() {
    int row, col, num, choice;

    while (1) {
        printSudoku();
        printf("\nOptions:\n");
        printf("1. Enter a number\n");
        printf("2. Get a hint\n");
        printf("3. Quit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("\nEnter row (1-9): ");
            scanf("%d", &row);
            printf("Enter column (1-9): ");
            scanf("%d", &col);
            printf("Enter number (1-9): ");
            scanf("%d", &num);

            if (row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9) {
                printf("\nInvalid input! Try again.\n");
                continue;
            }

            if (sudoku[row - 1][col - 1] != 0) {
                printf("\nThat cell is already filled! Choose another.\n");
                continue;
            }

            if (!isValid(row - 1, col - 1, num)) {
                printf("\nInvalid move! That number cannot be placed there.\n");
                continue;
            }

            sudoku[row - 1][col - 1] = num;
            printf("\nNumber placed successfully!\n");

            if (isSudokuComplete()) {
                printSudoku();
                printf("\nCongratulations! You have completed the Sudoku!\n");
                break;
            }
        } 
        else if (choice == 2) {
            hint();
        } 
        else if (choice == 3) {
            printf("\nThank you for playing Sudoku! Goodbye.\n");
            break;
        } 
        else {
            printf("\nInvalid choice! Try again.\n");
        }
    }
}

int main() {
    printf("Welcome to Interactive Sudoku!\n");
    playGame();
    return 0;
}
