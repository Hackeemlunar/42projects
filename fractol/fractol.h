#ifndef FRACTOL_H
# define FRACTOL_H
# include "libft/libft.h"

typedef struct	s_img
{
    struct s_img    *next;
    void            *img;
    void            *mlx;
    void            *mlx_win;
    char            *addr;
    int             bits_per_pixel;
    int             line_length;
    int             endian;
}   t_img;

#endif