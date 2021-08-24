#include "include/game.h"
#include <stdio.h>

int main(int argc, char const *argv[]){
    int row, col;
    int temp = 0;

    printf("Insira o numero de linhas e colunas:\n");
    scanf("%d %d", &row, &col);
    printf("\n");

    int** board = create_board(row, col);

    for (int i=0; i<row; i++){
        for (int j=0; j<col; j++){
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }

    for (; ; ){
        game_step(board, row, col);

        printf("\n");
        for (int i=0; i<row; i++){
            for (int j=0; j<col; j++){
                printf("%d ", board[i][j]);
                temp += board[i][j];
            }
            printf("\n");
        }

        if (temp == 0) break;
        else temp = 0;
    }

    clear_board_memory(board, row); 
    return 0;
}
