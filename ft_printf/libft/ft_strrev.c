/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:35:24 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/14 19:08:30 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrev(char *s)
{
	int		len;
	int		i;
	char	temp;

	i = -1;
	len = ft_strlen(s);
	while (++i < --len)
	{
		temp = s[i];
		s[i] = s[len];
		s[len] = temp;
	}
}
