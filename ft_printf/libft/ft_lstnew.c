/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:35:25 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/28 17:11:45 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*linked_list;

	linked_list = (t_list *) malloc(sizeof(t_list));
	if (!linked_list)
		return (NULL);
	linked_list->content = content;
	linked_list->next = NULL;
	return (linked_list);
}

// int main(void)
// {
//     t_list *a = ft_lstnew("Hello");
//     printf("Data is: %s\n", a->content);
//     return 0;
// }
