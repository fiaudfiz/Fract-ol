/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:39:47 by miouali           #+#    #+#             */
/*   Updated: 2026/02/26 16:39:56 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_fractol *f, int x, int y, int color)
{
	char	*dst;

	dst = f->addr + (y * f->line_length + x * (f->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	init_fractol(t_fractol *f)
{
	f->min_real_window = -2.0;
	f->max_real_window = 2.0;
	f->min_imaginary_window = -2.0;
	f->max_imaginary_window = 2.0;
	f->max_iteration = MAX_ITER;
	f->init_max_re = f->max_real_window;
	f->init_min_re = f->min_real_window;
	f->init_max_im = f->max_imaginary_window;
	f->init_min_im = f->min_imaginary_window;
	f->color_offset = 0;
	f->mouse_pressed = 0;
	f->mlx = mlx_init();
	if (!f->mlx)
		return (0);
	f->win = mlx_new_window(f->mlx, WIN_WIDTH, WIN_HEIGHT, "Fract-ol");
	if (!f->win)
		return (0);
	f->img = mlx_new_image(f->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!f->img)
		return (0);
	f->addr = mlx_get_data_addr(f->img, &f->bits_per_pixel,
			&f->line_length, &f->endian);
	return (1);
}

int	main(int ac, char **av)
{
	t_fractol	f;

	parse_args(ac, av, &f);
	if (!init_fractol(&f))
		return (1);
	init_palette(&f);
	render_fractal_simd(&f);
	mlx_put_image_to_window(f.mlx, f.win, f.img, 0, 0);
	mlx_hook(f.win, 2, 1L << 0, key_handler, &f);
	mlx_hook(f.win, 17, 0, close_handler, &f);
	mlx_hook(f.win, 12, 0, handle_expose, &f);
	mlx_hook(f.win, 4, 1L << 2, mouse_handler, &f);
	mlx_hook(f.win, 5, 1L << 3, mouse_release, &f);
	mlx_hook(f.win, 6, 1L << 6, motion_handler, &f);
	mlx_loop(f.mlx);
	return (0);
}
