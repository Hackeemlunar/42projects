/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:21:55 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/01 22:10:19 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void my_mlx_pixel_put(t_window *window, int x, int y, int color)
{
	char *dst;
	dst = window->addr + (y * window->line_len) +
		  (x * (window->bits_ppx / 8));
	*(unsigned int *)dst = color;
}

void destroy_window(t_window *window)
{
	mlx_destroy_image(window->mlx, window->img);
	mlx_destroy_window(window->mlx, window->win);
	free(window->mlx);
}

void fill_background(t_window *window, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < window->height)
	{
		x = 0;
		while (x < window->width)
		{
			my_mlx_pixel_put(window, x, y, color);
			x++;
		}
		y++;
	}
}

int get_color(int iter, int max_iter, t_window *window)
{
	double t;
	int r;
	int g;
	int b;

	t = (double)iter / max_iter + window->color_sft;
	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return (r << 16 | g << 8 | b);
}
