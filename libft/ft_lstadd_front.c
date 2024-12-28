/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:27:11 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/28 17:12:56 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (*lst == NULL)
		*lst = new;
	else
		new->next = *lst;
}

// int main(void)
// {
//     t_list *e = NULL;
//     t_list *a = ft_lstnew("Hackeem");
//     t_list *b = ft_lstnew("By");
//     t_list *c = ft_lstnew("World!");
//     t_list *d = ft_lstnew("Hello");
//     ft_lstadd_front(&e, a);
//     ft_lstadd_front(&a, b);
//     ft_lstadd_front(&b, c);
//     ft_lstadd_front(&c, d);
//     t_list *tmp = d;
//     while (tmp != NULL)
//     {
//         printf("Data is: %s\n", tmp->content);
//         tmp = tmp->next;
//     }
//     return 0;
// }
