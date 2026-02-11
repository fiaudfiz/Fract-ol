/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fractal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:13:17 by miouali           #+#    #+#             */
/*   Updated: 2026/02/03 10:39:21 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_color(t_fractol *f, int *pixel_ptr)
{
	if (f->iteration == f->max_iteration)
		*pixel_ptr = 0x000000;
	else
		*pixel_ptr = f->palette[f->iteration % MAX_ITER];
}

void	render_fractal(t_fractol *f)
{
	int	*pixel_ptr;

	pixel_ptr = (int *)f->addr;
	init(f);
	while (f ->pixel_y < WIN_HEIGHT)
	{
		f ->pixel_x = 0;
		f ->pixel_imaginary = f->max_imaginary_window
			+ (double)f ->pixel_y * f->imaginary_factor;
		while (f ->pixel_x < WIN_WIDTH)
		{
			f ->pixel_real = f->min_real_window
				+ (double)f ->pixel_x * f->real_factor;
			f -> iteration = 0;
			if (!fractal(f, &pixel_ptr))
			{
				calculate_iteration(f);
				put_color(f, pixel_ptr);
				pixel_ptr++;
				f->pixel_x++;
			}
		}
		f->pixel_y++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
