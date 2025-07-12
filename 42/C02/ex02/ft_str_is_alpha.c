#include <stdio.h>

int ft_str_is_alpha(char *str)
{
    while (*str)
    {
        *str++;
        printf("%d", *str -'0');
        if (*str -'0' < '0' || *str -'0' > || (*str -'0' > 57 && *str -'0' < 65) || (*str -'0' > 90 && *str -'0' < 97))
        {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    printf("%d", ft_str_is_alpha("abb444jvh10404bb"));
    return (0);
}