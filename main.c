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

typedef struct ghost 
{
	void *imgg;
	char * path;
	int widht;
	int hight;
	int x,y;/* data */
} ghost;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	escq(int keycode, t_vars *vars)
{	
	if (keycode == 119)
		
	printf("%d\n", keycode);
	if(keycode == 65307)
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}
int close2(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int mouse(int button, int x, int y, ghost *g)
{
	if (button == 1)
	{
		g->x = x;
		g->y = y;
	}
	

	printf("%d\n", button);
	printf("%d\n", x);
	printf("%d\n", y);
	return (0);
}




int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}



int main(void)
{
	
	t_data	img 	;
	t_vars 	vars 	;
	ghost 	ghost 	;

	ghost.path = "./ghost_down1.xpm";
	ghost.x = WIDTH / 2;
	ghost.y = HEIGHT / 2;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "mlx window");
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//fill_win(&img);
	
	//mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	//draw_circle(WIDTH / 2, HEIGHT / 2, 100, &img);
	//draw_line(WIDTH / 2, HEIGHT / 2, WIDTH / 2 + 100, HEIGHT / 2, &img);
	//draw_hexagone(0, 0, 0 , HEIGHT / 2, WIDTH / 2 + 200, HEIGHT / 2, WIDTH / 2 + 300, HEIGHT / 2, &img);
	//draw_triangle(0, 0, 200, 200, 0, 100, &img);
	ghost.imgg = mlx_xpm_file_to_image(vars.mlx, ghost.path, &ghost.widht, &ghost.hight);
	
	mlx_put_image_to_window(vars.mlx, vars.win, ghost.imgg, ghost.x, ghost.y);
	mlx_key_hook(vars.win, &escq, &vars);
	mlx_mouse_hook(vars.win,&mouse, &vars);
	mlx_hook(vars.win, 17, 3, &close2, &vars);
	mlx_loop(vars.mlx);	
}