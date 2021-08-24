#include "../include/game.h"
#include <stdio.h>
#include <stdlib.h>

enum{alive=1, dead=0};

int** create_board(int r, int c){
    int** board = (int**) malloc(sizeof(int*)*r);
    for (int i=0; i<r; i++) board[i] = (int*) malloc(sizeof(int)*c);

    FILE* file = NULL;
    file = fopen("board.txt", "r");
    if (file == NULL) return NULL;

    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
            fscanf (file, "%d", &board[i][j]);
        }
    }

    fclose(file);
    return board;
}

int** create_empty_board(int r, int c){
    int** board = (int**) malloc(sizeof(int*)*r);
    for (int i=0; i<r; i++) board[i] = (int*) malloc(sizeof(int)*c);

    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
            board[i][j] = dead;
        }
    }

    return board;
}

int check_neighbours(int** board, int r, int c, int pos_x, int pos_y){
    int neighbours = 0;
    
    for (int i=-1; i<=1; i++){
        for (int j=-1; j<=1; j++){
            if (i == 0 && j == 0) continue;
            if (pos_x+i == -1 || pos_y+j == -1) continue;
            if (pos_x+i == r || pos_y+j == c) continue;
            if (board[pos_x+i][pos_y+j] == alive) neighbours++;
        }
    }

    return neighbours;
}

int game_step(int** board, int r, int c){
    if (board == NULL) return 0;

    int neighbours;
    int** temp_board = create_empty_board(r, c);
    
    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
            temp_board[i][j] = board[i][j];
        }
    }
    
    for (int i=0; i<r; i++){
        for (int j=0; j<r; j++){
            neighbours = check_neighbours(board, r, c, i, j);

            if (board[i][j] == alive && neighbours < 2) temp_board[i][j] = dead;
            if (board[i][j] == alive && (neighbours == 2 || neighbours == 3)) temp_board[i][j] = alive;
            if (board[i][j] == alive && neighbours > 3) temp_board[i][j] = dead;
            if (board[i][j] == dead && neighbours == 3) temp_board[i][j] = alive;
        }
    }
    
    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
            board[i][j] = temp_board[i][j];
        }
    }
    
    clear_board_memory(temp_board, r);
    return 1;
}

int clear_board_memory(int** board, int r){
    if (board == NULL) return 0;
    
    for (int i=0; i<r; i++) free(board[i]);
    free(board);

    return 1;
}