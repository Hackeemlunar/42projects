/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:21:55 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/03 20:24:57 by hmensah-         ###   ########.fr       */
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

int destroy_window(t_window *window)
{
	mlx_destroy_image(window->mlx, window->img);
	mlx_destroy_window(window->mlx, window->win);
	free(window->mlx);
	exit(0);
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
    double	hue;

    if (iter == max_iter)
        return (window->bg_color);
    hue = fmod(((double)iter / max_iter + window->color_sft), 1.0);
    return (hsv_to_rgb(hue, 1.0, 1.0));
}

void update_color_shift(t_window *window)
{
    window->color_sft += 0.005;
    if (window->color_sft >= 1.0)
        window->color_sft -= 1.0;
}
