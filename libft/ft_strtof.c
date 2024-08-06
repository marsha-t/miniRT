#include "libft.h"

float ft_strtof(const char *str)
{
    float   result;
    float   fraction;
    int     sign;

    result = 0.0;
    fraction = 1.0;
    sign = 1;
    while (ft_isspace((unsigned char)*str))
        str++;
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    else if (*str == '+')
        str++;
    while (ft_isdigit((unsigned char)*str))
    {
        result = result * 10.0f + (*str - '0');
        str++;
    }
    if (*str == '.')
    {
        str++;
        while(ft_isdigit((unsigned char)*str))
        {
            fraction /= 10.0f;
            result += (*str - '0') * fraction;
            str++;
        }
    }
    result *= sign;
    return (result);
}