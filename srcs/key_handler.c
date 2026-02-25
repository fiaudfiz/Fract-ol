/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:21:54 by miouali           #+#    #+#             */
/*   Updated: 2026/02/15 15:00:55 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_handler(t_fractol *f)
{
	mlx_destroy_image(f ->mlx, f->img);
	mlx_destroy_window(f-> mlx, f->win);
	mlx_destroy_display(f-> mlx);
	free (f-> mlx);
	exit(0);
	return (0);
}

void	move_fractal(int key, t_fractol *f)
{
	if (key == 65361)
	{
		f->min_real_window -= f->offset;
		f->max_real_window -= f->offset;
	}
	else if (key == 65362)
	{
		f->min_imaginary_window += f->offset;
		f->max_imaginary_window += f->offset;
	}
	else if (key == 65363)
	{
		f->min_real_window += f->offset;
		f->max_real_window += f->offset;
	}
	else if (key == 65364)
	{
		f->min_imaginary_window -= f->offset;
		f->max_imaginary_window -= f->offset;
	}
}

int	key_handler(int key, t_fractol *f)
{
	f->offset = (f->max_real_window - f-> min_real_window) * 0.05;
	if (key == 65307)
		close_handler(f);
	else if (key >= 65361 && key <= 65364)
		move_fractal(key, f);
	render_fractal_simd(f);
	return (0);
}

int	handle_expose(t_fractol *f)
{
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	return (0);
}
