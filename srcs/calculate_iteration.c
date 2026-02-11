/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_iteration.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:14:17 by miouali           #+#    #+#             */
/*   Updated: 2026/02/03 09:39:30 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	calculate_iteration_simple(t_fractol *f)
{
	f->period = 20;
	f->old_imaginary = 0;
	f->old_real = 0;
	while (f ->z_real * f ->z_real + f ->z_imaginary
		* f ->z_imaginary < 4 && f->iteration < f->max_iteration)
	{
		f->temp_real = ((f ->z_real * f ->z_real)
				- (f ->z_imaginary * f ->z_imaginary)) + f ->c_real;
		f -> z_imaginary = 2 * f ->z_imaginary * f ->z_real + f ->c_imaginary;
		f ->z_real = f->temp_real;
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

void	calculate_iteration(t_fractol *f)
{
	if (f->type_of_fractal == 3)
		burning_ship_iteration(f);
	else if (f-> type_of_fractal == 4)
		tricorn_iteration(f);
	else if (f-> type_of_fractal == 5)
		celtic_iteration(f);
	else
		calculate_iteration_simple(f);
}
