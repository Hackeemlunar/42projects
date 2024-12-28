/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:58:59 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/28 17:12:45 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*first;
	int		size;

	first = lst;
	size = 0;
	while (first != NULL)
	{
		size++;
		first = first->next;
	}
	return (size);
}

// int main(void)
// {
//     t_list *e = NULL;
//     t_list *a = ft_lstnew("Hackeem");
//     t_list *b = ft_lstnew("By");
//     t_list *c = ft_lstnew("World!");
//     t_list *d = ft_lstnew("Hello");
//     t_list *f = ft_lstnew("Hellobbb");
//     ft_lstadd_back(&e, a);
//     ft_lstadd_back(&a, b);
//     ft_lstadd_back(&a, c);
//     ft_lstadd_back(&a, d);
//     ft_lstadd_back(&a, f);
//     t_list *tmp = a;
//     while (tmp != NULL)
//     {
//         printf("Data is: %s\n", tmp->content);
//         tmp = tmp->next;
//     }
//     printf("Len is: %d\n", ft_lstsize(a));
//     return 0;
// }
