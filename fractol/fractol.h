#ifndef FRACTOL_H
# define FRACTOL_H
# include "libft/libft.h"

typedef struct	s_idata
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    void    *mlx;
    void    *mlx_win;
}   t_idata;

#endif