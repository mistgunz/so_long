/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnait-el <rnait-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 07:52:37 by rnait-el          #+#    #+#             */
/*   Updated: 2022/07/02 07:52:38 by rnait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <mlx.h>

#define WIDTH 1920
#define HEIGHT 1080
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void drawline(t_data *data, int x1, int y1, int x2, int y2)
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	sx = x1 < x2 ? 1 : -1;
	sy = y1 < y2 ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		my_mlx_pixel_put(data, x1, y1, GREEN);
		if (x1 == x2 && y1 == y2)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err = err - dy;
			x1 = x1 + sx;
		}
		if (e2 < dx)
		{
			err = err + dx;
			y1 = y1 + sy;
		}
	}
}
int main(void)
{
	void	*mlx 	;
	void	*mlx_win 	;	
	t_data	img 	;
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx , 1920, 1080, "mlx window");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	drawline(&img, 1000, 1000, 1920, 1080);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	mlx_loop(mlx);
	
}



