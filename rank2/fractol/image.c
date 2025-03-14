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
    int x, y;
    int iter;
    int color;
    double z_re, z_im, old_re;

    y = 0;
    while (y < window->height)
    {
        x = 0;
        while (x < window->width)
        {
            z_re = 1.5 * (x - window->width / 2) / (0.5 * window->zoom * window->width) + window->offset_x;
            z_im = (y - window->height / 2) / (0.5 * window->zoom * window->height) + window->offset_y;
            iter = 0;
            while ((z_re * z_re + z_im * z_im < 4) && (iter < window->max_iter))
            {
                old_re = z_re;
                z_re = z_re * z_re - z_im * z_im + window->fractol_re;
                z_im = 2 * old_re * z_im + window->fractol_im;
                iter++;
            }
            color = get_color(iter, window);
            my_mlx_pixel_put(window, x, y, color);
            x++;
        }
        y++;
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
