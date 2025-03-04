#ifndef FRACTOL_H
# define FRACTOL_H
# include <math.h>
# include "mlx.h"
# include "libft/libft.h"
# define WIN_WIDTH 800
# define WIN_HEIGHT 800
typedef struct s_window
{
	void    *mlx;
	void    *win;
	void    *img;
	char    *addr;
	int     bits_ppx;
	int     line_len;
	int     endian;
	int     width;
	int     height;
	double  zoom;
	double  offset_x;
	double  offset_y;
	int     max_iter;
	int     color_sft;
	int     type;
	double  julia_re;
	double  julia_im;
	int     bg_color;
} t_window;

enum e_fract_type
{
	MANDELBROT,
	JULIA
};

void		event_handler(t_window *window);
void		my_mlx_pixel_put(t_window *window, int x, int y, int color);
int			destroy_window(t_window *window);
void		draw_fractal(t_window *window);
void		fill_background(t_window *window, int color);
int			get_color(int iter, int max_iter, t_window *window);
void		update_color_shift(t_window *window);
int			hsv_to_rgb(double h, double s, double v);
#endif