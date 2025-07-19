int check_rows(int *oard[4][4], int row, int *left_clues, int *right_clues);
int check_columns(int board[4][4], int col, int *top_clue, int *bottom_clues);
int check_value(int board[4][4], int i, int j, int val);
int ft_solve(int board[4][4], int pos, int clues[4][4]);
void ft_make_board(int clues[4][4]);