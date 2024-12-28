/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:05:57 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/22 18:17:52 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

// int main(void)
// {
//     printf("ft_isalpha: %d\n", ft_isalpha('K'));
//     printf("   isalpha: %d\n", isalpha('K'));
//     return 0;
// }
