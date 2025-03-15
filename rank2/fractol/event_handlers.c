/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:38:08 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/15 17:37:41 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_handler_mac(int keycode, t_window *window)
{
	if (keycode == 53)
	{
		destroy_window(window);
		exit(0);
	}
	else if (keycode == 126)
		window->ofs_y += 0.1 / window->zoom;
	else if (keycode == 125)
		window->ofs_y -= 0.1 / window->zoom;
	else if (keycode == 123)
		window->ofs_x += 0.1 / window->zoom;
	else if (keycode == 124)
		window->ofs_x -= 0.1 / window->zoom;
	else if (keycode == 24)
		window->max_iter += 10;
	else if (keycode == 27)
		window->max_iter -= 10;
	else if (keycode == 15)
	{
		window->zoom = 1;
		window->ofs_x = 0;
		window->ofs_y = 0;
	}
	draw_fractal(window);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_window *win)
{
	double	zoom_factor;
	double	m_re;
	double	m_im;
	int		zoom;

	zoom_factor = 1.1;
	zoom = win->zoom;
	m_re = 1.5 * (x - win->width / 2) / (0.5 * zoom * win->width) + win->ofs_x;
	m_im = (y - win->height / 2) / (0.5 * zoom * win->height) + win->ofs_y;
	if (button == 1)
		win->color_sft += 10;
	else if (button == 4)
	{
		zoom *= zoom_factor;
		win->ofs_x = m_re - (x - win->width / 2) / (0.5 * zoom * win->width);
		win->ofs_y = m_im - (y - win->height / 2) / (0.5 * zoom * win->height);
		win->max_iter = (int)(50 + log2(zoom) * 10);
	}
	else if (button == 5)
	{
		zoom /= zoom_factor;
		win->ofs_x = m_re - (x - win->width / 2) / (0.5 * zoom * win->width);
		win->ofs_y = m_im - (y - win->height / 2) / (0.5 * zoom * win->height);
	}
	return (win->zoom = zoom, draw_fractal(win), 0);
}

int	expose_handler(t_window *window)
{
	draw_fractal(window);
	return (0);
}

void	event_handler(t_window *window)
{
	mlx_hook(window->win, 2, 1L << 0, key_handler_mac, window);
	mlx_hook(window->win, 4, 1L << 2, mouse_handler, window);
	mlx_hook(window->win, 12, 1L << 15, expose_handler, window);
	mlx_hook(window->win, 17, 1L << 17, destroy_window, window);
}
