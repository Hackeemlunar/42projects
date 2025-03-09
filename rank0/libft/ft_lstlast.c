/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:08:52 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/28 17:04:01 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	last = lst;
	if (last == NULL)
		return (NULL);
	while (last->next != NULL)
	{
		last = last->next;
	}
	return (last);
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
//     t_list *temp2 = ft_lstlast(a);
//     while (tmp != NULL)
//     {
//         printf("Data is: %s\n", tmp->content);
//         tmp = tmp->next;
//     }
//     printf("Last item is: %s\n", temp2->content);
//     return 0;
// }
