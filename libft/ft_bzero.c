/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:06:26 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/20 21:06:37 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_bzero(void *s, size_t n)
{
    char    *c;
    size_t  i;
    size_t  len;

    i = 0;
    c = (char *)s;
    len = ft_strlen(c);
    while (n > 0 && i < n && i < len)
    {
        c[i] = '\0';
        i++;
    }
}

// int main(void)
// {
//     char res[14] = "hello world";
//     char res1[14] = "hello world";
//     ft_bzero(res+10, 20);
//     // bzero(res1+10, 10);
//     printf("  Mine: %s\n", res);
//     printf("System: %s\n", res1);
//     return 0;
// }
