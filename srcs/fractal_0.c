/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:14:56 by miouali           #+#    #+#             */
/*   Updated: 2026/02/03 09:39:45 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot(t_fractol *f)
{
	f->c_real = f->pixel_real;
	f->c_imaginary = f->pixel_imaginary;
	f->z_real = 0;
	f->z_imaginary = 0;
	f->equation = (f->pixel_real - 0.25) * (f->pixel_real - 0.25)
		+ f->pixel_imaginary * f->pixel_imaginary;
}

void	julia(t_fractol *f)
{
	f->c_real = f->julia_real_pixel;
	f->c_imaginary = f->julia_imaginary_pixel;
	f->z_real = f->pixel_real;
	f->z_imaginary = f->pixel_imaginary;
}

int	fractal(t_fractol *f, int **pixel_ptr)
{
	if (f->type_of_fractal == 1)
	{
		mandelbrot(f);
		if (f->equation * (f->equation + (f->pixel_real - 0.25))
			< 0.25 * f->pixel_imaginary * f->pixel_imaginary
			|| (f->pixel_real + 1) * (f->pixel_real + 1)
			+ f->pixel_imaginary * f->pixel_imaginary < 0.0625)
		{
			**pixel_ptr = 0x000000;
			(*pixel_ptr)++;
			f -> pixel_x++;
			return (1);
		}
	}
	else if (f->type_of_fractal == 2)
		julia(f);
	else if (f->type_of_fractal == 3)
		burning_ship(f);
	else if (f-> type_of_fractal == 4)
		tricorn(f);
	else if (f->type_of_fractal == 5)
		celtic(f);
	return (0);
}
