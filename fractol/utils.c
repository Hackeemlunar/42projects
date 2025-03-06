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

// HSV to RGB conversion
static int hsv_to_rgb(double h, double s, double v) {
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

int get_color(int iter, int max_iter, t_window *window)
{
    if (iter == max_iter)
	        return 0x000000FF;
    double hue = fmod(((double)iter / max_iter + window->color_sft), 1.0);
    return hsv_to_rgb(hue, 1.0, 1.0);
}
