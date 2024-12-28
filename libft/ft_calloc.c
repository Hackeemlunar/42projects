/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:06:41 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/27 22:42:45 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	total_bytes;

	total_bytes = size * count;
	if (size != 0 && total_bytes / size != count)
		return (NULL);
	mem = malloc(total_bytes);
	if (!mem)
		return (NULL);
	return (ft_memset(mem, 0, total_bytes));
}

// int main(void)
// {
//     int i = 0;
//     char *numbers = (char *)ft_calloc(10, 4);
//     while(i < 100000)
//     {
//         printf("I %d: %d\n", i, numbers[i]);
//         i++;
//     }
//     return 0;
// }
