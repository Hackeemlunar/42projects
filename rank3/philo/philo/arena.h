/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:32:15 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/20 20:30:50 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include <stdlib.h>

typedef struct s_arena
{
	size_t	size;
	size_t	used;
	char	*buffer;
}			t_arena;

// ************** Arena Functions **************
void	arena_destroy(t_arena *arena);
void	*arena_alloc(t_arena *arena, size_t size);
void	arena_reset(t_arena *arena);
t_arena	*arena_create(size_t size);
#endif
