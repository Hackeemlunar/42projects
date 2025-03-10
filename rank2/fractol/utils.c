/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:21:55 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/10 16:28:11 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_window *window, int x, int y, int color)
{
	char	*dst;

	dst = window->addr + (y * window->line_len) + (x * (window->bits_ppx / 8));
	*(unsigned int *)dst = color;
}

void	destroy_window(t_window *window)
{
	mlx_destroy_image(window->mlx, window->img);
	mlx_destroy_window(window->mlx, window->win);
	free(window->mlx);
}

void	fill_background(t_window *window, int color)
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

int	get_color(int iter, t_window *window)
{
    int		r, g, b;
    double	frequency = 0.1; // Controls psychedelic effect speed

    // Normalize iteration count with a dynamic shift

    // Apply psychedelic shifting based on `color_sft`
    r = (int)(sin(frequency * iter + window->color_sft * 0.2) * 127 + 128);
    g = (int)(sin(frequency * iter + window->color_sft * 0.3 + 2) * 127 + 128);
    b = (int)(sin(frequency * iter + window->color_sft * 0.5 + 4) * 127 + 128);

    return (r << 16 | g << 8 | b);
}
