/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:39:24 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/10 16:23:15 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	pfm_iter(t_window *win, double r_i[2], double no_ri[4], int *iter)
{
	while (((no_ri[0] * no_ri[0] + no_ri[1] * no_ri[1]) < 4)
			&& *iter < win->max_iter)
	{
		no_ri[2] = no_ri[0];
		no_ri[3] = no_ri[1];
		no_ri[0] = no_ri[2] * no_ri[2] - no_ri[3] * no_ri[3] + r_i[0];
		no_ri[1] = 2 * no_ri[2] * no_ri[3] + r_i[1];
		(*iter)++;
	}
}

void render_mandelbrot(t_window *window)
{
	int		x_y[2];
	int		iter;
	double	r_i[2];
	double	no_ri[4]; // new re, new im, old re, old im
	int		color;

	x_y[1] = 0;
	while (x_y[1] < window->height)
	{
		x_y[0] = 0;
		while (x_y[0] < window->width)
		{
			r_i[0] = 1.5 * (x_y[0] - window->width / 2) / (0.5 * window->zoom * window->width) + window->offset_x;
			r_i[1] = (x_y[1] - window->height / 2) / (0.5 * window->zoom * window->height) + window->offset_y;
			no_ri[0] = no_ri[1] = no_ri[2] = no_ri[3] = 0;
			iter = 0;
			pfm_iter(window, r_i, no_ri, &iter);
			color = get_color(iter, window);
			my_mlx_pixel_put(window, x_y[0], x_y[1], color);
			x_y[0]++;
		}
		x_y[1]++;
	}
}

void render_julia(t_window *window)
{
	double new_x;
	double new_y;
	double old_x;
	int iter;
	int color;

	iter = 0;
	while (iter < window->max_iter && (window->offset_x + iter) < window->width)
	{
		new_x = window->offset_x;
		new_y = window->offset_y;
		while (new_x * new_x + new_y * new_y < 4)
		{
			old_x = new_x;
			new_x = new_x * new_x - new_y * new_y + window->fractol_re;
			new_y = 2 * old_x * new_y + window->fractol_im;
			iter++;
		}
		color = get_color(iter, window);
		my_mlx_pixel_put(window, window->offset_x + iter, window->offset_y, color);
	}
}

void draw_fractal(t_window *window)
{
	if (window->type == MANDELBROT)
		render_mandelbrot(window);
	else if (window->type == JULIA)
		render_julia(window);
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
}
