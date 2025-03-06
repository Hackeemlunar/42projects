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

int key_handler_linux(int keycode, t_window *window)
{
	if (keycode == 65307) // Escape
		destroy_window(window);
	else if (keycode == 65362) // Up Arrow
		window->offset_y += 0.1 / window->zoom;
	else if (keycode == 65364) // Down Arrow
		window->offset_y -= 0.1 / window->zoom;
	else if (keycode == 65361) // Left Arrow
		window->offset_x += 0.1 / window->zoom;
	else if (keycode == 65363) // Right Arrow
		window->offset_x -= 0.1 / window->zoom;
	else if (keycode == 61) // Plus/Equals
		window->max_iter += 10;
	else if (keycode == 45) // Minus/Hyphen
		window->max_iter -= 10;

	else if (keycode == 114) // 'r'
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
    if (button == 1) // Scroll up (zoom in)
    {
        double zoom_factor = 1.1;

        // Map mouse position to fractal space
        double mouse_re = 1.5 * (x - window->width / 2) / (0.5 * window->zoom * window->width) + window->offset_x;
        double mouse_im = (y - window->height / 2) / (0.5 * window->zoom * window->height) + window->offset_y;

        // Update zoom level
        window->zoom *= zoom_factor;

        // Adjust offsets to zoom toward the mouse position
        window->offset_x = mouse_re - (x - window->width / 2) / (0.5 * window->zoom * window->width);
        window->offset_y = mouse_im - (y - window->height / 2) / (0.5 * window->zoom * window->height);
    }
    else if (button == 2) // Scroll down (zoom out)
    {
        double zoom_factor = 1.1;

        // Map mouse position to fractal space
        double mouse_re = 1.5 * (x - window->width / 2) / (0.5 * window->zoom * window->width) + window->offset_x;
        double mouse_im = (y - window->height / 2) / (0.5 * window->zoom * window->height) + window->offset_y;

        // Update zoom level
        window->zoom /= zoom_factor;

        // Adjust offsets to zoom away from the mouse position
        window->offset_x = mouse_re - (x - window->width / 2) / (0.5 * window->zoom * window->width);
        window->offset_y = mouse_im - (y - window->height / 2) / (0.5 * window->zoom * window->height);
    }

    // Redraw the fractal
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
	mlx_key_hook(window->win, key_handler_linux, window);
	mlx_mouse_hook(window->win, mouse_handler, window);
	mlx_expose_hook(window->win, expose_handler, window);
	mlx_hook(window->win, 17, 0, destroy_window, window);
}
