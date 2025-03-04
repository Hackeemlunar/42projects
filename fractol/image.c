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

#include "fractol.h"

void render_mandelbrot(t_window *window)
{
    int x, y;
    int iter;
    double pr, pi; // Real and imaginary parts of the complex number
    double new_re, new_im, old_re, old_im;
    int color;

    y = 0;
    while (y < window->height)
    {
        x = 0;
        while (x < window->width)
        {
            pr = 1.5 * (x - window->width / 2) / (0.5 * window->zoom * window->width) + window->offset_x;
            pi = (y - window->height / 2) / (0.5 * window->zoom * window->height) + window->offset_y;
            new_re = new_im = old_re = old_im = 0;
            iter = 0;
            while (iter < window->max_iter)
            {
                old_re = new_re;
                old_im = new_im;
                new_re = old_re * old_re - old_im * old_im + pr;
                new_im = 2 * old_re * old_im + pi;
                if ((new_re * new_re + new_im * new_im) > 4)
                    break;
                iter++;
            }
            color = get_color(iter, window->max_iter, window);
            my_mlx_pixel_put(window, x, y, color);
            x++;
        }
        y++;
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
			new_x = new_x * new_x - new_y * new_y + window->julia_re;
			new_y = 2 * old_x * new_y + window->julia_im;
			iter++;
		}
		color = get_color(iter, window->max_iter, window);
		my_mlx_pixel_put(window, window->offset_x + iter, window->offset_y, color);
	}
}

void draw_fractal(t_window *window)
{
	// fill_background(window, window->bg_color);
	update_color_shift(window);
	if (window->type == MANDELBROT)
		render_mandelbrot(window);
	else if (window->type == JULIA)
		render_julia(window);
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
}
