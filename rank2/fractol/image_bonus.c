/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:02:36 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/15 21:38:01 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ship_iter(t_window *win, double r_i[2], double no_ri[4], int *iter)
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
		no_ri[0] = fabs(no_ri[2]) * fabs(no_ri[2])
			- fabs(no_ri[3]) * fabs(no_ri[3]) + r_i[0];
		no_ri[1] = 2 * fabs(no_ri[2]) * fabs(no_ri[3]) + r_i[1];
		(*iter)++;
	}
}

void	render_burning_ship(t_window *window)
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
			ship_iter(window, r_i, no_ri, &iter);
			color = get_color(iter, window);
			my_mlx_pixel_put(window, x_y[0], x_y[1], color);
			x_y[0]++;
		}
		x_y[1]++;
	}
}
