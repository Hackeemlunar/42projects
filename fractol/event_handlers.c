/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:21:55 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/04 17:24:08 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int key_handler_mac(int keycode, t_window *window)
{
	if (keycode == 53) // 65307 (Escape)
		destroy_window(window);
	else if (keycode == 126) // 65362 (Up Arrow)
		window->offset_y += 0.1 / window->zoom;
	else if (keycode == 125) // 65364 (Down Arrow)
		window->offset_y -= 0.1 / window->zoom;
	else if (keycode == 123) // 65361 (Left Arrow)
		window->offset_x += 0.1 / window->zoom;
	else if (keycode == 124) // 65363 (Right Arrow)
		window->offset_x -= 0.1 / window->zoom;
	else if (keycode == 24) // 61 (Plus/Equals)
		window->max_iter += 10;
	else if (keycode == 27) // 45 (Minus/Hyphen)
		window->max_iter -= 10;
	else if (keycode == 15) // 114 ('r')
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
	if (button == 1)
		window->color_sft;
	else if (button == 4)
	{
		
	}
	else if (button == 5)
	{
		window->zoom /= 1.1;
		window->offset_x -= (x - window->width / 2) * 0.01 / window->zoom;
		window->offset_y -= (y - window->height / 2) * 0.01 / window->zoom;
	}
	draw_fractal(window);
	return (0);
}

int expose_handler(t_window *window)
{
	draw_fractal(window);
	return (0);
}

void event_handler(t_window *window)
{
	mlx_key_hook(window->win, key_handler_mac, window);
	mlx_mouse_hook(window->win, mouse_handler, window);
	mlx_expose_hook(window->win, expose_handler, window);
	mlx_hook(window->win, 17, 0, destroy_window, window);
}
