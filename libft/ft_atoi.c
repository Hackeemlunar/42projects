/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:00:52 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/19 19:39:22 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\f' || c == '\r'
		|| c == '\v' || c == '\t')
		return (1);
	return (0);
}

int ft_atoi(const char *str)
{
    int res;
    int sign;
    int counter;

    res = 0;
    sign = 1;
    counter = 0;
    while (ft_isspace(str[counter]))
        counter++;
    if (str[counter] == '-')
    {
        sign *= -1;
        counter++;
    }
    while(str[counter] <= '9' && str[counter] >= '0')
    {
        res = (res * 10) + (str[counter] - '0');
        counter++;
    }
    return sign * res;
}

// int main(int argc, char **argv)
// {
//     argc += 0;
//     printf("FT_atoi: %d\n", ft_atoi(argv[1]));
//     printf("   Atoi: %d\n", atoi(argv[1]));
// }
