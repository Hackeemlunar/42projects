/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:17:22 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/28 17:00:56 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = *lst;
	if (last == NULL)
	{
		last = new;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
}

// int main(void)
// {
//     t_list *e = NULL;
//     t_list *a = ft_lstnew("Hackeem");
//     t_list *b = ft_lstnew("By");
//     t_list *c = ft_lstnew("World!");
//     t_list *d = ft_lstnew("Hello");
//     ft_lstadd_back(&e, a);
//     ft_lstadd_back(&a, b);
//     ft_lstadd_back(&a, c);
//     ft_lstadd_back(&a, d);
//     t_list *tmp = a;
//     while (tmp != NULL)
//     {
//         printf("Data is: %s\n", tmp->content);
//         tmp = tmp->next;
//     }
//     return 0;
// }
