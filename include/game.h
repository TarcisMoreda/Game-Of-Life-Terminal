int** create_board(int r, int c);
int** create_empty_board(int r, int c);
int check_neighbours(int** board, int r, int c, int pos_x, int pos_y);
int game_step(int** board, int r, int c);
int clear_board_memory(int** board, int r);