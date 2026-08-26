/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:13:41 by miouali           #+#    #+#             */
/*   Updated: 2026/03/03 10:57:53 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init(t_fractol *f)
{
	f ->pixel_y = 0;
	f ->pixel_x = 0;
	f -> real_factor = (f->max_real_window - f->min_real_window) / WIN_WIDTH;
	f -> imaginary_factor = (f->min_imaginary_window - f->max_imaginary_window)
		/ WIN_HEIGHT;
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
