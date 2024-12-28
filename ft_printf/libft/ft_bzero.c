/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:06:26 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/27 22:25:52 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
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
