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

int hsv_to_rgb(double h, double s, double v) {
    int i;
    double f, p, q, t, r, g, b;

    if (s == 0) {
        r = g = b = v; // Grayscale
    } else {
        h = fmod(h, 1.0);
        if (h < 0) h += 1.0;
        h *= 6.0;
        i = (int)h;
        f = h - i;
        p = v * (1.0 - s);
        q = v * (1.0 - s * f);
        t = v * (1.0 - s * (1.0 - f));

        switch (i) {
            case 0: r = v; g = t; b = p; break;
            case 1: r = q; g = v; b = p; break;
            case 2: r = p; g = v; b = t; break;
            case 3: r = p; g = q; b = v; break;
            case 4: r = t; g = p; b = v; break;
            default: r = v; g = p; b = q; break;
        }
    }

    return ((int)(r * 255) << 16) | ((int)(g * 255) << 8) | (int)(b * 255);
}

void render_mandelbrot(t_window *window) {
    int x, y, iter;
    double c_re, c_im, z_re, z_im, tmp;
    double zoom_factor_x = 1.5 / (0.5 * window->zoom * window->width);
    double zoom_factor_y = 1.0 / (0.5 * window->zoom * window->height);
    double center_x = window->width / 2.0;
    double center_y = window->height / 2.0;

    // Loop through each pixel
    y = 0;
    while (y < window->height) {
        x = 0;
        while (x < window->width) {
            // Map screen coordinates to fractal space
            c_re = zoom_factor_x * (x - center_x) + window->offset_x;
            c_im = zoom_factor_y * (y - center_y) + window->offset_y;

            // Mandelbrot iteration
            z_re = 0;
            z_im = 0;
            iter = 0;
            while (z_re * z_re + z_im * z_im <= 4 && iter < window->max_iter) {
                tmp = z_re;
                z_re = z_re * z_re - z_im * z_im + c_re;
                z_im = 2 * tmp * z_im + c_im;
                iter++;
            }

            // Psychedelic color based on iteration count and color shift
            double hue = fmod(((double)iter / window->max_iter + window->color_sft), 1.0);
            int color = hsv_to_rgb(hue, 1.0, 1.0); // Full saturation and value

            // Draw the pixel
            my_mlx_pixel_put(window, x, y, color);

            x++;
        }
        y++;
    }
}

void render_julia(t_window *window) {
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

            // Psychedelic color based on iteration count
            double hue = fmod(((double)iter / window->max_iter + window->color_sft), 1.0);
            int color = hsv_to_rgb(hue, 1.0, 1.0); // Full saturation and value

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
	update_color_shift(window);
	if (window->type == MANDELBROT)
		render_mandelbrot(window);
	else if (window->type == JULIA)
		render_julia(window);
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
}
