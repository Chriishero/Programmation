char *ft_strcpy(char *dest, char *src)
{
    while (*src || *dest)
    {
        *dest = *src;
        *dest++;
        *src++;
    }
    return dest;
}