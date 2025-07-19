#include "putchar.h"
#include <stdio.h>

int check_rows(int board[4][4], int row, int *left_clues, int *right_clues)
{
    int i;
    int max;
    int count;

    i = 0;
    max = 0;
    count = 0;
    while (i < 4)
    {
        if (board[row][i] > max)
        {
            max = board[row][i];
            count++;
        }
        i++;
    }
    if (count > left_clues[row])
        return (0);
    max = 0;
    count = 0;
    i--;
    while (i >= 0)
    {
        if (board[row][i] > max)
        {
            max = board[row][i];
            count++;
        }
        i--;
    }
    if (count != right_clues[row])
        return (0);
    return (1);
}

int check_columns(int board[4][4], int col, int *top_clues, int *bottom_clues)
{
    int i;
    int max;
    int count;

    i = 0;
    max = 0;
    count = 0;
    while (i < 4)
    {
        if (board[i][col] > max)
        {
            max = board[i][col];
            count++;
        }
        i++;
    }
    if (count != top_clues[col])
        return (0);
    max = 0;
    count = 0;
    i--;
    while (i >= 0)
    {
        if (board[i][col] > max)
        {
            max = board[i][col];
            count++;
        }
        i--;
    }
    if (count > bottom_clues[col])
        return (0);
    return (1);
}

int check_value(int board[4][4], int row, int col, int val)
{
    int i;

    i = 0;
    while (i < 4)
    {
        if ((board[row][i] == val || board[i][col] == val) && val > 0 && val <= 4)
            return (0);
        i++;
    }
    return (1);
}

int ft_solve(int board[4][4], int pos, int clues[4][4])
{
    int val;
    int row;
    int col;

    if (pos == 4 * 4)
        return (1);
    row = pos / 4;
    col = pos % 4;
    val = 1;
    while (val <= 4)
    {
        if (check_value(board, row, col, val))
        {
            board[row][col] = val;
            if (col == 4 - 1)
            {
                if (!check_rows(board, row, clues[2], clues[3]))
                    return (0);
            }
            if (row == 4 - 1)
            {
                if (!check_columns(board, col, clues[0], clues[1]))
                    return (0);
            }
            if (ft_solve(board, pos + 1, clues))
            {
                return (1);
            }
            board[row][col] = 0;
        }
        val++;
    }
    return (0);
}

void ft_make_board(int clues[4][4])
{
    int i;
    int j;
    int board[4][4];
    
    i = 0;
    j = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            board[i][j] = 0;
            j++;
        }
        i++;
    }
    ft_solve(board, 0, clues);
    i = 0;
    j = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            ft_putchar(board[i][j] + '0');
            j++;
        }
        ft_putchar('\n');
        i++;
    }
}