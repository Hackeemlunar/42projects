/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:21:55 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/15 17:25:11 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_window *window, int x, int y, int color)
{
	char	*dst;

	dst = window->addr + (y * window->line_len) + (x * (window->bits_ppx / 8));
	*(unsigned int *)dst = color;
}

int	destroy_window(t_window *window)
{
	mlx_destroy_image(window->mlx, window->img);
	mlx_destroy_window(window->mlx, window->win);
	free(window->mlx);
	exit(0);
}

int	get_color(int iter, t_window *window)
{
	int		r;
	int		g;
	int		b;
	double	frequency;

	frequency = 0.1;
	r = (int)(sin(frequency * iter + window->color_sft * 0.2) * 127 + 128);
	g = (int)(sin(frequency * iter + window->color_sft * 0.3 + 2) * 127 + 128);
	b = (int)(sin(frequency * iter + window->color_sft * 0.5 + 4) * 127 + 128);
	return (r << 16 | g << 8 | b);
}
