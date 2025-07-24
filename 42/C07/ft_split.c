#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_char_in_str(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (0);
		i++;
	}
	return (1);
}

char	**ft_split(char *str, char *charset)
{
	int	separator;
	int	i;
	int	split;
	char	*s;
	char	**tab;
	
	tab = (char **)malloc(sizeof(char *) * ft_strlen(str) + 1);
	separator = 0;
	split = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_char_in_str(str[i], charset))
		{
			separator = i;
			i = 0;
			split = 1;
			if (s != NULL)
				free(s);
			s = (char *)malloc(sizeof(char) * separator + 1);
		}
		if (i < separator && split)
			s[i] = str[i];
		else if (split)
		{
			*tab++ = s;
			split = 0;
		}	
		i++;
	}
	*tab = NULL;
	return (&tab[0]);
}

#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc > 2)
	{
		char **tab = ft_split(argv[1], argv[2]);
		while (*tab)
			printf("%s\n", *tab++);
	}
	return (0);
}
