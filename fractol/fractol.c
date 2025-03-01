#include "mlx.h"
#include "fractol.h"


void    my_mlx_pixel_put(t_idata *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    fill_image(t_idata *data, int color, int width, int height)
{
    int x;
    int y;

    y = 0;
    while (y < height - 1)
    {
        x = 0;
        while (x < width - 1)
        {
            my_mlx_pixel_put(data, x, y, color);
            x++;
        }
        y++;
    }
}

int expose_hook(t_idata *data, int width, int height) {
    int color = 0x00000055;
    fill_image(data, color, width, height);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
    return 0;
}

int main(void)
{
    t_idata  data;

    data.mlx = mlx_init();
    data.mlx_win = mlx_new_window(data.mlx, 800, 800, "Fractol");
    data.img = mlx_new_image(data.mlx, 800, 800);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

    mlx_expose_hook(data.mlx_win, expose_hook, &data);
    expose_hook(&data, 800, 800); // Initial draw.
    mlx_loop(data.mlx);
}