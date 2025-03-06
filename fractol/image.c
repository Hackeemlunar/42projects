/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:21:55 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/04 17:15:41 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void render_mandelbrot(t_window *window)
{
	int x, y, iter;
	double z_re, z_im, c_re, c_im, tmp;
	double zoom_factor_x = 1.5 / (0.5 * window->zoom * window->width);
	double zoom_factor_y = 1.0 / (0.5 * window->zoom * window->height);
	double center_x = window->width / 2.0;
	double center_y = window->height / 2.0;

	y = 0;
	while (y < window->height)
	{
		x = 0;
		while (x < window->width)
		{
			// Map screen coordinates to fractal space
			c_re = zoom_factor_x * (x - center_x) + window->offset_x;
			c_im = zoom_factor_y * (y - center_y) + window->offset_y;
			z_re = 0;
			z_im = 0;

			// Mandelbrot iteration
			iter = 0;
			while (z_re * z_re + z_im * z_im <= 4 && iter < window->max_iter)
			{
				tmp = z_re;
				z_re = z_re * z_re - z_im * z_im + c_re;
				z_im = 2 * tmp * z_im + c_im;
				iter++;
			}
			// Psychedelic color based on iteration count
			int color = get_color(iter, window->max_iter, window);
			// Draw the pixel
			my_mlx_pixel_put(window, x, y, color);
			x++;
		}
		y++;
	}
}

static void render_julia(t_window *window) {
    int x, y, iter;
    double z_re, z_im, tmp;
    double zoom_factor_x = 1.5 / (0.5 * window->zoom * window->width);
    double zoom_factor_y = 1.0 / (0.5 * window->zoom * window->height);
    double center_x = window->width / 2.0;
    double center_y = window->height / 2.0;

    y = 0;
    while (y < window->height) {
        x = 0;
        while (x < window->width) {
            // Map screen coordinates to fractal space
            z_re = zoom_factor_x * (x - center_x) + window->offset_x;
            z_im = zoom_factor_y * (y - center_y) + window->offset_y;

            // Julia iteration
            iter = 0;
            while (z_re * z_re + z_im * z_im <= 4 && iter < window->max_iter) {
                tmp = z_re;
                z_re = z_re * z_re - z_im * z_im + window->julia_re;
                z_im = 2 * tmp * z_im + window->julia_im;
                iter++;
            }
			int color = get_color(iter, window->max_iter, window);
            // Draw the pixel
            my_mlx_pixel_put(window, x, y, color);
            x++;
        }
        y++;
    }
}

void draw_fractal(t_window *window)
{
	// fill_background(window, window->bg_color);
	// update_color_shift(window);
	if (window->type == MANDELBROT)
		render_mandelbrot(window);
	else if (window->type == JULIA)
		render_julia(window);
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
}
