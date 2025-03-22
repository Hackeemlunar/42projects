/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:21:55 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/16 18:28:34 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_menu(void)
{
	char	*message;

	message = "Scroll down to zoom in and scroll up to zoom out\n"
		"Left click to change colors\n"
		"Use Arrow keys to move the image left, right, up and down respectively"
		"\nClick '-' to reduce iteration\n"
		"press '+' to increase the iteration\n"
		"Press 'r' to restore window state\n"
		"Press ESC to close the window\n";
	ft_putstr_fd(message, 1);
}

int	parse_args(int argc, char **argv, t_window *window)
{
	if (argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))
		window->type = MANDELBROT;
	else if (argc == 2 && !ft_strncmp(argv[1], "burning_ship", 13))
		window->type = BURNING_SHIP;
	else if (argc == 4 && !ft_strncmp(argv[1], "julia", 5))
	{
		window->type = JULIA;
		window->fractol_re = atof(argv[2]);
		window->fractol_im = atof(argv[3]);
	}
	else
	{
		ft_putstr_fd("Usage: ./fractol mandelbrot\n", 2);
		ft_putstr_fd("Usage: ./fractol burning_ship\n", 2);
		ft_putstr_fd("Usage: ./fractol julia arg1 arg2\n", 2);
		return (1);
	}
	print_menu();
	return (0);
}

void	setup_mlx(t_window *window)
{
	window->mlx = mlx_init();
	window->win = mlx_new_window(window->mlx, WIN_WIDTH, WIN_HEIGHT, "Fractol");
	window->img = mlx_new_image(window->mlx, WIN_WIDTH, WIN_HEIGHT);
	window->addr = mlx_get_data_addr(window->img, &window->bits_ppx,
			&window->line_len, &window->endian);
	window->width = WIN_WIDTH;
	window->height = WIN_HEIGHT;
	window->zoom = 1;
	window->ofs_x = 0;
	window->ofs_y = 0;
	window->max_iter = 100;
	window->color_sft = 0;
	window->bg_color = 0x0000F005;
}

int	main(int argc, char **argv)
{
	t_window	window;

	if (parse_args(argc, argv, &window) != 0)
		return (1);
	setup_mlx(&window);
	event_handler(&window);
	mlx_loop(window.mlx);
	return (0);
}
