#ifndef FRACTOL_H
# define FRACTOL_H
# include <math.h>
# include "mlx.h"
# include "libft/libft.h"
# define WIN_WIDTH 800
# define WIN_HEIGHT 800

typedef struct s_window
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	double		offset_x;
	double		offset_y;
	double		julia_re;
	double		julia_im;
	double		zoom;
	int			bits_ppx;
	int			line_len;
	int			endian;
	int			width;
	int			height;
	int			max_iter;
	int			color_sft;
	int			type;
	int			bg_color;
}			t_window;

enum e_fract_type
{
	MANDELBROT,
	JULIA
};

// Handles events such as key presses and mouse movements
void		event_handler(t_window *window);

// Puts a pixel of a specified color at (x, y) in the window
void		my_mlx_pixel_put(t_window *window, int x, int y, int color);

// Destroys the window and frees associated resources
void		destroy_window(t_window *window);

// Draws the fractal on the window
void		draw_fractal(t_window *window);

// Fills the window background with a specified color
void		fill_background(t_window *window, int color);

// Calculates the color for a given iteration count
int			get_color(int iter, int max_iter, t_window *window);

// Updates the color shift value for the fractal
void		update_color_shift(t_window *window);

#endif