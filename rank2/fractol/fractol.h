/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:21:20 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/22 20:17:06 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIN_WIDTH 800
# define WIN_HEIGHT 800
# include <math.h>
# include "../libft/libft.h"
# include "../mlx_mac/mlx.h"

typedef enum e_fract_type
{
	MANDELBROT,
	JULIA,
	BURNING_SHIP
}	t_fract_type;

typedef struct s_window
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	double			zoom;
	double			ofs_x;
	double			color_sft;
	double			fractol_re;
	double			fractol_im;
	double			ofs_y;
	t_fract_type	type;
	int				height;
	int				bits_ppx;
	int				line_len;
	int				endian;
	int				width;
	int				max_iter;
	int				bg_color;
}	t_window;

/* utils.c*/
void	my_mlx_pixel_put(t_window *window, int x, int y, int color);
int		destroy_window(t_window *window);
int		get_color(int iter, t_window *window);
void	event_handler(t_window *window);
void	draw_fractal(t_window *window);
/*------   Bonus	------------*/
void	render_burning_ship(t_window *window);
#endif