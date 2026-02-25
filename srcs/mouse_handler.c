/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:26:02 by miouali           #+#    #+#             */
/*   Updated: 2026/02/03 09:40:06 by miouali          ###   ########.fr       */
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

int	mouse_handler(int button, int x, int y, t_fractol *f)
{
	double	mouse_re;
	double	mouse_im;
	double	zoom_factor;

	zoom_factor = 0;
	mouse_re = (double)x
		* ((f->max_real_window - f->min_real_window) / WIN_WIDTH)
		+ f->min_real_window;
	mouse_im = (double)y
		* ((f-> min_imaginary_window - f-> max_imaginary_window) / WIN_HEIGHT)
		+ f-> max_imaginary_window;
	if (button != 4 && button != 5)
		return (0);
	if (button == 4)
		zoom_factor = 0.9;
	else if (button == 5)
		zoom_factor = 1.1;
	apply_zoom(f, mouse_re, mouse_im, zoom_factor);
	render_fractal_simd(f);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	return (0);
}
