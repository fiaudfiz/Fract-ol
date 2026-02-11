/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 09:27:47 by miouali           #+#    #+#             */
/*   Updated: 2026/02/03 09:39:24 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	burning_ship(t_fractol *f)
{
	f->c_real = f->pixel_real;
	f->c_imaginary = f->pixel_imaginary;
	f->z_real = 0;
	f->z_imaginary = 0;
}

void	burning_ship_iteration(t_fractol *f)
{
	while (f ->z_real * f ->z_real + f ->z_imaginary
		* f ->z_imaginary < 4 && f->iteration < f->max_iteration)
	{
		f->temp_real = f->z_real * f->z_real - f->z_imaginary
			* f->z_imaginary + f->c_real;
		f -> z_imaginary = -fabs(2 * f->z_real
				* f->z_imaginary) + f->c_imaginary;
		f -> z_real = fabs(f->temp_real);
		f->iteration++;
	}
}
