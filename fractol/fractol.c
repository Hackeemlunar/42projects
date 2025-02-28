#include "mlx_mac/mlx.h"

typedef struct  s_data {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    void    *mlx;
    void    *mlx_win;
}   t_data;

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    fill_image(t_data *data, int color)
{
    int x;
    int y;

    y = 0;
    while (y < 800)
    {
        x = 0;
        while (x < 800)
        {
            my_mlx_pixel_put(data, x, y, color);
            x++;
        }
        y++;
    }
}

int expose_hook(t_data *data) {
    int color = 0x00590929;
    fill_image(data, color);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
    return 0;
}

int main(void)
{
    t_data  data;

    data.mlx = mlx_init();
    data.mlx_win = mlx_new_window(data.mlx, 800, 800, "Fractol");
    data.img = mlx_new_image(data.mlx, 800, 800);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

    mlx_expose_hook(data.mlx_win, expose_hook, &data);
    expose_hook(&data);
    mlx_loop(data.mlx);
}