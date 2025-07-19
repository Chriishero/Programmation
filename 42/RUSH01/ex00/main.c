#include "atoi_split.h" 
#include "skyscrapers.h"

int main(int argc, char *argv[])
{
    int *clues;
    int clues_sorted[4][4];
    int i;
    int j;

    clues = ft_atoi_split(argv[1]);
    i = 0;
    j = 0;
    while (i < 4)
    {
        while (j < 16)
        {
            clues_sorted[i][j % 4] = clues[j];
            j++;
        }
        i++;
    }
    if (argc == 2)
        ft_make_board(clues_sorted);
    return (0);
}