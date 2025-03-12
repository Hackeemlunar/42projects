/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:38:08 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/10 20:06:35 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int key_handler(int keycode, t_window *window)
{
	if (keycode == 65307)
	{
		destroy_window(window);
		exit(0);
	}
	else if (keycode == 65362)
		window->offset_y -= 0.1 / window->zoom;
	else if (keycode == 65364)
		window->offset_y += 0.1 / window->zoom;
	else if (keycode == 65361)
		window->offset_x -= 0.1 / window->zoom;
	else if (keycode == 65363)
		window->offset_x += 0.1 / window->zoom;
	else if (keycode == 61)
		window->max_iter += 10;
	else if (keycode == 45)
		window->max_iter -= 10;
	else if (keycode == 65361)
		window->color_sft -= 0.01;
	else if (keycode == 65363)
		window->color_sft += 0.01;
	else if (keycode == 114)
	{
		window->zoom = 1;
		window->offset_x = 0;
		window->offset_y = 0;
	}
	draw_fractal(window);
	return (0);
}

int key_handler_mac(int keycode, t_window *window)
{
	if (keycode == 53) // Escape key
	{
		destroy_window(window);
		exit(0);
	}
	else if (keycode == 126) // Up arrow key
		window->offset_y -= 0.1 / window->zoom;
	else if (keycode == 125) // Down arrow key
		window->offset_y += 0.1 / window->zoom;
	else if (keycode == 123) // Left arrow key
		window->offset_x -= 0.1 / window->zoom;
	else if (keycode == 124) // Right arrow key
		window->offset_x += 0.1 / window->zoom;
	else if (keycode == 24) // Plus key
		window->max_iter += 10;
	else if (keycode == 27) // Minus key
		window->max_iter -= 10;
	else if (keycode == 123) // Left arrow key
		window->color_sft -= 0.01;
	else if (keycode == 124) // Right arrow key
		window->color_sft += 0.01;
	else if (keycode == 15) // 'R' key
	{
		window->zoom = 1;
		window->offset_x = 0;
		window->offset_y = 0;
	}
	draw_fractal(window);
	return (0);
}

int mouse_handler(int button, int x, int y, t_window *window)
{
	double	zoom_factor;
	double	mouse_re;
	double	mouse_im;

	zoom_factor = 1.1;
	mouse_re = 1.5 * (x - window->width / 2) / (0.5 * window->zoom * window->width) + window->offset_x;
	mouse_im = (y - window->height / 2) / (0.5 * window->zoom * window->height) + window->offset_y;
	if (button == 1)
		window->color_sft += 10;
	else if (button == 4)
	{
		window->zoom *= zoom_factor;
		window->offset_x = mouse_re - (x - window->width / 2) / (0.5 * window->zoom * window->width);
		window->offset_y = mouse_im - (y - window->height / 2) / (0.5 * window->zoom * window->height);
		window->max_iter = (int)(50 + log2(window->zoom) * 10);
	}
	else if (button == 5)
	{
		window->zoom /= zoom_factor;
		window->offset_x = mouse_re - (x - window->width / 2) / (0.5 * window->zoom * window->width);
		window->offset_y = mouse_im - (y - window->height / 2) / (0.5 * window->zoom * window->height);
	}
	return (draw_fractal(window), 0);
}

int expose_handler(t_window *window)
{
	draw_fractal(window);
	return (0);
}

void event_handler(t_window *window)
{
	mlx_hook(window->win, 2, 1L << 0, key_handler_mac, window);
	mlx_hook(window->win, 4, 1L << 2, mouse_handler, window);
	mlx_hook(window->win, 12, 1L << 15, expose_handler, window);
}
