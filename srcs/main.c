/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 10:38:48 by miouali           #+#    #+#             */
/*   Updated: 2026/02/15 14:56:23 by miouali          ###   ########.fr       */
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
	f->dx = (f->max_real_window - f->min_real_window) / WIN_WIDTH;
	f->dy = (f->max_imaginary_window - f->min_imaginary_window) / WIN_HEIGHT;
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

int	main(int argc, char **argv)
{
	t_fractol	f;

	parse_args(argc, argv, &f);
	if (!init_fractol(&f))
		return (1);
	init_palette(&f);
	render_fractal(&f);
	mlx_put_image_to_window(f.mlx, f.win, f.img, 0, 0);
	mlx_key_hook(f.win, key_handler, &f);
	mlx_hook(f.win, 17, 0, close_handler, &f);
	mlx_hook(f.win, 12, 0, handle_expose, &f);
	mlx_mouse_hook(f.win, mouse_handler, &f);
	mlx_loop(f.mlx);
	return (0);
}
