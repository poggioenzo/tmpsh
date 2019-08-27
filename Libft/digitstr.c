#include "libft.h"

int             digitstr(char *str)
{
        while (*str)
        {
                if (!ft_isdigit(*str++))
                        return (0);
        }
        return (1);
}
