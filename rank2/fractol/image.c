/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:39:24 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/15 22:27:55 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	pfm_iter(t_window *win, double r_i[2], double no_ri[4], int *iter)
{
	no_ri[0] = 0;
	no_ri[1] = 0;
	no_ri[2] = 0;
	no_ri[3] = 0;
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

void	render_mandelbrot(t_window *window)
{
	int		x_y[2];
	int		iter;
	double	r_i[2];
	double	no_ri[4];
	int		color;

	x_y[1] = 0;
	while (x_y[1] < window->height)
	{
		x_y[0] = 0;
		while (x_y[0] < window->width)
		{
			r_i[0] = 1.5 * (x_y[0] - window->width / 2)
				/ (0.5 * window->zoom * window->width) + window->ofs_x;
			r_i[1] = (x_y[1] - window->height / 2)
				/ (0.5 * window->zoom * window->height) + window->ofs_y;
			iter = 0;
			pfm_iter(window, r_i, no_ri, &iter);
			color = get_color(iter, window);
			my_mlx_pixel_put(window, x_y[0], x_y[1], color);
			x_y[0]++;
		}
		x_y[1]++;
	}
}

static void	julia_iter(t_window *win, int x_y[2], double zo_ri[3], int *iter)
{
	zo_ri[0] = 1.5 * (x_y[0] - win->width / 2)
		/ (0.5 * win->zoom * win->width) + win->ofs_x;
	zo_ri[1] = (x_y[1] - win->height / 2)
		/ (0.5 * win->zoom * win->height) + win->ofs_y;
	while ((zo_ri[0] * zo_ri[0] + zo_ri[1] * zo_ri[1] < 4)
		&& (*iter < win->max_iter))
	{
		zo_ri[2] = zo_ri[0];
		zo_ri[0] = zo_ri[0] * zo_ri[0] - zo_ri[1] * zo_ri[1]
			+ win->fractol_re;
		zo_ri[1] = 2 * zo_ri[2] * zo_ri[1] + win->fractol_im;
		(*iter)++;
	}
}

void	render_julia(t_window *window)
{
	int		x_y[2];
	int		iter;
	int		color;
	double	zo_ri[3];

	x_y[1] = 0;
	while (x_y[1] < window->height)
	{
		x_y[0] = 0;
		while (x_y[0] < window->width)
		{
			iter = 0;
			julia_iter(window, x_y, zo_ri, &iter);
			color = get_color(iter, window);
			my_mlx_pixel_put(window, x_y[0], x_y[1], color);
			x_y[0]++;
		}
		x_y[1]++;
	}
}

void	draw_fractal(t_window *window)
{
	if (window->type == MANDELBROT)
		render_mandelbrot(window);
	else if (window->type == JULIA)
		render_julia(window);
	else if (window->type == BURNING_SHIP)
		render_burning_ship(window);
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
}
