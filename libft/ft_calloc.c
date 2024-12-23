/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:06:41 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/22 21:56:43 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	char	*mem_cpy;
	size_t	i;
	size_t	total_bytes;

	i = 0;
	total_bytes = size * count;
	mem = malloc(total_bytes);
	if (!mem)
		return (NULL);
	mem_cpy = (char *)mem;
	while (i < total_bytes)
	{
		mem_cpy[i] = 0;
		i++;
	}
	return (mem);
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
