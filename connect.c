#include "slist.h"
#include <stdio.h>
#include<stdbool.h>

#define ROWS 6
#define COLS 7

char board[ROWS][COLS];
Move *movesList = NULL;

void initializeBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("|%c", board[i][j]);
        }
        printf("|\n");
    }
    printf("===============\n");
}

int takeTurn(char player) {
    int column;
    printf("%s to play. Pick a column (1-7):", player == 'R' ? "Red" : "Yellow");
    scanf("%d", &column);

    if (column < 1 || column > 7 || board[0][column - 1] != ' ') {
        printf("Invalid move!\n");
        return 0;
    }

    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][column - 1] == ' ') {
            board[i][column - 1] = player;
            insertAtTail(&movesList, player, column);
            return 1;
        }
    }
    return 0;
}

bool checkWin(char board[ROWS][COLS], char player, int lastRow, int lastCol) {

    int count = 0;
    for (int col = 0; col < COLS; col++) {
        count = (board[lastRow][col] == player) ? count + 1 : 0;
        if (count == 4) return true;
    }


    count = 0;
    for (int row = 0; row < ROWS; row++) {
        count = (board[row][lastCol] == player) ? count + 1 : 0;
        if (count == 4) return true;
    }

  
    count = 0;
    int startRow = lastRow + min(ROWS - 1 - lastRow, lastCol);
    int startCol = lastCol - min(ROWS - 1 - lastRow, lastCol);
    while (startRow >= 0 && startCol < COLS) {
        count = (board[startRow][startCol] == player) ? count + 1 : 0;
        if (count == 4) return true;
        startRow--;
        startCol++;
    }


    count = 0;
    startRow = lastRow - min(lastRow, lastCol);
    startCol = lastCol - min(lastRow, lastCol);
    while (startRow < ROWS && startCol < COLS) {
        count = (board[startRow][startCol] == player) ? count + 1 : 0;
        if (count == 4) return true;
        startRow++;
        startCol++;
    }

    return false;
}


void replay() {
    initializeBoard();
    Move *temp = movesList;
    while (temp) {
        takeTurn(temp->player);
        displayBoard();
        temp = temp->next;
    }
}

int main() {
    initializeBoard();
    char currentPlayer = 'R';
    int winFlag = 0;
    
    while (1) {
        displayBoard();
        if (!takeTurn(currentPlayer)) continue;
        
        if (checkWin() == currentPlayer) {
            winFlag = 1;
            break;
        }
        
        currentPlayer = currentPlayer == 'R' ? 'Y' : 'R';
    }
    
    displayBoard();
    printf("You win, %s!\n", currentPlayer == 'R' ? "Red" : "Yellow");
    printf("Good game!\n");

    char option;
    printf("Press 'q' to quit or 'r' to replay or any other key to continue:");
    scanf(" %c", &option);
    if (option == 'r') replay();

    freeList(movesList);
    return 0;
}



