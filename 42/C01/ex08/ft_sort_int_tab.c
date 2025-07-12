#include <stdio.h>

void ft_sort_int_tab(int *tab, int size)
{
	int i, temp;
	int sorted;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (i < size)
		{
			if (tab[i] > tab[i + 1])
			{
				temp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = temp;
				sorted = 0;
			}
			i++;
		}
	}
}


int main(){
    int tab[5] = {14, 1, 21, 12, 56};
    ft_sort_int_tab(tab, 5);
    for(int i = 0; i < 5; i++){
        printf("%d, ", tab[i]);
    }

    return 0;
}