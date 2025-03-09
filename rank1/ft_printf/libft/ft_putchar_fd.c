/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:49:29 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/23 18:49:47 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// int main(void)
// {
//     char *a = "Hello World!";
//     int i = 0;
//     while (a[i])
//     {
//         ft_putchar_fd(a[i], 1);
//         i++;
//     }
//     ft_putchar_fd('\n', 1);
//     return 0;
// }
