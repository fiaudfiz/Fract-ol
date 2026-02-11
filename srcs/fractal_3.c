/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   celtic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 09:23:20 by miouali           #+#    #+#             */
/*   Updated: 2026/02/03 09:39:37 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	celtic(t_fractol *f)
{
	f->c_real = f->pixel_real;
	f->c_imaginary = f->pixel_imaginary;
	f->z_real = 0;
	f->z_imaginary = 0;
}

void	celtic_iteration(t_fractol *f)
{
	f->period = 20;
	f->old_imaginary = 0;
	f->old_real = 0;
	while (f ->z_real * f ->z_real + f ->z_imaginary
		* f ->z_imaginary < 4 && f->iteration < f->max_iteration)
	{
		f->temp_real = fabs(f->z_real * f->z_real - f->z_imaginary
				* f->z_imaginary) + f->c_real;
		f->z_imaginary = 2 * f->z_real * f->z_imaginary + f->c_imaginary;
		f->z_real = f->temp_real;
		f->iteration++;
		if (f-> z_real == f->old_real && f->z_imaginary == f->old_imaginary)
		{
			f->iteration = f-> max_iteration;
			break ;
		}
		f->period++;
		if (f->period > 20)
		{
			f->period = 0;
			f->old_real = f-> z_real;
			f->old_imaginary = f-> z_imaginary;
		}
	}
}
