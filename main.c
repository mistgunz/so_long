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
#include <stdio.h>
#include <math.h>
#include "ft_itoa.c"

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

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	close(int keycode, t_vars *vars)
{	
	printf("%d\n", keycode);
	if(keycode == 65307)
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}
int mouse(int button, int x, int y, t_vars *vars)
{
	printf("%d\n", button);
	printf("%d\n", x);
	printf("%d\n", y);
	return (0);
}

void draw_circle(int x, int y , int r, t_data *data )
{
	int ang = 0;
	int step = 1;
	while (ang < 360)
	{
		my_mlx_pixel_put(data, x + r * cos(ang * M_PI / 180), y + r * sin(ang * M_PI / 180), RED);
		ang += step;
	}

}
void draw_line(int x1, int y1, int x2, int y2, t_data *data)
{


	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = x1 < x2 ? 1 : -1;
	int sy = y1 < y2 ? 1 : -1;
	int err = dx - dy;
	while (1)
	{
		my_mlx_pixel_put(data, x1, y1, RED);
		if (x1 == x2 && y1 == y2)
			break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, t_data *data)
{
	draw_line(x1, y1, x2, y2, data);
	draw_line(x2, y2, x3, y3, data);
	draw_line(x3, y3, x1, y1, data);
}

void draw_hexagone(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, t_data *data)
{
	draw_line(x1, y1, x2, y2, data);
	draw_line(x2, y2, x3, y3, data);
	draw_line(x3, y3, x4, y4, data);
	draw_line(x4, y4, x1, y1, data);
}


int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int add_shade(float dist, int color)
{
	int r, g, b;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = r * dist ;
	g = g * dist ;
	b = b * dist ;
	return (create_trgb(0, r, g, b));
}



void fill_win(t_data *data)
{	
	int x,y,i,j;

	i = 255;
	y = 0;
	while(y < HEIGHT)
	{
		x = 0;
		while(x < WIDTH)
		{
			my_mlx_pixel_put(data, x, y,add_shade( 1,create_trgb(1, 0,250, 0)));
			x++;
		}
		y++;
		//if (y % 10 == 0)
		//	i++;
	}
}





int main(void)
{
	
	t_data	img 	;
	t_vars 	vars 	;

	
	
	
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "mlx window");
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	//mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	//draw_circle(WIDTH / 2, HEIGHT / 2, 100, &img);
	//draw_line(WIDTH / 2, HEIGHT / 2, WIDTH / 2 + 100, HEIGHT / 2, &img);
	//draw_hexagone(0, 0, 0 , HEIGHT / 2, WIDTH / 2 + 200, HEIGHT / 2, WIDTH / 2 + 300, HEIGHT / 2, &img);
	//draw_triangle(0, 0, 200, 200, 0, 100, &img);
	fill_win(&img);
	printf("%X\n", create_trgb(0, 255, 0, 0));	
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, &close, &vars);
	mlx_mouse_hook(vars.win,&mouse, &vars);
	mlx_loop(vars.mlx);
	
	
	
}



