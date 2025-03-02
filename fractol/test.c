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

void my_mlx_pixel_put(t_img *window, int x, int y, int color)
{
	char *dst;

	dst = window->addr + (y * window->line_length) +
		  (x * (window->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int setup_window(t_img *window, int height, int width)
{
	window->mlx = mlx_init();
	if (!window->mlx)
		return (1);
	window->mlx_win = mlx_new_window(window->mlx, width, height, "Fractol");
	if (!window->mlx_win)
		return (1);
	window->img = mlx_new_image(window->mlx, width, height);
	if (!window->img)
		return (1);
	window->addr = mlx_get_data_addr(window->img, &window->bits_per_pixel,
									 &window->line_length, &window->endian);
	if (!window->addr)
		return (1);
	window->next = NULL;
	return (0);
}

void fill_imag(t_img *img, int color, int width, int height)
{
	int x, y;
	int radius = (width < height ? width : height) / 2;
	int center_x = width / 2;
	int center_y = height / 2;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if ((x - center_x) * (x - center_x) + (y - center_y) *
					(y - center_y) <= radius * radius)
				my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

int add_image(t_img *window, t_img *img, int height, int width)
{
	img->mlx = window->mlx;
	img->mlx_win = window->mlx_win;
	img->img = mlx_new_image(img->mlx, width, height);
	if (!img->img)
		return (1);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
								  &img->line_length, &img->endian);
	if (!img->addr)
		return (1);
	img->next = NULL;
	img->next = window->next;
	window->next = img;
	return (0);
}

void fill_image(t_img *img, int color, int width, int height)
{
	int x;
	int y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

int expose_hook(void *param)
{
	t_img	*window;
	t_img	*img;
	int		color;

	window = (t_img *)param;
	color = 0x00407055;
	fill_image(window, color, 800, 800);
	mlx_put_image_to_window(window->mlx, window->mlx_win, window->img, 0, 0);
	img = window->next;
	while (img)
	{
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 300, 200);
		img = img->next;
	}
	return 0;
}

void draw_julia(t_img *img, int width, int height)
{
	int x, y;
	int max_iter = 200;
	double new_re, new_im, old_re, old_im;
	double zoom = 1;
	double move_x = 0;
	double move_y = 0;
	double pr, pi;
	int background_color = 0x00407055;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			pr = 1.5 * (x - width / 2) / (0.5 * zoom * width) + move_x;
			pi = (y - height / 2) / (0.5 * zoom * height) + move_y;
			new_re = new_im = old_re = old_im = 0;
			int i = 0;
			while (i < max_iter)
			{
				old_re = new_re;
				old_im = new_im;
				new_re = old_re * old_re - old_im * old_im + pr;
				new_im = 2 * old_re * old_im + pi;
				if (hypot(new_re, new_im) > 2)
					break;
				i++;
			}
			if (i == max_iter)
				my_mlx_pixel_put(img, x, y, background_color);
			else
				my_mlx_pixel_put(img, x, y, i * 256 / max_iter);
			x++;
		}
		y++;
	}
}

void resize_window(t_img *win, int width, int height)
{
	// Destroy the current win and image
	mlx_destroy_window(win->mlx, win->mlx_win);
	mlx_destroy_image(win->mlx, win->img);

	// Create a new win with the new dimensions
	win->mlx_win = mlx_new_window(win->mlx, width, height, "Fractol");
	if (!win->mlx_win)
		exit(1);
	win->img = mlx_new_image(win->mlx, width, height);
	if (!win->img)
		exit(1);
	win->addr = mlx_get_data_addr(win->img, &win->bits_per_pixel,
									 &win->line_length, &win->endian);
	if (!win->addr)
		exit(1);
}

int	key_handler(int keycode, t_img *win)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(win->mlx, win->mlx_win);
		exit(0);
	}
	else if (keycode == 114) // 'R' key for resizing
		resize_window(win, 1024, 768); // Resize to 1024x768
	ft_printf("Keycode: %d\n", keycode);
	return (0);
}

int main(void)
{
	t_img window;
	t_img img;

	if (setup_window(&window, 800, 800))
		return (ft_putendl_fd("Error setting up window", 2), 1);
	if (add_image(&window, &img, 200, 200))
		return (ft_putendl_fd("Error setting up img", 2), 1);
	// fill_imag(&img, 0x00ff7055, 200, 200);
	draw_julia(&img, 200, 200);
	mlx_hook(window.mlx_win, 2, 1L<<0, key_handler, &window);
	mlx_expose_hook(window.mlx_win, expose_hook, &window);
	mlx_loop(window.mlx);
}