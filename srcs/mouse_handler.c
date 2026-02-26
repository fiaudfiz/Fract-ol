/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:26:02 by miouali           #+#    #+#             */
/*   Updated: 2026/02/26 16:34:09 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	apply_zoom(t_fractol *f, double mouse_re,
		double mouse_im, double zoom_factor)
{
	f->min_real_window = mouse_re
		+ (f->min_real_window - mouse_re) * zoom_factor;
	f->max_real_window = mouse_re
		+ (f->max_real_window - mouse_re) * zoom_factor;
	f->min_imaginary_window = mouse_im
		+ (f->min_imaginary_window - mouse_im) * zoom_factor;
	f->max_imaginary_window = mouse_im
		+ (f->max_imaginary_window - mouse_im) * zoom_factor;
}

int	mouse_release(int button, int x, int y, t_fractol *f)
{
	(void)button;
	(void)x;
	(void)y;
	f->mouse_pressed = 0;
	return (0);
}

static void	handle_zoom(int button, int x, int y, t_fractol *f)
{
	double		mouse_re;
	double		mouse_im;
	double		zoom_factor;

	zoom_factor = 0;
	mouse_re = (double)x * ((f->max_real_window - f->min_real_window)
			/ WIN_WIDTH) + f->min_real_window;
	mouse_im = (double)y * ((f->min_imaginary_window - f->max_imaginary_window)
			/ WIN_HEIGHT) + f->max_imaginary_window;
	if (button == 4)
		zoom_factor = 0.9;
	else if (button == 5)
		zoom_factor = 1.1;
	apply_zoom(f, mouse_re, mouse_im, zoom_factor);
	render_fractal_simd(f);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}

int	mouse_handler(int button, int x, int y, t_fractol *f)
{
	if (button == 1)
	{
		f->mouse_pressed = 1;
		f->last_x = x;
		f->last_y = y;
		return (0);
	}
	if (button == 4 || button == 5)
		handle_zoom(button, x, y, f);
	return (0);
}

int	motion_handler(int x, int y, t_fractol *f)
{
	double	dx;
	double	dy;

	if (f->mouse_pressed == 0)
		return (0);
	dx = (x - f->last_x) * f->real_factor;
	dy = (y - f->last_y) * f->imaginary_factor;
	f->min_real_window -= dx;
	f->max_real_window -= dx;
	f->max_imaginary_window -= dy;
	f->min_imaginary_window -= dy;
	f->last_x = x;
	f->last_y = y;
	render_fractal_simd(f);
	return (0);
}
